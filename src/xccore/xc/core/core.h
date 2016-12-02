/*
* License:The MIT License (MIT)
*
* Copyright (c) 2012,2013,2014 Yanyu Su
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
*
* Date:   18/04/2012
*
* Purpose:
* basical types and marcos
*
* Note:
*/
#pragma once

#include <string>
#include <boost/lexical_cast.hpp>

/******************************************************************************/
/* function input, output parameter and return value prefix                   */
/******************************************************************************/
#define _in   const &   // input parameter of right value
#define _out        &   // output parameter of left value
//#define _rv      &&   // output parameter of left value

#define _wt        &  // return value of writable left value
#define _rd  const &  // return value of readonly left value
#define _ret const    // return by value (use c++ complier optimaization)

namespace xc
{

typedef void*         VoidPtr;    // pointer to void
typedef const void*   CVoidPtr;   // pointer to const object
typedef void* const   VoidCPtr;   // const pointer to object
typedef char*         StrPtr;     // pointer to c string
typedef const char*   CStrPtr;    // pointer to const c string
class                 String;
class                 Result;
//typedef boost::exception exception;

/******************************************************************************/
/* function input, output parameter and return value prefix                   */
/******************************************************************************/
class String : public std::string
{
public:
  String()
    : std::string() {  }

  String ( String _in v )
    : std::string ( v ) {  }

  template<typename T>
  String ( T _in v )
    : std::string ( boost::lexical_cast<std::string> ( v ) ) {  }

  String ( std::string _in v )
    : std::string ( v ) {  }

  String ( std::string _in str, size_t _in pos, size_t _in len )
    : std::string ( str, pos, len ) {  }

  String ( CStrPtr _in v )
    : std::string ( v ) {  }

  String ( CStrPtr _in v, size_t _in n )
    : std::string ( v, n ) {  }

  template <class InputIterator>
  String ( InputIterator first, InputIterator last )
    : std::string ( first, last ) {  }

  virtual ~String() {  }

  template<typename T>
  T _ret To ( T _in deful ) const throw ( )
  {
    try
    {
      return  boost::lexical_cast<T> ( static_cast<std::string> ( *this ) ) ;
    }
    catch ( boost::bad_lexical_cast _in v )
    {
      return deful;
    }
  }

  template<typename T>
  T _ret To () const throw ( boost::bad_lexical_cast )
  {
    try
    {
      return  boost::lexical_cast<T> ( static_cast<std::string> ( *this ) ) ;
    }
    catch ( boost::bad_lexical_cast _in v )
    {
      throw;
    }
  }

  String _rd Print ( CStrPtr _in format, ... ) /*throw (std::runtime_error)*/;

  String _rd AppendPrint ( CStrPtr _in format, ... ) /*throw (std::runtime_error)*/;
};

std::string _ret StringPrint ( CStrPtr _in format, ... );
std::string _wt  StringAppend ( std::string _out output, CStrPtr _in format, ... ) ;
void Debug ( CStrPtr _in format, ... );
void Performance ( CStrPtr _in format, ... );
/******************************************************************************/
/* function input, output parameter and return value prefix                   */
/******************************************************************************/
class Result
{
public:
  typedef int ID;
  static const ID SUCCESS = 0;

  Result ( ID _in l, String _in s )
    : mCode ( l )
    , mCatalog ( s )
  {
  }

  inline CStrPtr _ret message () const
  {
    return mCatalog.c_str();
  }

  inline bool _ret is_failed() const
  {
    return SUCCESS != mCode;
  }

  inline bool _ret is_succeed() const
  {
    return SUCCESS == mCode;
  }

  inline ID _rd code() const
  {
    return mCode;
  }

  static inline Result Success()
  {
    return Result ( 0, "success" );
  }

protected:
  ID                 mCode;
  String             mCatalog;
};

class exception : boost::exception
{
public:
  exception() throw() {  }

  virtual ~exception() throw() {  }

  exception ( std::exception _in e )
    : stde()
  {
    stde = e;
  }

  virtual CStrPtr _ret Message() const throw()
  {
    return "exception";
  }

protected:
  std::exception stde;
};

/*
class ResultCatalog
{
public:

  static const ResultID Success = 0;

  ResultCatalog() { }

  ResultCatalog ( ResultCatalog _in v ) { }

  virtual ~ResultCatalog() { }

  virtual CStrPtr _ret Message ( ResultID _in id ) const = 0;

  virtual Result _ret  Make ( ResultID _in id, CResultPtr _in p ) const = 0;

protected:

  virtual CStrPtr _ret DefaultMessage ( ResultID _in id ) const
  {
    if ( id == Success )
      return "success";
    else
      return "failed";
  }

};

class Result
{
public:
  Result ( ResultID _in l, CResultCatalogPtr _in c, CResultPtr _in p = 0 )
    : mCode ( l )
    , mCatalog ( c )
    , mParent ( p )
  {
  }

  inline CStrPtr _ret Message () const
  {
    if ( mCatalog )
      return mCatalog->Message ( mCode );
    else
      return "Undefined Catalog";
  }

  inline bool _ret IsFailed() const
  {
    return Success() != mCode;
  }

  inline bool _ret IsSucceed() const
  {
    return Success() == mCode;
  }

  inline size_t _rd Code() const
  {
    return mCode;
  }

protected:
  ResultID           mCode;
  CResultCatalogPtr  mCatalog;
  CResultPtr         mParent;
};
*/

}

#ifndef XC_PERFORMANCE
#define XC_PERFORMANCE(...)  xc::Performance(__VA_ARGS__);
#endif

#ifndef XC_DEBUG
#define XC_DEBUG(...)  xc::Debug(__VA_ARGS__);
#endif

#ifndef XC_INFO
#define XC_INFO(...)   printf(__VA_ARGS__); printf("\n");
#endif

#ifndef XC_WARN
#define XC_WARN(...)   printf(__VA_ARGS__); printf("\n");
#endif

#ifndef XC_ERROR
#define XC_ERROR(...)   printf(__VA_ARGS__); printf("\n");
#endif

#define XC_ASSERT(x)    assert(x);
#define XC_PAUSE(...)   assert("xc pause");/*printf("xc debug paused, press any key to continue\n at %s:%s.\n",__FILE__,__LINE__); printf(__VA_ARGS__); printf("\n"); while(!getchar());*/
