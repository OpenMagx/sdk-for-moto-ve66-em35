#ifndef ZRTSTRUCTUREDATAPARSER_H
#define ZRTSTRUCTUREDATAPARSER_H

#if defined(EZX_ZN5) || defined(EZX_U9) || defined(EZX_Z6W)
class ZRtStructureDataParser
{
public:	
    typedef struct
    {
        int paragraph;
        int beginPos;
        int endPos;
        QMap<QString, QString> attrs;
    }RT_STRUCTUREDATA;
};
#else
class ZRtStructureDataParser
{
public:	
    ZRtStructureDataParser();
    ~ZRtStructureDataParser();
    
    typedef struct
    {
        int paragraph;
        int beginPos;
        int endPos;
        QMap<QString, QString> attrs;
    }RT_STRUCTUREDATA;
};
#endif

#endif

