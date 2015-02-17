/*

    This file is part of naMultiplyNode.

    naMultiplyNode is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/lgpl.html>.

    Author:     Nathaniel Anozie      ogbonnawork at gmail dot com
    Url:        nathananozie dot blogspot dot com
    Date:       2015 / 02 / 16

*/

/**
naMultiplyNode.cpp
Like multiply divide node but for multiply only and up to 10 scalar inputs

//example
createNode naMultiplyNode;

@note Inspired by David Gould -- learning about writing nodes from his book: Complete Maya Programming
@note Inspired by Marco Giordano -- learning about writing nodes from his online tutorials
@note Inspired by Jeremie Passerin (jeremiepasserin dot com) -- learning about writing nodes from his online tutorials
*/
//02-16-2015        --  initial release


#include "naMultiplyNode.h"


#include <maya/MPlug.h>
#include <maya/MDataBlock.h>
#include <maya/MDataHandle.h>
#include <maya/MFnNumericAttribute.h>

#include <maya/MFnPlugin.h>

#define naAuthor "Nathaniel Anozie"
#define naNodeName "naMultiplyNode"

/**
*/

//the id
MTypeId naMultiplyNode::id(0x00121C2E); //look at last 2 digits: 42, I have up to 63


//DESCRIPTION: attribute information
//
MObject naMultiplyNode::aIn_01;
MObject naMultiplyNode::aIn_02;
MObject naMultiplyNode::aIn_03;
MObject naMultiplyNode::aIn_04;
MObject naMultiplyNode::aIn_05;
MObject naMultiplyNode::aIn_06;
MObject naMultiplyNode::aIn_07;
MObject naMultiplyNode::aIn_08;
MObject naMultiplyNode::aIn_09;
MObject naMultiplyNode::aIn_10;


MObject naMultiplyNode::aOut;

//no special actions on creation or destruction
naMultiplyNode::naMultiplyNode(){}
naMultiplyNode::~naMultiplyNode(){}

void* naMultiplyNode::creator()
{ 
    return new naMultiplyNode();
}


