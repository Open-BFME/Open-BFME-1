// ?clearDisabled@Object@@QAE_NW4DisabledType@@@Z
// partial score=0.92 date=2026-09-06
// cl: /DNDEBUG /MD /EHsc
// BFME 1 Object::clearDisabled at RVA 0x001C8440.

typedef bool Bool;

enum DisabledType
{
	DISABLED_DEFAULT,
	DISABLED_HACKED,
	DISABLED_EMP,
	DISABLED_HELD,
	DISABLED_PARALYZED,
	DISABLED_UNMANNED,
	DISABLED_UNDERPOWERED,
	DISABLED_FREEFALL,
	DISABLED_SUBDUED,
	DISABLED_SCRIPT_DISABLED,
	DISABLED_SCRIPT_UNDERPOWERED,
	DISABLED_COUNT
};

enum TintStatus
{
	TINT_STATUS_DISABLED = 1
};

template<int count>
class BitFlags
{
public:
	BitFlags() : m_bits(0) {}
	explicit BitFlags(unsigned int bits) : m_bits(bits) {}

	Bool test(int bit) const
	{
		return (m_bits & (1U << (bit & 31))) != 0;
	}

	void set(int bit, Bool value)
	{
		if (value)
			m_bits |= 1U << (bit & 31);
		else
			m_bits &= ~(1U << (bit & 31));
	}

	Bool any() const
	{
		return m_bits != 0;
	}

	int countInverseIntersection(const BitFlags &that) const;

	public:
	unsigned int m_bits;
};

typedef BitFlags<DISABLED_COUNT> DisabledMaskType;

class AsciiString
{
};

struct Rva002E5FF0Str
{
	void *m_data;
};

extern Rva002E5FF0Str Rva01336E50Str;

struct Coord3D
{
	float x;
	float y;
	float z;
};

class AudioEventRTS
{
public:
	AudioEventRTS(const AsciiString &eventName, int ownerID);
	~AudioEventRTS();
	AudioEventRTS &operator=(const AudioEventRTS &that);
	void setPosition(const Coord3D *position);

private:
	unsigned char m_data[0x70];
};

class Rva005A00B0AudioClient
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot0a();
	virtual void slot0b();
	virtual void slot0c();
	virtual void slot0d();
	virtual void slot0e();
	virtual void slot0f();
	virtual void slot10();
	virtual void addAudioEvent(AudioEventRTS *event);
	virtual void slot18();
	virtual void slot19();
	virtual void slot1a();
	virtual void slot1b();
	virtual void slot1c();
	virtual void slot1d();
	virtual void slot1e();
	virtual void slot1f();
	virtual void slot20();
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual void slot24();
	virtual void slot25();
	virtual void slot26();
	virtual void slot27();
	virtual void slot28();
	virtual void slot29();
	virtual void slot2a();
	virtual void slot2b();
	virtual void slot2c();
	virtual void slot2d();
	virtual void slot2e();
	virtual void slot2f();
	virtual void slot30();
	virtual void slot31();
	virtual void slot32();
	virtual void slot33();
	virtual void slot34();
	virtual void slot35();
	virtual void slot36();
	virtual void slot37();
	virtual void slot38();
	virtual void slot39();
	virtual void slot3a();
	virtual void slot3b();
	virtual void slot3c();
	virtual void slot3d();
	virtual void slot3e();
	virtual void slot3f();
	virtual void slot40();
	virtual void slot41();
	virtual void slot42();
	virtual void slot43();
	virtual void slot44();
	virtual void slot45();
	virtual void slot46();
	virtual void slot47();
	virtual void slot48();
	virtual void slot49();
	virtual void slot4a();
	virtual void slot4b();
	virtual void slot4c();
	virtual void slot4d();
	virtual void slot4e();
	virtual void *getMiscAudio();
};

extern Rva005A00B0AudioClient *TheAudioClientUpdate;

enum KindOfType
{
	KINDOF_STRUCTURE = 7,
	KINDOF_VEHICLE = 9
};

class Thing
{
public:
	Bool isKindOf(KindOfType kindOf) const;
};

class BfmeClear4D0
{
public:
	Bool bfmeClear4D0(int type);
};

