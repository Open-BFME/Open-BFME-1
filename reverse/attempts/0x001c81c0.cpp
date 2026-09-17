// ?setDisabledUntil@Object@@QAEXW4DisabledType@@I@Z
// partial score=0.416 date=2026-09-17
// Object::setDisabledUntil, retail 0x001C81C0.
// cl: /DNDEBUG /MD /EHsc

typedef bool Bool;
typedef unsigned int UnsignedInt;

class AsciiString { unsigned int m_data; };
struct Coord3D { float x, y, z; };

class AudioEventRTS
{
public:
	AudioEventRTS(const AsciiString &, int);
	virtual ~AudioEventRTS();
	AudioEventRTS &operator=(const AudioEventRTS &);
	void setPosition(const Coord3D *);
private:
	unsigned char m_data[0x6C];
};

enum DisabledType { DISABLED_PLACEHOLDER };
enum KindOfType { KINDOF_PLACEHOLDER };

class DisabledBits
{
public:
	void set(UnsignedInt bit, Bool value);
	unsigned int m_bits;
};

class AudioClient
{
public:
#define APAD(n) virtual void apad##n();
	APAD(0) APAD(1) APAD(2) APAD(3) APAD(4) APAD(5) APAD(6) APAD(7)
	APAD(8) APAD(9) APAD(10) APAD(11) APAD(12) APAD(13) APAD(14) APAD(15) APAD(16)
	virtual void addAudioEvent(AudioEventRTS *event);
	APAD(18) APAD(19) APAD(20) APAD(21) APAD(22) APAD(23) APAD(24) APAD(25)
	APAD(26) APAD(27) APAD(28) APAD(29) APAD(30) APAD(31) APAD(32) APAD(33)
	APAD(34) APAD(35) APAD(36) APAD(37) APAD(38) APAD(39) APAD(40) APAD(41)
	APAD(42) APAD(43) APAD(44) APAD(45) APAD(46) APAD(47) APAD(48) APAD(49)
	APAD(50) APAD(51) APAD(52) APAD(53) APAD(54) APAD(55) APAD(56) APAD(57)
	APAD(58) APAD(59) APAD(60) APAD(61) APAD(62) APAD(63) APAD(64) APAD(65)
	APAD(66) APAD(67) APAD(68) APAD(69) APAD(70) APAD(71) APAD(72)
	virtual void *getMiscAudio();
#undef APAD
};

class Drawable { public: unsigned char m_pad[0x114]; unsigned int m_status; };

class Object;
class Contain
{
public:
#define CPAD(n) virtual void cpad##n();
	CPAD(0) CPAD(1) CPAD(2) CPAD(3) CPAD(4) CPAD(5) CPAD(6) CPAD(7)
	CPAD(8) CPAD(9) CPAD(10) CPAD(11) CPAD(12) CPAD(13) CPAD(14) CPAD(15)
	CPAD(16) CPAD(17) CPAD(18) CPAD(19) CPAD(20) CPAD(21) CPAD(22) CPAD(23)
	CPAD(24) CPAD(25) CPAD(26) CPAD(27) CPAD(28) CPAD(29) CPAD(30) CPAD(31)
	CPAD(32) CPAD(33) CPAD(34) CPAD(35) CPAD(36) CPAD(37) CPAD(38) CPAD(39)
	CPAD(40) CPAD(41) CPAD(42) CPAD(43) CPAD(44) CPAD(45) CPAD(46) CPAD(47)
	CPAD(48) CPAD(49) CPAD(50) CPAD(51) CPAD(52) CPAD(53) CPAD(54) CPAD(55)
	CPAD(56) CPAD(57) CPAD(58) CPAD(59) CPAD(60) CPAD(61) CPAD(62) CPAD(63)
	CPAD(64) CPAD(65) CPAD(66)
	virtual Object *getRider();
#undef CPAD
};

struct GameLogic { unsigned char m_pad[0x3C]; UnsignedInt m_frame; };

