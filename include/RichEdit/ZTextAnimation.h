#ifndef ZTEXTANIMATION_H
#define ZTEXTANIMATION_H

#include <qstring.h>
#include <qmap.h>
#include <qmime.h>
#include <qpainter.h>

#include "ZTextCustomItem.h"

#if defined(EZX_ZN5) || defined(EZX_U9) || defined(EZX_Z6W)
class ZTextAnimation;
#else
class ZTextDocument;

class Q_EXPORT ZTextAnimation : public ZTextCustomItem
{
    Q_OBJECT
public:
    ZTextAnimation( ZTextDocument *p,const QMap<QString, QString> &attr, const QString& context, QMimeSourceFactory &factory );
    virtual ~ZTextAnimation();
    
    virtual void draw(QPainter* p, int x, int y, int cx, int cy, int cw, int ch, const QColorGroup& cg, bool selected );
    virtual QString richText() const;
};
#endif

#endif
