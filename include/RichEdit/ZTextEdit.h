#ifndef ZTEXTEDIT_H
#define ZTEXTEDIT_H

#include <ZScrollPanel.h>
#include <qmap.h>

#include "ZRtStyleSheet.h"
#include "ZRtStructureDataParser.h"

enum AnchorAttribute {
    AnchorName,
    AnchorHref
};

class QPainter;
class ZTextDocument;
class ZTextCursor;
class QKeyEvent;
class QResizeEvent;
class QMouseEvent;
class QTimer;
class ZTextCommand;
class ZTextParagraph;
class ZTextFormat;
class QFont;
class QColor;
class ZTextString;
class QSyntaxHighlighter;

class ZTextEditPrivate;

class Q_EXPORT ZTextEdit : public ZScrollPanel
{
    Q_OBJECT
public:
    enum WordWrap {
	NoWrap,
	WidgetWidth,
	FixedPixelWidth,
	FixedColumnWidth
    };

    enum WrapPolicy {
	AtWordBoundary,
	AtWhiteSpace = AtWordBoundary,
	Anywhere,
	AtWordOrDocumentBoundary
    };

    enum AutoFormatting {
	AutoNone = 0,
	AutoBulletList = 0x00000001,
	AutoAll = 0xffffffff
    };

    enum KeyboardAction {
	ActionBackspace,
	ActionDelete,
	ActionReturn,
	ActionKill,
	ActionWordBackspace,
	ActionWordDelete
    };

    enum CursorAction {
	MoveBackward,
	MoveForward,
	MoveWordBackward,
	MoveWordForward,
	MoveUp,
	MoveDown,
	MoveLineStart,
	MoveLineEnd,
	MoveHome,
	MoveEnd,
	MovePgUp,
	MovePgDown
    };

    enum VerticalAlignment {
	AlignNormal,
	AlignSuperScript,
	AlignSubScript
    };

    enum TextInsertionFlags {
	RedoIndentation = 0x0001,
	CheckNewLines = 0x0002,
	RemoveSelected = 0x0004
    };

    #if defined(EZX_ZN5) || defined(EZX_U9) || defined(EZX_Z6W)
    ZTextEdit( const QString& text, const QString& context = QString::null, bool bEnableBkImage=false, QWidget* parent=0, const char* name=0, int, bool);
    ZTextEdit( bool bEnableBkImage=false, QWidget* parent=0, const char* name=0, int, bool);
	ZTextEdit(QString const&, QString const&, QWidget* parent=0, char const* name=0, int, bool);
	ZTextEdit(QWidget* parent=0, char const* name=0, int=0, bool=1);
	#else
    ZTextEdit( const QString& text, const QString& context = QString::null, bool bEnableBkImage=false, QWidget* parent=0, const char* name=0);
    ZTextEdit( bool bEnableBkImage=false, QWidget* parent=0, const char* name=0 );
	ZTextEdit(QString const&, QString const&, QWidget* parent=0, char const* name=0);
	ZTextEdit(QWidget* parent=0, char const* name=0);	
	#endif
    virtual ~ZTextEdit();

    void ensureDisplayLastPage();
    virtual void beforeInsertTextFromIm( QPoint pos, QPoint &newPos );
    void textChangedFromIm(int);
    
    QColorGroup::ColorRole backgroundRoleFromMode( BackgroundMode mode);
    void setEraseColor( const QColor & color ); 
    void setInputMethodEnabled( bool b );
    void repaintContents( bool erase=TRUE );  
    bool isHorizontalSliderPressed();  
    bool isVerticalSliderPressed();   
    void updateContents();
    void setPaletteBackgroundColor( const QColor &color, QWidget *pWidget); 

    QRect contentsToViewportEx(const QRect& rt);

    void setLeftMargin(int left);

    void setDefaultHighlight(uint index);
    void gotoSd(uint index, bool repaint=true);
    bool getSd( uint index, ZRtStructureDataParser::RT_STRUCTUREDATA &sd);
    void gotoSd(ZRtStructureDataParser::RT_STRUCTUREDATA &sd, bool repaint=true);
    bool getCurrentHighlightItem( ZRtStructureDataParser::RT_STRUCTUREDATA &sd);
    bool getPreviousSd( ZRtStructureDataParser::RT_STRUCTUREDATA &sd );
    bool getNextSd( ZRtStructureDataParser::RT_STRUCTUREDATA &sd );
    bool isSdVisible(ZRtStructureDataParser::RT_STRUCTUREDATA &sd, bool entirely = false);
    bool isCharVisible( int paragraph, int index );
  
    short getLineWidth();
        
    QString text() const;
    QString text( int para ) const;
    TextFormat textFormat() const;
    QString context() const;
    QString documentTitle() const;

    void getSelection( int *paraFrom, int *indexFrom, int *paraTo, int *indexTo, int selNum = 0 ) const;

    int paragraphs() const;
    int lines() const;
    int linesOfParagraph( int para ) const;
    int length() const;
    int paragraphLength( int para ) const;

    QMimeSourceFactory* mimeSourceFactory() const;

