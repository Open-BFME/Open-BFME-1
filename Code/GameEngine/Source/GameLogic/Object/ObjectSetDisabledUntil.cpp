// ?setDisabledUntil@ObjectSetDisabledUntilShim@@QAEXW4DisabledType@@I@Z
// Clean BFME reconstruction of the pinned incremental-link target at retail 0x001C81C0.
// cl: /DNDEBUG /MD /EHsc

typedef bool Bool;
typedef unsigned int UnsignedInt;

class AsciiString { unsigned int m_data; };
struct Coord3D { float x, y, z; };

class AudioEventRTS
{
public:
	AudioEventRTS(const AsciiString &, int);
	virtual void slot00();
	~AudioEventRTS();
	AudioEventRTS &operator=(const AudioEventRTS &);
	void setPosition(const Coord3D *);
private:
	unsigned char m_data[0x6C];
};

enum DisabledType { DISABLED_PLACEHOLDER };
enum KindOfType { KINDOF_PLACEHOLDER };

class DisabledMaskType
{
public:
	void set(UnsignedInt bit, int value);
		Bool any() const { return m_bits != 0; }
	Bool test(UnsignedInt bit) const { UnsignedInt bits = m_bits; return (bits & (1U << (bit & 31))) != 0; }
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

class Thing
{
public:
	Bool isKindOf(KindOfType type) const;
};

class ObjectSetDisabledUntilShim;

class Object
{
public:
	void setDisabledUntil(DisabledType, UnsignedInt);
	void pauseAllSpecialPowers(Bool pause) const;
protected:
	void onDisabledEdge(Bool disabled);
	friend class ObjectSetDisabledUntilShim;
};
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

class ObjectSetDisabledUntilShim
{
public:
	void setDisabledUntil(DisabledType type, UnsignedInt frame);
	Bool isDisabled() const { return m_disabledMask.any(); }
	Bool isDisabledByType(DisabledType type) const { return m_disabledMask.test((UnsignedInt)type); }
	const Coord3D *getPosition() const { return &m_position; }
	Contain *getContain() const { return m_contain; }
private:
	unsigned char m_toPosition[0x38];
	Coord3D m_position;
	unsigned char m_toDrawable[0x80 - 0x44];
	Drawable *m_drawable;
	unsigned char m_toDisabled[0x1A4 - 0x84];
	DisabledMaskType m_disabledMask;
	UnsignedInt m_disabledTillFrame[11];
	unsigned char m_toContain[0x1FC - 0x1D4];
	Contain *m_contain;
};

extern AudioClient *TheAudioClientUpdate;
extern GameLogic *TheBfmeGameLogic;

#pragma comment(linker, "/alternatename:??0AudioEventRTS@@QAE@ABVAsciiString@@H@Z=?j_00025306@@YAXXZ")
#pragma comment(linker, "/alternatename:??1AudioEventRTS@@QAE@XZ=?j_00026f35@@YAXXZ")
#pragma comment(linker, "/alternatename:??4AudioEventRTS@@QAEAAV0@ABV0@@Z=?j_0001f753@@YAXXZ")
#pragma comment(linker, "/alternatename:?setPosition@AudioEventRTS@@QAEXPBUCoord3D@@@Z=?j_00001e88@@YAXXZ")
#pragma comment(linker, "/alternatename:?isKindOf@Thing@@QBE_NW4KindOfType@@@Z=?j_0003251f@@YAXXZ")
#pragma comment(linker, "/alternatename:?pauseAllSpecialPowers@Object@@QBEX_N@Z=?j_00023e11@@YAXXZ")
#pragma comment(linker, "/alternatename:?set@DisabledMaskType@@QAEXIH@Z=?j_0001800c@@YAXXZ")
#pragma comment(linker, "/alternatename:?onDisabledEdge@Object@@IAEX_N@Z=?j_00045430@@YAXXZ")

void ObjectSetDisabledUntilShim::setDisabledUntil(DisabledType type, UnsignedInt frame)
{
	int disabledType = (int)type;
	ObjectSetDisabledUntilShim *self = this;
	Bool edgeCase = !self->isDisabled();
	if (disabledType < 0 || disabledType >= 11)
		return;

	AudioEventRTS sound(*(const AsciiString *)0x01336E50, 0);
	if (disabledType == 5 && !((Thing *)self)->isKindOf((KindOfType)0x48))
	{
		sound = *(AudioEventRTS *)((char *)TheAudioClientUpdate->getMiscAudio() + 0x7E0);
		sound.setPosition(self->getPosition());
		TheAudioClientUpdate->addAudioEvent(&sound);
	}
	else if (disabledType == 6 || disabledType == 2)
	{
		if (!self->isDisabledByType((DisabledType)6) &&
			!self->isDisabledByType((DisabledType)2))
		{
			if (((Thing *)self)->isKindOf((KindOfType)7))
			{
				sound = *(AudioEventRTS *)((char *)TheAudioClientUpdate->getMiscAudio() + 0x620);
				sound.setPosition(self->getPosition());
				TheAudioClientUpdate->addAudioEvent(&sound);
			}
			else if (((Thing *)self)->isKindOf((KindOfType)9))
			{
				sound = *(AudioEventRTS *)((char *)TheAudioClientUpdate->getMiscAudio() + 0x700);
				sound.setPosition(self->getPosition());
				TheAudioClientUpdate->addAudioEvent(&sound);
			}
		}
	}

	if (self->m_disabledTillFrame[disabledType] != frame)
	{
		if (disabledType != 3 && !self->isDisabledByType((DisabledType)disabledType))
			((Object *)self)->pauseAllSpecialPowers(true);
		self->m_disabledTillFrame[disabledType] = frame;
		self->m_disabledMask.set((UnsignedInt)disabledType, TheBfmeGameLogic->m_frame < frame);
		Drawable *drawable = self->m_drawable;
		if (drawable && self->isDisabled() && disabledType != 3 &&
			 disabledType != 9 && disabledType != 5 && disabledType != 4 && disabledType != 8)
			drawable->m_status |= 1;
		Contain *contain = self->getContain();
	if (contain)
		{
			Object *rider = contain->getRider();
			if (rider)
				rider->setDisabledUntil((DisabledType)disabledType, frame);
		}
	}
	if (edgeCase)
		((Object *)self)->onDisabledEdge(true);
}



