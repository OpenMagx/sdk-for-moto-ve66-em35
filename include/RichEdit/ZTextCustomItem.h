#ifndef ZTEXTCURSORITEM_H
#define ZTEXTCURSORITEM_H

#include "ZTextCursor.h"
#include <qpainter.h>

class ZTextFlow;
class ZTextParagraph;
class ZTextDocument;

class Q_EXPORT ZTextCustomItem : public QObject
{
    Q_OBJECT
public:
    ZTextCustomItem(){/*???*/};
    virtual ~ZTextCustomItem();

    virtual void adjustToPainter( QPainter* );

    enum Placement {  };
    virtual Placement placement() const;

    virtual bool ownLine() const;
    virtual void resize( int nwidth );
    virtual void invalidate();

    virtual bool isNested() const;
    virtual int minimumWidth() const;

    virtual QString richText() const;

    virtual bool enter( ZTextCursor *, ZTextDocument *&doc, ZTextParagraph *&parag, int &idx, int &ox, int &oy, bool atEnd = FALSE );
    virtual bool enterAt( ZTextCursor *, ZTextDocument *&doc, ZTextParagraph *&parag, int &idx, int &ox, int &oy, const QPoint & );
    virtual bool next( ZTextCursor *, ZTextDocument *&doc, ZTextParagraph *&parag, int &idx, int &ox, int &oy );
    virtual bool prev( ZTextCursor *, ZTextDocument *&doc, ZTextParagraph *&parag, int &idx, int &ox, int &oy );
    virtual bool down( ZTextCursor *, ZTextDocument *&doc, ZTextParagraph *&parag, int &idx, int &ox, int &oy );
    virtual bool up( ZTextCursor *, ZTextDocument *&doc, ZTextParagraph *&parag, int &idx, int &ox, int &oy );

    ZTextDocument *parent;
    ZTextParagraph *parag;

    virtual void pageBreak( int  y, ZTextFlow* flow );

    QString propertyStr() const;
    bool charStop();

protected:
	uint fix[15];
};

#endif
