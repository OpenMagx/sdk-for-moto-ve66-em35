#ifndef ZTEXTFLOW_H
#define ZTEXTFLOW_H

#include "ZTextCustomItem.h"

#if defined(EZX_ZN5) || defined(EZX_U9) || defined(EZX_Z6W)
class ZTextFlow;
#else
class QPainter;
class QColorGroup;

class Q_EXPORT ZTextFlow
{
public:
    ZTextFlow();
    virtual ~ZTextFlow();

    virtual void setWidth( int width );
    int width() const;

    virtual void setPageSize( int ps );

    virtual int adjustLMargin( int yp, int h, int margin, int space );
    virtual int adjustRMargin( int yp, int h, int margin, int space );

    virtual void registerFloatingItem( ZTextCustomItem* item );
    virtual void unregisterFloatingItem( ZTextCustomItem* item );
    virtual QRect boundingRect() const;
    virtual void drawFloatingItems(QPainter* p, int cx, int cy, int cw, int ch, const QColorGroup& cg, bool selected );

    virtual int adjustFlow( int  y, int w, int h );

    virtual bool isEmpty();

    void clear();

private:
	uint fix[5];
};
#endif

#endif
