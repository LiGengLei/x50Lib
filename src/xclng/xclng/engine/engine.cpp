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

#include <sstream>
#include <boost/regex.hpp>
#include <boost/shared_ptr.hpp>
#include "engine.h"

using namespace std;

boost::regex regComment( REGEX_COMMNET );
boost::regex regEndSpace( REGEX_ENDSPACE );
boost::regex regEnter( REGEX_ENTER );
boost::regex regFunction( REGEX_FUNCTION );
boost::regex regWhile( REGEX_WHILE );
boost::regex regEnd( REGEX_END );

xSpace::xSpace(const xptrSpace parent, const string &params)
    : mParent(parent)
    , mParams(params)
{
    
}

const std::string xSpace::linesToString(const string &prefix)
{
    std::string pfix = "  " + prefix;
    std::stringstream stm;
    for(std::list<xLine>::iterator iter = mLines.begin(); iter != mLines.end(); ++iter )
    {
        stm << iter->toString(pfix) << std::endl;
    }
    return stm.str();
}

const size_t xSpace::read(stringstream &stm, xptrSpace space)
{
    size_t count = 0;
    while(stm.good()&&!stm.eof())
    {
        ++count;
        char szLine[2048];
        stm.getline(szLine,2048,';');
        if(!stm.good())
        {
            return count;
        }
        std::string line(" ");
        line.append(szLine);
        if(boost::regex_match(line,regFunction))
        {
            std::cout << "[ F]" << line << std::endl;
            xptrSpace pSpace(new xFunction(space,line));
            space->mLines.push_back( xLine(pSpace) );
            count = count + read(stm,pSpace);
        }
        else if(boost::regex_match(line,regWhile))
        {
            std::cout << "[ W]" << line << std::endl;
            xptrSpace pSpace(new xWhile(space,line));
            space->mLines.push_back( xLine(pSpace) );
            count = count + read(stm,pSpace);
        }
        //
        else if(boost::regex_match(line,regEnd))
        {
            std::cout << "[ E]" << line << std::endl;
            return count;
        }
        //
        else
        {
            std::cout << "[ S]" << line << std::endl;
            xptrStatement pStatement(new xStatement(space,line));
            space->mLines.push_back( xLine(pStatement) );
        }
    }
    return count;
}

const size_t xSpace::findResource(const std::string & name)
{
    std::map<std::string, size_t>::const_iterator itr =
            mResourcesMap.find(name);

    if(itr != mResourcesMap.end())
    {
        return itr->second;
    }
    else if(this->mParent)
    {
        return mParent->findResource(name);
    }
    else
    {
        return -1;
    }
}

xStatement::xStatement(const xptrSpace parent, const string &statement)
    : mParent(parent)
    , mStatement(statement)
{

}

const std::string xStatement::toString(const string &prefix)
{
    return std::string("S:") + prefix + mStatement;
}

xLine::xLine(const xptrStatement statement)
    : pSpace()
{
    pStatement = statement;
}

xLine::xLine(const xptrSpace space)
    : pStatement()
{
    pSpace = space;
}

const string xLine::toString(const string &prefix)
{
    if(pStatement)
    {
        return pStatement->toString(prefix);
    }
    else if(pSpace)
    {
        return pSpace->toString(prefix);
    }
    else
    {
        return std::string("error.");
    }
}

xIf::xIf(const xptrSpace parent, const string &params)
    : xSpace(parent,params)
{

}

const std::string xIf::toString(const std::string & prefix)
{
    return std::string("I:") + prefix + mParams + std::string("\n")
            + linesToString(prefix)
            + std::string("W:") + prefix + std::string("END");
}

xWhile::xWhile(const xptrSpace parent, const string &params)
    : xSpace(parent,params)
{

}

const std::string xWhile::toString(const std::string & prefix)
{
    return std::string("W:") + prefix + mParams + std::string("\n")
            + linesToString(prefix)
            + std::string("W:") + prefix + std::string(" END");
}

xFunction::xFunction(const xptrSpace parent, const string &params)
    : xSpace(parent,params)
{

}

const std::string xFunction::toString(const std::string & prefix)
{
    return std::string("N:") + prefix + mParams + std::string("\n")
            + linesToString(prefix)
            + std::string("N:") + prefix + std::string(" END");
}

xWorkspace::xWorkspace(const xptrSpace parent, const string &params)
    : xSpace(parent,params)
{

}

const std::string xWorkspace::toString(const std::string & prefix)
{
    return std::string("F:") + prefix + mParams + std::string("\n")
            + linesToString(prefix)
            + std::string("F:") + prefix + std::string(" END");
}

void xPreProcess(const std::string & strIn, std::string & strOut)
{
    strOut = boost::regex_replace(strIn,regComment,"");
    strOut = boost::regex_replace(strOut,regEndSpace,"");
    strOut = boost::regex_replace(strOut,regEnter,"");
}

xptrWorkspace xLoadWorkspace(std::stringstream & stm, const std::string & name)
{
    xptrWorkspace pWorkspace(new xWorkspace(xptrSpace(),name));
    pWorkspace->read(stm, pWorkspace);
    return pWorkspace;
}

