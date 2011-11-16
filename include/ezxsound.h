#ifndef __EZXSOUND_H_
#define __EZXSOUND_H_ 1

#include <stdlib.h>

class AM_VIRTUAL_DEV_BASE_CLASS;  
class AM_VIRTUAL_CODEC_CLASS
{
public:
    AM_VIRTUAL_CODEC_CLASS();
	~AM_VIRTUAL_CODEC_CLASS();
	int getGEQStatus(bool& enabled);
	int setGEQStatus(bool enabled);
	int getAIEValue(int& currentLevel, int& maxLevel);
    int setAIEValue(int currentLevel, int maxLevel);
    int getAIEStatus(bool& enabled);
	int setAIEStatus(bool enabled);
    int getCodecType(int& codecType);
    int setCodecType(int codecType);
	int getBassboostValue(int& currentLevel, int& maxLevel);
	int setBassboostValue(int currentLevel, int maxLevel);
    int getGEQGainProfile(int& profileIndex);
    int setGEQGainProfile(int profileIndex);
    int getBassboostStatus(bool& enabled);
	int setBassboostStatus(bool enabled);
    int am_virtcodec_set_ptr(AM_VIRTUAL_DEV_BASE_CLASS* base);
    int am_virtcodec_set_params();
private:
    AM_VIRTUAL_DEV_BASE_CLASS *ptr;
    bool GEQ_enabled;//0x04 : 0
    int GEQ_profile;//0x08 : 1
    int GEQ_profile2;//0x0c : 0 == GEQ_profile
    bool AIE_enabled;//0x10 : 0
    int AIE_currentLevel;//0x14 : 1
    int AIE_maxLevel;//0x18 : 7
    int unknown;//0x1c : 0
    bool Bassboost_enabled;//0x20 : 0
    int Bassboost_currentLevel;//0x24 : 1
    int Bassboost_maxLevel;//0x28 : 7 
    int unknown2;//0x2c : 0
    int codecType;//0x30 : 3
};

class AM_VIRTUAL_DEV_BASE_CLASS
{
public:
    AM_VIRTUAL_DEV_BASE_CLASS();
	virtual ~AM_VIRTUAL_DEV_BASE_CLASS();
	virtual int read(short * pBuffer, unsigned int length);
	virtual int write(short * pBuffer, unsigned int length);
	virtual int canWrite() = 0;
	virtual int canRead() = 0;
	virtual int bytesWritten() const;
	virtual int channels() const;
	virtual int frequency() const;
	virtual int bytesPerSample() const;
	virtual int bufferSize() const = 0;
	virtual int getVolume(unsigned int& left, unsigned int& right, bool& muted) = 0;
	virtual bool isMuted() = 0;
	virtual int increaseVolume() = 0;
	virtual int decreaseVolume() = 0;
	virtual int setVolume(int level) = 0;
	virtual int setMMVolume(int level) = 0;
	virtual int volumeChanged(bool muted) = 0;
	virtual int setAudioDevice(unsigned int, unsigned int, unsigned int) = 0;
	virtual int checkDevState();
	virtual int flush(void);
	virtual int bytesRendered() const;
	virtual int refresh(void);
	virtual int open();
	virtual int close();
	virtual int lock();
	virtual int unlock();
	virtual int pause();
	virtual int resume();
private:
    //AM_VIRTUAL_CODEC_CLASS *ptr;//0xD4;
};

enum SOUNDM_AUDIO_NORMALDEV_TYPE_ENUM_T
{
SOUNDM_AUDIOLVL_NORMALOUT_2  = 0x02,
SOUNDM_AUDIO_NORMALOUT_0 = 0xc001,
SOUNDM_AUDIO_NORMALOUT_1 = 0xc002,
SOUNDM_AUDIO_NORMALOUT_2 = 0xc003,
SOUNDM_AUDIO_NORMALOUT_3 = 0xc004,
//used_by_flashclient = 0x405
};
enum AUD_RULE_SET_T
{

};
enum SOUNDM_AUDIO_SYSTEMDEV_TYPE_ENUM_T
{

};
enum AAL_STATUS_ENUM_T
{

};
class AM_NORMAL_DEV_INTERFACE : public AM_VIRTUAL_DEV_BASE_CLASS
{
    char data[212];
	AM_VIRTUAL_CODEC_CLASS *pVirtualCodec;//0xD4
	char data2[72];
public:
	AM_NORMAL_DEV_INTERFACE(AUD_RULE_SET_T);
	AM_NORMAL_DEV_INTERFACE(SOUNDM_AUDIO_NORMALDEV_TYPE_ENUM_T);
	AM_NORMAL_DEV_INTERFACE(SOUNDM_AUDIO_NORMALDEV_TYPE_ENUM_T, AUD_RULE_SET_T);
	AM_NORMAL_DEV_INTERFACE(SOUNDM_AUDIO_NORMALDEV_TYPE_ENUM_T, unsigned int freq = 44100, unsigned int channels =2, unsigned int bytesPerSample = 2);	
	AM_NORMAL_DEV_INTERFACE(SOUNDM_AUDIO_NORMALDEV_TYPE_ENUM_T, unsigned int freq = 44100, unsigned int channels =2, unsigned int bytesPerSample = 2, AUD_RULE_SET_T);
	AM_NORMAL_DEV_INTERFACE();
	virtual ~AM_NORMAL_DEV_INTERFACE();
public:
    virtual int read(short* pBuffer, unsigned int length);
	virtual int write(short* pBuffer, unsigned int length);
	virtual int canWrite();
	virtual int canRead();
	virtual int bytesWritten() const;
	virtual int channels() const;
	virtual int frequency() const;
	virtual int bytesPerSample() const;
	virtual int bufferSize() const;
	virtual int getVolume(unsigned int& left, unsigned int& right, bool& muted);
	virtual bool isMuted();
	virtual int increaseVolume();
	virtual int decreaseVolume();
	virtual int setVolume(int level);
    virtual int setMMVolume(int level);
	virtual int volumeChanged(bool muted);
	virtual int setAudioDevice(unsigned int, unsigned int, unsigned int);
	virtual int checkDevState();
    virtual int flush();
	virtual int bytesRendered() const;
	virtual int refresh();
	virtual int open();
	virtual int close();
	virtual int lock();
	virtual int unlock();
	virtual int pause();
	//virtual int resume();
	int resume();
	int recordStartTime(struct timeval &startTime);
	int SetPathRule(AUD_RULE_SET_T);
	int writeAlignedData(short*, unsigned int, AAL_STATUS_ENUM_T*);
private:
    int am_normdev_init(SOUNDM_AUDIO_NORMALDEV_TYPE_ENUM_T, unsigned int, unsigned int, unsigned int, AUD_RULE_SET_T);
};

#endif
