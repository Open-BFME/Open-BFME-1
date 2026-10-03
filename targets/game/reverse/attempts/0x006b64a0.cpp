// ?canPlayNow@SoundManager@@QAE_NPAVAudioEventRTS@@@Z
// partial score=1.0 date=2026-10-02
// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: AudioEventRTS::resolveOwnerPosition, retail 0x000B4020, 367B.
// thiscall, two stack args, `ret 8`. Proves the layout of the owner fields:
//   this+0x2C m_ownerID   this+0x30 m_ownerType
//   this+0x34 m_positionOfAudio  this+0x40 m_found (one byte)
//
// The dispatch table at 0x4B4190 has six entries; 0, 1, 2 and 5 reach four
// distinct bodies and 3 and 4 share the zero-fill at +0x149. Those are exactly
// the m_ownerType values the matched constructors write, and each case's null
// path branches to THAT case's own tail, not to a shared fallback -- so the
// tail sits outside the null test in every arm. Case 5's outer null test
// (Glo012F1028) converges on its own tail the same way.
//
// Two codegen facts this shape depends on, both measured:
//
//  1. Retail keeps FOUR byte-identical 34-byte case tails. MSVC 7.1 cross-jumps
//     identical tails, which is where the ~80-byte deficit of the earlier
//     attempts went. Distinct barrier intrinsics on the last statement before
//     each `return` keep the copies apart at zero byte cost: neither intrinsic
//     emits an instruction or a relocation. All three non-trivial arms need a
//     DISTINCT barrier set; fewer arms merge again.
//
//  2. The cached-position copy must read through a reference-returning
//     getPosition(). A pointer-returning one folds the +0x38 into each load,
//     giving `mov ecx,[eax+0x38]` instead of retail's `add eax,0x38` followed
//     by `lea ecx,[esi+0x34]` with both pointers live in registers.
//
// Case 5's owner-position build needs a NON-volatile Coord3D temporary filled
// through set(x, y, z) and copied back; a volatile one forces an x87
// fld/fst/fstp triple where retail uses plain dword moves.

extern "C" void _WriteBarrier();
#pragma intrinsic(_WriteBarrier)
extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)

typedef int ObjectID;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Matrix/Coord3D.h
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
	float m_maxDistance;
	char m_gap1[0x18];
	int m_priority;
	unsigned int m_flags;
	unsigned int m_control;
	char m_gap2[0x38];
	float m_rva_078;
	char m_gap3[8];
	int m_type;
};

class Object
{
public:
	char m_pad00[0x38];
	Coord3D m_position;

	const Coord3D &getPosition() const { return m_position; }
};

class Drawable
{
public:
	// pinned retail ILT thunk 0x0004B12D: pointer-returning, so the copy below
	// dereferences. Case 2's Object view is inlined instead, which is what lets
	// it keep the add/lea form.
	const Coord3D *getPosition() const;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GameClient.h
class GameClient
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1C();
	virtual void slot20();
	virtual void slot24();
	virtual void slot28();
	virtual Drawable *findDrawableByID(ObjectID id);
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GameLogic.h
class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
};

class LivingWorldOwner
{
public:
	char m_pad00[0x0c];
	float m_x;
	float m_y;
};

class LivingWorldOwnerLookup
{
public:
	void *findOwnerByID(ObjectID id);
};

// The retail global at 0x012F0898 is EA's `GameLogic *TheGameLogic`, defined
// once in game/GameEngine/Source/GameLogic/System/GameLogic.cpp; this TU's
// GameLogic class above is its view of that layout and mangles identically.
extern GameLogic *TheGameLogic;
extern GameClient *TheGameClient;
extern void *Glo012F1028;

class AudioEventRTS
{
public:
	bool isPositionalAudio() const;
	void resolveOwnerPosition(Coord3D *pos, bool *found);

	char m_prefix[8];
	AudioEventInfo *m_info;

	private:
	char m_pad0C[0x20];
	ObjectID m_ownerID;
	int m_ownerType;
	Coord3D m_positionOfAudio;
	volatile bool m_found;
};

void AudioEventRTS::resolveOwnerPosition(Coord3D *pos, bool *found)
{
	Coord3D ownerPosition;

	switch (m_ownerType)
	{
	case 0:
		*found = true;
		pos->x = m_positionOfAudio.x;
		pos->y = m_positionOfAudio.y;
		pos->z = m_positionOfAudio.z;
		return;

	case 2:
		{
			Object *object = TheGameLogic->findObjectByID(m_ownerID);
			if (object != 0)
			{
				m_found = 1;
				m_positionOfAudio = object->getPosition();
			}
			*found = m_found;
			pos->x = m_positionOfAudio.x;
			pos->y = m_positionOfAudio.y;
			pos->z = m_positionOfAudio.z;
			_WriteBarrier();
return;
		}

	case 1:
		{
			Drawable *drawable = TheGameClient->findDrawableByID(m_ownerID);
			if (drawable != 0)
			{
				m_found = 1;
				m_positionOfAudio = *drawable->getPosition();
			}
			*found = m_found;
			pos->set(&m_positionOfAudio);
			_ReadWriteBarrier();
return;
		}

	case 5:
		if (Glo012F1028 != 0)
		{
			LivingWorldOwner *owner = (LivingWorldOwner *)
				((LivingWorldOwnerLookup *)Glo012F1028)->findOwnerByID(m_ownerID);
			if (owner != 0)
			{
				m_found = 1;
				ownerPosition.set(owner->m_x, owner->m_y, 0.0f);
				m_positionOfAudio = ownerPosition;
			}
		}
		*found = m_found;
		pos->x = m_positionOfAudio.x;
		pos->y = m_positionOfAudio.y;
		pos->z = m_positionOfAudio.z;
		_WriteBarrier();
_ReadWriteBarrier();
return;
	}

	*found = false;
	pos->x = 0.0f;
	pos->y = 0.0f;
	pos->z = 0.0f;
}

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

bool SoundManager::canPlayNow(AudioEventRTS *event)
{
	register unsigned char soundTypeBit = 8;

	if (event->isPositionalAudio()) {
		if (!(event->m_info->m_flags & soundTypeBit) && event->m_info->m_priority != 4) {
			if (!(event->m_info->m_maxDistance >= m_rva_00C->m_rva_07C)) {
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
				if (event->m_info->m_flags & soundTypeBit) {
					void *state = *(void **)((char *)this + 0xc);
					range = (float)*(int *)((char *)state + 0x38);
				} else {
					range = event->m_info->m_rva_078;
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

	if (event->m_info->m_type != 2)
		return true;

	if (event->isPositionalAudio()) {
		if (m_numPlaying3DSamples < m_num3DSamples)
			return true;
	} else if (m_numPlaying2DSamples < m_num2DSamples) {
		return true;
	}

	if (((const Rva006B2110 *)this)->method(event))
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