/**called once when node registered
*/
MStatus naMultiplyNode::initialize()
{
    MFnNumericAttribute nattr;
    
    MStatus stat;
    
    //Input Attributes
    //all writable, all keyable, all shown
    //
    aIn_01 = nattr.create( "aIn_01", "in_01", MFnNumericData::kFloat,0, &stat );
    //not providing own error handling
    CHECK_MSTATUS( stat );
    CHECK_MSTATUS( nattr.setKeyable(true) );
    CHECK_MSTATUS( nattr.setStorable(true) );
    CHECK_MSTATUS( nattr.setDefault(1.0f) ); //default at 1 important so unspecified inputs dont have adverse affect on multiplication
    
    //
    aIn_02 = nattr.create( "aIn_02", "in_02", MFnNumericData::kFloat,0, &stat );
    //not providing own error handling
    CHECK_MSTATUS( stat );
    CHECK_MSTATUS( nattr.setKeyable(true) );
    CHECK_MSTATUS( nattr.setStorable(true) );
    CHECK_MSTATUS( nattr.setDefault(1.0f) );
    //
    aIn_03 = nattr.create( "aIn_03", "in_03", MFnNumericData::kFloat,0, &stat );
    //not providing own error handling
    CHECK_MSTATUS( stat );
    CHECK_MSTATUS( nattr.setKeyable(true) );
    CHECK_MSTATUS( nattr.setStorable(true) );
    CHECK_MSTATUS( nattr.setDefault(1.0f) );
    //
    aIn_04 = nattr.create( "aIn_04", "in_04", MFnNumericData::kFloat,0, &stat );
    //not providing own error handling
    CHECK_MSTATUS( stat );
    CHECK_MSTATUS( nattr.setKeyable(true) );
    CHECK_MSTATUS( nattr.setStorable(true) );
    CHECK_MSTATUS( nattr.setDefault(1.0f) );
    //
    aIn_05 = nattr.create( "aIn_05", "in_05", MFnNumericData::kFloat,0, &stat );
    //not providing own error handling
    CHECK_MSTATUS( stat );
    CHECK_MSTATUS( nattr.setKeyable(true) );
    CHECK_MSTATUS( nattr.setStorable(true) );
    CHECK_MSTATUS( nattr.setDefault(1.0f) );
    //
    aIn_06 = nattr.create( "aIn_06", "in_06", MFnNumericData::kFloat,0, &stat );
    //not providing own error handling
    CHECK_MSTATUS( stat );
    CHECK_MSTATUS( nattr.setKeyable(true) );
    CHECK_MSTATUS( nattr.setStorable(true) );
    CHECK_MSTATUS( nattr.setDefault(1.0f) );
    //
    aIn_07 = nattr.create( "aIn_07", "in_07", MFnNumericData::kFloat,0, &stat );
    //not providing own error handling
    CHECK_MSTATUS( stat );
    CHECK_MSTATUS( nattr.setKeyable(true) );
    CHECK_MSTATUS( nattr.setStorable(true) );
    CHECK_MSTATUS( nattr.setDefault(1.0f) );
    //
    aIn_08 = nattr.create( "aIn_08", "in_08", MFnNumericData::kFloat,0, &stat );
    //not providing own error handling
    CHECK_MSTATUS( stat );
    CHECK_MSTATUS( nattr.setKeyable(true) );
    CHECK_MSTATUS( nattr.setStorable(true) );
    CHECK_MSTATUS( nattr.setDefault(1.0f) );
    //
    aIn_09 = nattr.create( "aIn_09", "in_09", MFnNumericData::kFloat,0, &stat );
    //not providing own error handling
    CHECK_MSTATUS( stat );
    CHECK_MSTATUS( nattr.setKeyable(true) );
    CHECK_MSTATUS( nattr.setStorable(true) );
    CHECK_MSTATUS( nattr.setDefault(1.0f) );
    //
    aIn_10 = nattr.create( "aIn_10", "in_10", MFnNumericData::kFloat,0, &stat );
    //not providing own error handling
    CHECK_MSTATUS( stat );
    CHECK_MSTATUS( nattr.setKeyable(true) );
    CHECK_MSTATUS( nattr.setStorable(true) );
    CHECK_MSTATUS( nattr.setDefault(1.0f) );
    ////////////////
    ////////////////
    
    
    
    //Output Attributes
    aOut = nattr.create( "output", "out", MFnNumericData::kFloat,0, &stat );
    //not providing own error handling
    CHECK_MSTATUS( stat );
    CHECK_MSTATUS( nattr.setHidden(false) );
    CHECK_MSTATUS( nattr.setReadable(true) );
    CHECK_MSTATUS( nattr.setWritable(false) );
    CHECK_MSTATUS( nattr.setKeyable(false) );
    
    
    //add attributes defined for node
    CHECK_MSTATUS( addAttribute( aIn_01 ) );
    CHECK_MSTATUS( addAttribute( aIn_02 ) );
    CHECK_MSTATUS( addAttribute( aIn_03 ) );
    CHECK_MSTATUS( addAttribute( aIn_04 ) );
    CHECK_MSTATUS( addAttribute( aIn_05 ) );
    CHECK_MSTATUS( addAttribute( aIn_06 ) );
    CHECK_MSTATUS( addAttribute( aIn_07 ) );
    CHECK_MSTATUS( addAttribute( aIn_08 ) );
    CHECK_MSTATUS( addAttribute( aIn_09 ) );
    CHECK_MSTATUS( addAttribute( aIn_10 ) );
    
    CHECK_MSTATUS( addAttribute( aOut ) );
    
    
    //make sure if any of inputs change the output should get computed
    //here were not actually making a calculation but we still
    //want the out to be up to date with most recent connections
    //
    CHECK_MSTATUS( attributeAffects(aIn_01, aOut) );
    CHECK_MSTATUS( attributeAffects(aIn_02, aOut) );
    CHECK_MSTATUS( attributeAffects(aIn_03, aOut) );
    CHECK_MSTATUS( attributeAffects(aIn_04, aOut) );
    CHECK_MSTATUS( attributeAffects(aIn_05, aOut) );
    CHECK_MSTATUS( attributeAffects(aIn_06, aOut) );
    CHECK_MSTATUS( attributeAffects(aIn_07, aOut) );
    CHECK_MSTATUS( attributeAffects(aIn_08, aOut) );
    CHECK_MSTATUS( attributeAffects(aIn_09, aOut) );
    CHECK_MSTATUS( attributeAffects(aIn_10, aOut) );    
    
    return( MS::kSuccess );
}



