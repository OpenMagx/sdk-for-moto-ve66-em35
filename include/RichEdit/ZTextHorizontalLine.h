#ifndef ZTEXTHORIZONTALLINE_H
#define ZTEXTHORIZONTALLINE_H

#include "ZTextCustomItem.h"

#include <qmap.h>
#include <qmime.h>
#include <qstring.h>

#if defined(EZX_ZN5) || defined(EZX_U9) || defined(EZX_Z6W)
class ZTextHorizontalLine;
#else
class ZTextDocument;
class QPainter;
class QColorGroup;

class Q_EXPORT ZTextHorizontalLine : public ZTextCustomItem
{
public:
    ZTextHorizontalLine( ZTextDocument *p, const QMap<QString, QString> &attr, const QString& context,
			 QMimeSourceFactory &factory );
    virtual ~ZTextHorizontalLine();

    void adjustToPainter( QPainter* );
    void draw(QPainter* p, int x, int y, int cx, int cy, int cw, int ch, const QColorGroup& cg, bool selected );
    QString richText() const;

private:
	uint fix[5];

};
#endif

#endif
