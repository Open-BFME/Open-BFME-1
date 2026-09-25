// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

typedef unsigned int UnsignedInt;
typedef float Real;

enum ObjectID
{
	INVALID_ID = 0
};

struct RGBColor;

class BfmeThingBXF
{
public:
	void bfmeThenBXF(int value);
};

struct RGBColor
{
	Real red;
	Real green;
	Real blue;
};

class AudioEventRTS
{
public:
	AudioEventRTS(const AudioEventRTS &right);
	~AudioEventRTS();
	void setObjectID(UnsignedInt objectID);

private:
	unsigned char m_storage[0x70];
};

#pragma comment(linker, "/alternatename:?friend_setUndetectedDefector@Object@@QAEX_N@Z=?j_0001c864@@YAXXZ")
#pragma comment(linker, "/alternatename:?bfmeThenBXF@BfmeThingBXF@@QAEXH@Z=?j_0004067e@@YAXXZ")
#pragma comment(linker, "/alternatename:??0AudioEventRTS@@QAE@ABV0@@Z=?j_00047b27@@YAXXZ")
#pragma comment(linker, "/alternatename:?setObjectID@AudioEventRTS@@QAEXI@Z=?j_00019a6a@@YAXXZ")
#pragma comment(linker, "/alternatename:??1AudioEventRTS@@QAE@XZ=?j_00026f35@@YAXXZ")
#pragma comment(linker, "/alternatename:__ftol2=_ftol2")

class Rva005A00B0AudioClient
{
public:
#define BFME_AUDIO_SLOT(n) virtual void slot##n();
	BFME_AUDIO_SLOT(0) BFME_AUDIO_SLOT(1) BFME_AUDIO_SLOT(2) BFME_AUDIO_SLOT(3)
	BFME_AUDIO_SLOT(4) BFME_AUDIO_SLOT(5) BFME_AUDIO_SLOT(6) BFME_AUDIO_SLOT(7)
	BFME_AUDIO_SLOT(8) BFME_AUDIO_SLOT(9) BFME_AUDIO_SLOT(10)
	BFME_AUDIO_SLOT(11) BFME_AUDIO_SLOT(12) BFME_AUDIO_SLOT(13) BFME_AUDIO_SLOT(14)
	BFME_AUDIO_SLOT(15) BFME_AUDIO_SLOT(16)
	virtual unsigned int addAudioEvent(AudioEventRTS *event);
	BFME_AUDIO_SLOT(18) BFME_AUDIO_SLOT(19) BFME_AUDIO_SLOT(20) BFME_AUDIO_SLOT(21)
	BFME_AUDIO_SLOT(22) BFME_AUDIO_SLOT(23) BFME_AUDIO_SLOT(24) BFME_AUDIO_SLOT(25)
	BFME_AUDIO_SLOT(26) BFME_AUDIO_SLOT(27) BFME_AUDIO_SLOT(28) BFME_AUDIO_SLOT(29)
	BFME_AUDIO_SLOT(30) BFME_AUDIO_SLOT(31) BFME_AUDIO_SLOT(32) BFME_AUDIO_SLOT(33)
	BFME_AUDIO_SLOT(34) BFME_AUDIO_SLOT(35) BFME_AUDIO_SLOT(36) BFME_AUDIO_SLOT(37)
	BFME_AUDIO_SLOT(38) BFME_AUDIO_SLOT(39) BFME_AUDIO_SLOT(40) BFME_AUDIO_SLOT(41)
	BFME_AUDIO_SLOT(42) BFME_AUDIO_SLOT(43) BFME_AUDIO_SLOT(44) BFME_AUDIO_SLOT(45)
	BFME_AUDIO_SLOT(46) BFME_AUDIO_SLOT(47) BFME_AUDIO_SLOT(48) BFME_AUDIO_SLOT(49)
	BFME_AUDIO_SLOT(50) BFME_AUDIO_SLOT(51) BFME_AUDIO_SLOT(52) BFME_AUDIO_SLOT(53)
	BFME_AUDIO_SLOT(54) BFME_AUDIO_SLOT(55) BFME_AUDIO_SLOT(56) BFME_AUDIO_SLOT(57)
	BFME_AUDIO_SLOT(58) BFME_AUDIO_SLOT(59) BFME_AUDIO_SLOT(60) BFME_AUDIO_SLOT(61)
	BFME_AUDIO_SLOT(62) BFME_AUDIO_SLOT(63) BFME_AUDIO_SLOT(64) BFME_AUDIO_SLOT(65)
	BFME_AUDIO_SLOT(66) BFME_AUDIO_SLOT(67) BFME_AUDIO_SLOT(68) BFME_AUDIO_SLOT(69)
	BFME_AUDIO_SLOT(70) BFME_AUDIO_SLOT(71) BFME_AUDIO_SLOT(72)
	virtual void *getMiscAudio();
	BFME_AUDIO_SLOT(74) BFME_AUDIO_SLOT(75) BFME_AUDIO_SLOT(76) BFME_AUDIO_SLOT(77)
	BFME_AUDIO_SLOT(78)
#undef BFME_AUDIO_SLOT
};

