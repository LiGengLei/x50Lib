/*
* License:The MIT License (MIT)
*
* Copyright (c) 2013,2014 Yanyu Su
*
* Permission is hereby granted, free of charge, to any person obTining a copy
* of this software and associated documenTtion files (the "Software"), to deal
* in the Software without restriction, including without limiTtion the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or subsTntial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTBILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
* THE SOFTWARE.
*/
#pragma once
#include <xc/core/core.h>
#include <vector>
#include <list>
#include <boost/scoped_ptr.hpp>
#include <boost/asio.hpp>
#include <boost/lambda/bind.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits.hpp>

namespace xc
{
namespace Dev
{
////////////////////////////////////////////////////////////////////////////////
// IConvertibleTo                                                             //
////////////////////////////////////////////////////////////////////////////////
template<typename TargetT>
class IConvertibleTo
{
public:
  typedef TargetT TargetType;

  IConvertibleTo() {  }

  IConvertibleTo ( IConvertibleTo _in v ) {  }

  virtual ~IConvertibleTo() {  }

  virtual operator TargetType _ret () const = 0;
};

////////////////////////////////////////////////////////////////////////////////
// Array                                                                      //
////////////////////////////////////////////////////////////////////////////////
template<typename T>
class Array : public std::vector< T >
{
public:
  static const int IS_DERIVED_FROM_XC_DEV_ARRAY = 1;

  Array() : std::vector< T >() {  }

  Array ( size_t _in s ) : std::vector< T > ( s ) {  }

  Array ( Array _in value ) : std::vector< T > ( value ) {  }

  virtual ~Array() {  }

  void PushBack ( Array _in value )
  {
    std::vector< T >::reserve ( std::vector< T >::size() + value.size () );
    std::vector< T >::insert ( std::vector<T>::end(), value.begin(), value.end() );
  }

  void PushBack ( T _in value )
  {
    std::vector< T >::push_back ( value );
  }

  inline String _ret ToString() const
  {
    String ret;
    ret.clear();
    ret.reserve ( std::vector< T >::size() );

    for ( size_t i = 0; i < std::vector< T >::size(); ++i )
    {
      if ( isprint ( std::vector< T >::at ( i ) ) )
      {
        ret.push_back ( std::vector< T >::at ( i ) );
      }
      else
        ret.push_back ( ' ' );
    }

    return ret;
  }

  inline String _ret ToDetail() const
  {
    String ret;
    ret.clear();
    ret.reserve ( std::vector< T >::size() );

    bool lastPrint = false;
    for ( size_t i = 0; i < std::vector< T >::size(); ++i )
    {
      if ( isprint ( std::vector< T >::at ( i ) ) )
      {
        if ( lastPrint )
          ret.append ( "%c", std::vector< T >:: at ( i ) );
        else
          ret.append ( " %2c", std::vector< T >::at ( i ) );

        lastPrint = true;
      }
      else
      {
        ret.append ( " %02x", std::vector< T >::at ( i ) );
        lastPrint = false;
      }
    }

    return ret;
  }
};

////////////////////////////////////////////////////////////////////////////////
// Keyword                                                                    //
////////////////////////////////////////////////////////////////////////////////
template<class T0>
class Keyword : public IConvertibleTo< Array<T0> >
{
public:
  Keyword ( CStrPtr _in name, T0 _in value )
    : mName ( name )
    , value_ ( value )  {  }

  Keyword ( Keyword _in value )
    : mName ( value.mName )
    , value_ ( value.value_ )  {  }

  virtual ~Keyword()  {  }

  String _rd name() const
  {
    return mName;
  }

  Array<T0> _rd value() const
  {
    return value_;
  }

  operator Array<T0> _ret() const
  {
    return value_;
  }

protected:
  String     mName;
  Array<T0>  value_;

  Keyword()
    : mName ( "" )
    , value_ ( T0() )  {  }

protected:
  static void add ( CStrPtr _in name, T0 _in value )
  {
    typename std::list< Keyword<T0> >::iterator itr = REGISTER.begin();

    for ( ; itr != REGISTER.end(); ++itr )
    {
      if ( itr->Value() == value )
        return ;

      if ( itr->Value() > value )
        break;
    }

    typename std::list< Keyword <T0> >::iterator ret =
      REGISTER.insert ( itr, Keyword<T0> ( name, value ) );
  }

