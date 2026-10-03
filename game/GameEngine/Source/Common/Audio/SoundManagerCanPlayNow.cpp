// cl: /DNDEBUG /MD /EHsc
//
// The 0x006B7E10 caller and the symbol pin identify SoundManager::canPlayNow.
// Retail returns four stack bytes at +0x191 and begins INT3 padding at +0x194,
// so this body spans 404 bytes. The Zero Hour header marks canPlayNow virtual,
// but BFME's decorated symbol is nonvirtual and retail reads BFME-specific
// fields at +0x00C and +0x608 through +0x614. This TU keeps that measured ABI view
// local, including the two retail vtable slots used by this function.
//
// Retail calls ILT 0x0001D1B0, which jumps to the generated body at 0x006B2110.
// callees.py infers a thiscall with one pointer argument and an EAX result; the
// typed member-pointer call below retains the existing thunk identity.

struct Coord3D
{
	float x, y, z;

	void set(const Coord3D *other)
	{
		x = other->x;
		y = other->y;
		z = other->z;
	}

	void set(float xValue, float yValue, float zValue)
	{
		x = xValue;
		y = yValue;
		z = zValue;
	}
};

struct AudioEventInfo
{
	char m_prefix[0x18];
	float m_minVolume;
	char m_gap1[0x18];
	int m_priority;
	unsigned int m_type;
	unsigned int m_control;
	char m_gap2[0x38];
	float m_maxDistance;
	char m_gap3[8];
	int m_soundType;
};

class AudioEventRTS
{
public:
    bool isPositionalAudio() const;
    void resolveOwnerPosition(Coord3D *position, bool *found);

    unsigned char m_prefix[8];
    AudioEventInfo *m_info;
};

struct BfmeSoundRange
{
	char m_gap00[0x38];
	int m_rva_038;
	char m_gap3C[0x3c];
	float m_rva_078;
	float m_rva_07C;
};

class SoundManager
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
	virtual void slot16(); virtual void slot17(); virtual void slot18(); virtual void slot19();
	virtual void slot20(); virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void slot24(); virtual void slot25(); virtual void slot26(); virtual void slot27();
	virtual void slot28(); virtual void slot29(); virtual void slot30(); virtual void slot31();
	virtual void slot32(); virtual void slot33(); virtual void slot34(); virtual void slot35();
	virtual void slot36(); virtual void slot37(); virtual void slot38(); virtual void slot39();
	virtual void slot40(); virtual void slot41(); virtual void slot42(); virtual void slot43();
	virtual void slot44(); virtual void slot45(); virtual void slot46(); virtual void slot47();
	virtual void slot48(); virtual void slot49(); virtual void slot50(); virtual void slot51();
	virtual void slot52(); virtual void slot53(); virtual void slot54(); virtual void slot55();
	virtual void slot56(); virtual void slot57(); virtual void slot58(); virtual void slot59();
	virtual void slot60(); virtual void slot61(); virtual void slot62(); virtual void slot63();
	virtual void slot64(); virtual void slot65(); virtual void slot66();
	virtual const Coord3D *slot67();
	virtual void slot68(); virtual void slot69(); virtual void slot70(); virtual void slot71();
	virtual void slot72(); virtual void slot73(); virtual void slot74(); virtual void slot75();
	virtual void slot76(); virtual void slot77(); virtual void slot78(); virtual void slot79();
	virtual void slot80(); virtual void slot81(); virtual void slot82(); virtual void slot83();
	virtual void slot84(); virtual void slot85(); virtual void slot86(); virtual void slot87();
	virtual void slot88(); virtual void slot89(); virtual void slot90(); virtual void slot91();
	virtual void slot92(); virtual void slot93(); virtual void slot94(); virtual void slot95();
	virtual void slot96(); virtual void slot97();
	virtual bool slot98(AudioEventRTS *event);

protected:
	virtual bool violatesVoice(AudioEventRTS *event);

public:
	bool canPlayNow(AudioEventRTS *event);

private:
	char m_prefix[8];
	BfmeSoundRange *m_rva_00C;
	char m_pad10[0x5f8];
	unsigned int m_num2DSamples;
	unsigned int m_num3DSamples;
	unsigned int m_numPlaying2DSamples;
	unsigned int m_numPlaying3DSamples;
};

class MilesAudioManager
{
public:
	bool doesViolateLimit(AudioEventRTS *event) const;
	bool isPlayingAlready(AudioEventRTS *event) const;
};

class Rva006B2110
{
public:
	bool method(AudioEventRTS *event) const;
};
extern void j_0001d1b0();

bool SoundManager::canPlayNow(AudioEventRTS *event)
{
	register unsigned char soundTypeBit = 8;

	if (event->isPositionalAudio()) {
		if (!(event->m_info->m_type & soundTypeBit) && event->m_info->m_priority != 4) {
			if (!(event->m_info->m_minVolume >= m_rva_00C->m_rva_07C)) {
				Coord3D position;
				bool found;
				event->resolveOwnerPosition(&position, &found);
				Coord3D listener;
				const Coord3D *listenerPosition = slot67();
				listener.set(listenerPosition);
				if (!found)
					return false;
				float dx = listener.x - position.x;
				float dy = listener.y - position.y;
				float dz = listener.z - position.z;
				float range;
				if (event->m_info->m_type & soundTypeBit) {
					void *state = *(void **)((char *)this + 0xc);
					range = (float)*(int *)((char *)state + 0x38);
				} else {
					range = event->m_info->m_maxDistance;
				}
				if (dx * dx + dy * dy + dz * dz >= range * range)
					return false;
				if (slot98(event)) {
					*((unsigned char *)event + 0x47) = 1;
					return false;
				}
			}
		}
	}

	if (SoundManager::violatesVoice(event)) {
		unsigned char voiceFlag = (event->m_info->m_control >> 3) & 1;
		return voiceFlag;
	}

	if (((const MilesAudioManager *)this)->doesViolateLimit(event))
		return false;

	if (event->m_info->m_control & soundTypeBit)
		return true;

	if (event->m_info->m_soundType != 2)
		return true;

	if (event->isPositionalAudio()) {
		if (m_numPlaying3DSamples < m_num3DSamples)
			return true;
	} else if (m_numPlaying2DSamples < m_num2DSamples) {
		return true;
	}

	typedef bool (Rva006B2110::*LowerPriority)(AudioEventRTS *) const;
	union { void (*raw)(void); LowerPriority method; } call;
	call.raw = j_0001d1b0;
	if ((((Rva006B2110 *)this)->*call.method)(event))
		return true;

	if (event->m_info->m_control & soundTypeBit) {
		bool retVal = ((const MilesAudioManager *)this)->isPlayingAlready(event);
		if (retVal)
			return true;
		else
			return false;
	}

	return false;
}