class Object
{
public:
	void setDisabledUntil(DisabledType type, UnsignedInt frame);
	Bool isKindOf(KindOfType type) const;
	Bool isDisabled() const { return m_disabledMask.m_bits != 0; }
	void pauseAllSpecialPowers(Bool pause) const;
	void onDisabledEdge(Bool disabled);
private:
	unsigned char m_toPosition[0x38];
	Coord3D m_position;
	unsigned char m_toDrawable[0x80 - 0x44];
	Drawable *m_drawable;
	unsigned char m_toDisabled[0x1A4 - 0x84];
	DisabledBits m_disabledMask;
	UnsignedInt m_disabledTillFrame[11];
	unsigned char m_toContain[0x1FC - 0x1D4];
	Contain *m_contain;
};

extern AudioClient *TheAudioClientUpdate;
extern GameLogic *TheBfmeGameLogic;

#pragma comment(linker, "/alternatename:??0AudioEventRTS@@QAE@ABVAsciiString@@H@Z=?j_00025306@@YAXXZ")
#pragma comment(linker, "/alternatename:??1AudioEventRTS@@UAE@XZ=?j_00026f35@@YAXXZ")
#pragma comment(linker, "/alternatename:??4AudioEventRTS@@QAEAAV0@ABV0@@Z=?j_0001f753@@YAXXZ")
#pragma comment(linker, "/alternatename:?setPosition@AudioEventRTS@@QAEXPBUCoord3D@@@Z=?j_00001e88@@YAXXZ")
#pragma comment(linker, "/alternatename:?isKindOf@Object@@QBE_NW4KindOfType@@@Z=?j_0003251f@@YAXXZ")
#pragma comment(linker, "/alternatename:?pauseAllSpecialPowers@Object@@QBEX_N@Z=?j_00023e11@@YAXXZ")
#pragma comment(linker, "/alternatename:?set@DisabledBits@@QAEXI_N@Z=?j_0001800c@@YAXXZ")
#pragma comment(linker, "/alternatename:?onDisabledEdge@Object@@IAEX_N@Z=?j_00045430@@YAXXZ")

void Object::setDisabledUntil(DisabledType type, UnsignedInt frame)
{
	int disabledType = (int)type;
	Object *self = this;
	Bool edgeCase = !self->isDisabled();
	if (disabledType < 0 || disabledType >= 11)
		return;

	AudioEventRTS sound(*(const AsciiString *)0x01336E50, 0);
	if (disabledType == 5 && !self->isKindOf((KindOfType)0x48))
	{
		sound = *(AudioEventRTS *)((char *)TheAudioClientUpdate->getMiscAudio() + 0x7E0);
		sound.setPosition(&self->m_position);
		TheAudioClientUpdate->addAudioEvent(&sound);
	}
	else if (disabledType == 6 || disabledType == 2)
	{
		if ((self->m_disabledMask.m_bits & 0x40) == 0 &&
			(self->m_disabledMask.m_bits & 0x04) == 0)
		{
			if (self->isKindOf((KindOfType)7))
			{
				sound = *(AudioEventRTS *)((char *)TheAudioClientUpdate->getMiscAudio() + 0x620);
				sound.setPosition(&self->m_position);
				TheAudioClientUpdate->addAudioEvent(&sound);
			}
			else if (self->isKindOf((KindOfType)9))
			{
				sound = *(AudioEventRTS *)((char *)TheAudioClientUpdate->getMiscAudio() + 0x700);
				sound.setPosition(&self->m_position);
				TheAudioClientUpdate->addAudioEvent(&sound);
			}
		}
	}

	if (self->m_disabledTillFrame[disabledType] != frame)
	{
		if (disabledType != 3 && (self->m_disabledMask.m_bits & (1U << disabledType)) == 0)
			self->pauseAllSpecialPowers(true);
		self->m_disabledTillFrame[disabledType] = frame;
		self->m_disabledMask.set((UnsignedInt)disabledType, frame > TheBfmeGameLogic->m_frame);
		if (self->m_drawable && self->m_disabledMask.m_bits != 0 && disabledType != 3 &&
			disabledType != 9 && disabledType != 5 && disabledType != 4 && disabledType != 8)
			self->m_drawable->m_status |= 1;
		if (self->m_contain)
		{
			Object *rider = self->m_contain->getRider();
			if (rider)
				rider->setDisabledUntil((DisabledType)disabledType, frame);
		}
	}
	if (edgeCase)
		self->onDisabledEdge(true);
}
