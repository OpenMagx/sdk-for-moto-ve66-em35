

// Copyright (c) 27-Apr-07 - 2008 Motorola, Inc. All rights reserved.


#ifndef PUBLIC_API_WIDGET_ZPROGRESSDLG_H
#define PUBLIC_API_WIDGET_ZPROGRESSDLG_H

#ifndef __cplusplus
#error "This is a C++ header file; it requires C++ to compile."
#endif

#include "ZPopup.h"

#include "ZMeterModule.h"

#include "qstring.h"
#include "qobjectdefs.h"
#include "qwidget.h"
#include "qnamespace.h"
#include "qglobal.h"
#include "qpixmap.h"
#include "qevent.h"
#include "qpalette.h"

class ZLabel;
class ZSoftKey;
class ZMeter;

struct ZProgressDlgPrivate;

class ZProgressDlg : public ZPopup
{
    Q_OBJECT

public:
    ZProgressDlg(const QString& strDlgTitle,
                 const QString& strInstructText,
                 int nTotalStep,
                 int nMaxSize,
                 QWidget* parent = NULL, const char* name = 0, bool modal = true, WFlags f = 0, 
                 Qt::DisplayID displayId = MainDisplay);
    ZProgressDlg(const QString& strDlgTitle,
                 const QString& strInstructText,
                 const QString& strFileName,
                 QWidget* parent = NULL, const char* name = 0, bool modal = true, WFlags f = 0, 
                 Qt::DisplayID displayId = MainDisplay);
    ZProgressDlg(const QString& strDlgTitle,
                 const QString& strInstructText,
                 int nTotalStep = 10,
                 QWidget* parent = NULL, const char* name = 0, bool modal = true, WFlags f = 0, 
                 Qt::DisplayID displayId = MainDisplay);
    ZProgressDlg(QWidget* parent = NULL, const char* name = 0, bool modal = true, WFlags f = 0, 
    			 Qt::DisplayID displayId = MainDisplay);


    virtual ~ZProgressDlg();
    int getProgressTotalStep();
    void setProgressTotalStep(int nTotalStep);
    void setProgress(int nProgress);
    int getProgress();
    bool  wasCancelled() const;
    void setAutoReset(bool b);
    bool autoReset() const;
    void setAutoClose(bool b);
    bool autoClose() const;
    int getMinimumDuration() const;
    void changeMeter(const QString& strFileName);
    void changeMeter(int nTotalStep, int nMaxSize);
    void changeMeter(int nTotalStep);
    ZMeterModule* getMeterModule();
    void setMMAlign(ZMeterModule::Alignment align);
    void setMMLabelText(const QString& str);
    void setAutoPercentFlag(bool bAuto);
    ZMeter* getMeter();

public slots:
    void    cancel();
    void    reset();
    void    setMinimumDuration(int ms);

signals:
    void    cancelled();

protected slots:
    virtual void slotResizeAllChild(int);
    void    forceShow();
    void slotLeftSoftKeyClicked();

protected:
    virtual void    keyPressEvent( QKeyEvent*);

private:
    void initialize( const QString&, const QString& );
    void setMeterModule(ZMeterModule*);

private:
    ZProgressDlgPrivate* mpData;
};


#endif

