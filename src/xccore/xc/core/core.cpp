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
#include <cstdio>
#include <cerrno>
#include <cstdarg>
#include <cstring>
#include <stdexcept>
#include "core.h"

namespace xc
{

//const size_t Result::ERROR_SUCCESS = 0;

inline void StringPrintfImpl ( std::string _out output, CStrPtr _in format,
                               va_list args )
{

  const std::string::size_type write_point = output.size();
  std::string::size_type remaining = output.capacity() - write_point;
  output.resize ( output.capacity() );

  va_list args_copy;
  va_copy ( args_copy, args );
  int bytes_used = vsnprintf ( &output[write_point], remaining, format,
                               args_copy );
  va_end ( args_copy );

  if ( bytes_used < 0 )
  {
    throw std::runtime_error (
      std::string ( "Invalid format string; snprintf returned negative " ) );
  }
  else if ( bytes_used < remaining )
  {
    output.resize ( write_point + bytes_used );
  }
  else
  {
    output.resize ( write_point + bytes_used + 1 );
    remaining = bytes_used + 1;
    va_list args_copy;
    va_copy ( args_copy, args );
    bytes_used = vsnprintf ( &output[write_point], remaining, format,
                             args_copy );
    va_end ( args_copy );

    if ( bytes_used + 1 != remaining )
    {
      throw std::runtime_error (
        std::string ( "vsnprint retry did not manage to work " ) );
    }

    output.resize ( write_point + bytes_used );
  }
}

std::string _ret StringPrint ( CStrPtr _in format, ... )
{
	std::string ret(32UL >= strlen(format) * 2 ? 32UL: strlen(format) * 2, '\0');
  ret.resize ( 0 );

  va_list ap;
  va_start ( ap, format );
  StringPrintfImpl ( ret, format, ap );
  va_end ( ap );
  return ret;
}

std::string _wt StringAppend ( std::string _out output, CStrPtr _in format, ... )
{
  va_list ap;
  va_start ( ap, format );
  StringPrintfImpl ( output, format, ap );
  va_end ( ap );
  return output;
}

void StringPrint ( std::string _out output, CStrPtr _in format, ... )
{
  output.clear();
  va_list ap;
  va_start ( ap, format );
  StringPrintfImpl ( output, format, ap );
  va_end ( ap );
}

String _rd String::Print ( CStrPtr _in format, ... )
{
  clear();
  va_list ap;
  va_start ( ap, format );
  StringPrintfImpl ( *this, format, ap );
  va_end ( ap );
  return *this;
}

String _rd String::AppendPrint ( CStrPtr _in format, ... )
{
  va_list ap;
  va_start ( ap, format );
  StringPrintfImpl ( *this, format, ap );
  va_end ( ap );
  return *this;
}

void Debug ( CStrPtr _in format, ... )
{
  va_list ap;
  va_start ( ap, format );
  printf("[DEBUG]:");
  vprintf (format,ap);
  printf("\n");
  va_end(ap);
}

void Performance ( CStrPtr _in format, ... )
{
  va_list ap;
  va_start ( ap, format );
  printf("[PERFORMANCE]:");
  vprintf (format,ap);
  printf("\n");
  va_end(ap);
}

}
