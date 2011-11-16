#ifndef ZINPUTMETHODSKIN_H
#define ZINPUTMETHODSKIN_H

#include <qpixmap.h>

#if defined(EZX_ZN5) || defined(EZX_U9) || defined(EZX_Z6W)
class ZTextInputMethodSkin;
#else
class QColor;

class ZTextInputMethodSkin
{
public:
    ZTextInputMethodSkin();
    ~ZTextInputMethodSkin();

    static QPixmap &getAlternateIcon();
    static int getUnderLineHeight();
    static QColor &getInteractiveHighlightColor();
};
#endif

#endif