  static std::list<Keyword <T0> > REGISTER;
};

////////////////////////////////////////////////////////////////////////////////
// ConvertibleData                                                            //
////////////////////////////////////////////////////////////////////////////////
template<typename SourceT, typename  TargetT>
class ConvertibleData : public xc::Dev::IConvertibleTo<TargetT>
{
public:
  typedef SourceT SourceType;
  typedef TargetT TargetType;

  ConvertibleData()
    : mData()  {  }

  ConvertibleData ( ConvertibleData _in v )
    : mData ( v.mData )  {  }

  ConvertibleData ( SourceType _in v )
    : mData ( v )  {  }

  virtual ~ConvertibleData()  {  }

  operator TargetType _ret () const
  {
    return mConvertor ( mData );
  }

  operator SourceType _rd () const
  {
    return mData;
  }

  SourceType _rd operator = ( SourceType _in v )
  {
    return mData = v;
  }

protected:
  SourceType mData;

  virtual TargetType _ret ToTarget() const = 0;
};

////////////////////////////////////////////////////////////////////////////////
// OpenConnector                                                              //
////////////////////////////////////////////////////////////////////////////////
template<typename T0>
class OpenConnector
{
public:
  const static long             DEFAULT_WAITTIME = 1;

  OpenConnector()
    : mIOService()
    , mSocket ( mIOService )
    , mDeadline ( mIOService )
  {
    mDeadline.expires_at ( boost::posix_time::pos_infin );
    _CheckDeadline();
  }

  virtual ~OpenConnector()  {  }

  bool _ret Connect ( xc::String _in host, xc::String _in port,
                      boost::posix_time::time_duration _in timeout
                      = boost::posix_time::seconds ( DEFAULT_WAITTIME ) )
  {
    XC_DEBUG ( "%s. ",  __FUNCTION__ );

    boost::asio::ip::tcp::resolver::query query ( host, port );
    boost::asio::ip::tcp::resolver::iterator iter =
      boost::asio::ip::tcp::resolver ( mIOService ).resolve ( query );

    mDeadline.expires_from_now ( timeout );

    for ( ; iter != boost::asio::ip::tcp::resolver::iterator(); ++iter )
    {
      mSocket.close();

      boost::system::error_code ec = boost::asio::error::would_block;

      mSocket.async_connect ( iter->endpoint(), boost::lambda::var ( ec ) = boost::lambda::_1 );

      do mIOService.run_one();
      while ( ec == boost::asio::error::would_block );

      if ( !ec && mSocket.is_open() )
      {
        return true;
      }
      else
      {
        XC_DEBUG ( "%s failed in trying making connection. "
                   "EC = %s::%s ",
                   __FUNCTION__,
                   ec.category().name(),
                   ec.message().c_str() );
      }
    }

    XC_DEBUG ( "%s failed to connect to %s:%s. ",
               __FUNCTION__,
               host.c_str(),
               port.c_str() );

    return false;
  }

  bool _ret Close()
  {
    XC_DEBUG ( "%s. ", __FUNCTION__ );

    bool ret = true;
    boost::system::error_code ec;
    mSocket.shutdown ( boost::asio::ip::tcp::socket::shutdown_both, ec );
    if ( ec )
    {
      XC_DEBUG ( "%s calling shutdown failed. "
                 "EC = %s::%s ",
                 __FUNCTION__,
                 ec.category().name(),
                 ec.message().c_str() );
      ret = false;
    }
    //
    mSocket.close ( ec );
    if ( ec )
    {
      XC_DEBUG ( "%s calling close failed. "
                 "EC = %s::%s ",
                 __FUNCTION__,
                 ec.category().name(),
                 ec.message().c_str() );
      ret = false;
    }
    //
    return true;
  }

  bool _ret Shutdown()
  {
    XC_DEBUG ( "%s. ",  __FUNCTION__ );
    bool ret = Close();
    mIOService.stop ();
    return ret;
  }

