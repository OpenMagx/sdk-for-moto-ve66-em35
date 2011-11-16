#ifndef ZTEXTSTRINGCHAR_H
#define ZTEXTSTRINGCHAR_H

#include "qstring.h"

class ZTextFormat;
class ZTextCustomItem;
class TsLayout_;

class Q_EXPORT ZTextStringChar
{
public:
    ZTextStringChar(){};
    ~ZTextStringChar();

    int height() const;
    int ascent() const;
    int descent() const;
    ZTextFormat *format() const;
    void setFormat( ZTextFormat *f );
    void setCustomItem( ZTextCustomItem *i );
    void loseCustomItem();
    QString anchorName() const;
    QString anchorHref() const;
    void setAnchor( const QString& name, const QString& href );
    static bool isThaiComposibleVowel(const QChar& c);
    static bool isThaiConsonant(const QChar& c);
    static bool isThaiTone(const QChar& c);
    static bool isThaiComposibleMark(const QChar& c);
    static bool isThaiCanNotBeStopChar(const QChar& c);
    static bool isThaiChar(const QChar& c);
	static bool isLTRBidiClass(TsBidiCharClass);
	static bool isNeutralBidiClass(TsBidiCharClass);
	static bool isRTLBidiClass(TsBidiCharClass);    
	int getCharType(QChar const*);
	int getCharWidth(TsLayout_*, int, int, int);

    
private:
	uint gix[10];
};

#endif
