// ?canPlayNow@SoundManager@@QAE_NPAVAudioEventRTS@@@Z
// partial score=0.58 date=2026-09-10
// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AudioEventInfo.h
struct AudioEventInfo
{
	unsigned char m_prefix[0x18];
	float m_maxDistance;
	unsigned char m_gap1[0x18];
	int m_priority;
	unsigned int m_flags;
	unsigned int m_control;
	unsigned char m_gap2[0x44];
	int m_type;
};

struct Coord3D
{
	float x;
	float y;
	float z;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AudioEventRTS.h
class AudioEventRTS
{
private:
	unsigned char m_prefix[8];

public:
	AudioEventInfo *m_info;

	bool isPositionalAudio() const;
	void resolveOwnerPosition(Coord3D *position, bool *found);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AudioRequest.h
struct AudioRequest
{
	int m_request;
	AudioEventRTS *m_pendingEvent;
	bool m_usePendingEvent;
	bool m_requiresCheckForSample;
};

struct BfmeSoundRange
{
	unsigned char m_gap38[0x38];
	int m_integerRange;
	unsigned char m_gap3c[0x3c];
	float m_floatRange;
	float m_maxDistance;
};

// BFME's request path calls this policy helper on the Miles object itself;
// the derived request class below preserves that object ABI.
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
	virtual void v44(); virtual void v45(); virtual void v46(); virtual void v47();
	virtual void v48(); virtual void v49(); virtual void v50(); virtual void v51();
	virtual void v52(); virtual void v53(); virtual void v54(); virtual void v55();
	virtual void v56(); virtual void v57(); virtual void v58(); virtual void v59();
	virtual void v60(); virtual void v61(); virtual void v62(); virtual void v63();
	virtual void v64(); virtual void v65(); virtual void v66();
	virtual const Coord3D *getListenerPosition();
	virtual void v68(); virtual void v69(); virtual void v70(); virtual void v71();
	virtual void v72(); virtual void v73(); virtual void v74(); virtual void v75();
	virtual void v76(); virtual void v77(); virtual void v78(); virtual void v79();
	virtual void v80(); virtual void v81(); virtual void v82(); virtual void v83();
	virtual void v84(); virtual void v85(); virtual void v86(); virtual void v87();
	virtual void v88(); virtual void v89(); virtual void v90(); virtual void v91();
	virtual void v92(); virtual void v93(); virtual void v94(); virtual void v95();
	virtual void v96(); virtual void v97();
	virtual bool v98(AudioEventRTS *event);

protected:
	virtual bool violatesVoice(AudioEventRTS *event);

	public:
	bool canPlayNow(AudioEventRTS *event);
	bool doesViolateLimit(AudioEventRTS *event);
	bool isPlayingLowerPriority(AudioEventRTS *event);
	bool isPlayingAlready(AudioEventRTS *event);

private:
	unsigned char m_prefix[8];
	BfmeSoundRange *m_state;
	unsigned char m_padding[0x5f8];
	unsigned int m_num2DSamples;
	unsigned int m_num3DSamples;
	unsigned int m_numPlaying2DSamples;
	unsigned int m_numPlaying3DSamples;
};

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

bool SoundManager::canPlayNow(AudioEventRTS *event)
{
	register unsigned char soundTypeBit = 8;

	if (event->isPositionalAudio()) {
		if (!(event->m_info->m_flags & soundTypeBit) && event->m_info->m_priority != 4) {
			if (!(event->m_info->m_maxDistance >= m_state->m_maxDistance)) {
				Coord3D position;
				bool found;
				event->resolveOwnerPosition(&position, &found);
				Coord3D listener = *getListenerPosition();
				if (!found)
					return false;
				float dx = listener.x - position.x;
				float dy = listener.y - position.y;
				float dz = listener.z - position.z;
				float range;
				if (event->m_info->m_flags & soundTypeBit)
					range = (float)m_state->m_integerRange;
				else
					range = m_state->m_floatRange;
				if (range * range < dx * dx + dy * dy + dz * dz) {
					if (v98(event))
						*((unsigned char *)event + 0x47) = 1;
					return false;
				}
			}
		}
	}

	if (SoundManager::violatesVoice(event)) {
		return (event->m_info->m_control >> 3) & 1;
	}

	if (doesViolateLimit(event))
		return false;

	if (event->m_info->m_control & soundTypeBit)
		return true;

	if (event->m_info->m_type != 2)
		return true;

	if (event->isPositionalAudio()) {
		if (m_numPlaying3DSamples < m_num3DSamples)
			return true;
	} else if (m_numPlaying2DSamples < m_num2DSamples) {
		return true;
	}

	if (isPlayingLowerPriority(event))
		return true;

	if (event->m_info->m_control & soundTypeBit)
		return isPlayingAlready(event);

	return false;
}