  boost::system::error_code _ret Send ( Array<T0> _in cmd,
                                        boost::posix_time::time_duration timeout
                                        = boost::posix_time::seconds ( DEFAULT_WAITTIME ) )
  {
    mDeadline.expires_from_now ( timeout );

    boost::system::error_code ec = boost::asio::error::would_block;

    boost::asio::async_write (
      mSocket, boost::asio::buffer ( cmd.data(), cmd.size() ),
      boost::lambda::var ( ec ) = boost::lambda::_1 );

    do mIOService.run_one();
    while ( ec == boost::asio::error::would_block );

    XC_DEBUG ( "%s [%ld bytes] %s ",
               __FUNCTION__,
               cmd.size(),
               cmd.ToDetail().c_str() );

    return ec;
  }

  boost::system::error_code _ret Read ( Array<T0> _out ary,
                                        boost::posix_time::time_duration timeout
                                        = boost::posix_time::seconds ( DEFAULT_WAITTIME ) )
  {
    mDeadline.expires_from_now ( timeout );

    boost::system::error_code ec = boost::asio::error::would_block;
    std::size_t len = 0;
    mSocket.async_read_some ( boost::asio::buffer ( ary ),
                              ( boost::lambda::var ( ec ) = boost::lambda:: _1,
                                boost::lambda::var ( len ) = boost::lambda:: _2 ) );

    do mIOService.run_one();
    while ( ec == boost::asio::error::would_block );

    ary.resize ( len );

    XC_DEBUG ( "%s [%ld bytes] %s ",
               __FUNCTION__,
               len,
               ary.ToDetail().c_str() );

    return ec;
  }

private:
  void _CheckDeadline()
  {
    if ( mDeadline.expires_at() <= boost::asio::deadline_timer::traits_type::now() )
    {
      Close();
      mDeadline.expires_at ( boost::posix_time::pos_infin );
    }
    mDeadline.async_wait ( boost::lambda::bind ( &OpenConnector::_CheckDeadline, this ) );
  }

  boost::asio::io_service       mIOService;
  boost::asio::ip::tcp::socket  mSocket;
  boost::asio::deadline_timer   mDeadline;
};

////////////////////////////////////////////////////////////////////////////////
// Connector                                                                  //
////////////////////////////////////////////////////////////////////////////////
typedef size_t                             OperatorID;
template<typename T>
class Connector : protected OpenConnector <T>
{
public:
  typedef boost::shared_ptr< Connector <T> > Ptr;
  static const OperatorID                    OPERTOR_NULL;// = 0;
  static const OperatorID                    OPERTOR_INIT;// = 1;

  static Ptr _ret MakeInstace()
  {
    return  Ptr ( new Connector() );
  }

  virtual ~Connector()
  {
    XC_DEBUG ( "connector released" );
  }

  bool _ret Connect ( xc::String _in host, xc::String _in port,
                      boost::posix_time::time_duration _in timeout
                      = boost::posix_time::seconds ( OpenConnector <T>::DEFAULT_WAITTIME ) )
  {
    return OpenConnector<T>::Connect ( host, port, timeout );
  }

  bool _ret Close()
  {
    return OpenConnector<T>::Close();
  }

  bool _ret Shutdown()
  {
    return OpenConnector<T>::Shutdown();
  }

  OperatorID _ret GenerateID()
  {
    return ++mIDs;
  }

  OperatorID _ret CurrentOperator() const
  {
    return mCurrentOperator;
  }

  boost::system::error_code _ret Send ( OperatorID _in id, Array<T> _in cmd )
  {
    EnsureLock ( id );
    return OpenConnector<T>::Send ( cmd );
  }

  virtual boost::system::error_code _ret Read ( OperatorID _in id, Array<T> _out ary )
  {
    EnsureLock ( id );
    return OpenConnector<T>::Read ( ary );
  }

  bool TryLock ( OperatorID _in id )
  {
    if ( OPERTOR_NULL != CurrentOperator() && id != CurrentOperator() )
    {
      return false;
    }
    _SetCurrentOperator ( id );
    return true;
  }

  void Lock ( OperatorID _in id )
  {
    while ( OPERTOR_NULL != CurrentOperator() && id != CurrentOperator() )
    {
      sleep ( 1 );
      XC_INFO ( "%s", __FUNCTION__ );
    }
    _SetCurrentOperator ( id );
  }

  void EnsureLock ( OperatorID _in id ) const
  {
    while ( id != CurrentOperator() )
    {
      sleep ( 1 );
      XC_INFO ( "%s", __FUNCTION__ );
    }
    return;
  }

