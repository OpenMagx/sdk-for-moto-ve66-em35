//
// Writen by Ant-ON, 2010
//
// Fix for VE66/EM35, 2.1.2011
//
// email: prozanton@gmail.com
//

#ifndef SETUP_UTIL_H 
#define SETUP_UTIL_H

#include "SETUP_UTIL_Define.h"
#include "SETUP_SET_Manager.h"
#include <qstring.h>
#include <qstringlist.h>
#include <qmap.h>

class STRU_IATC_PROFILE_RING_TONE_D;

struct ALERTSTYLE_DATA_S
{
    // ...
};

struct PROFILE_DATA_S
{
    // ...
};

struct JAVA_SYSTEM_S
{
    QString midp;
    QString cldt;
    QString s1;
    QString s2;
    QString heapSize;
    QString cdc;
};

enum ENUM_PRELOADED_PROFILE_E
{
};

struct SETUP_SYSTEM_INFORMATION
{
	QString s;//???
    // ...	
};

struct PROFILE_CONFIG_S
{
    QString id;
    QString name;
    // ...
};

class SETUP_Utility_Impl;

class SETUP_Utility
{
public:
	SETUP_Utility();
	~SETUP_Utility();

	enum SLIDE_CLOSED_SETTING_E
	{
		SLIDE_NO_ACTION=0,
		SLIDE_CLOSE_ALL=1,
		SLIDE_BREAK_DIAL=2,		
	};

	QString defaultPictureFile();
	QString defaultSoundFile();
	void getActiveAlertStyle(int&);
	void getAirplaneModePromptStatus(bool&);
	void getAlertsAlertStyle(ENUM_ALERT_STYLE&);
	void getAlertsAlertStyle(int, ENUM_ALERT_STYLE&);
	void getAlertStyleIcon(int, QString&);
	void getAlertStyleList(QMap<int, ALERTSTYLE_DATA_S>&, bool);
	void getAlertStyleName(int, QString&, bool);
	void getAlertStyleName(QString&, bool);
	void getAlertTone(ENUM_ALERT_TYPE, QString&);
	void getAutoAnswerTime(int&);
	void getBackLightDimIntensity();
	void getBackLightInLockDurationTool(SETUP_SET_Manager&);
	void getBackLightInLockDuration();
	void getBackLightInLockIntensityTool(SETUP_SET_Manager&);
	void getBackLightInLockIntensity();
	void getBackLightValue(int&);
	void getBackLightValueTool(SETUP_SET_Manager&, int&);
	void getBlendingColor(unsigned int&);
	void getBlendingPercentage(int&);
	void getChargingLightStatus(bool&);
	int  getDimDisplayTimer();
	int  getDisplayTimer();
	void getFlexBit(unsigned short, bool&);
	void getIncomingCallAlertStyle(ENUM_ALERT_STYLE&);
	void getIncomingCallAlertStyle(int, ENUM_ALERT_STYLE&);
	void getInstantPhoneLockStatus(bool&);
	void getInstantPhoneLockStatusTool(SETUP_SET_Manager&, bool&);
	void getJavaHeapSize(int&);
	void getJavaOTATimeout(int&);
	void getLcdSleepTime(int&);
	void getLightPattern(ENUM_ALERT_TYPE, QString&);
	void getMaxBrightnessRangeTool(SETUP_SET_Manager&, int&);
	void getMinBrightnessRangeTool(SETUP_SET_Manager&, int&);
	void getMinUnlockCodeLength(unsigned int&);
	void getOmegaStatus(bool&);
	void getPersonalDictionaryLockStatus(bool&);
	void getPhoneAutoLockStatus(bool&);
	void getPhoneAutoLockTime(int&);
	void getPowerDownImage(QString&);
	void getPowerUpImage(QString&);
	void getPreviousAlertStyle(int&);
	void getProximitySoundStatus();
	void getScreensaverStatus();
	void getScreensaverTimer();
	void getScrSaver(QString&);
	SLIDE_CLOSED_SETTING_E getSlideClosedSetting();
	void getSliderTone(QString&, QString&);
	void getSoundVolume(ENUM_SOUND_TYPE_E, int&);
	void getSpeakerVolume(int&);
	void getSystemSetupManager();
	void getTalkingPhoneStatus(ENUM_TALKINGPHONE_READOUT_TYPE, int&);
	void getTimeout(ENUM_TIMER_TYPE, int&);
	void getUSBStatus(int&);
	void getUserDefinedLanguageType(QString&);
	void getUserDefinedLanguageTypeTool(SETUP_SET_Manager&, QString&);
	void getVoiceDialStatus(bool&);
	void getVRTalkingPhone(bool&);
	void getWallpaperFileName(QString&);
	void getWallpaper(QString&);
	void getWallpaperTransparency(bool&);
	bool isAirplaneModeOn();
	bool isFeatureAvailable(unsigned short);
	bool isOSSLicense(QString const&);
	void md5Encrypt(unsigned char*, unsigned short, char*);
	void restoreActiveAlertStyle();
	void setActiveAlertStyle(int, bool);
	void setAirplaneMode(bool);
	void setAsWallpaper(QString);
	void setBacklightValue();
	void setDisplayTimer(unsigned int);
	void setInstantPhoneLockStatus(bool);
	void setLanguageType(QString);
	void setMinUnlockCodeLength(unsigned int);
	void setPhoneAutoLockTime(SETUP_PHONELOCK_TYPE_T);
	void setPhoneLockCode(QString const&);
	void setPhoneLockFlag(bool);
	void setPhoneLockTimeOutFlag(bool);
	void setScrSaver(QString const&);
	void setSilentStatus(bool);
	void setSoundVolume(ENUM_SOUND_TYPE_E, int);
	void setSpeakerVolume(int);
	void setTalkingPhoneStatus(ENUM_TALKINGPHONE_READOUT_TYPE, bool);
	void setTimeout(ENUM_TIMER_TYPE, int);
	void setupInitialize();
	void setUSBStatus(int);
	void setVibrateStatus(bool);
	void setWallPaper(QString const&);
	bool verifyAutoLanguageCode(int);
	bool verifyPersonalDictionaryLockPassword(QString);
	void verifySecurityCode(QString const&, bool&);
	void verifyUnlockCode(QString const&, bool&); 
};