class ContainModuleInterface
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot0a();
	virtual void slot0b();
	virtual void slot0c();
	virtual void slot0d();
	virtual void slot0e();
	virtual void slot0f();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual void slot1a();
	virtual void slot1b();
	virtual void slot1c();
	virtual void slot1d();
	virtual void slot1e();
	virtual void slot1f();
	virtual void slot20();
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual void slot24();
	virtual void slot25();
	virtual void slot26();
	virtual void slot27();
	virtual void slot28();
	virtual void slot29();
	virtual void slot2a();
	virtual void slot2b();
	virtual void slot2c();
	virtual void slot2d();
	virtual void slot2e();
	virtual void slot2f();
	virtual void slot30();
	virtual void slot31();
	virtual void slot32();
	virtual void slot33();
	virtual void slot34();
	virtual void slot35();
	virtual void slot36();
	virtual void slot37();
	virtual void slot38();
	virtual void slot39();
	virtual void slot3a();
	virtual void slot3b();
	virtual void slot3c();
	virtual void slot3d();
	virtual void slot3e();
	virtual void slot3f();
	virtual void slot40();
	virtual void slot41();
	virtual void slot42();
	virtual BfmeClear4D0 *friend_getRider();
};

class Object : public Thing
{
public:
	Bool clearDisabled(DisabledType type);
	void pauseAllSpecialPowers(Bool disabling) const;
	void checkDisabledStatus();

protected:
	void onDisabledEdge(Bool becomingDisabled);

private:
	unsigned char m_pad00[0x38];
	unsigned char m_position[sizeof(Coord3D)];
	unsigned char m_pad3c[0x3c];
	void *m_drawable;
	unsigned char m_pad84[0x120];
	DisabledMaskType m_disabledMask;
	unsigned int m_disabledTillFrame[DISABLED_COUNT];
	unsigned char m_pad1d4[0x28];
	ContainModuleInterface *m_contain;
};

#pragma comment(linker, "/alternatename:??0AudioEventRTS@@QAE@ABVAsciiString@@H@Z=?j_00025306@@YAXXZ")
#pragma comment(linker, "/alternatename:??1AudioEventRTS@@QAE@XZ=?j_00026f35@@YAXXZ")
#pragma comment(linker, "/alternatename:??4AudioEventRTS@@QAEAAV0@ABV0@@Z=?j_0001f753@@YAXXZ")
#pragma comment(linker, "/alternatename:?setPosition@AudioEventRTS@@QAEXPBUCoord3D@@@Z=?j_00001e88@@YAXXZ")
#pragma comment(linker, "/alternatename:?countInverseIntersection@?$BitFlags@$0L@@@QBEHABV1@@Z=?j_000108f2@@YAXXZ")
#pragma comment(linker, "/alternatename:?pauseAllSpecialPowers@Object@@QBEX_N@Z=?j_00023e11@@YAXXZ")
#pragma comment(linker, "/alternatename:?checkDisabledStatus@Object@@QAEXXZ=?j_0001c85f@@YAXXZ")
#pragma comment(linker, "/alternatename:?onDisabledEdge@Object@@IAEX_N@Z=?j_00045430@@YAXXZ")

extern void j_00001e88();
extern void j_000108f2();
extern void j_0001c85f();
extern void j_0001f753();
extern void j_00023e11();
extern void j_0003251f();
extern void j_0003c06a();
extern void j_00043c8e();
extern void j_00045430();

struct BfmeAudioAssignCall
{
	AudioEventRTS &call(const AudioEventRTS &event);
};

struct BfmeAudioSetPositionCall
{
	void call(const Coord3D *position);
};

struct BfmeCountInverseIntersectionCall
{
	int call(const DisabledMaskType &that) const;
};

struct BfmePauseCall
{
	void call(Bool disabling) const;
};

struct BfmeCheckCall
{
	void call();
};

struct BfmeEdgeCall
{
	void call(Bool becomingDisabled);
};

struct BfmeTintCall
{
	void call(int statusBits);
};

static __forceinline void bfmeAudioAssign(AudioEventRTS *sound, const AudioEventRTS *event)
{
	typedef AudioEventRTS &(BfmeAudioAssignCall::*Function)(const AudioEventRTS &);
	union { void (*raw)(void); Function member; } fn;
	fn.raw = j_0001f753;
	(reinterpret_cast<BfmeAudioAssignCall *>(sound)->*fn.member)(*event);
}

static __forceinline void bfmeAudioSetPosition(AudioEventRTS *sound, const Coord3D *position)
{
	typedef void (BfmeAudioSetPositionCall::*Function)(const Coord3D *);
	union { void (*raw)(void); Function member; } fn;
	fn.raw = j_00001e88;
	(reinterpret_cast<BfmeAudioSetPositionCall *>(sound)->*fn.member)(position);
}

static __forceinline int bfmeCountInverseIntersection(const DisabledMaskType *flags,
	const DisabledMaskType *exceptions)
{
	typedef int (BfmeCountInverseIntersectionCall::*Function)(const DisabledMaskType &) const;
	union { void (*raw)(void); Function member; } fn;
	fn.raw = j_000108f2;
	return (reinterpret_cast<const BfmeCountInverseIntersectionCall *>(flags)->*fn.member)(*exceptions);
}

