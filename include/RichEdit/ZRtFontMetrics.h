#ifndef ZRTFONTMETRICS_H
#define ZRTFONTMETRICS_H

#include "qfontmetrics.h"

#if defined(EZX_ZN5) || defined(EZX_U9) || defined(EZX_Z6W)
class ZRtFontMetrics;
#else
class ZRtFontMetrics
{
public:
	ZRtFontMetrics();
	~ZRtFontMetrics();

	int charWidth(QFontMetrics, QString const&, int);
	int charWidth(QFontMetrics*, QString const&, int);

};
#endif

#endif
