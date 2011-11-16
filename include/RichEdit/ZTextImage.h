#ifndef ZTEXTIMAGE_H
#define ZTEXTIMAGE_H

#include "ZTextCustomItem.h"

#include <qmap.h>
#include <qmime.h>
#include <qstring.h>

#if defined(EZX_ZN5) || defined(EZX_U9) || defined(EZX_Z6W)
class ZTextImage;
#else
class ZTextDocument;
class QPainter;
class QColorGroup;
class QRect;

class Q_EXPORT ZTextImage : public ZTextCustomItem
{
    Q_OBJECT
public:
    ZTextImage( ZTextDocument *p, const QMap<QString, QString> &attr, const QString& context,
		QMimeSourceFactory &factory );
    virtual ~ZTextImage();

    Placement placement() const;
    void adjustToPainter( QPainter* );

    QString richText() const;

    void draw( QPainter* p, int x, int y, int cx, int cy, int cw, int ch, const QColorGroup& cg, bool selected );

    void setParagraph( ZTextParagraph * pParagraph);   

private slots:
    void slotMovieUpdated(const QRect&);

signals:
    void signalDrawAnimation( ZTextImage * );
    void signalDestroy( ZTextImage * );

protected:
	uint fix[15];
};
#endif 

#endif 