    QBrush paper() const;
    bool linkUnderline() const;


    bool hasSelectedText() const;
    QString selectedText() const;

    WordWrap wordWrap() const;
    int wrapColumnOrWidth() const;
    WrapPolicy wrapPolicy() const;

    void getCursorPosition( int *parag, int *index ) const;

    bool isModified() const;
    virtual void setModified( bool m );
    bool italic() const;
    bool bold() const;
    bool underline() const;
    QColor color() const;
    int alignment() const;

    QColor paragraphBackgroundColor( int para ) const;
    bool eventFilter( QObject *o, QEvent *e );

    void drawBackgroundEzx(QPainter& painter, int x, int y, const QRect& rect);
    ZSkinBase* getDetailItemSkin();
    ZSkinBase* getImageItemSkin();
    
    //
    void cursorLeft(bool);
    void cursorRight(bool);
    void cursorRightFinish(bool, int);
    void disableKey(int const&);
    
    bool getCapsLockAvailable();
    int getInputModeCursorModel();
    QString getLayoutString();
    int getMaxTextLength();
    
    void setCapsLockAvailable(bool);
    void setCursorFlagByNewChar(QChar const*);
    enum CursorFlagDirection { CF_NONE, CF_RTL, CF_LTR };
    void setCursorFlagDirection( CursorFlagDirection );
    enum CursorFlagExist { CF__NONE, CF_YES };
    void setCursorFlagExist( CursorFlagExist );
    void setInputModeCursorModel(int);
    void setMaxLength(int);
    void setMaxTextLength(int);

	void specialInputModeCursorModel(bool);
	void updateModelBeforeInsert(QString const&);
	
    #if defined(EZX_ZN5) || defined(EZX_U9) || defined(EZX_Z6W)
	void decreaseEmoticonsPlaying();
	void disableSdHighlight();
	void enableSdHighlight();
	int  getAnimationCycles();
	void getEmoticonsPlaying();
	int  getImlen();
	int  getim();
	void getMediaSdName(ZRtStructureDataParser::RT_STRUCTUREDATA, QString&);
	void getParaModel();
	QUuid getTextEntryMode();
	void highlightBottomVisibleSd(int, int);
	void highlightTopVisibleSd(int, int);
	int im;
	void increaseEmoticonsPlaying();
	bool isExplicitlyDisabledSd(ZRtStructureDataParser::RT_STRUCTUREDATA);
	void playNewEmoticons();
	void playOrStopEmoticonsOfPara(int, int, int, bool);
	void playScrolledEmoticons(int);
	void resetPmTimer();
	void setAnimationCycles(int);
	void setim(int);
	void setImlen(int);
	void setPaddingProp(ZWidgetPaddingInfo const&);
	void setTextEntryMode(QUuid const&);
	int total;
	#endif	
	
    //

public slots:
    void setEnabled( bool );
    virtual void setMimeSourceFactory( QMimeSourceFactory* factory );
    virtual void setPaper( const QBrush& pap );
    virtual void setLinkUnderline( bool );

    virtual void setWordWrap( WordWrap mode );
    virtual void setWrapColumnOrWidth( int );
    virtual void setWrapPolicy( WrapPolicy policy );

    virtual void append( const QString& text );

    virtual void setText( const QString &txt, const QString &context );
    virtual void setTextFormat( TextFormat f );

    virtual void selectAll( bool select = TRUE );
    virtual void setReadOnly( bool b );

    virtual void clear();
    virtual void del();
    virtual void backspace();
    virtual void indent();
    virtual void setItalic( bool b );
    virtual void setBold( bool b );
    virtual void setUnderline( bool b );
    virtual void setColor( const QColor &c );
    virtual void setVerticalAlignment( VerticalAlignment a );
    virtual void setAlignment( int a );


    virtual void setCursorPosition( int parag, int index );
    virtual void setSelection( int parag_from, int index_from, int parag_to, int index_to, int selNum = 0);
    virtual void setSelectionAttributes( int selNum, const QColor &back, bool invertText );
    virtual void moveCursor( CursorAction action, bool select );
    virtual void doKeyboardAction( KeyboardAction action );
    virtual void removeSelectedText( int selNum = 0 );
    virtual void removeSelection( int selNum = 0 );


    void insert( const QString &text, uint insertionFlags = CheckNewLines | RemoveSelected );


    virtual void insertAt( const QString &text, int para, int index );
    virtual void removeParagraph( int para );
    virtual void insertParagraph( const QString &text, int para );

    virtual void setParagraphBackgroundColor( int para, const QColor &bg );
    virtual void clearParagraphBackground( int para );

    void sentEventEndComposition();

signals:
    void signalBeforeInsertTextFromIm(QPoint pos, QPoint &newPos);	
    void textChangedByIM(int);
    void textChanged();
    void undoAvailable( bool yes );
    void redoAvailable( bool yes );
    void currentFontChanged( const QFont &f );
    void currentColorChanged( const QColor &c );
    void currentAlignmentChanged( int a );
    void currentVerticalAlignmentChanged( VerticalAlignment a );
    void cursorPositionChanged( ZTextCursor *c );
    void cursorPositionChanged( int para, int pos );
    void returnPressed();
    void modificationChanged( bool m );
    void clicked( int parag, int index );
    void doubleClicked( int parag, int index );

