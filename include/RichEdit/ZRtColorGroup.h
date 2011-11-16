#ifndef ZRTCOLORGROUP_H
#define ZRTCOLORGROUP_H

#include "qcolor.h"

#if defined(EZX_ZN5) || defined(EZX_U9) || defined(EZX_Z6W)
class ZRtColorGroup;
#else
class ZRtColorGroup
{
public:
    ZRtColorGroup();
    ~ZRtColorGroup();

    QColor link();
    QColor linkVisited();
    
};
#endif

#endif