  void Unlock ( OperatorID _in id )
  {
    if ( id == CurrentOperator() )
    {
      _SetCurrentOperator ( OPERTOR_NULL );
    }
    return;
  }

private:
  OperatorID                           mCurrentOperator;
  OperatorID                           mIDs;

  void _SetCurrentOperator ( OperatorID _in id )
  {
    mCurrentOperator = id;
  }

  Connector ( )
    : OpenConnector<T>()
    , mCurrentOperator ( OPERTOR_NULL )
    , mIDs ( OPERTOR_INIT )
  {

  }
};

template<typename T>
const OperatorID Connector<T>::OPERTOR_NULL = 0;

template<typename T>
const OperatorID Connector<T>::OPERTOR_INIT = 1;

////////////////////////////////////////////////////////////////////////////////
// Operator                                                                   //
////////////////////////////////////////////////////////////////////////////////
template<typename T>
class Operator
{
public:
  Operator ( typename Connector<T>::Ptr _in ptr )
    : mConnector ( ptr )
    , mID ( mConnector->GenerateID() )
  {

  }

  Operator ( Operator _in v )
    : mConnector ( v.mConnector )
    , mID ( v.mID )
  {

  }

  virtual ~Operator()
  {

  }

protected:
  void _Send ( Array<T> _in pkg ) throw ( exception )
  {
    boost::system::error_code ec = mConnector->Send ( mID, pkg );
    if ( ec )
    {
      XC_ERROR ( "%s failed: %s %s",
                 __FUNCTION__,
                 ec.category().name(),
                 ec.message().c_str() );
      throw exception();
    }
    return;
  }

  Array<T> _ret _Read ( size_t _in length ) throw ( exception )
  {
    Array<T> ary ( length );
    boost::system::error_code ec = mConnector->Read ( mID, ary );
    if ( ec )
    {
      XC_ERROR ( "%s failed: %s %s",
                 __FUNCTION__,
                 ec.category().name(),
                 ec.message().c_str() );
      throw exception();
    }
    return ary;
  }

  void _Lock() const
  {
    mConnector->Lock ( mID );
  }

  void _EnsureLock() const
  {
    mConnector->EnsureLock ( mID );
  }

  void _Unlock() const
  {
    mConnector->Unlock ( mID );
  }

private:
  typename Connector<T>::Ptr        mConnector;
  OperatorID                                 mID;
};

namespace NetworkBasedDev
{
namespace StringProtocol
{
typedef xc::String                 String;
typedef String::value_type        AtomicType;
typedef OpenConnector<AtomicType> OpenConnector;
typedef Connector<AtomicType>     Connector;
typedef Operator<AtomicType>      Operator;

class Array : public xc::Dev::Array<AtomicType>
{
public:
  Array()
    : xc::Dev::Array<AtomicType>()
  {  }

  Array ( Array _in v )
    : xc::Dev::Array<AtomicType> ( v )
  {  }

  Array ( xc::Dev::Array<AtomicType> _in v )
    : xc::Dev::Array<AtomicType> ( v )
  {  }

  Array ( xc::String _in vr )
    : xc::Dev::Array<AtomicType> ()
  {
    xc::Dev::Array<AtomicType>::reserve ( vr.size () );
    for ( size_t i = 0; i < vr.size (); ++i )
      xc::Dev::Array<AtomicType>::PushBack ( static_cast<AtomicType> ( vr[i] ) );
  }

  virtual ~Array()
  {  }
};

template<typename T>
class ConvertibleData : public xc::Dev::ConvertibleData<Array, T>
{
public:
  ConvertibleData()
    : xc::Dev::ConvertibleData<Array, T>()
  {  }

  ConvertibleData ( ConvertibleData _in v )
    : xc::Dev::ConvertibleData<Array, T> ( v )
  {  }

  ConvertibleData ( xc::Dev::ConvertibleData<Array, T> _in v )
    : xc::Dev::ConvertibleData<Array, T> ( v )
  {  }

  virtual ~ConvertibleData()
  {  }

protected:
  typename xc::Dev::ConvertibleData<Array, T>::TargetType _ret ToTarget() const
  {
    Array ret ( xc::String ( this->mData ) );
    return ret;
  }
};

typedef ConvertibleData<int>    Int;
typedef ConvertibleData<double> Double;

}
}

}
}
