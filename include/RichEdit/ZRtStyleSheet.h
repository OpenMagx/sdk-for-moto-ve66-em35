// based on qstylesheet.h

#ifndef ZRTSTYLESHEET_H
#define ZRTSTYLESHEET_H

#include "qstring.h"
#include "qdict.h"
#include "qobject.h"


#if defined(EZX_ZN5) || defined(EZX_U9) || defined(EZX_Z6W)
class Q_EXPORT ZRtStyleSheetItem : public Qt
{
public:
    enum DisplayMode 
    {
	DisplayBlock,
	DisplayInline,
	DisplayListItem,
	DisplayNone
    };

    enum VerticalAlignment {
	VAlignBaseline,
	VAlignSub,
	VAlignSuper
    };

    enum WhiteSpaceMode 
    {
	WhiteSpaceNormal,
	WhiteSpacePre,
	WhiteSpaceNoWrap
    };

    enum Margin {
	MarginLeft,
	MarginRight,
	MarginTop,
	MarginBottom,
	MarginFirstLine,
	MarginAll,
	MarginVertical,
	MarginHorizontal
    };
    
    enum ListStyle 
    {
	ListDisc,
	ListCircle,
	ListSquare,
	ListDecimal,
	ListLowerAlpha,
	ListUpperAlpha
    };
};
class ZRtStyleSheet;
#else
class ZRtStyleSheet;
class ZTextDocument;
template<class Key, class T> class QMap;
class ZRtStyleSheetItemData;

class Q_EXPORT ZRtStyleSheetItem : public Qt
{
public:
    ZRtStyleSheetItem( ZRtStyleSheet* parent, const QString& name );
    ZRtStyleSheetItem( const ZRtStyleSheetItem & );
    ~ZRtStyleSheetItem();

    ZRtStyleSheetItem& operator=( const ZRtStyleSheetItem& other );

    QString name() const;

    ZRtStyleSheet* styleSheet();
    const ZRtStyleSheet* styleSheet() const;

    enum AdditionalStyleValues { Undefined  = - 1};

    enum DisplayMode 
    {
	DisplayBlock,
	DisplayInline,
	DisplayListItem,
	DisplayNone
    };

    DisplayMode displayMode() const;
    void setDisplayMode(DisplayMode m);

    int alignment() const;
    void setAlignment( int f);

    enum VerticalAlignment {
	VAlignBaseline,
	VAlignSub,
	VAlignSuper
    };

    VerticalAlignment verticalAlignment() const;
    void setVerticalAlignment( VerticalAlignment valign );

    int fontWeight() const;
    void setFontWeight(int w);

    int logicalFontSize() const;
    void setLogicalFontSize(int s);

    int logicalFontSizeStep() const;
    void setLogicalFontSizeStep( int s );

    int fontSize() const;
    void setFontSize(int s);

    QString fontFamily() const;
    void setFontFamily( const QString& );

    int numberOfColumns() const;
    void setNumberOfColumns(int ncols);

    QColor color() const;
    void setColor( const QColor &);

    bool fontItalic() const;
    void setFontItalic( bool );
    bool definesFontItalic() const;

    bool fontUnderline() const;
    void setFontUnderline( bool );
    bool definesFontUnderline() const;

    bool fontStrikeOut() const;
    void setFontStrikeOut( bool );
    bool definesFontStrikeOut() const;

    bool isAnchor() const;
    void setAnchor(bool anc);

    enum WhiteSpaceMode 
    {
	WhiteSpaceNormal,
	WhiteSpacePre,
	WhiteSpaceNoWrap
    };
    
    WhiteSpaceMode whiteSpaceMode() const;
    void setWhiteSpaceMode(WhiteSpaceMode m);

    enum Margin {
	MarginLeft,
	MarginRight,
	MarginTop,
	MarginBottom,
	MarginFirstLine,
	MarginAll,
	MarginVertical,
	MarginHorizontal
    };

    int margin( Margin m) const;
    void setMargin( Margin, int);

    enum ListStyle 
    {
	ListDisc,
	ListCircle,
	ListSquare,
	ListDecimal,
	ListLowerAlpha,
	ListUpperAlpha
    };

    ListStyle listStyle() const;
    void setListStyle( ListStyle );

    QString contexts() const;
    void setContexts( const QString& );
    bool allowedInContext( const ZRtStyleSheetItem* ) const;

    bool selfNesting() const;
    void setSelfNesting( bool );

    void setLineSpacing( int ls );
    int lineSpacing() const;

private:
    void init();
    ZRtStyleSheetItemData* d;
};


class ZTextCustomItem;

class Q_EXPORT ZRtStyleSheet : public QObject
{
    Q_OBJECT
public:
    ZRtStyleSheet( QObject *parent=0, const char *name=0 );
    virtual ~ZRtStyleSheet();

    static ZRtStyleSheet* defaultSheet();
    static void setDefaultSheet( ZRtStyleSheet* );


    ZRtStyleSheetItem* item( const QString& name);
    const ZRtStyleSheetItem* item( const QString& name) const;

    void insert( ZRtStyleSheetItem* item);

    virtual ZTextCustomItem* tag( const QString& name,
				  const QMap<QString, QString> &attr,
				  const QString& context,
				  const QMimeSourceFactory& factory,
				  bool emptyTag, ZTextDocument *doc ) const;
				  
    static QString escape( const QString& );
    static QString convertFromPlainText( const QString&,
					 ZRtStyleSheetItem::WhiteSpaceMode mode = ZRtStyleSheetItem::WhiteSpacePre );
    static bool mightBeRichText( const QString& );

    virtual void scaleFont( QFont& font, int logicalSize ) const;

    virtual void error( const QString& ) const;

private:
    void init();
    QDict<ZRtStyleSheetItem> styles;
    ZRtStyleSheetItem* nullstyle;
};
#endif

#endif
