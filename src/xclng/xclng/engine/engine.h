/*
* License:The MIT License (MIT)
*
* Copyright (c) 2013,2014 Yanyu Su
* State Key Laboratory of Robotics and System, Harbin Institute of Technology
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
#include <string>
#include <sstream>
#include <boost/regex.hpp>
#include <boost/shared_ptr.hpp>
#include "definition.h"

class xPoint;
class xFrame;
class xResource;
typedef boost::shared_ptr<xPoint> xptrPoint;
typedef boost::shared_ptr<xFrame> xptrFrame;

class xFrame
{
protected:
    std::string name;
};

class xPoint
{
protected:
    std::string name;
};

class xResource
{
public:
    xResource()
    {
    }

    virtual ~xResource()
    {

    }

protected:
    std::string name;
};

class xSpace;
class xStatement;
class xLine;

typedef boost::shared_ptr<xSpace> xptrSpace;
typedef boost::shared_ptr<xStatement> xptrStatement;
typedef boost::shared_ptr<xLine> xptrLine;

class xSpace
{
public:
    virtual const std::string toString(const std::string &prefix) = 0;
    virtual const std::string linesToString(const std::string &prefix);
    virtual const size_t read(std::stringstream &stm, xptrSpace space);
    virtual const size_t findResource(const std::string & name);
    xSpace(const xptrSpace parent, const std::string & params);
    //virtual ~xSpace();

protected:
    xptrSpace                       mParent;
    std::string                     mParams;
    std::list<xLine>                mLines;

    std::vector<xResource>          mResources;
    std::map<std::string, size_t>   mResourcesMap;
};

class xStatement
{
public:
    xStatement(const xptrSpace parent, const std::string &statement);
    const std::string toString(const std::string &prefix);

protected:
    xptrSpace   mParent;
    std::string mStatement;
};

class xLine
{
public:
    xLine(const xptrStatement statement);
    xLine(const xptrSpace space);
    const std::string toString(const std::string &prefix);

protected:
    xptrStatement pStatement;
    xptrSpace     pSpace;
};

class xIf : public xSpace
{
public:
    xIf(const xptrSpace parent, const std::string & params);
    const std::string toString(const std::string & prefix);
};
typedef boost::shared_ptr<xIf> xptrIf;

class xWhile : public xSpace
{
public:
    xWhile(const xptrSpace parent, const std::string & params);
    const std::string toString(const std::string & prefix);
};
typedef boost::shared_ptr<xWhile> xptrWhile;

class xFunction : public xSpace
{
public:
    xFunction(const xptrSpace parent, const std::string & params);
    const std::string toString(const std::string & prefix);
};
typedef boost::shared_ptr<xFunction> xptrFunction;

class xWorkspace : public xSpace
{
public:
    xWorkspace(const xptrSpace parent, const std::string & params);
    const std::string toString(const std::string & prefix);
};
typedef boost::shared_ptr<xWorkspace> xptrWorkspace;

void xPreProcess(const std::string & strIn, std::string & strOut);
xptrWorkspace xLoadWorkspace(std::stringstream & stm, const std::string & name);
