#ifndef ZTEXTSTRING_H
#define ZTEXTSTRING_H

#include <qstring.h>
#include "ZMemArray.h"

class ZTextStringChar;
class ZTextFormat;

class Q_EXPORT ZTextString
{
public:
    ZTextString();
    ZTextString( const ZTextString &s );
    virtual ~ZTextString();

    static QString toString( const ZMemArray<ZTextStringChar> &data );
    QString toString() const;

    int width( int idx ) const;

    void insert( int index, const QString &s, ZTextFormat *f );
    void insert( int index, const QChar *unicode, int len, ZTextFormat *f );
    void insert( int index, ZTextStringChar *c, bool doAddRefFormat = FALSE );
    void truncate( int index );
    void remove( int index, int len );
    void clear();

    void setFormat( int index, ZTextFormat *f, bool useCollection );

    QChar::Direction direction() const;

    bool validCursorPosition( int idx );
    int nextCursorPosition( int idx );
    int previousCursorPosition( int idx );

    void checkBidi() const;

private:
	uint fix[10];
};

#endif
