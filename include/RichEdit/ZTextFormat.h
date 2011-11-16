#ifndef ZTEXTFORMAT_H
#define ZTEXTFORMAT_H

#include "ZTextCommand.h"
#include "ZRtStyleSheet.h"
#include "ZMemArray.h"

#include <qmap.h>
#include <qfont.h>
#include <qstring.h>

#if defined(EZX_ZN5) || defined(EZX_U9) || defined(EZX_Z6W)
class ZTextFormatCommand;
class ZTextFormatCollection;
class ZTextFormat;
#else
class ZTextCursor;
class QPaintDevice;

class Q_EXPORT ZTextFormatCommand : public ZTextCommand
{
public:
    ZTextFormatCommand( ZTextDocument *d, int sid, int sidx, int eid, int eidx, const ZMemArray<ZTextStringChar> &old, ZTextFormat *f, int fl );
    virtual ~ZTextFormatCommand();

    Commands type() const;
    ZTextCursor *execute( ZTextCursor *c );
    ZTextCursor *unexecute( ZTextCursor *c );

protected:
	uint fix[10];
};

class Q_EXPORT ZTextFormatCollection
{
public:
    ZTextFormatCollection();
    virtual ~ZTextFormatCollection();

    void setDefaultFormat( ZTextFormat *f );
    ZTextFormat *defaultFormat() const;
    virtual ZTextFormat *format( ZTextFormat *f );
    virtual ZTextFormat *format( ZTextFormat *of, ZTextFormat *nf, int flags );
    virtual ZTextFormat *format( const QFont &f, const QColor &c );
    virtual void remove( ZTextFormat *f );

    void updateDefaultFormat( const QFont &font, const QColor &c, ZRtStyleSheet *sheet );

    void setPaintDevice( QPaintDevice * );

private:
    void updateKeys();

private:
	uint fix[15];
};

class Q_EXPORT ZTextFormat
{
    friend class ZTextFormatCollection;
    friend class ZTextDocument;

public:
    enum Flags {
	NoFlags,
	Bold = 1,
	Italic = 2,
	Underline = 4,
	Family = 8,
	Size = 16,
	Color = 32,
	Misspelled = 64,
	VAlign = 128,
	StrikeOut= 256,
	Font = Bold | Italic | Underline | Family | Size | StrikeOut,
	Format = Font | Color | Misspelled | VAlign
    };

    enum VerticalAlignment { AlignNormal, AlignSuperScript, AlignSubScript };

    ZTextFormat();
    virtual ~ZTextFormat();

    ZTextFormat( const ZRtStyleSheetItem *s );
    ZTextFormat( const QFont &f, const QColor &c, ZTextFormatCollection *parent = 0 );
    ZTextFormat( const ZTextFormat &fm );
    ZTextFormat makeTextFormat( const ZRtStyleSheetItem *style, const QMap<QString,QString>& attr, double scaleFontsFactor ) const;
    ZTextFormat& operator=( const ZTextFormat &fm );
    QColor color() const;
    QFont font() const;
    bool isMisspelled() const;
    VerticalAlignment vAlign() const;
    int minLeftBearing() const;
    int minRightBearing() const;
    int width( const QChar &c ) const;
    int width( const QString &str, int pos ) const;
    int height() const;
    int ascent() const;
    int descent() const;
    int leading() const;
    bool useLinkColor() const;

    void setBold( bool b );
    void setItalic( bool b );
    void setUnderline( bool b );
    void setStrikeOut( bool b );
    void setFamily( const QString &f );
    void setPointSize( int s );
    void setFont( const QFont &f );
    void setColor( const QColor &c );
    void setMisspelled( bool b );
    void setVAlign( VerticalAlignment a );

    ZTextFormatCollection *parent() const;
    const QString &key() const;

    static QString getKey( const QFont &f, const QColor &c, bool misspelled, VerticalAlignment vAlign );

    void addRef();
    void removeRef();

    QString makeFormatChangeTags( int align, ZTextFormat* defaultFormat, ZTextFormat *f, const QString& oldAnchorHref, const QString& anchorHref ) const;
    QString makeFormatEndTags( ZTextFormat* defaultFormat, const QString& anchorHref ) const;

    static void setPainter( QPainter *p );
    static QPainter* painter();

protected:
    virtual void generateKey();

private:
    void update();
    static void applyFont( const QFont &f );

private:
	uint fix[80];

};
#endif

#endif
