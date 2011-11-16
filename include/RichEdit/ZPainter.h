#ifndef ZPAINTER_H
#define ZPAINTER_H

#include "qpainter.h"

#if defined(EZX_ZN5) || defined(EZX_U9) || defined(EZX_Z6W)
class ZPainter;
#else
class ZPainter
{
public:
    ZPainter();
    ~ZPainter();

    enum TextDirection { Auto, RTL, LTR };
    enum CoordinateMode { Coord1, Coord2 };
	
    static void drawText( QPainter &painter, int x, int y, const QString &, int = -1, TextDirection dir = Auto );
    static void drawText( QPainter &painter, const QPoint &, const QString &, int = -1, TextDirection dir = Auto );
    static void drawText( QPainter &painter, int x, int y, const QString &, int, int, TextDirection dir = Auto );
    static void drawText( QPainter &painter, const QPoint &, const QString &, int, int, TextDirection dir = Auto );
    static QRegion clipRegion(QPainter &painter, CoordinateMode );
    static void setClipRegion(QPainter &painter, const QRegion &, CoordinateMode = Coord1 );
    static void drawPixmap( QPainter &painter, const QRect &, const QPixmap & );
};
#endif

#endif
