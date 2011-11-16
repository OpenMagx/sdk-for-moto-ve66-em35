#ifndef ZTEXTHSPAN_H
#define ZTEXTHSPAN_H

#include "ZTextCustomItem.h"

#include <qmap.h>
#include <qmime.h>
#include <qstring.h>

#if defined(EZX_ZN5) || defined(EZX_U9) || defined(EZX_Z6W)
class ZTextHSpan;
#else
class ZTextDocument;
class QPainter;
class QColorGroup;

class Q_EXPORT ZTextHSpan : public ZTextCustomItem
{
    Q_OBJECT
public:
    ZTextHSpan( ZTextDocument *p,const QMap<QString, QString> &attr, const QString& context,
                QMimeSourceFactory &factory );
    virtual ~ZTextHSpan();
    virtual void draw(QPainter* p, int x, int y, int cx, int cy, int cw, int ch, const QColorGroup& cg, bool selected );

    virtual QString richText() const;
};
#endif

#endif
