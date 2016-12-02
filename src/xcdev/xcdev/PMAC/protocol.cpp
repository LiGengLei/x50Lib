/*
* License:The MIT License (MIT)
*
* Copyright (c) 2013 Yanyu Su
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
#include "protocol.h"

namespace xc
{
namespace Dev
{
namespace PMAC
{

const Keyword VR_PMAC_SENDLINE ( "VR_PMAC_SENDLINE", 0XB0 );
const Keyword VR_PMAC_GETLINE ( "VR_PMAC_GETLINE", 0XB1 );
const Keyword VR_PMAC_FLUSH ( "VR_PMAC_FLUSH", 0XB3 );
const Keyword VR_PMAC_GETMEM ( "VR_PMAC_GETMEM", 0XB4 );
const Keyword VR_PMAC_SETMEM ( "VR_PMAC_SETMEM", 0XB5 );
const Keyword VR_PMAC_SETBIT ( "VR_PMAC_SETBIT", 0XBA );
const Keyword VR_PMAC_PORT ( "VR_PMAC_PORT", 0XBE );
const Keyword VR_PMAC_GETRESPONSE ( "VR_PMAC_GETRESPONSE", 0XBF );
const Keyword VR_PMAC_READREADY ( "VR_PMAC_READREADY", 0XC2 );
const Keyword VR_PMAC_RESPONSE ( "VR_PMAC_RESPONSE", 0XC4 );
const Keyword VR_PMAC_GETBUFFER ( "VR_PMAC_GETBUFFER", 0XC5 );
const Keyword VR_PMAC_WRITEBUFFER ( "VR_PMAC_WRITEBUFFER", 0XC6 );
const Keyword VR_PMAC_WRITEERROR ( "VR_PMAC_WRITEERROR", 0XC7 );
const Keyword VR_UPLOAD ( "VR_UPLOAD", 0xC0 );
const Keyword VR_DOWNLOAD ( "VR_DOWNLOAD", 0x40 );
const Keyword VR_FWDOWNLOAD ( "VR_FWDOWNLOAD", 0XCB );
const Keyword VR_IPADDRESS ( "VR_IPADDRESS", 0XE0 );
const Keyword VR_INTRSRTING ( "VR_INTRSRTING", 0XE1 );
const Keyword VR_EMPTY ( "VR_EMPTY", 0X0 );
const OperatorID Connector::OPERTOR_NULL = 0;
const OperatorID Connector::OPERTOR_INIT = 1;

}
}
}
