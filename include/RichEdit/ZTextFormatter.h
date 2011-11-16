#ifndef ZTEXTFORMATTER_H
#define ZTEXTFORMATTER_H

#include <qmap.h>

class ZTextParagraph;
class ZTextLineStart;
class ZTextStringChar;
class ZTextString;
class ZTextDocument;

class Q_EXPORT ZTextFormatter
{
public:
    ZTextFormatter();
    virtual ~ZTextFormatter();

    virtual int format( ZTextDocument *doc, ZTextParagraph *parag, int start, const QMap<int, ZTextLineStart*> &oldLineStarts ) = 0;
    virtual int formatVertically( ZTextDocument* doc, ZTextParagraph* parag );

    virtual void setWrapEnabled( bool b );
    virtual void setWrapAtColumn( int c );

	void setAllowBreakInWords(bool);

protected:
    virtual ZTextLineStart *formatLine( ZTextParagraph *parag, ZTextString *string, ZTextLineStart *line, ZTextStringChar *start,
					       ZTextStringChar *last, int align = Qt::AlignLeft, int space = 0 );
    virtual ZTextLineStart *bidiReorderLine( ZTextParagraph *parag, ZTextString *string, ZTextLineStart *line, ZTextStringChar *start,
						    ZTextStringChar *last, int align, int space );
    void insertLineStart( ZTextParagraph *parag, int index, ZTextLineStart *ls );

protected:
	uint fix[10];
};

class Q_EXPORT ZTextFormatterBreakInWords : public ZTextFormatter
{
public:
    ZTextFormatterBreakInWords();
    virtual ~ZTextFormatterBreakInWords() {}

    int format( ZTextDocument *doc, ZTextParagraph *parag, int start, const QMap<int, ZTextLineStart*> &oldLineStarts );

};

class Q_EXPORT ZTextFormatterBreakWords : public ZTextFormatter
{
public:
    ZTextFormatterBreakWords();
    virtual ~ZTextFormatterBreakWords() {}

    int format( ZTextDocument *doc, ZTextParagraph *parag, int start, const QMap<int, ZTextLineStart*> &oldLineStarts );

};

#endif
