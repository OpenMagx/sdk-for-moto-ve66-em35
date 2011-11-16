#ifndef ZTEXTINSERTCOMMAND_H
#define TEXTINSERTCOMMAND_H

#include "ZTextDeleteCommand.h"

#if defined(EZX_ZN5) || defined(EZX_U9) || defined(EZX_Z6W)
class ZTextInsertCommand;
#else
class ZTextDocument;
class ZTextCursor;

class Q_EXPORT ZTextInsertCommand : public ZTextDeleteCommand
{
public:
    ZTextInsertCommand( ZTextDocument *d, int i1, int i2, const ZMemArray<ZTextStringChar>& a1, const QByteArray& a2 )
    	:ZTextDeleteCommand(d, i1, i2, a1, a2) {};
    virtual ~ZTextInsertCommand();

    Commands type() const;
    ZTextCursor *execute( ZTextCursor *c );
    ZTextCursor *unexecute( ZTextCursor *c );

};
#endif

#endif
