#ifndef ZTEXTVSPAN_H
#define ZTEXTVSPAN_H

#include "ZTextCustomItem.h"

#include <qmap.h>
#include <qmime.h>
#include <qstring.h>

#if defined(EZX_ZN5) || defined(EZX_U9) || defined(EZX_Z6W)
class ZTextVSpan;
#else
class ZTextDocument;
class QPainter;
class QColorGroup;
class QRect;

class Q_EXPORT ZTextVSpan : public ZTextCustomItem
{
    Q_OBJECT
public:
    ZTextVSpan( ZTextDocument *p,const QMap<QString, QString> &attr, const QString& context, QMimeSourceFactory &factory );
    virtual ~ZTextVSpan();
    virtual void draw(QPainter* p, int x, int y, int cx, int cy, int cw, int ch, const QColorGroup& cg, bool selected );

    virtual QString richText() const;
};
#endif

#endif
