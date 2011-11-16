#ifndef ZTEXTPAGESTEP_H
#define ZTEXTPAGESTEP_H

#include "ZTextImage.h"

#include <qmap.h>
#include <qmime.h>
#include <qstring.h>

#if defined(EZX_ZN5) || defined(EZX_U9) || defined(EZX_Z6W)
class ZTextFlow;
#else
class ZTextDocument;
class QPainter;
class QColorGroup;

class Q_EXPORT ZTextPageSep : public ZTextImage
{
    Q_OBJECT
public:
    ZTextPageSep( ZTextDocument *p,const QMap<QString, QString> &attr, const QString& context, QMimeSourceFactory &factory );
    virtual ~ZTextPageSep();
    
    virtual void draw(QPainter* p, int x, int y, int cx, int cy, int cw, int ch, const QColorGroup& cg, bool selected );
    virtual QString richText() const;
    QString getPageSepStr();
   
private:
	uint fix[10];
};
#endif

#endif
