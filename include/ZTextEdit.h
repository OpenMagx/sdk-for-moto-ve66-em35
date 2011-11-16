#ifndef ZTEXTEDIT_H
#define ZTEXTEDIT_H

#include "ZScrollPanel.h"


class ZTextDocument;
struct QUndoRedoInfoPrivate;
class ZTextFormat;
class ZTextCursor;
class ZTextParagraph;
class ZRtStyleSheet;
class ZTextString;
class QPainter;
class QKeyEvent;
class QResizeEvent;
class QMouseEvent;
class QFont;
class QColor;


enum AnchorAttribute {
    AnchorName,
    AnchorHref
};



class ZTextEdit : public ZScrollPanel
{
	Q_OBJECT
	uint temp[20];
	
private:

    struct UndoRedoInfo 
    {	
	enum Type { Invalid, Insert, Delete, Backspace, Return, RemoveSelected, Format, Style };
	
	~UndoRedoInfo();		 // FUNC
	UndoRedoInfo(ZTextDocument*);		 // FUNC	
	
	void clear();		 // FUNC
	bool valid() const;		 // FUNC
    };
    
public:

    enum VerticalAlignment {
	AlignNormal,
	AlignSuperScript,
	AlignSubScript
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
    
	enum CursorFlagDirection {};
	enum CursorFlagExist {};

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
    
	ZTextEdit(bool, QWidget*, char const*, int, bool);
	ZTextEdit(const QString& text, const QString& context = QString::null, bool bEnableBkImage=false,QWidget* parent=0, const char* name=0, int, bool);		
	ZTextEdit(const QString& text, const QString& context,QWidget* parent=0, const char* name=0, int, bool);	
	ZTextEdit(QWidget*, char const*, int, bool);
	~ZTextEdit();   

