#ifndef ZTEXTCOMMAND_H
#define ZTEXTCOMMAND_H

#if defined(EZX_ZN5) || defined(EZX_U9) || defined(EZX_Z6W)
class ZTextCommand;
class ZTextCommandHistory;
#else
class Q_EXPORT ZTextCommand
{
public:
    ZTextCommand(){/*???*/};
    virtual ~ZTextCommand();

	enum Commands {/*???*/};

    virtual Commands type() const;

protected:
    uint fix[5];
};

class Q_EXPORT ZTextCommandHistory
{
public:
    ZTextCommandHistory(){/*???*/};
    virtual ~ZTextCommandHistory();

    void addCommand( ZTextCommand *cmd );
    ZTextCursor *undo( ZTextCursor *c );
    ZTextCursor *redo( ZTextCursor *c );

    bool isUndoAvailable();
    bool isRedoAvailable();

protected:
    uint fix[5];
};
#endif

#endif
