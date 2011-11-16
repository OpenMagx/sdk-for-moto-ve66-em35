// Writed by Ant-ON, 2011

#ifndef J2ME_NAMS
#define J2ME_NAMS

class J2ME_NAMS_ClientAMNotifier
{
public:
	static J2ME_NAMS_ClientAMNotifier * getInstance(QObject const*, char const*, QObject const*, char const*);
	static J2ME_NAMS_ClientAMNotifier * getInstance();
	void J2ME_NAMS_ClientAMNotifier::releaseInstance();
};

extern "C"
{
	void J2ME_NAMS_Initialize();
	void J2ME_NAMS_DeInitialize();
		
	void J2ME_NAMS_BackgroundApp();
	int  J2ME_NAMS_ForegroundApp();	
	
	void J2ME_NAMS_NotifyApp();
	void J2ME_NAMS_PauseApp();
	void J2ME_NAMS_ResumeApp();	
	void J2ME_NAMS_StartApp();	
	void J2ME_NAMS_StopApp();	
	
	void J2ME_NAMS_CleanupVM();
	void J2ME_NAMS_GetAppState();
	void J2ME_NAMS_GetRunningApps();
	void J2ME_NAMS_RegisterAppStatusNotification();
	void J2ME_NAMS_StopAllApps();
	
	void J2ME_NAMS_SetRaiseVMCB();
	void J2ME_NAMS_SetStartVMCB();
	void J2ME_NAMS_SetStopVMCB();

	int  J2ME_NAMS_VM_Initialize();
	
	void J2ME_NAMS_VM_IsAppInBackgroundRunMode();
	void J2ME_NAMS_VM_IsBackgroundApp();
		
	void J2ME_NAMS_VM_Cleanup();
	int  J2ME_NAMS_VM_GetForegroundAppId();
	void J2ME_NAMS_VM_ReportStatus();
	void J2ME_NAMS_VM_SetAppCBs();
	void J2ME_NAMS_VM_SetNotificationCB();
	void J2ME_NAMS_VM_SetWindowCBs();
};

#endif