	int alignment() const;		 // FUNC
	QString anchorAt(QPoint const&, AnchorAttribute);		 // FUNC
	QString anchorAt(QPoint const&);		 // FUNC
	void append(QString const&);		 // FUNC
	void autoFormatting() const;		 // FUNC
	void backgroundRoleFromMode(QWidget::BackgroundMode);		 // FUNC
	void backspace();		 // FUNC
	void beforeInsertTextFromIm(QPoint, QPoint&);		 // FUNC
	void blinkCursor();		 // FUNC
	void bold() const;		 // FUNC
	void changeCursor(int);		 // FUNC
	void charAt(QPoint const&, int*) const;		 // FUNC
	void checkUndoRedoInfo(UndoRedoInfo::Type);		 // FUNC
	void clearParagraphBackground(int);		 // FUNC
	void clear();		 // FUNC
	void clicked(int, int);		 // FUNC
	void clrkeyRemoveMultiple(QKeyEvent*);		 // FUNC
	QColor color() const;		 // FUNC
	QString context() const;		 // FUNC
	void currentAlignmentChanged(int);		 // FUNC
	void currentColorChanged(QColor const&);		 // FUNC
	void currentFontChanged(QFont const&);		 // FUNC
	void currentFont() const;		 // FUNC
	void currentVerticalAlignmentChanged(VerticalAlignment);		 // FUNC
	void cursorLeft(bool);		 // FUNC
	void cursorPositionChanged(int, int);		 // FUNC
	void cursorPositionChanged(ZTextCursor*);		 // FUNC
	void cursorRight(bool);		 // FUNC
	void cursorRightFinish(bool, int);		 // FUNC
	void decreaseEmoticonsPlaying();		 // FUNC
	void del();		 // FUNC
	void disableKey(int const&);		 // FUNC
	void disableSdHighlight();		 // FUNC
	void doChangeInterval();		 // FUNC
	QString documentTitle() const;		 // FUNC
	void documentWidthChanged(int);		 // FUNC
	void doKeyboardAction(KeyboardAction);		 // FUNC
	void doResize();		 // FUNC
	void doSetSelection(int, int, int, int, int, bool, bool);		 // FUNC
	void doubleClicked(int, int);		 // FUNC
	void drawBackgroundEzx(QPainter&, int, int, QRect const&);	 // FUNC
	void drawContents(QPainter*, int, int, int, int);		 // FUNC
	void drawContents(QPainter*);		 // FUNC
	void drawCursor(bool);		 // FUNC
	void enableSdHighlight();		 // FUNC
	void endOfText();		 // FUNC
	void ensureCursorVisible();		 // FUNC
	void ensureDisplayLastPage();		 // FUNC
	void ensureFormatted(ZTextParagraph*);		 // FUNC
	bool eventFilter(QObject*, QEvent*);		 // FUNC
	bool event(QEvent*);		 // FUNC
	void family() const;		 // FUNC
	bool focusNextPrevChild(bool);		 // FUNC
	QFont font() const;		 // FUNC
	void formatMore();		 // FUNC
	void getAnimationCycles();		 // FUNC
	bool getCurrentHighlightItem(/*ZRtStructureDataParser::RT_STRUCTUREDATA*/int&);		 // FUNC
	void getCursorPosition(int*, int*) const;		 // FUNC
	void getDetailItemSkin();		 // FUNC
	void getEmoticonsPlaying();		 // FUNC
	void getFormat(int, int, QFont*, QColor*, VerticalAlignment*);		 // FUNC
	void getImageItemSkin();		 // FUNC
	void getImlen();		 // FUNC
	void getim();		 // FUNC
	void getInputModeCursorModel();		 // FUNC
	void getLayoutString();		 // FUNC
	void getLineWidth();		 // FUNC
	void getMaxTextLength();		 // FUNC
	void getMediaSdName(/*ZRtStructureDataParser::RT_STRUCTUREDATA*/int, QString&);		 // FUNC
	void getNextSd(/*ZRtStructureDataParser::RT_STRUCTUREDATA*/int&);	 // FUNC
	void getParagraphFormat(int, QFont*, QColor*, VerticalAlignment*, int*, /*ZRtStyleSheetItem::DisplayMode*/int*, /*ZRtStyleSheetItem::ListStyle*/int*, int*);		 // FUNC
	void getParaModel();		 // FUNC
	void getPreviousSd(/*ZRtStructureDataParser::RT_STRUCTUREDATA*/int&);	 // FUNC
	bool getSd(unsigned int, /*ZRtStructureDataParser::RT_STRUCTUREDATA*/int&);		 // FUNC
	void getSelection(int*, int*, int*, int*, int) const;		 // FUNC
	void getTextEntryMode();		 // FUNC
	void gotoSd(unsigned int, bool);		 // FUNC
	void gotoSd(/*ZRtStructureDataParser::RT_STRUCTUREDATA*/int&, bool, bool);		 // FUNC
	void handleReadOnlyKeyEvent(QKeyEvent*);		 // FUNC
	bool hasSelectedText() const;		 // FUNC
	int heightForWidth(int) const;		 // FUNC
	void highlightBottomVisibleSd(int, int);		 // FUNC
	void highlightTopVisibleSd(int, int);		 // FUNC
	void increaseEmoticonsPlaying();		 // FUNC
	void indent();		 // FUNC
	void init();		 // FUNC
	void insertAt(QString const&, int, int);		 // FUNC
	void insertParagraph(QString const&, int);		 // FUNC
	void insert(QString const&, bool, bool, bool);		 // FUNC
	void insert(QString const&, unsigned int);		 // FUNC
	void isCharVisible(int, int);		 // FUNC
	void isExplicitlyDisabledSd(/*ZRtStructureDataParser::RT_STRUCTUREDATA*/int);		 // FUNC
	void isHorizontalSliderPressed();		 // FUNC
	void isModified() const;		 // FUNC
	void isRedoAvailable() const;		 // FUNC
	void isSdVisible(/*ZRtStructureDataParser::RT_STRUCTUREDATA*/int&, bool); // FUNC
	void isUndoAvailable() const;		 // FUNC
	void isUndoRedoEnabled() const;		 // FUNC
	void isVerticalSliderPressed();		 // FUNC
	void italic() const;		 // FUNC
	void keyPressEvent(QKeyEvent*);		 // FUNC
	void keyReleaseEvent(QKeyEvent*);		 // FUNC
	void length() const;		 // FUNC
	void lineOfChar(int, int);		 // FUNC
	void lines() const;		 // FUNC
	void linesOfParagraph(int) const;		 // FUNC
	void linksEnabled() const;		 // FUNC
	void linkUnderline() const;		 // FUNC
	void makeParagVisible(ZTextParagraph*);		 // FUNC
	void maxLogLines();		 // FUNC
	void mimeSourceFactory() const;		 // FUNC
	void modificationChanged(bool);		 // FUNC
	void moveCursor(CursorAction, bool);		 // FUNC
	void moveCursor(CursorAction);		 // FUNC
	void omgProcessSDScroll(QKeyEvent*);		 // FUNC
	void omgProcessTextEntryScroll(QKeyEvent*);		 // FUNC
	void paintDocument(bool, QPainter*, int, int, int, int);		 // FUNC
	void paper() const;		 // FUNC
	void paragraphAt(QPoint const&) const;		 // FUNC
	void paragraphBackgroundColor(int) const;		 // FUNC
	void paragraphLength(int) const;		 // FUNC
	void paragraphRect(int) const;		 // FUNC
	void paragraphs() const;		 // FUNC
	void placeCursor(QPoint const&, ZTextCursor*, bool);		 // FUNC
	void placeCursor(QPoint const&, ZTextCursor*);		 // FUNC
	void playNewEmoticons();		 // FUNC
	void playOrStopEmoticonsOfPara(int, int, int, bool);		 // FUNC
	void playScrolledEmoticons(int);		 // FUNC
	void pointSize() const;		 // FUNC
	void polish();		 // FUNC
	void readFormats(ZTextCursor&, ZTextCursor&, ZTextString&, bool); // FUNC
	void redoAvailable(bool);		 // FUNC
	void redo();		 // FUNC
	void removeParagraph(int);		 // FUNC
	void removeSelectedText(int);		 // FUNC
	void removeSelection(int);		 // FUNC
	void repaintChanged();		 // FUNC
	void repaintContents(bool);		 // FUNC
	void resetFormat();		 // FUNC
	void resetPmTimer();		 // FUNC
	void resizeEvent(QResizeEvent*);		 // FUNC
	void returnPressed();		 // FUNC
	void scrollToAnchor(QString const&);		 // FUNC
	void scrollToBottom();		 // FUNC
	void selectAll( bool select = TRUE );		 // FUNC
	QString selectedText() const;		 // FUNC
	void sentEventEndComposition();		 // FUNC
	void setAlignment(int);		 // FUNC
	void setAnimationCycles(int);		 // FUNC
	void setAutoFormatting(unsigned int);		 // FUNC
	void setBold(bool);		 // FUNC
	void setColor(QColor const&);		 // FUNC
	void setCurrentFont(QFont const&);		 // FUNC
	void setCursorFlagByNewChar(QChar const*);		 // FUNC
	void setCursorFlagDirection(CursorFlagDirection);	 // FUNC
	void setCursorFlagExist(CursorFlagExist);		 // FUNC
	void setCursorPosition(int, int);		 // FUNC
	void setDefaultHighlight(unsigned int);		 // FUNC
	void setDocument(ZTextDocument*);		 // FUNC
	void setEnabled(bool);		 // FUNC
	void setEraseColor(QColor const&);		 // FUNC
	void setFamily(QString const&);		 // FUNC
	void setFontInternal(QFont const&);		 // FUNC
	void setFont(QFont const&);		 // FUNC
	void setFormat(ZTextFormat*, int);		 // FUNC
	void setim(int);		 // FUNC
	void setImlen(int);		 // FUNC
	void setInputMethodEnabled(bool);		 // FUNC
	void setInputModeCursorModel(int);		 // FUNC
	void setItalic(bool);		 // FUNC
	void setLeftMargin(int);		 // FUNC
	void setLinkUnderline(bool);		 // FUNC
	void setMaxLength(int);		 // FUNC
	void setMaxLogLines(int);		 // FUNC
	void setMaxTextLength(int);		 // FUNC
	void setMimeSourceFactory(QMimeSourceFactory*);		 // FUNC
	void setModified(bool);		 // FUNC
	void setModified();		 // FUNC
	void setOverwriteMode(bool);		 // FUNC
	void setPaddingProp(ZWidgetPaddingInfo const&);		 // FUNC
	void setPaletteBackgroundColor(QColor const&, QWidget*);		 // FUNC
	void setPalette(QPalette const&);		 // FUNC
	void setPaper(QBrush const&);		 // FUNC
	void setParagraphBackgroundColor(int, QColor const&);		 // FUNC
	void setParagType(/*ZRtStyleSheetItem::DisplayMode*/int, /*ZRtStyleSheetItem::ListStyle*/int);		 // FUNC
	void setPointSize(int);		 // FUNC
	void setReadOnly(bool);		 // FUNC
	void setSelectionAttributes(int, QColor const&, bool);		 // FUNC
	void setSelection(int, int, int, int, int selNum = 0);		 // FUNC
	void setStyleSheet(ZRtStyleSheet*);		 // FUNC
	void setTabChangesFocus(bool);		 // FUNC
	void setTabStopWidth(int);		 // FUNC
	void setTextEntryMode(QUuid const&);		 // FUNC
	void setTextFormat(Qt::TextFormat);		 // FUNC
	void setText(QString const&, QString const&);		 // FUNC
	void setText(QString const&);		 // FUNC
	void setUnderline(bool);		 // FUNC
	void setUndoDepth(int);		 // FUNC
	void setUndoRedoEnabled(bool);		 // FUNC
	void setVerticalAlignment(VerticalAlignment);		 // FUNC
	void setWordWrap(WordWrap);		 // FUNC
	void setWrapColumnOrWidth(int);		 // FUNC
	void setWrapPolicy(WrapPolicy);		 // FUNC
	void signalBeforeInsertTextFromIm(QPoint, QPoint&);		 // FUNC
	QSize sizeHint() const;		 // FUNC
	void sliderReleased();		 // FUNC
	void slotSetDefaultHightSd();		 // FUNC
	void slotTextChanged();		 // FUNC
	void specialInputModeCursorModel(bool);		 // FUNC
	void styleSheet() const;		 // FUNC
	void sync();		 // FUNC
	void syntaxHighlighter() const;		 // FUNC
	void tabChangesFocus() const;		 // FUNC
	void tabStopWidth() const;		 // FUNC
	void textChangedByIM(int);		 // FUNC
	void textChangedFromIm(int);		 // FUNC
	void textChanged();		 // FUNC
	QString text() const;		 // FUNC
	void textFormat() const;		 // FUNC
	void text(int) const;		 // FUNC
	void timerEvent(QTimerEvent*);		 // FUNC
	void topOfText();		 // FUNC
	void underline() const;		 // FUNC
	void undoAvailable(bool);		 // FUNC
	void undoDepth() const;		 // FUNC
	void undo();		 // FUNC
	void updateContents();		 // FUNC
	void updateCurrentFormat();		 // FUNC
	void updateCursor(QPoint const&);		 // FUNC
	void updateMicroFocusHint();		 // FUNC
	void updateModelBeforeInsert(QString const&);		 // FUNC
	void updateStyles();		 // FUNC
	void viewportResizeEvent(QResizeEvent*);		 // FUNC
	void windowActivationChange(bool);		 // FUNC
	void wordWrap() const;		 // FUNC
	void wrapColumnOrWidth() const;		 // FUNC
	void wrapPolicy() const;		 // FUNC
	
	//OBJECT
	int im;
	int total;
	
private:
#if defined(Q_DISABLE_COPY)
    ZTextEdit( const ZTextEdit & );
    ZTextEdit &operator=( const ZTextEdit & );
#endif 
};

#endif

