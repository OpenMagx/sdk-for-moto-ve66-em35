

// Copyright (c) 24-Apr-07 - 2008 Motorola, Inc. All rights reserved.


#ifndef UTIL_ACTIONREGISTRY_H
#define UTIL_ACTIONREGISTRY_H

#ifndef __cplusplus
#error "This is a C++ header file; it requires C++ to compile."
#endif

#include "AM_Global.h"
#include "AM_Defs.h"
#include "ZConfig.h"
#include <qobject.h>

class AM_ActionRegistry : public QObject
{
    Q_OBJECT
public:
    AM_ActionRegistry(QObject  * parent = 0, const char * name = 0);                         
    ~AM_ActionRegistry();                        

    void initRegisterData();

    AM_RESULT_CODE_T getDefaultHandlerId(const QString& action, QString& handler) const;
    AM_RESULT_CODE_T getSystemHandlerId(const QString& action, QString& handler) const;
    AM_RESULT_CODE_T getHandlerIds(const QString& action, QStringList& handlerList) const;
    AM_RESULT_CODE_T registerActionHandler(const QString& action, const QString& handler, bool def=false);
    AM_RESULT_CODE_T unregisterActionHandler(const QString& action, const QString& handler);
    AM_RESULT_CODE_T unregisterActionHandler(const QString& handler);
    /*
    void unregisterAction(const QString& action);*/
    void getPredefinedAction(QStringList& actionList) const;
    bool isRegisteredAction(const QString& action) const;

private:
    void getFileLock(const int fd);
    void releaseFileLock(const int fd);
    AM_RESULT_CODE_T removeActionHandler(ZConfig& cf, const QString& action, const QString& handler);
    const QString registerFile() const;
    const QString originalRegisterFile() const;
};

#endif  