class SETUP_Utility_Impl: public SETUP_Utility
{
public:
	void copyFile(QString, QString);
	void dcSoundSettingsInit(bool);
	void dcThemeInit(bool);
	void defaultAniDir();
	void defaultPictureDir();
	void dynamicIdleInit();
	void dynamicIdleMakeDir(QString const&);
	void getDisplayDefaultFile(QString const&);
	void getFirstFileByNameFilter(QString const&, QString const&);
	void getFlexBitFileName(unsigned short);
	void getFlexBitFromBP(void*, unsigned char, unsigned char*);
	void getHapticStatus(bool&);
	void getHeapSizeStr(int);
	void getInputModeType(QString&);
	void getJavaSystemInfo(JAVA_SYSTEM_S&);
	void getPersonalDictionaryLockPassword(QString&);
	void getShortcutFileName();
	void getStatusLight(bool&);
	void getTimestampFileName();
	void getTTYType(int&);
	void initFlexbitFromBP();
	bool isResourceImgUpdated();
	bool isSupportedMMUI();
	void isSupportVR(bool&);
	void readThemeSettingValue(ENUM_ALERT_TYPE, QString&);
	bool setAirplaneModePromptStatus(bool);
	bool setChargingLightStatus(bool);
	bool setHapticStatus(bool);
	bool setInputModeType(QString);
	bool setPersonalDictionaryLockPassword(QString);
	bool setPersonalDictionaryLockStatus(bool);
	bool setProximitySoundStatus(bool);
	bool setScreensaverStatus(bool);
	bool setSlideClosedSetting(SETUP_Utility::SLIDE_CLOSED_SETTING_E);
	bool setStatusLight(bool);
	void systemDataInit();
};

#endif  

