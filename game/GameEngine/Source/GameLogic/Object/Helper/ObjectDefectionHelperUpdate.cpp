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
};

struct RGBColor
{
	Real red;
	Real green;
	Real blue;
};

extern void j_0001c864();
extern void j_0004067e();
extern void j_00047b27();
extern void j_00019a6a();
extern void j_00026f35();

// TU-local view of retail's 0x70-byte AudioEventRTS. The real copy constructor
// and destructor (??0/??1AudioEventRTS) already have their own bodies in
// AudioEventRTSCopyAndLifetime.cpp, so they are not defined here; retail calls
// them through the ILTs at 0x00047B27 and 0x00026F35.
class AudioEventRTS
{
public:
	unsigned char m_storage[0x70];
};

// Retail's temp is a real object with a constructor and a destructor: that is
// what puts the unwind table and the 0x70-byte stack slot in the frame. Both
// bodies dispatch through the retail ILT rather than being written here.
class AudioEventRTSTemp
{
public:
	AudioEventRTSTemp(const AudioEventRTSTemp &right)
	{
		union
		{
			void (*address)();
			void (AudioEventRTSTemp::*member)(const AudioEventRTSTemp &);
		} call;
		call.address = j_00047b27;
		(this->*call.member)(right);
	}
	~AudioEventRTSTemp()
	{
		union
		{
			void (*address)();
			void (AudioEventRTSTemp::*member)();
		} call;
		call.address = j_00026f35;
		(this->*call.member)();
	}

private:
	unsigned char m_storage[0x70];
};

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

class AudioManager;
extern AudioManager *TheAudio;
static inline Rva005A00B0AudioClient *TheAudioClientUpdateView() { return (Rva005A00B0AudioClient *)TheAudio; }

struct Rva00367E30Logic
{
	unsigned char m_padding[0x3c];
	UnsignedInt m_frame;
};

extern const Real g_bfmeUint32Scale;
extern const Real g_bfmeDefaultBU;
extern const Real g_rva0107533C;

class GameLogic;
extern GameLogic *TheGameLogic;
static inline Rva00367E30Logic *TheBfmeGameLogicView() { return (Rva00367E30Logic *)TheGameLogic; }

#define Rva0107C6EC 0.02f

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
	bool getIsUndetectedDefector() const { return (m_privateStatus & 2) != 0; } \
	bool isEffectivelyDead() const { return (m_privateStatus & 1) != 0; } \
	AIUpdateInterface *getAI() const { return m_ai; } \
	ObjectID getID() const { return m_id; } \
	const ObjectStatusBits &getStatusBits() const { return *(const ObjectStatusBits *)m_status; }
#include "../object.h"

// Retail calls these bodies through incremental-link thunks, so the calls are
// Retail calls these bodies through incremental-link thunks, so each call site
// dispatches through a member pointer whose ABI matches the retail member and
// whose address is the thunk. No linker alias directive needed.

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

	UnsignedInt now = TheBfmeGameLogicView()->m_frame;
	if (now >= m_defectionDetectionEnd)
	{
		union
		{
			void (*address)();
			void (Object::*member)(bool);
		} call;
		call.address = j_0001c864;
		(obj->*call.member)(false);
		if (draw && m_doDefectorFX)
		{
			RGBColor white = {1, 1, 1};
			union
			{
				void (*address)();
				void (BfmeThingBXF::*member)(int);
			} callBxf;
			callBxf.address = j_0004067e;
			(draw->*callBxf.member)((int)&white);
			{
				AudioEventRTSTemp sound = *reinterpret_cast<AudioEventRTSTemp *>(
					(char *)TheAudioClientUpdateView()->getMiscAudio() + 0x2a0);
				union
				{
					void (*address)();
					void (AudioEventRTSTemp::*member)(UnsignedInt);
				} callSetID;
				callSetID.address = j_00019a6a;
				(sound.*callSetID.member)(obj->getID());
				TheAudioClientUpdateView()->addAudioEvent(
					reinterpret_cast<AudioEventRTS *>(&sound));
			}
		}
		return UPDATE_SLEEP_FOREVER;
	}

	if ((obj->getAI() != 0 && obj->isEffectivelyDead()) ||
		(obj->m_status[0] & 0x2000))
	{
		union
		{
			void (*address)();
			void (Object::*member)(bool);
		} call;
		call.address = j_0001c864;
		(obj->*call.member)(false);
		return UPDATE_SLEEP_FOREVER;
	}

	if (draw && m_doDefectorFX)
	{
		bool lastPhase = (((int)m_defectionDetectionFlashPhase) & 1) != 0;
		UnsignedInt timeLeft = m_defectionDetectionEnd - now;
		m_defectionDetectionFlashPhase += g_rva0107533C *
			(g_bfmeDefaultBU - (Real)timeLeft * Rva0107C6EC);
		bool thisPhase = (((int)m_defectionDetectionFlashPhase) & 1) != 0;

		if (lastPhase && !thisPhase)
		{
			union
			{
				void (*address)();
				void (BfmeThingBXF::*member)(int);
			} callBxf;
			callBxf.address = j_0004067e;
			(draw->*callBxf.member)(0);
			{
				AudioEventRTSTemp sound = *reinterpret_cast<AudioEventRTSTemp *>(
					(char *)TheAudioClientUpdateView()->getMiscAudio() + 0x230);
				union
				{
					void (*address)();
					void (AudioEventRTSTemp::*member)(UnsignedInt);
				} callSetID;
				callSetID.address = j_00019a6a;
				(sound.*callSetID.member)(obj->getID());
				TheAudioClientUpdateView()->addAudioEvent(
					reinterpret_cast<AudioEventRTS *>(&sound));
			}
		}
	}

	return UPDATE_SLEEP_NONE;
}
