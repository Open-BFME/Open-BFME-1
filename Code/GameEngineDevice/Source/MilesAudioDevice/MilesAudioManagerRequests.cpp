// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AudioEventInfo.h
struct AudioEventInfo
{
	unsigned char m_prefix[0x84];
	int m_type;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AudioEventRTS.h
class AudioEventRTS
{
private:
	unsigned char m_prefix[8];

public:
	AudioEventInfo *m_info;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AudioRequest.h
struct AudioRequest
{
	int m_request;
	AudioEventRTS *m_pendingEvent;
	bool m_usePendingEvent;
	bool m_requiresCheckForSample;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GameSounds.h
class SoundManager
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
	virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
	virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
	virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
	virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27();
	virtual void v28(); virtual void v29(); virtual void v30(); virtual void v31();
	virtual void v32(); virtual void v33(); virtual void v34(); virtual void v35();
	virtual void v36(); virtual void v37(); virtual void v38(); virtual void v39();
	virtual void v40(); virtual void v41(); virtual void v42();
	virtual void getInfoForAudioEvent(AudioEventRTS *event);

	bool canPlayNow(AudioEventRTS *event);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/MilesAudioDevice/MilesAudioManager.h
class MilesAudioManager : public SoundManager
{
public:
	bool checkForSample(AudioRequest *request);
};

bool MilesAudioManager::checkForSample(AudioRequest *request)
{
	if (request->m_pendingEvent == 0) {
		return true;
	}

	if (request->m_pendingEvent->m_info == 0) {
		getInfoForAudioEvent(request->m_pendingEvent);
	}

	if (request->m_pendingEvent->m_info->m_type != 2) {
		return true;
	}

	return canPlayNow(request->m_pendingEvent);
}
