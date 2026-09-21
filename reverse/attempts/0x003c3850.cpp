// ?d_003c3850@@YAXXZ
// partial score=0.88 date=2026-09-18
// cl: /DNDEBUG /MD /EHsc
//
// Retail 0x003C3850 (495 bytes).  The constructor/destructor at 0x003C2FC0/
// 0x003C31D0 install LivingWorldLogic's vtable and establish the +0x28 region
// manager, +0x30 string and +0x84 two-byte objective vector used here.  The
// direct caller at 0x003C3AE0 passes the same record through ILT 0x00044DF5.
// The original method name is not recoverable, so the exported method keeps
// the body address in its name.

template <typename T>
class StringBase
{
protected:
	struct Header
	{
		int m_refCount;
		unsigned short m_length;
		unsigned short m_capacity;
		T m_text[1];
	};

	StringBase() : m_data(0) {}
	StringBase(const StringBase<T> &other);
	~StringBase() { releaseBuffer(); }

	public:
	void set(const StringBase<T> &other);
	void releaseBuffer();

protected:
	Header *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString(const AsciiString &other)
		: StringBase<char>(other)
	{
	}
	~AsciiString() {}

	void set(const AsciiString &other)
	{
		((StringBase<char> *)this)->set(
			*(const StringBase<char> *)&other);
	}

	bool hasText() const
	{
		return m_data != 0 && m_data->m_length != 0;
	}
};

struct BfmePairESA
{
	int m_first;
	int m_second;
};

typedef BfmePairESA Rva003C3850Pair;

class BfmeStrESA : public AsciiString
{
public:
	BfmeStrESA() : AsciiString() {}
	~BfmeStrESA() {}
};

namespace Gen003C2EE0Stl
{
	template <typename T>
	class allocator
	{
	};

	template <typename T, typename Allocator>
	class vector
	{
	public:
		T *m_begin;
		T *m_finish;
		T *m_end;

		void resize(unsigned int count, T value);
	};
}

typedef Gen003C2EE0Stl::vector<unsigned short,
	Gen003C2EE0Stl::allocator<unsigned short> > Rva003C3850Vector;

struct Rva003C3850IntRange
{
	int *m_begin;
	int *m_finish;

	unsigned int size() const
	{
		return (unsigned int)(m_finish - m_begin);
	}
};

struct Rva003C3850VisibleValue
{
	unsigned char m_value;
	unsigned char m_padding;

	Rva003C3850VisibleValue()
		: m_value(1), m_padding(0)
	{
	}
};

class LivingWorldRegion
{
	public:
	char m_unmodelled00[4];
	AsciiString m_name;
	char m_unmodelled08[0x4c];
	Rva003C3850IntRange m_firstRange;
	char m_unmodelled5c[4];
	Rva003C3850IntRange m_secondRange;

	unsigned int missionObjectiveCount() const
	{
		return m_firstRange.size() + m_secondRange.size();
	}

};

class LivingWorldRegionManager
{
public:
	void *m_vtable;
	void *m_regions;
	LivingWorldRegion *m_selectedRegion;
	int m_unmodelled0C;
	bool m_enabled;
};

class ClientSubsystem
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02();
	virtual void slot03(); virtual void slot04(); virtual void slot05();
	virtual void slot06(); virtual void slot07(); virtual void slot08();
	virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14();
	virtual void slot15(); virtual void slot16(); virtual void slot17();
	virtual void slot18(); virtual void slot19(); virtual void slot20();
	virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void slot24(); virtual void slot25(); virtual void slot26();
	virtual void slot27(); virtual void slot28(); virtual void slot29();
	virtual void slot30(); virtual void slot31(); virtual void slot32();
	virtual void slot33(); virtual void slot34(); virtual void slot35();
	virtual void slot36(); virtual void slot37(); virtual void slot38();
	virtual void slot39(); virtual void slot40(); virtual void slot41();
	virtual void slot42(); virtual void slot43(); virtual void slot44();
	virtual void slot45(); virtual void slot46(); virtual void slot47();
	virtual void slot48(); virtual void slot49(); virtual void slot50();
	virtual void slot51(); virtual void slot52(); virtual void slot53();
	virtual void slot54(); virtual void slot55(); virtual void slot56();
	virtual void slot57(); virtual void slot58(); virtual void slot59();
	virtual void slot60(); virtual void slot61(); virtual void slot62();
	virtual void slot63(); virtual void slot64(); virtual void slot65();
	virtual void slot66(); virtual void slot67(); virtual void slot68();
	virtual void slot69(); virtual void slot70(); virtual void slot71();
	virtual void slot72(); virtual void slot73(); virtual void slot74();
	virtual void slot75(); virtual void slot76(); virtual void slot77();
	virtual void slot78(); virtual void slot79(); virtual void slot80();
	virtual void slot81(); virtual void slot82(); virtual void slot83();
	virtual void slot84(); virtual void slot85(); virtual void slot86();
	virtual void slot87(); virtual void slot88(); virtual void slot89();
	virtual void slot90(); virtual void slot91(); virtual void slot92();
	virtual void slot93(); virtual void slot94();
};

class InGameUI
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02();
	virtual void slot03(); virtual void slot04(); virtual void slot05();
	virtual void slot06(); virtual void slot07(); virtual void slot08();
	virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14();
	virtual void slot15(); virtual void slot16(); virtual void slot17();
	virtual void slot18(); virtual void slot19(); virtual void slot20();
	virtual void slot21(); virtual void slot22(); virtual void slot23();
};

class Keyboard
{
public:
	bool isShift();
};

class GlobalData
{
public:
	char m_padding00[0x90];
	unsigned char m_flag90;
};

class GameLogic
{
};

class Rva003C3850LookupOwner
{
};

