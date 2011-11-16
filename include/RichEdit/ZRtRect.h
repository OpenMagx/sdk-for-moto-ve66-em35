#ifndef ZRTRECT_H
#define ZRTRECT_H

#include "qrect.h"

#if defined(EZX_ZN5) || defined(EZX_U9) || defined(EZX_Z6W)
class ZRtRect;
#else
class ZRtRect
{
public:
    ZRtRect();
    ~ZRtRect();

    static void addCoords( QRect &rect, int x1, int y1, int x2, int y2 );    
};
#endif

#endif