    void endOfText();
    void topOfText();
 

protected:
    void doSetSelection(int paraFrom, int indexFrom, int paraTo, int indexTo, int selNum, bool repaint=true);
    void repaintChanged();
    void updateStyles();
    void drawContents( QPainter *p, int cx, int cy, int cw, int ch );
    bool event( QEvent *e );
    void keyPressEvent( QKeyEvent *e );
    void clrkeyRemoveMultiple(QKeyEvent *e); 
    void resizeEvent( QResizeEvent *e );
    void viewportResizeEvent( QResizeEvent* );

    bool focusNextPrevChild( bool next );
    void setDocument( ZTextDocument *doc );
    
    void drawCursor( bool visible );

    void windowActivationChange( bool );

    void timerEvent(QTimerEvent*);
    
public /*protected*/ slots:
    void slotTextChanged();
    
    void slotSetDefaultHightSd();
    virtual void scrollToBottom();
    virtual void doChangeInterval();
    void sliderReleased();

    virtual void setStyleSheet( ZRtStyleSheet* styleSheet );
    virtual void scrollToAnchor( const QString& name );
    virtual void setTabStopWidth( int ts );

    virtual void sync();
    virtual void undo();
    virtual void redo();
    virtual void setFamily( const QString &f );
    virtual void setPointSize( int s );
    virtual void setFont( const QFont &f );
    virtual void setParagType( ZRtStyleSheetItem::DisplayMode dm, ZRtStyleSheetItem::ListStyle listStyle );
    virtual void resetFormat();
    virtual void setFormat( ZTextFormat *f, int flags );
    virtual void ensureCursorVisible();
    virtual void placeCursor( const QPoint &pos, ZTextCursor *c = 0 );

    virtual void setUndoRedoEnabled( bool b );
    void setTabChangesFocus( bool b );
    void polish();
    void setMaxLogLines( int numLines );
    int maxLogLines();
    virtual void insert( const QString &text, bool indent, bool checkNewLine, bool removeSelected = TRUE ); //----GAO BING


private slots:
    void formatMore();
    void doResize();
    void blinkCursor();
    void setModified();
    void documentWidthChanged( int w );

    void changeCursor(int sp);

private:
    struct Q_EXPORT UndoRedoInfo 
    {
		UndoRedoInfo( ZTextDocument *dc );
		~UndoRedoInfo();
		void clear();
		bool valid() const;
		
		enum Type {};

		uint fix[10];
    };

private:
    void setPalette( const QPalette & );
    int lineOfChar( int para, int chr );
    QRect paragraphRect( int para ) const;
    int paragraphAt( const QPoint &pos ) const;
    int charAt( const QPoint &pos, int *para ) const;
    ZRtStyleSheet* styleSheet() const;
    bool isUndoAvailable() const;
    bool isRedoAvailable() const;
    int heightForWidth( int w ) const;

    int tabStopWidth() const;

    QString anchorAt( const QPoint& pos );
    QString anchorAt( const QPoint& pos, AnchorAttribute a );

    QSize sizeHint() const;
    bool isUndoRedoEnabled() const;
    QFont font() const;
    QFont currentFont() const;
    QString family() const;
    int pointSize() const;

    virtual bool getFormat( int para, int index, QFont *font, QColor *color, VerticalAlignment *verticalAlignment );

    virtual bool getParagraphFormat( int para, QFont *font, QColor *color,
				     VerticalAlignment *verticalAlignment, int *alignment,
				     ZRtStyleSheetItem::DisplayMode *displayMode,
				     ZRtStyleSheetItem::ListStyle *listStyle,
				     int *listDepth );

    bool tabChangesFocus() const;

    void setAutoFormatting( uint features );
    uint autoFormatting() const;
    virtual void setUndoDepth( int d );
    int undoDepth() const;
    QSyntaxHighlighter *syntaxHighlighter() const;

    void updateCursor( const QPoint & pos );

    void drawContents( QPainter * );
    void init();
    void checkUndoRedoInfo( UndoRedoInfo::Type t );
    void updateCurrentFormat();
    bool handleReadOnlyKeyEvent( QKeyEvent *e );
    void makeParagVisible( ZTextParagraph *p );

    void setFontInternal( const QFont &f );

    void readFormats( ZTextCursor &c1, ZTextCursor &c2, ZTextString &text, bool fillStyles = FALSE );
    void paintDocument( bool drawAll, QPainter *p, int cx = -1, int cy = -1, int cw = -1, int ch = -1 );
    void moveCursor( CursorAction action );
    void ensureFormatted( ZTextParagraph *p );
    void placeCursor( const QPoint &pos, ZTextCursor *c, bool link );
    void updateMicroFocusHint();

private:
	uint fix[150];
	ZTextEditPrivate * p;
};

#endif
