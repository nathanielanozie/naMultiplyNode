#ifndef NAMULTIPLYNODE_H
#define NAMULTIPLYNODE_H

#include <maya/MPxNode.h>
#include <maya/MGlobal.h>
#include <maya/MTypeId.h>


class naMultiplyNode : public MPxNode
{
    public:
        naMultiplyNode();
        virtual ~naMultiplyNode();
        
        static void* creator(); 
        virtual MStatus compute(const MPlug&, MDataBlock& );
        static MStatus initialize();
        static MTypeId id;
    
    protected:
        //the inputs max 10 
        static MObject aIn_01;
        static MObject aIn_02;
        static MObject aIn_03;
        static MObject aIn_04;
        static MObject aIn_05;
        static MObject aIn_06;
        static MObject aIn_07;
        static MObject aIn_08;
        static MObject aIn_09;
        static MObject aIn_10;
        
        //the output for node
        static MObject aOut;
};



#endif