static __forceinline void bfmePause(const Object *object, Bool disabling)
{
	typedef void (BfmePauseCall::*Function)(Bool) const;
	union { void (*raw)(void); Function member; } fn;
	fn.raw = j_00023e11;
	(reinterpret_cast<const BfmePauseCall *>(object)->*fn.member)(disabling);
}

static __forceinline void bfmeCheck(Object *object)
{
	typedef void (BfmeCheckCall::*Function)();
	union { void (*raw)(void); Function member; } fn;
	fn.raw = j_0001c85f;
	(reinterpret_cast<BfmeCheckCall *>(object)->*fn.member)();
}

static __forceinline void bfmeEdge(Object *object, Bool becomingDisabled)
{
	typedef void (BfmeEdgeCall::*Function)(Bool);
	union { void (*raw)(void); Function member; } fn;
	fn.raw = j_00045430;
	(reinterpret_cast<BfmeEdgeCall *>(object)->*fn.member)(becomingDisabled);
}

static __forceinline void bfmeClearTint(void *drawable, int statusBits)
{
	typedef void (BfmeTintCall::*Function)(int);
	union { void (*raw)(void); Function member; } fn;
	fn.raw = j_00043c8e;
	(reinterpret_cast<BfmeTintCall *>(drawable)->*fn.member)(statusBits);
}

static __forceinline Bool bfmeClearRider(BfmeClear4D0 *rider, DisabledType type)
{
	typedef Bool (BfmeClear4D0::*Function)(int);
	union { void (*raw)(void); Function member; } fn;
	fn.raw = j_0003c06a;
	return (rider->*fn.member)(type);
}

Bool Object::clearDisabled(DisabledType type)
{
	if (type < 0 || type >= DISABLED_COUNT)
		return false;

	if (!m_disabledMask.test(type))
		return false;

	if (type == DISABLED_UNDERPOWERED || type == DISABLED_EMP)
	{
		AudioEventRTS sound(reinterpret_cast<const AsciiString &>(Rva01336E50Str), 0);
		if (m_disabledMask.m_bits & 0x40)
		{
			if (type != DISABLED_UNDERPOWERED)
				goto no_reenabled_sound;
		}
		if (m_disabledMask.m_bits & 0x04)
		{
			if (type != DISABLED_EMP)
				goto no_reenabled_sound;
		}

		{
			if (isKindOf(KINDOF_STRUCTURE))
		{
				AudioEventRTS *event = reinterpret_cast<AudioEventRTS *>(
					reinterpret_cast<unsigned char *>(TheAudioClientUpdate->getMiscAudio()) + 0x690);
				bfmeAudioAssign(&sound, event);
				bfmeAudioSetPosition(&sound, reinterpret_cast<const Coord3D *>(m_position));
				TheAudioClientUpdate->addAudioEvent(&sound);
			}
			else if (isKindOf(KINDOF_VEHICLE))
			{
				AudioEventRTS *event = reinterpret_cast<AudioEventRTS *>(
					reinterpret_cast<unsigned char *>(TheAudioClientUpdate->getMiscAudio()) + 0x770);
				bfmeAudioAssign(&sound, event);
				bfmeAudioSetPosition(&sound, reinterpret_cast<const Coord3D *>(m_position));
				TheAudioClientUpdate->addAudioEvent(&sound);
			}
		}
	no_reenabled_sound:;
	}

	if (type != DISABLED_HELD && m_disabledMask.test(type))
		bfmePause(this, false);

	if (m_contain)
	{
		BfmeClear4D0 *rider = m_contain->friend_getRider();
		if (rider && m_disabledTillFrame[type] == 0x3fffffff)
			bfmeClearRider(rider, type);
	}

	m_disabledTillFrame[type] = 0;
	m_disabledMask.m_bits &= ~(1U << (type & 31));

	DisabledMaskType exceptions(0x228);
	if (m_disabledMask.m_bits != 0)
	{
		DisabledMaskType myFlagsMinusExceptions = m_disabledMask;
		if (bfmeCountInverseIntersection(&myFlagsMinusExceptions, &exceptions) != 0)
			goto no_disabled_tint;
	}
	if (m_drawable)
		bfmeClearTint(m_drawable, TINT_STATUS_DISABLED);

no_disabled_tint:;

	bfmeCheck(this);
	if (!m_disabledMask.any())
		bfmeEdge(this, false);

	return true;
}
