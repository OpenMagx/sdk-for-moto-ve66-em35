// Writed by Ant-ON <prozanton@gmail.com>, 29.12.2010
//
// Lib: libezxpm.so
//
// Based on: lm_app_interface.h
//

#ifndef PM_APP_INTERFACE_H
#define PM_APP_INTERFACE_H

extern "C" {

#define PM_APP_SUCCESS              0

typedef enum
{
} PM_APP_REQUEST_T;

typedef enum
{
	PM_APP_HIGHTSPEED_FINISHED,	
	PM_APP_HIGHTSPEED_ALLOW,
	PM_APP_HIGHTSPEED_REQUEST,
} PM_APP_HIGHTSPEED;

typedef enum
{
	PM_APP_DVFS_DISABLE,
	PM_APP_DVFS_ENABLE,		
} PM_APP_DVFS;

int PM_app_connect();
void PM_app_disconnect(int fd);
int PM_app_reqSend(PM_APP_REQUEST_T req);
int PM_app_sendMsg(int fd, unsigned short id, void *buf, unsigned short len);
int PM_getStatus();
int PM_getVotes();
int PM_setupDVFS(int fd, PM_APP_DVFS);
int PM_setupHighSpeed(int fd, PM_APP_HIGHTSPEED);
int PM_setupOPP();
int PM_setupReleaseChargerRestrict();

}

#endif
