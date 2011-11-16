#ifndef ZTEXTPHARAGRAPH_H
#define ZTEXTPHARAGRAPH_H

#include "ZRtStructureDataParser.h"

#include <qvaluelist.h>
#include <qmap.h>
#include <qpainter.h>

class ZTextParagraphPseudoDocument;
class ZTextDocument;
class ZTextString;
class ZTextStringChar;
class ZTextLineStart;
class ZTextCursor;
class ZTextTableCell;
class ZTextParagraphSelection;
class ZTextFormatCollection;
class ZTextFormatter;
class ZTextCommandHistory;

class Q_EXPORT ZTextParagraphData
{
public:
    ZTextParagraphData() {}
    virtual ~ZTextParagraphData();
    virtual void join( ZTextParagraphData * );
};

class Q_EXPORT ZTextParagraph
{
public:
    ZTextParagraph( ZTextDocument *d, ZTextParagraph *pr = 0, ZTextParagraph *nx = 0, bool updateIds = TRUE );
    ~ZTextParagraph();           

    QValueList<ZRtStructureDataParser::RT_STRUCTUREDATA> mSdList;
    
    ZTextString *string() const;
    ZTextStringChar *at( int i ) const;
    int leftGap() const;

    void setListItem( bool li );

    void setListDepth( int depth );

    ZTextParagraphPseudoDocument *pseudoDocument() const;

    void show();
    void hide();

    ZTextParagraph *prev() const;
    ZTextParagraph *next() const;
    void setPrev( ZTextParagraph *s );
    void setNext( ZTextParagraph *s );

    void insert( int index, const QString &s );
    void insert( int index, const QChar *unicode, int len );
    void append( const QString &s, bool reallyAtEnd = FALSE );
    void truncate( int index );
    void remove( int index, int len );
    void join( ZTextParagraph *s );

    void invalidate( int chr );

    void move( int &dy );
    void format( int start = -1, bool doMove = TRUE );

    bool isValid() const;
    bool hasChanged() const;
    void setChanged( bool b, bool recursive = FALSE );

    int lineHeightOfChar( int i, int *bl = 0, int *y = 0 ) const;
    ZTextStringChar *lineStartOfChar( int i, int *index = 0, int *line = 0 ) const;
    int lines() const;
    ZTextStringChar *lineStartOfLine( int line, int *index = 0 ) const;
    int lineY( int l ) const;
    int lineBaseLine( int l ) const;
    int lineHeight( int l ) const;
    void lineInfo( int l, int &y, int &h, int &bl ) const;

    void setSelection( int id, int start, int end );
    void removeSelection( int id );
    int selectionStart( int id ) const;
    int selectionEnd( int id ) const;
    bool hasSelection( int id ) const;
    bool hasAnySelection() const;
    bool fullSelected( int id ) const;

    void setEndState( int s );
    int endState() const;

    void setParagId( int i );
    int paragId() const;

    bool firstPreProcess() const;
    void setFirstPreProcess( bool b );

    void indent( int *oldIndent = 0, int *newIndent = 0 );

    void setExtraData( ZTextParagraphData *data );
    ZTextParagraphData *extraData() const;

    QMap<int, ZTextLineStart*> &lineStartList();

    void setFormat( int index, int len, ZTextFormat *f, bool useCollection = TRUE, int flags = -1 );

    void setAlignment( int a );
    int alignment() const;

    void paint( QPainter &painter, const QColorGroup &cg, ZTextCursor *cursor = 0, bool drawSelections = FALSE,
			int clipx = -1, int clipy = -1, int clipw = -1, int cliph = -1 );

    int topMargin() const;
    int bottomMargin() const;
    int leftMargin() const;
    int firstLineMargin() const;
    int rightMargin() const;
    int lineSpacing() const;

    void registerFloatingItem( ZTextCustomItem *i );
    void unregisterFloatingItem( ZTextCustomItem *i );

    ZTextTableCell *tableCell() const;

    QBrush *background() const;

    int documentWidth() const;
    int documentVisibleWidth() const;
    int documentX() const;
    int documentY() const;
    ZTextFormatCollection *formatCollection() const;
    ZTextFormatter *formatter() const;

    int nextTab( int i, int x );
    int *tabArray() const;
    void setTabArray( int *a );
    void setTabStops( int tw );

    void adjustToPainter( QPainter *p );

    void setNewLinesAllowed( bool b );
    bool isNewLinesAllowed() const;

    QString richText() const;

    void addCommand( ZTextCommand *cmd );
    ZTextCursor *undo( ZTextCursor *c = 0 );
    ZTextCursor *redo( ZTextCursor *c  = 0 );
    ZTextCommandHistory *commands() const;
    void copyParagData( ZTextParagraph *parag );


    void setBackgroundColor( const QColor &c );
    void clearBackgroundColor();

    void setDirection( QChar::Direction d );
    QChar::Direction direction() const;

    void readStyleInformation( QDataStream& stream );
    void writeStyleInformation( QDataStream& stream ) const;
    
    //
	ZTextStringChar *getFirstVisualCharLB(ZTextStringChar*, int const&);
	ZTextStringChar *getLastVisualCharRB(ZTextStringChar*, int const&);
	ZTextStringChar *getLineOfChar(ZTextStringChar*);
	//
    

protected:
    void setColorForSelection( QColor &c, QPainter &p, const QColorGroup& cg, int selection );
    void drawLabel( QPainter* p, int x, int y, int w, int h, int base, const QColorGroup& cg );
    void drawString( QPainter &painter, QRect &rect, const QString &str, int start, int len, int xstart,
			     int y, int baseLine, int w, int h, bool drawSelections, int fullSelectionWidth,
			     ZTextStringChar *formatChar, const QColorGroup& cg,
			     bool rightToLeft );
			     
private:
    QMap<int, ZTextParagraphSelection> &selections() const;
    QList<ZTextCustomItem> &floatingItems() const;
    void invalidateStyleCache();
    
protected:    
	uint fix[50];
};


#endif
