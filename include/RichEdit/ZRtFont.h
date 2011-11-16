#ifndef ZRTFONT_H
#define ZRTFONT_H

#include "qfont.h"

#if defined(EZX_ZN5) || defined(EZX_U9) || defined(EZX_Z6W)
class ZRtFont;
#else
class ZRtFont
{
public:
    ZRtFont();
    ~ZRtFont();

    static bool overline(QFont font);
    static void setOverline( QFont &font, bool );
};
#endif

#endif


