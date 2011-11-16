#ifndef ZTEXTTABLE
#define ZTEXTTABLE

#include "ZTextCustomItem.h"
#include "ZRtStyleSheet.h"

#include <qmap.h>
#include <qmime.h>
#include <qstring.h>
#include <qlayout.h>
#include <qsize.h>

#if defined(EZX_ZN5) || defined(EZX_U9) || defined(EZX_Z6W)
class ZTextTable;
class ZTextTableCell;
#else
class ZTextDocument;
class ZTextCursor;
class ZTextDocument;
class ZTextParagraph;
class ZTextFormat;
class ZTextTable;
class QPainter;
class QColorGroup;
class QRect;

class Q_EXPORT ZTextTableCell : public QLayoutItem
{
public:
    ZTextTableCell( ZTextTable* table,
		    int row, int column,
		    const QMap<QString, QString> &attr,
		    const ZRtStyleSheetItem* style,
		    const ZTextFormat& fmt, const QString& context,
		    QMimeSourceFactory &factory, ZRtStyleSheet *sheet, const QString& doc );
    virtual ~ZTextTableCell();

    QSize sizeHint() const ;
    QSize minimumSize() const ;
    QSize maximumSize() const ;
    QSizePolicy::ExpandData expanding() const;
    bool isEmpty() const;
    void setGeometry( const QRect& ) ;
    QRect geometry() const;

    bool hasHeightForWidth() const;
    int heightForWidth( int ) const;

    void adjustToPainter( QPainter* );


    void draw( QPainter* p, int x, int y, int cx, int cy, int cw, int ch, const QColorGroup& cg, bool selected );

    virtual void invalidate();

    int verticalAlignmentOffset() const;
    int horizontalAlignmentOffset() const;

private:
	uint fix[20];
};

class Q_EXPORT ZTextTable: public ZTextCustomItem
{
public:
    ZTextTable( ZTextDocument *p, const QMap<QString, QString> &attr );
    virtual ~ZTextTable();

    void adjustToPainter( QPainter *p );
    void pageBreak( int  y, ZTextFlow* flow );
    void draw( QPainter* p, int x, int y, int cx, int cy, int cw, int ch,
	       const QColorGroup& cg, bool selected );

    void resize( int nwidth );
    virtual void invalidate();

    virtual bool enter( ZTextCursor *c, ZTextDocument *&doc, ZTextParagraph *&parag, int &idx, int &ox, int &oy, bool atEnd = FALSE );
    virtual bool enterAt( ZTextCursor *c, ZTextDocument *&doc, ZTextParagraph *&parag, int &idx, int &ox, int &oy, const QPoint &pos );
    virtual bool next( ZTextCursor *c, ZTextDocument *&doc, ZTextParagraph *&parag, int &idx, int &ox, int &oy );
    virtual bool prev( ZTextCursor *c, ZTextDocument *&doc, ZTextParagraph *&parag, int &idx, int &ox, int &oy );
    virtual bool down( ZTextCursor *c, ZTextDocument *&doc, ZTextParagraph *&parag, int &idx, int &ox, int &oy );
    virtual bool up( ZTextCursor *c, ZTextDocument *&doc, ZTextParagraph *&parag, int &idx, int &ox, int &oy );

    QString richText() const;

    int minimumWidth() const;

    void setParagraph(ZTextParagraph *p);

private:
    void format( int w );
    void addCell( ZTextTableCell* cell );

private:
	uint fix[30];
};
#endif

#endif