#define TheAudioClientUpdate (*(Rva005A00B0AudioClient **)0x012ED668)

struct Rva00367E30Logic
{
	unsigned char m_padding[0x3c];
	UnsignedInt m_frame;
};

extern const Real g_bfmeUint32Scale;
extern const Real g_bfmeDefaultBU;
extern const Real g_bfmeK1253;

#define Rva0107C6EC (*(const Real *)0x0107C6EC)
#define TheBfmeGameLogic (*(Rva00367E30Logic **)0x012F0898)

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1,
	UPDATE_SLEEP_FOREVER = 0x3fffffff
};

class Object;

class UpdateModule
{
public:
	virtual void updateModuleAnchor();

protected:
	void setWakeFrame(Object *, UpdateSleepTime);
	void *m_moduleData;
	Object *m_object;
};

class ObjectHelper : public UpdateModule
{
public:
	virtual ~ObjectHelper();
};

class BehaviorModuleInterface
{
public:
	virtual void behaviorModuleInterfaceAnchor();
};

class UpdateModuleInterface
{
public:
	virtual UpdateSleepTime update();
};

class ObjectStatusBits
{
public:
	bool test(int bit) const
	{
		return (m_bits[bit >> 5] & (1 << (bit & 31))) != 0;
	}

private:
	UnsignedInt m_bits[3];
};

#define BFME_HAVE_OBJECTID
#define OBJECT_TU_MEMBERS \
	void friend_setUndetectedDefector(bool); \
	bool getIsUndetectedDefector() const { return (m_privateStatus & 2) != 0; } \
	bool isEffectivelyDead() const { return (m_privateStatus & 1) != 0; } \
	AIUpdateInterface *getAI() const { return m_ai; } \
	ObjectID getID() const { return m_id; } \
	const ObjectStatusBits &getStatusBits() const { return *(const ObjectStatusBits *)m_status; }
#include "../object.h"

class ObjectDefectionHelper : public ObjectHelper,
	public BehaviorModuleInterface,
	public UpdateModuleInterface
{
public:
	virtual UpdateSleepTime update();

private:
	unsigned char m_padding[0xc];
	UnsignedInt m_defectionDetectionStart;
	UnsignedInt m_defectionDetectionEnd;
	Real m_defectionDetectionFlashPhase;
	bool m_doDefectorFX;
};

UpdateSleepTime ObjectDefectionHelper::update()
{
	Object *obj = m_object;
	BfmeThingBXF *draw = reinterpret_cast<BfmeThingBXF *>(obj->getDrawable());

	if (!obj->getIsUndetectedDefector())
		return UPDATE_SLEEP_FOREVER;

	UnsignedInt now = TheBfmeGameLogic->m_frame;
	if (now >= m_defectionDetectionEnd)
	{
		obj->friend_setUndetectedDefector(false);
		if (draw && m_doDefectorFX)
		{
			RGBColor white = {1, 1, 1};
			draw->bfmeThenBXF((int)&white);
			{
				AudioEventRTS sound = *reinterpret_cast<AudioEventRTS *>(
					(char *)TheAudioClientUpdate->getMiscAudio() + 0x2a0);
				sound.setObjectID(obj->getID());
				TheAudioClientUpdate->addAudioEvent(&sound);
			}
		}
		return UPDATE_SLEEP_FOREVER;
	}

	if ((obj->getAI() != 0 && obj->isEffectivelyDead()) ||
		(obj->m_status[0] & 0x2000))
	{
		obj->friend_setUndetectedDefector(false);
		return UPDATE_SLEEP_FOREVER;
	}

	if (draw && m_doDefectorFX)
	{
		bool lastPhase = (((int)m_defectionDetectionFlashPhase) & 1) != 0;
		UnsignedInt timeLeft = m_defectionDetectionEnd - now;
		m_defectionDetectionFlashPhase += g_bfmeK1253 *
			(g_bfmeDefaultBU - (Real)timeLeft * Rva0107C6EC);
		bool thisPhase = (((int)m_defectionDetectionFlashPhase) & 1) != 0;

		if (lastPhase && !thisPhase)
		{
			draw->bfmeThenBXF(0);
			{
				AudioEventRTS sound = *reinterpret_cast<AudioEventRTS *>(
					(char *)TheAudioClientUpdate->getMiscAudio() + 0x230);
				sound.setObjectID(obj->getID());
				TheAudioClientUpdate->addAudioEvent(&sound);
			}
		}
	}

	return UPDATE_SLEEP_NONE;
}
