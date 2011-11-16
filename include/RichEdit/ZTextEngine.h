#ifndef ZTEXTENGINE_H
#define ZTEXTENGINE_H

#include <qstring.h>

#if defined(EZX_ZN5) || defined(EZX_U9) || defined(EZX_Z6W)
class ZTextEngine;
#else
class ZTextEngine 
{
public:
    ZTextEngine( const QString &str);
    ~ZTextEngine();

    void itemize( int mode = 0 );
    static void bidiReorder( int numRuns, const Q_UINT8 *levels, int *visualOrder );
    const void *attributes();
    void shape( int item ) const;
    int width( int charFrom, int numChars ) const;
    void boundingBox( int from,  int len ) const;
    void splitItem( int item, int pos );
    void reallocate( int totalGlyphs );
    
protected:
	uint fix[20];
};
#endif

#endif
