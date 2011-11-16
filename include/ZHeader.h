//Fix for VE66/EM35 by Ant-ON, 2009

// Copyright (c) 27-Apr-07 - 2008 Motorola, Inc. All rights reserved.


#ifndef ZHEADER_H
#define ZHEADER_H

#ifndef __cplusplus
#error "This is a C++ header file; it requires C++ to compile."
#endif

#include <ZWidget.h>
#include <qstring.h>
#include <qrect.h>

class ZHeaderBase;

class ZHeader : public ZWidget
{
Q_OBJECT
public:
    enum HEADER_TYPE
    {
        CLI_HEADER,         
        CLI_IDL,            
        MAINDISPLAY_IDL,    
        MAINDISPLAY_HEADER, 
        HEADER_TYPE_NUM     
    };

    enum HEADER_STATUS
    {
        AIRPLANE = 1,   
        ROAMING,        
        SIGNAL,         
        ACTIVE_CIRCUIT_DATA_CALL,   
        ACTIVE_VOICE_CALL,          
        VIDEO_CALL,     
        UMA,            
        WIFI,           
        GPRS,           
        EDGE,           
        THREEG,         
        CDMAPDS,        
        SERVICE,        
        CALLFORWARDING, 
        ACTIVELINE,     
        VOICEPRIVACY,   
        VR,             
        BATTERY,        
        IM,             
        SYNC,           
        BT,             
        NOTIFY,         
        PRESENCE,       
        LOCATION,       
        HOMEZONE,       
        ALERT,          
        WIFISIGNAL,     
        USB,            
        SPEAKER,        
        FDN,            
        HSDPA,          
        JAVA,           
        PTT,            
        ROGERSMAIL,     
        VIDEO_MAIL,     
        VOICE_MAIL,     
        EMAIL,          
        VIDEO_MESSAGE,  
        VOICE_MESSAGE,  
        TEXT_MESSAGE,   
        MESSAGE,        
        MULTIMEDIA,     
        RADIO,          
        DLNA,           
        STATUS_NUM      
    };

    enum
    {
        EMPTY_STATUS = -1,  
        START_BLINK = -3,   
        END_BLINK = -4,     
        MIN_VALID_VALUE = END_BLINK
    };

    typedef struct AppStatus
    {
        Q_INT8 status;  
        QString strResID[HEADER_TYPE_NUM+1];
    } AppStatus_S;

    class AppStatusInfo_S
    {
    public:
        AppStatusInfo_S() : appStatus(NULL) {
        }    

        ~AppStatusInfo_S() {
            if (appStatus) {
                delete []appStatus;
                appStatus = NULL;
            }
        }

        Q_INT8 status;          
        Q_INT32 numStatus;      
        Q_INT32 priority;       
        AppStatus_S* appStatus; 
    };

    static bool registerInfo(const ZHeader::AppStatusInfo_S& as) {
        return false;
    }

    static bool unregisterInfo(ZHeader::HEADER_STATUS s) {
        return false;
    }

    ZHeader(QWidget* parent = 0, const char* name = 0, WFlags f = 0);

    ZHeader(ZHeader::HEADER_TYPE t,
            QWidget* parent = 0,
            const char* name = 0,
            WFlags f = 0);

	//Add by Ant-ON
	void hideMeter();
	void setMeterRange(int, int);
	void setMeterValue(int);
	void showMeter();	
	//end

    QString getPrimTitle();

    QString getSecondTitle();

    void setPrimTitle(const QString &text);

    void setSecondTitle(const QString &text);

    bool setTitleIcon(const QPixmap& pmp);

    QPixmap getTitleIcon();

    void setAlignment(int alignment);

    int alignment();

    bool isZEnable();

    void setTruncEnable(bool bTrunc);

    bool isTruncEnable();

    QPixmap getBlendedPixmap(int nIdx);

    void setPalette(const QPalette& pal);

    bool switchHeader(ZHeader::HEADER_TYPE);

    static QSize headerSize(ZHeader::HEADER_TYPE t);

    static bool changeStatus(ZHeader::HEADER_STATUS s, int statusVal);

    static int getStatusVal(ZHeader::HEADER_STATUS s);

    ~ZHeader();

signals:
    void primTitleChanged(const QString& s);

    void secondTitleChanged(const QString& s);

    void serverInitialized();

    void blendedPixmapChanged(int nIdx);

protected:
    void init();

    virtual void paintEvent(QPaintEvent*);

    virtual void resizeEvent(QResizeEvent*);

private:
    ZHeaderBase * d;
};

#endif

