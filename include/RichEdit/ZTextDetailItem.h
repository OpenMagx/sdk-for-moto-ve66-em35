#ifndef ZTEXTDETAILITEM_H
#define ZTEXTDETAILITEM_H

#include "ZTextImage.h"
#include <qmap.h>
#include <qmime.h>
#include <qpainter.h>

#if defined(EZX_ZN5) || defined(EZX_U9) || defined(EZX_Z6W)
class ZTextDetailItem;
#else
class ZTextDocument;
class QColorGroup;

class Q_EXPORT ZTextDetailItem : public ZTextImage
{
    Q_OBJECT
public:
    ZTextDetailItem( ZTextDocument *p, const QMap<QString, QString> &attr, const QString& context, QMimeSourceFactory &factory );
    virtual ~ZTextDetailItem();
    virtual void draw(QPainter* p, int x, int y, int cx, int cy, int cw, int ch, const QColorGroup& cg, bool selected );
protected:
    QPixmap icon;
    int h;
};
#endif

#endif