/**called on every createNode command or dependency node create
*/
MStatus naMultiplyNode::compute( const MPlug& plug, MDataBlock& data)
{
    MStatus stat;
    //if any plug is changed make sure output knows this
    //only output attribute is computed
    //if( plug == aOut || plug == aIn_01 || plug == aIn_02 || plug == aIn_03 || plug == aIn_04
    //    || plug == aIn_05 || plug == aIn_06 || plug == aIn_07|| plug == aIn_08 || plug == aIn_09 || plug == aIn_10 )
    if( plug == aOut )
    {   
        //do the multiplification here
        double in_01, in_02, in_03, in_04, in_05, in_06, in_07, in_08, in_09, in_10; //needed
        
        //first get input
        //making one data handle for each input
        MDataHandle aIn_01_handle = data.inputValue( aIn_01, &stat );
        CHECK_MSTATUS(stat);
        in_01 = aIn_01_handle.asFloat(); //important using asFloat not asDouble
        MDataHandle aIn_02_handle = data.inputValue( aIn_02, &stat );
        CHECK_MSTATUS(stat);
        in_02 = aIn_02_handle.asFloat();
        MDataHandle aIn_03_handle = data.inputValue( aIn_03, &stat );
        CHECK_MSTATUS(stat);
        in_03 = aIn_03_handle.asFloat();
        MDataHandle aIn_04_handle = data.inputValue( aIn_04, &stat );
        CHECK_MSTATUS(stat);
        in_04 = aIn_04_handle.asFloat();
        MDataHandle aIn_05_handle = data.inputValue( aIn_05, &stat );
        CHECK_MSTATUS(stat);
        in_05 = aIn_05_handle.asFloat();
        MDataHandle aIn_06_handle = data.inputValue( aIn_06, &stat );
        CHECK_MSTATUS(stat);
        in_06 = aIn_06_handle.asFloat();
        MDataHandle aIn_07_handle = data.inputValue( aIn_07, &stat );
        CHECK_MSTATUS(stat);
        in_07 = aIn_07_handle.asFloat();
        MDataHandle aIn_08_handle = data.inputValue( aIn_08, &stat );
        CHECK_MSTATUS(stat);
        in_08 = aIn_08_handle.asFloat();
        MDataHandle aIn_09_handle = data.inputValue( aIn_09, &stat );
        CHECK_MSTATUS(stat);
        in_09 = aIn_09_handle.asFloat();
        MDataHandle aIn_10_handle = data.inputValue( aIn_10, &stat );
        CHECK_MSTATUS(stat);
        in_10 = aIn_10_handle.asFloat();
        //
        MDataHandle outHandle = data.outputValue(aOut, &stat);
        CHECK_MSTATUS(stat);
        
        double result = 0;
        result = in_01*in_02*in_03*in_04*in_05*in_06*in_07*in_08*in_09*in_10;
        
        //error checking
        /*
        MGlobal::displayInfo(MString("Multipy # are: ") + in_01 + "," + in_02+ "," + in_03+ "," + in_04+ "," + in_05+ "," + in_06+ "," + in_07+ "," + in_08+ "," + in_09+ "," + in_10);
        MGlobal::displayInfo(MString("Result #is: ") + result);
        */
        
        outHandle.setFloat( result ); //do multiplication, if using float need setFloat, if double setDouble crucial
        
        
        //tell maya attribute updated
        /*
        aIn_01_handle.setClean();
        aIn_02_handle.setClean();
        aIn_03_handle.setClean();
        aIn_04_handle.setClean();
        aIn_05_handle.setClean();
        aIn_06_handle.setClean();
        aIn_07_handle.setClean();
        aIn_08_handle.setClean();
        aIn_09_handle.setClean();
        aIn_10_handle.setClean();
        //even set cleaning out handle
        */
        outHandle.setClean();

        data.setClean( plug ); //clean the appropriate plug
    }
    else{
        stat = MS::kUnknownParameter;   
    }
        
    
    return stat;
}






/**notice this one isn't part of our class header
*/
MStatus initializePlugin(MObject obj)
{
    MFnPlugin plugin(obj,naAuthor,"","Any");
    
    CHECK_MSTATUS(   plugin.registerNode( naNodeName, naMultiplyNode::id, naMultiplyNode::creator, naMultiplyNode::initialize, MPxNode::kDependNode  ) );
    
    return( MS::kSuccess);
}

MStatus uninitializePlugin(MObject obj)
{
    MFnPlugin plugin(obj);
    CHECK_MSTATUS(plugin.deregisterNode( naMultiplyNode::id ) );
    
    return( MS::kSuccess);
}