class Gen_00609320
{
};

class CampaignManager
{
};

class Rva003C1A50
{
public:
	void clearTwoVec();
};

class BfmeHostESA
{
public:
	void bfmeGetESA(BfmeStrESA *out, BfmePairESA *range);
};

class Rva003855C0
{
public:
	void reset();
};

class Rva003BFB20
{
public:
	void run(int value);
};

class Rva003C0110Owner
{
public:
	struct Rva003C0110ElementResult;
	Rva003C0110ElementResult *findByName(StringBase<char> *key);
};

class Rva006092D0State
{
public:
	void rva00609360(void *source);
};

class Gen003C73A0Item
{
};

class Gen003C73A0Owner
{
public:
	void *m_vtable;
	void *m_regions;
	LivingWorldRegion *m_selectedRegion;
	int m_unmodelled0C;
	bool m_enabled;
	void *m_unmodelled14;
	void *m_unmodelled18;

	bool containsOrEmpty(Gen003C73A0Item *item) const;
};

class LivingWorldLogicPrimaryBase
{
public:
	virtual void slot00();
	char m_unmodelled04[0x24];
};

class LivingWorldLogic
	: public LivingWorldLogicPrimaryBase
{
public:
	bool rva003C3850(LivingWorldRegion *record);

private:
	Gen003C73A0Owner *m_regionManager;
	char m_unmodelled2C[4];
	AsciiString m_currentRegionName;
	char m_unmodelled34[0x50];
	Rva003C3850Vector m_missionObjectiveStates;
};

extern void j_0001b333();
extern void j_000299ce();
extern void j_000295d7();
extern void j_000495da();
extern void j_0001d8c7();
extern void j_00035ff3();
extern void j_000156b3();
extern void j_0003a4a4();
extern void j_000475a5();
extern void j_00032a56();
extern void j_0002e46();
extern void j_000012e4();

extern ClientSubsystem *TheAudioClientUpdate;
extern InGameUI *TheInGameUI;
extern GameLogic *TheBfmeGameLogic;
extern Keyboard *TheKeyboard;
extern GlobalData *TheWritableGlobalData;
extern CampaignManager *TheLivingWorldLogic;
extern Gen_00609320 *g_bfmeStateDF;
#define Rva01336E50Empty (*(AsciiString *)0x01336E50)

typedef void (LivingWorldLogic::*ClearObjectiveVectors)();
typedef void (Rva003C3850Vector::*ResizeObjectiveVector)(
	unsigned int, unsigned short);
typedef void (GameLogic::*ApplyCQ)(
	AsciiString, Rva003C3850Pair *);
typedef bool (Keyboard::*IsShift)();
typedef void (LivingWorldLogic::*RecordAction)(LivingWorldRegion *);
typedef bool (LivingWorldRegionManager::*ContainsRecord)(
	LivingWorldRegion *);
typedef Rva003C3850LookupOwner *(LivingWorldLogic::*FindRecord)(
  AsciiString *);
typedef void (LivingWorldRegion::*SetRecordName)(AsciiString *);
typedef void (Gen_00609320::*UpdateState)(void *);

bool LivingWorldLogic::rva003C3850(LivingWorldRegion * const record)
{
	register LivingWorldRegion *value = record;
	register LivingWorldLogic *owner = this;

	if (value != 0)
	{

	TheAudioClientUpdate->slot94();

	owner->m_currentRegionName.set(value->m_name);
	TheInGameUI->slot23();

	((Rva003C1A50 *)owner)->clearTwoVec();

	unsigned int count = value->missionObjectiveCount();
	Rva003C3850VisibleValue initialValue;

	m_missionObjectiveStates.resize(count,
		*(unsigned short *)&initialValue);

	unsigned short *stateEnd = m_missionObjectiveStates.m_finish;
	unsigned short *state = m_missionObjectiveStates.m_begin;
	Rva003C3850VisibleValue visible;
	while (state != stateEnd)
	{
		*state = *(unsigned short *)&visible;
		++state;
	}

	Rva003C3850Pair range;
	BfmeStrESA text;
	((BfmeHostESA *)owner)->bfmeGetESA(&text, &range);

	((Rva003855C0 *)TheBfmeGameLogic)->reset();

	if (text.hasText())
	{
		union
		{
			void (*raw)();
			ApplyCQ member;
		} apply;
		apply.raw = ::j_0001d8c7;
		(TheBfmeGameLogic->*apply.member)(
			text, &range);
	}

	union
	{
		void (*raw)();
		RecordAction member;
	} action;
	action.raw = ::j_00035ff3;
	(owner->*action.member)(value);

	if (TheKeyboard->isShift() &&
		TheWritableGlobalData->m_flag90 != 0)
	{
		((Rva003BFB20 *)owner)->run((int)value);
		return true;
	}

	if (!owner->m_regionManager->containsOrEmpty(
		(Gen003C73A0Item *)value))
	{
		owner->m_currentRegionName.set(Rva01336E50Empty);
		return false;
	}

	Rva003C0110Owner::Rva003C0110ElementResult *found =
		((Rva003C0110Owner *)owner)->findByName(
			(StringBase<char> *)&text);

	union
	{
		void (*raw)();
		SetRecordName member;
	} setName;
	setName.raw = ::j_0002e46;
	if (found != 0)
		(value->*setName.member)(
			(AsciiString *)((char *)found + 0x40));
	else
		(value->*setName.member)(
			&Rva01336E50Empty);

	owner->m_regionManager->m_selectedRegion = value;
	owner->m_regionManager->m_enabled = false;

	((Rva006092D0State *)g_bfmeStateDF)->rva00609360(
		(char *)TheLivingWorldLogic + 0x20);
	return true;
	}
	return false;
}
