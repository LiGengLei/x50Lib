/*
* License:The MIT License (MIT)
*
* Copyright (c) 2013,2014 Yanyu Su
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
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
#include <boost/asio.hpp>
#include <boost/lambda/bind.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/static_assert.hpp>

namespace xc
{
namespace Dev
{
namespace PMAC
{
typedef uint8_t         Byte;
typedef uint16_t        Word;
class                   Keyword;
class                   Array;
class                   Packet;
class                   OpenConnector;
typedef size_t          OperatorID;
class                   Connector;
class                   Operator;
class                   OnlineOperator;
class                   RotaryBufferOperator;
typedef boost::shared_ptr<Connector>  ConnectorPtr;

extern const Keyword VR_PMAC_SENDLINE    ;//= 0XB0;
extern const Keyword VR_PMAC_GETLINE     ;//= 0XB1;
extern const Keyword VR_PMAC_FLUSH       ;//= 0XB3;
extern const Keyword VR_PMAC_GETMEM      ;//= 0XB4;
extern const Keyword VR_PMAC_SETMEM      ;//= 0XB5;
extern const Keyword VR_PMAC_SETBIT      ;//= 0XBA;
extern const Keyword VR_PMAC_SETBITS     ;//= 0XBB;
extern const Keyword VR_PMAC_PORT        ;//= 0XBE;
extern const Keyword VR_PMAC_GETRESPONSE ;//= 0XBF;
extern const Keyword VR_PMAC_READREADY   ;//= 0XC2;
extern const Keyword VR_PMAC_RESPONSE    ;//= 0XC4;
extern const Keyword VR_PMAC_GETBUFFER   ;//= 0XC5;
extern const Keyword VR_PMAC_WRITEBUFFER ;//= 0XC6;
extern const Keyword VR_PMAC_WRITEERROR  ;//= 0XC7;
extern const Keyword VR_UPLOAD           ;//= 0xC0;
extern const Keyword VR_DOWNLOAD         ;//= 0x40;
extern const Keyword VR_FWDOWNLOAD       ;//= 0XCB;
extern const Keyword VR_IPADDRESS        ;//= 0XE0;
extern const Keyword VR_INTRSRTING       ;//= 0XE1;
extern const Keyword VR_EMPTY            ;//= 0X0;

////////////////////////////////////////////////////////////////////////////////
// Keyword                                                                    //
////////////////////////////////////////////////////////////////////////////////
class Keyword
{
public:

  Keyword ( CStrPtr _in name, Byte _in value )
    : mName ( name )
    , mValue ( value )
  {
  }


  Keyword ( Keyword _in value )
    : mName ( value.mName )
    , mValue ( value.mValue ) {  }

  virtual ~Keyword() {  }

  Byte _ret Value() const
  {
    return mValue;
  }

  operator Byte _ret() const
  {
    return mValue;
  }

  operator CStrPtr _ret() const
  {
    return mName.c_str();
  }

protected:
  String mName;
  Byte  mValue;

protected:

  static void Add ( CStrPtr _in name, Byte _in value )
  {
    std::list<Keyword>::iterator itr = REGISTER.begin();

    for ( ; itr != REGISTER.end(); ++itr )
    {
      if ( itr->Value() == value )
        return ;

      if ( itr->Value() > value )
        break;
    }

    std::list<Keyword>::iterator ret =
      REGISTER.insert ( itr, Keyword ( name, value ) );
  }

protected:

  static std::list<Keyword> REGISTER;
};

////////////////////////////////////////////////////////////////////////////////
// Array                                                                      //
////////////////////////////////////////////////////////////////////////////////
class Array : public std::vector<Byte>
{
public:
  Array()
    : std::vector<Byte>()
  {
  }

  Array ( Array _in value )
    : std::vector<Byte> ( value )
  {
  }

  Array ( size_t _in size )
    : std::vector<Byte> ( size )
  {
  }

  virtual ~Array()
  {
  }

  void PushBack ( Byte _in value )
  {
    push_back ( value );
  }

  void PushBack ( std::vector<Byte> _in value )
  {
    insert ( std::vector<Byte>::end(), value.begin(), value.end() );
  }

  void PushBack ( Keyword _in value )
  {
    PushBack ( value.Value() );
  }

  void PushBack ( Word _in value )
  {
    Word ns = htons ( value );
    Byte * pch = reinterpret_cast<Byte *> ( &ns );
    push_back ( pch[0] );
    push_back ( pch[1] );
  }

  void PushBack ( String _in value )
  {
    reserve ( size() + value.size() );

    for ( size_t i = 0; i < value.size(); ++i )
      push_back ( static_cast<Byte> ( value[i] ) );
  }


  void PushBack ( CStrPtr _in value, size_t _in length )
  {
    reserve ( size() + length );

    for ( size_t i = 0; i < length; ++i )
      push_back ( static_cast<Byte> ( value[i] ) );
  }


  inline String _ret ToString() const
  {
    String ret;
    ret.clear();
    ret.reserve ( size() );

    for ( size_t i = 0; i < size(); ++i )
    {
      if ( isprint ( at ( i ) ) )
      {
        ret.push_back ( at ( i ) );
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
    ret.reserve ( size() );

    bool lastPrint = false;
    for ( size_t i = 0; i < size(); ++i )
    {
      if ( isprint ( at ( i ) ) )
      {
        if ( lastPrint )
          ret.append ( "%c", at ( i ) );
        else
          ret.append ( " %2c", at ( i ) );

        lastPrint = true;
      }
      else
      {
        ret.append ( " %02x", at ( i ) );
        lastPrint = false;
      }
    }

    return ret;
  }
};

////////////////////////////////////////////////////////////////////////////////
// Packet                                                                     //
////////////////////////////////////////////////////////////////////////////////
class Packet
{
public:

  static const size_t CMD_SIZE        = 8;
  static const size_t MAX_DATA_SIZE   = 1492;


  Packet()
    : mRequestType ( VR_DOWNLOAD )
    , mRequest ( VR_PMAC_SENDLINE )
    , mValue ( 0 )
    , mIndex ( 0 )
    , mLength ( 0 )
  {
  }


  Packet ( Packet _in value )
    : mRequestType ( value.mRequestType )
    , mRequest ( value.mRequest )
    , mValue ( value.mValue )
    , mIndex ( value.mIndex )
    , mData ( value.mData )
    , mLength ( value.mLength )
  {
  }


  Packet ( Byte _in rt, Byte _in r, Word _in v, Word _in i, Word _in l )
    : mRequestType ( rt )
    , mRequest ( r )
    , mValue ( v )
    , mIndex ( i )
    , mLength ( l )
  {
    mData.reserve ( l );
  }


  Packet ( Byte _in rt, Byte _in r, Word _in v, Word _in i )
    : mRequestType ( rt )
    , mRequest ( r )
    , mValue ( v )
    , mIndex ( i )
    , mLength ( 0 )
  {
  }


  virtual ~Packet()
  {
  }


  Array _ret ToArray() const
  {
    assert ( mData.size() < MAX_DATA_SIZE );
    Array array;
    array.reserve ( CMD_SIZE + mData.size() );
    array.PushBack ( mRequestType );
    array.PushBack ( mRequest );
    array.PushBack ( mValue );
    array.PushBack ( mIndex );
    array.PushBack ( mLength );
    array.PushBack ( mData );
    return array;
  }


  void SetHead ( Byte _in rt, Byte _in r, Word _in v, Word _in i )
  {
    mRequestType = rt;
    mRequest = r;
    mValue = v;
    mIndex = i;
  }


  void Length ( Word _in l )
  {
    mLength = l;
  }


  Word _ret Length() const
  {
    return mLength;
  }


  size_t _ret Size() const
  {
    return mData.size();
  }


  void SetData ( String _in str )
  {
    mData.clear();
    mData.reserve ( str.size() );
    mData.PushBack ( str );
    mLength = mData.size();
  }


  void AppendData ( String _in str )
  {
    mData.reserve ( mData.size() + str.size() + 1 );
    mData.PushBack ( str );
    mData.PushBack ( static_cast<Byte> ( 0 ) );
    mLength = mData.size();
  }

protected:

  Byte      mRequestType;
  Byte      mRequest;
  Word      mValue;
  Word      mIndex;
  Word      mLength;
  Array     mData;
};

////////////////////////////////////////////////////////////////////////////////
// Reply                                                                      //
////////////////////////////////////////////////////////////////////////////////
class Reply
{
public:

  Reply ( Array _in ary )
    : Segments()
  {
    boost::split ( Segments, ary.ToString(), boost::is_any_of ( " " ) );
  }


  Reply ( Reply _in v )
    : Segments ( v.Segments )
  {

  }


  virtual ~Reply()
  {

  }


  size_t _ret Size() const
  {
    return Segments.size();
  }


  double _ret AsDouble ( size_t _in i ) const
  {
    return atof ( Segments[i].c_str() );
  }


  int _ret AsInt ( size_t _in i ) const
  {
    return atoi ( Segments[i].c_str() );
  }


  long _ret AsLong ( size_t _in i ) const
  {
    return atol ( Segments[i].c_str() );
  }


  long long _ret AsLLong ( size_t _in i ) const
  {
    return atoll ( Segments[i].c_str() );
  }

public:

  std::vector<String> Segments;
};

////////////////////////////////////////////////////////////////////////////////
// OpenConnector                                                              //
////////////////////////////////////////////////////////////////////////////////
class OpenConnector : public boost::noncopyable
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


  virtual ~OpenConnector()
  {
  }


  bool _ret Connect ( String _in host, String _in port,
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


  bool _ret Cancel()
  {
    XC_DEBUG ( "%s. ", __FUNCTION__ );

    bool ret = true;
    boost::system::error_code ec;
    mSocket.cancel ( ec );
    if ( boost::asio::error::operation_not_supported == ec )
    {
      Close ();
      return true;
    }

    if ( ec )
      return false;
    else
      return true;
  }


  bool _ret Shutdown()
  {
    XC_DEBUG ( "%s. ",  __FUNCTION__ );
    bool ret = Close();
    mIOService.stop ();
    return ret;
  }


  boost::system::error_code _ret Send ( Array _in cmd,
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


  boost::system::error_code _ret Read ( Array _out ary,
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
  OpenConnector ( OpenConnector _in v )
    : mIOService()
    , mSocket ( mIOService )
    , mDeadline ( mIOService )
  {
  }

  OpenConnector _rd operator= ( OpenConnector _in v )
  {
    return *this;
  }


  void _CheckDeadline()
  {
    if ( mDeadline.expires_at() <= boost::asio::deadline_timer::traits_type::now() )
    {
      //Close();
      Cancel();
      mDeadline.expires_at ( boost::posix_time::pos_infin );
    }
    mDeadline.async_wait ( boost::lambda::bind ( &OpenConnector::_CheckDeadline, this ) );
  }


  boost::asio::io_service       mIOService;
  boost::asio::ip::tcp::socket  mSocket;
  boost::asio::deadline_timer   mDeadline;
};

////////////////////////////////////////////////////////////////////////////////
// ConnectorManger                                                            //
////////////////////////////////////////////////////////////////////////////////
class Connector : protected OpenConnector
{
public:

  static const OperatorID              OPERTOR_NULL;// = 0;
  static const OperatorID              OPERTOR_INIT;// = 1;


  static ConnectorPtr _ret MakeInstace()
  {
    return  ConnectorPtr ( new Connector() );
  }


  virtual ~Connector()
  {
    XC_DEBUG ( "connector released" );
  }


  bool _ret Connect ( String _in host, String _in port,
                      boost::posix_time::time_duration _in timeout
                      = boost::posix_time::seconds ( DEFAULT_WAITTIME ) )
  {
    return OpenConnector::Connect ( host, port, timeout );
  }


  bool _ret Close()
  {
    return OpenConnector::Close();
  }


  bool _ret Shutdown()
  {
    return OpenConnector::Shutdown();
  }


  OperatorID _ret GenerateID()
  {
    return ++mIDs;
  }


  OperatorID _ret CurrentOperator() const
  {
    return mCurrentOperator;
  }


  boost::system::error_code _ret Send ( OperatorID _in id, Array _in cmd )
  {
    EnsureLock ( id );
    return OpenConnector::Send ( cmd );
  }


  virtual boost::system::error_code _ret Read ( OperatorID _in id, Array _out ary )
  {
    EnsureLock ( id );
    return OpenConnector::Read ( ary );
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
    : OpenConnector()
    , mCurrentOperator ( OPERTOR_NULL )
    , mIDs ( OPERTOR_INIT )
  {  }
};

////////////////////////////////////////////////////////////////////////////////
// Operator                                                                   //
////////////////////////////////////////////////////////////////////////////////
class Operator
{
public:

  Operator ( ConnectorPtr _in ptr )
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

  void _Send ( Packet _in pkg ) throw ( exception )
  {
    boost::system::error_code ec = mConnector->Send ( mID, pkg.ToArray() );
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


  Array _ret _Read ( size_t _in length ) throw ( exception )
  {
    Array ary ( length );
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

  ConnectorPtr        mConnector;
  OperatorID          mID;
};

////////////////////////////////////////////////////////////////////////////////
// Operator                                                                   //
////////////////////////////////////////////////////////////////////////////////
class OnlineOperator : public Operator
{
public:

  OnlineOperator ( ConnectorPtr _in ptr )
    : Operator ( ptr )
  {

  }


  OnlineOperator ( OnlineOperator _in v )
    : Operator ( v )
  {

  }


  virtual ~OnlineOperator()
  {

  }


  Array _ret ReadReady() throw ( exception )
  {
    Packet p ( VR_UPLOAD, VR_PMAC_READREADY, 0, 0, 2 );
    Send ( p );
    return Read ();
  }


  Array _ret Flush() throw ( exception )
  {
    Packet p ( VR_DOWNLOAD, VR_PMAC_FLUSH, 0, 0 );
    Send ( p );
    return Read ();
  }


  Array _ret SendLine ( String _in line ) throw ( exception )
  {
    Packet p ( VR_DOWNLOAD, VR_PMAC_SENDLINE, 0, 0 );
    p.SetData ( line );
    Send ( p );
    return Read ( 256 );
  }


  Array _ret GetResponse ( String _in line ) throw ( exception )
  {
    Packet p ( VR_DOWNLOAD, VR_PMAC_GETRESPONSE, 0, 0 );
    p.SetData ( line );
    Send ( p );
    Array ret = Read ( 256 );
    return ret;
  }


  Array _ret WriteBuffer ( std::vector<String> _in lines ) throw ( exception )
  {
    Packet p ( VR_DOWNLOAD, VR_PMAC_WRITEBUFFER, 0, 0 );
    for ( size_t i = 0; i < lines.size(); ++i )
      p.AppendData ( lines[i] );
    Send ( p );
    return Read ( 32 );
  }


  Array _ret WriteBuffer ( String _in line, String _in seprates ) throw ( exception )
  {
    std::vector<String> segments;
    boost::split ( segments, line, boost::is_any_of ( seprates ) );
    return WriteBuffer ( segments );
  }

protected:

  virtual void Send ( Packet _in pkg ) throw ( exception )
  {
    _Lock();
    _Send ( pkg );
    _Unlock();
    return;
  }


  virtual Array _ret Read ( size_t _in length = 32 ) throw ( exception )
  {
    _Lock();
    Array ret = _Read ( length );
    _Unlock();
    return ret;
  }
};

class RotaryBufferOperator : public Operator
{
public:
  RotaryBufferOperator ( ConnectorPtr _in ptr )
    : Operator ( ptr )
  {

  }

  RotaryBufferOperator ( RotaryBufferOperator _in v )
    : Operator ( v )
  {

  }

  virtual ~RotaryBufferOperator()
  {

  }

  Array _ret SendLine ( String _in line ) throw ( exception )
  {
    Packet p ( VR_DOWNLOAD, VR_PMAC_SENDLINE, 0, 0 );
    p.SetData ( line );
    _Send ( p );
    return _Read ( 256 );
  }

  Array _ret GetResponse ( String _in line ) throw ( exception )
  {
    Packet p ( VR_DOWNLOAD, VR_PMAC_GETRESPONSE, 0, 0 );
    p.SetData ( line );
    _Send ( p );
    Array ret = _Read ( 256 );
    return ret;
  }

  Array _ret WriteBuffer ( std::vector<String> _in lines ) throw ( exception )
  {
    Packet p ( VR_DOWNLOAD, VR_PMAC_WRITEBUFFER, 0, 0 );
    for ( size_t i = 0; i < lines.size(); ++i )
      p.AppendData ( lines[i] );
    _Send ( p );
    return _Read ( 32 );
  }

  Array _ret Open() throw ( exception )
  {
    _Lock();
    Array ret =  GetResponse ( "OPEN ROT" );
    return ret;
  }


  Array _ret Close() throw ( exception )
  {
    Array ret =  GetResponse ( "CLOSE" );
    _Unlock();
    return ret;
  }

  Array _ret Create ( size_t _in cs, size_t _in size ) throw ( exception )
  {
    _Lock();
    Array ret =  GetResponse ( StringPrint ( "&%d DEFINE ROT %ld", cs, size ) );
    _Unlock();
    return ret;
  }


  Array _ret Locate ( size_t _in loc ) throw ( exception )
  {
    _Lock();
    Array ret =  GetResponse ( StringPrint ( "B%ld", loc ) );
    _Unlock();
    return ret;
  }

  Array _ret PR() throw ( exception )
  {
    return GetResponse ( "PR" );
  }

  Array _ret WriteBuffer ( String _in line, String _in seprates ) throw ( exception )
  {
    std::vector<String> segments;
    boost::split ( segments, line, boost::is_any_of ( seprates ) );
    return WriteBuffer ( segments );
  }

  Array _ret WriteBuffer ( String _in line ) throw ( exception )
  {
    return GetResponse ( line );
  }

};

}
}
}

/*
class ConnectorSimulator : public Connector
{
public:
  virtual boost::system::error_code _ret _Connect ( xc::xstring _in host, xc::xstring _in port )
  {
    return boost::system::errc::make_error_code ( boost::system::errc::success );
  }

  virtual boost::system::error_code _ret _Send ( xc::dev::pmac::Array _in cmd )
  {
    //std::cout << "[snd]" << cmd.ToStringDetail() << std::endl;
    return boost::system::errc::make_error_code ( boost::system::errc::success );
  }

  virtual boost::system::error_code _ret _Read ( Array _out ary )
  {
    ary.clear();
    ary.PushBack ( "0.0 0.0 0.0 0.0 0.0 0.0" );
    return boost::system::errc::make_error_code ( boost::system::errc::success );
  }

  virtual boost::system::error_code _ret _Disconnect()
  {
    return boost::system::errc::make_error_code ( boost::system::errc::success );
  }
};
*/
