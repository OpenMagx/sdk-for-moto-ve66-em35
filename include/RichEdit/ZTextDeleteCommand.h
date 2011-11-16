#ifndef ZTEXTDELETECOMMAND_H
#define ZTEXTDELETECOMMAND_H

#include "ZTextCommand.h"

#include <qarray.h>

#if defined(EZX_ZN5) || defined(EZX_U9) || defined(EZX_Z6W)
class ZTextDeleteCommand;
#else
class ZTextParagraph;
class ZTextDocument;

class Q_EXPORT ZTextDeleteCommand : public ZTextCommand
{
public:
    ZTextDeleteCommand( ZTextDocument *d, int i, int idx, const ZMemArray<ZTextStringChar> &str,
			const QByteArray& oldStyle );
    ZTextDeleteCommand( ZTextParagraph *p, int idx, const ZMemArray<ZTextStringChar> &str );
    virtual ~ZTextDeleteCommand();

    Commands type() const;
    ZTextCursor *execute( ZTextCursor *c );
    ZTextCursor *unexecute( ZTextCursor *c );

protected:
	uint fix[10];

};
#endif 

#endif 
