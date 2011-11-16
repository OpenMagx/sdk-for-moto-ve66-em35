#ifndef ZTEXTDOCUMENT_H
#define ZTEXTDOCUMENT_H

#include "ZRtStyleSheet.h"

#include <qobject.h>
#include <qlist.h>
#include <qmap.h>
#include <qstring.h>
#include <qvector.h>

class ZTextParagraph;
class ZTextCursor;
class ZTextCommand;
class ZTextCustomItem;
class ZTextEdit;
class ZTextFormat;
class ZTextFormatCollection;

class Q_EXPORT ZTextDocument : public QObject
{
    Q_OBJECT

public:
    ZTextDocument( ZTextDocument *p );
    ZTextDocument( ZTextDocument *d, ZTextFormatCollection *f );
    virtual ~ZTextDocument();

    QString text() const;
    QString text( int parag ) const;

    int widthUsed() const;
    int height() const;
    bool setMinimumWidth( int needed, int used = -1, ZTextParagraph *parag = 0 );

    void invalidate();

    bool hasSelection( int id, bool visible = FALSE ) const;
    void setSelectionStart( int id, const ZTextCursor &cursor );
    bool setSelectionEnd( int id, const ZTextCursor &cursor );
    void selectAll( int id );
    bool removeSelection( int id );
    void selectionStart( int id, int &paragId, int &index );
    ZTextCursor selectionStartCursor( int id );
    ZTextCursor selectionEndCursor( int id );
    void selectionEnd( int id, int &paragId, int &index );
    void setFormat( int id, ZTextFormat *f, int flags );
    void addSelection( int id );

    QString selectedText( int id, bool asRichText = FALSE ) const;
    void removeSelectedText( int id, ZTextCursor *cursor );
    void indentSelection( int id );

    ZTextParagraph *paragAt( int i ) const;

    void addCommand( ZTextCommand *cmd );
    ZTextCursor *undo( ZTextCursor *c = 0 );
    ZTextCursor *redo( ZTextCursor *c  = 0 );

    bool find( ZTextCursor &cursor, const QString &expr, bool cs, bool wo, bool forward);

    void setTextFormat( Qt::TextFormat f );
    Qt::TextFormat textFormat() const;

    bool inSelection( int selId, const QPoint &pos ) const;

    void setStyleSheet( ZRtStyleSheet *s );
    void setDefaultFormat( const QFont &font, const QColor &color );

    void setUnderlineLinks( bool b );

    void doLayout( QPainter *p, int w );
    void draw( QPainter *p, const QRect& rect, const QColorGroup &cg, const QBrush *paper = 0 );

    void drawParagraph( QPainter *p, ZTextParagraph *parag, int cx, int cy, int cw, int ch,
		    QPixmap *&doubleBuffer, const QColorGroup &cg,
		    bool drawCursor, ZTextCursor *cursor, bool resetChanged = TRUE );
    ZTextParagraph *draw( QPainter *p, int cx, int cy, int cw, int ch, const QColorGroup &cg,
		      bool onlyChanged = FALSE, bool drawCursor = FALSE, ZTextCursor *cursor = 0,
		      bool resetChanged = TRUE );

    void registerCustomItem( ZTextCustomItem *i, ZTextParagraph *p );
    void unregisterCustomItem( ZTextCustomItem *i, ZTextParagraph *p );

    void setPlainText( const QString &text );
    void setRichText( const QString &text, const QString &context );
    QString richText() const;
    QString plainText() const;

    bool focusNextPrevChild( bool next );

    int length() const;
    void clear( bool createEmptyParag = FALSE );

    virtual ZTextParagraph *createParagraph( ZTextDocument *d, ZTextParagraph *pr = 0, ZTextParagraph *nx = 0, bool updateIds = TRUE );

    bool hasFocusParagraph() const;
    QString focusHref() const;
    QString focusName() const;

    ZTextEdit* mpEditor;
    
    #if defined(EZX_ZN5) || defined(EZX_U9) || defined(EZX_Z6W)
	void setDocumentColor(QColor);
	#endif

signals:
    void minimumWidthChanged( int );

private:
    void init();
    QPixmap *bufferPixmap( const QSize &s );
    bool hasPrefix(const QChar* doc, int length, int pos, QChar c);
    bool hasPrefix(const QChar* doc, int length, int pos, const QString& s);
    ZTextCustomItem* parseTable( const QMap<QString, QString> &attr, const ZTextFormat &fmt,
				 const QChar* doc, int length, int& pos, ZTextParagraph *curpar );
    bool eatSpace(const QChar* doc, int length, int& pos, bool includeNbsp = FALSE );
    bool eat(const QChar* doc, int length, int& pos, QChar c);
    QString parseOpenTag(const QChar* doc, int length, int& pos, QMap<QString, QString> &attr, bool& emptyTag);
    QString parseCloseTag( const QChar* doc, int length, int& pos );
    QChar parseHTMLSpecialChar(const QChar* doc, int length, int& pos);
    QString parseWord(const QChar* doc, int length, int& pos, bool lower = TRUE);
    QChar parseChar(const QChar* doc, int length, int& pos, ZRtStyleSheetItem::WhiteSpaceMode wsm );
    void setRichTextInternal( const QString &text, ZTextCursor* cursor = 0 );
    void setRichTextMarginsInternal( QList< QVector<ZRtStyleSheetItem> >& styles, ZTextParagraph* stylesPar );

private:
	uint fix[60];
};


#endif
