#ifndef ZRTSTRING_H
#define ZRTSTRING_H

#include <qstring.h>

#if defined(EZX_ZN5) || defined(EZX_U9) || defined(EZX_Z6W)
class ZRtString;
#else
class ZRtString
{
public:
	ZRtString();
	~ZRtString();

	void endsWith(QString const&, QString const&, bool);
	void endsWith(QString const&, QString const&);
	void replace(QString&, QString, QString, bool);
	void section(QString&, char const*, int, int, int);
	void section(QString&, char, int, int, int);
	void section(QString&, QChar, int, int, int);
	void section(QString&, QRegExp const&, int, int, int);
	void section(QString&, QString const&, int, int, int);
	void setLength(QString&, unsigned int);
	void startsWith(QString const&, QString const&, bool);
	void startsWith(QString const&, QString const&);

};
#endif

#endif
