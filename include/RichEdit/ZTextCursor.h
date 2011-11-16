#ifndef ZTEXTCURSOR_H
#define ZTEXTCURSOR_H

#include <qpoint.h>

#if defined(EZX_ZN5) || defined(EZX_U9) || defined(EZX_Z6W)
class ZTextCursor;
#else
class ZTextDocument;
class ZTextParagraph;
class ZTextStringChar;
class ZMemArray<ZTextStringChar>;

class Q_EXPORT ZTextCursor
{
public:
    ZTextCursor( ZTextDocument *d = 0 );
    ZTextCursor( const ZTextCursor &c );
    virtual ~ZTextCursor();

	bool operator==( const ZTextCursor &c ) const;
	ZTextCursor &operator=( const ZTextCursor &c );

    int getCountBeforeCurrentLine();
    int getCursorIdxFromLayoutIdx();// int??? 
    int getCursorLine();
    int getLayoutIdxFromCursorIdx();// int???
    int getLeftX(int&, ZTextStringChar*, ZTextStringChar*);// int???
    int getRightX(int&, ZTextStringChar*, ZTextStringChar*);// int???
	QPoint getXY(int&, int&);// QPoint???

    ZTextDocument *document() const;
    int index() const;

    void gotoPosition( ZTextParagraph* p, int index = 0);
    void gotoLeft();
    void gotoRight();
    void gotoNextLetter();
    int  gotoPreviousLetter();
    void gotoUp();
    void gotoDown();
    void gotoLineEnd();
    void gotoLineStart();
    void gotoHome();
    void gotoEnd();
    void gotoPageUp( int visibleHeight );
    void gotoPageDown( int visibleHeight );
    void gotoNextWord( bool onlySpace = FALSE );
    void gotoPreviousWord( bool onlySpace = FALSE );
    void gotoWordLeft();
    void gotoWordRight();
    void gotoLastCharOfFormerLine();

    void insert( const QString &s, bool checkNewLine, ZMemArray<ZTextStringChar> *formatting = 0 );
    void splitAndInsertEmptyParagraph( bool ind = TRUE, bool updateIds = TRUE );
    bool remove();
    bool removePreviousChar();
    void indent();

    bool atParagStart();
    bool atParagEnd();

    int x();
    int y();

    int globalX();
    int globalY();

    int totalOffsetX() const;
    int totalOffsetY() const;

    bool place( const QPoint &pos, ZTextParagraph *s, bool link = false );
    void restoreState();

	bool isBidi();

    void fixCursorPosition();
    
private:
    void push();
    void pop();
    
    enum Operation {  };
    bool processNesting( Operation op );
    void invalidateNested();
    void gotoIntoNested( const QPoint &globalPos );

protected:
	uint fix[15];

};
#endif

#endif
