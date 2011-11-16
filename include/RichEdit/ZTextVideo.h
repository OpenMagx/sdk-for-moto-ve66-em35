#ifndef ZTEXTVIEO_H
#define ZTEXTVIEO_H

#include "ZTextImage.h"

#include <qmap.h>
#include <qmime.h>
#include <qstring.h>

#if defined(EZX_ZN5) || defined(EZX_U9) || defined(EZX_Z6W)
class ZTextVideo;
#else
class ZTextDocument;
class QPainter;
class QColorGroup;
class QRect;

class Q_EXPORT ZTextVideo : public ZTextImage
{
    Q_OBJECT
public:
    ZTextVideo( ZTextDocument *p,const QMap<QString, QString> &attr, const QString& context,QMimeSourceFactory &factory );
    virtual ~ZTextVideo();
    virtual void draw(QPainter* p, int x, int y, int cx, int cy, int cw, int ch, const QColorGroup& cg, bool selected );

    virtual QString richText() const;

public:
	uint fix[5];
};
#endif

#endif
