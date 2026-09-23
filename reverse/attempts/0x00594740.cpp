// ?rva00594740@AptPalantir@@QAEXPAVObject@@@Z
// partial score=0.97 date=2026-09-22
// cl: /DNDEBUG /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib
// AptPalantir::rva00594740, retail 0x00594740 (724 B, ret 4), plus the two
// static helpers VC7.1 compiled beside it with a private register ABI:
// 0x005946A0 (63 B, list in EAX, result slot in EBX) and 0x005946F0 (63 B,
// list in ECX, iterator on the stack, result slot in EDI). Both are called
// directly (no ILT thunk), from this body and from the 798-byte body at
// 0x00596D40 (0x00596DD4/0x00596E1D/0x00596E67), so they are statics of this
// TU and 0x00596D40 belongs here too; keeping their real source here
// reproduces all three bodies.
//
// Owner: the body passes its own `this` (ESI) to setRankProgress at
// 0x00588940 (ILT 0x0002CBD3), the matched ?setRankProgress@AptPalantir row,
// so it shares that class; its only caller 0x00597130 calls it on
// caller+8 through ILT 0x0000AA2E. The method name is address-derived.
//
// Behaviour the body proves: with an Object argument, or else for every
// selected drawable (InGameUI slot 63) whose template lacks KindOf bit 47,
// ask 0x00593440 for a 12-byte record; the selected drawables must agree
// (fields 0 and 4 equal, field 8 within 0.1f) or field 0 becomes 2. Field 0 is the mode kept at
// +4: 2 runs HideRankInterface, otherwise ShowRankInterface once; mode 0
// hands field 4 to bfmeHeroRankZE (0x00565720) and keeps it at +0xC once
// accepted, mode 1 sets "APT:HeroRank" to the "APT:PalantirTimeRemaining"
// text on first show; field 8 goes to setRankProgress when it changed.
#include "ascii_string.h"
#include "unicode_string.h"
#include <math.h>

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;
typedef float Real;

class Object;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Overridable.h
class Overridable
{
public:
	virtual ~Overridable();
	const Overridable *getFinalOverride(void) const
	{
		if (m_nextOverride)
			return m_nextOverride->getFinalOverride();
		return this;
	}
private:
	Overridable *m_nextOverride;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ThingTemplate.h
class ThingTemplate : public Overridable
{
public:
	Bool isKindOf(Int t) const
	{
		return (m_kindof[(UnsignedInt)t >> 5] & (1 << ((UnsignedInt)t & 31))) != 0;
	}
private:
	unsigned char m_unreconstructed_08[0xC8 - 0x08];
	UnsignedInt m_kindof[3];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Override.h
template <class T> class OVERRIDE
{
public:
	const T *operator*() const
	{
		if (!m_overridable)
			return 0;
		return (T *)m_overridable->getFinalOverride();
	}
	operator const T *() const { return operator*(); }
private:
	const T *m_overridable;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Thing.h
class Thing
{
public:
	const ThingTemplate *getTemplate(void) const { return m_template; }
private:
	virtual ~Thing();
	OVERRIDE<ThingTemplate> m_template;			// +0x04
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/Drawable.h
class Drawable : public Thing
{
public:
	Object *getObject() { return m_object; }
private:
	unsigned char m_unreconstructed_08[0xfc - 0x08];
	Object *m_object;						// +0xfc
};

struct BfmeDrawableListNode
{
	BfmeDrawableListNode *m_next;
	BfmeDrawableListNode *m_previous;
	Drawable *m_drawable;
};

class DrawableList
{
public:
	class const_iterator
	{
	public:
		const_iterator(BfmeDrawableListNode *node) : m_node(node) { }
		bool operator!=(const const_iterator &other) const { return m_node != other.m_node; }
		Drawable *operator*() const { return m_node->m_drawable; }
		const_iterator &operator++() { m_node = m_node->m_next; return *this; }
	private:
		BfmeDrawableListNode *m_node;
	};
	const_iterator begin() const { return const_iterator(m_node->m_next); }
	const_iterator end() const { return const_iterator(m_node); }
private:
	BfmeDrawableListNode *m_node;
};

class InGameUI
{
public:
#define BFME_UI_SLOT(n) virtual void slot##n() = 0;
	BFME_UI_SLOT(00) BFME_UI_SLOT(01) BFME_UI_SLOT(02) BFME_UI_SLOT(03)
	BFME_UI_SLOT(04) BFME_UI_SLOT(05) BFME_UI_SLOT(06) BFME_UI_SLOT(07)
	BFME_UI_SLOT(08) BFME_UI_SLOT(09) BFME_UI_SLOT(10) BFME_UI_SLOT(11)
	BFME_UI_SLOT(12) BFME_UI_SLOT(13) BFME_UI_SLOT(14) BFME_UI_SLOT(15)
	BFME_UI_SLOT(16) BFME_UI_SLOT(17) BFME_UI_SLOT(18) BFME_UI_SLOT(19)
	BFME_UI_SLOT(20) BFME_UI_SLOT(21) BFME_UI_SLOT(22) BFME_UI_SLOT(23)
	BFME_UI_SLOT(24) BFME_UI_SLOT(25) BFME_UI_SLOT(26) BFME_UI_SLOT(27)
	BFME_UI_SLOT(28) BFME_UI_SLOT(29) BFME_UI_SLOT(30) BFME_UI_SLOT(31)
	BFME_UI_SLOT(32) BFME_UI_SLOT(33) BFME_UI_SLOT(34) BFME_UI_SLOT(35)
	BFME_UI_SLOT(36) BFME_UI_SLOT(37) BFME_UI_SLOT(38) BFME_UI_SLOT(39)
	BFME_UI_SLOT(40) BFME_UI_SLOT(41) BFME_UI_SLOT(42) BFME_UI_SLOT(43)
	BFME_UI_SLOT(44) BFME_UI_SLOT(45) BFME_UI_SLOT(46) BFME_UI_SLOT(47)
	BFME_UI_SLOT(48) BFME_UI_SLOT(49) BFME_UI_SLOT(50) BFME_UI_SLOT(51)
	BFME_UI_SLOT(52) BFME_UI_SLOT(53) BFME_UI_SLOT(54) BFME_UI_SLOT(55)
	BFME_UI_SLOT(56) BFME_UI_SLOT(57) BFME_UI_SLOT(58) BFME_UI_SLOT(59)
	BFME_UI_SLOT(60) BFME_UI_SLOT(61) BFME_UI_SLOT(62)
#undef BFME_UI_SLOT
	virtual const DrawableList *getAllSelectedDrawables() const = 0;	// slot 63 (+0xfc)
};

extern InGameUI *TheInGameUI;

class GameTextInterface
{
public:
	virtual void vfn00();
	virtual void vfn01();
	virtual void vfn02();
	virtual void vfn03();
	virtual void vfn04();
	virtual void vfn05();
	virtual void vfn06();
	virtual void vfn07();
	virtual void vfn08();
	virtual UnicodeString fetch(AsciiString label, Bool *exists = 0);	// +0x24
};

extern GameTextInterface *TheGameText;

class WindowManager
{
public:
	void bfme_setAptText(const AsciiString &name, const UnicodeString &text);
};

extern WindowManager *g_theWindowManager;

class Rva00563E00
{
public:
	static void go();	// runs APT "ShowRankInterface"
};

class Rva00563E30
{
public:
	static void go();	// runs APT "HideRankInterface"
};

extern char bfmeHeroRankZE(int value);

// the 12-byte record 0x00593440 (cdecl, one Object* argument) returns through
// its hidden result pointer; the constructor is the body's initial {2, 0, 0.0f}
struct Rva00593440Record
{
	Rva00593440Record() : dword_0(2), dword_4(0), float_8(0.0f) { }

	Int dword_0;
	Int dword_4;
	Real float_8;
};

Rva00593440Record rva00593440(Object *object);

class AptPalantir
{
public:
	void setRankProgress(Real value);
	void rva00594740(Object *object);

private:
	Bool byte_0;
	Int dword_4;
	Bool byte_8;
	Int dword_c;
	Real m_rankProgress;
};

// retail 0x005946A0: first selected drawable whose template lacks KindOf bit 47
static DrawableList::const_iterator rva005946a0(const DrawableList *list)
{
	DrawableList::const_iterator it = list->begin();
	DrawableList::const_iterator end = list->end();
	for (; it != end; ++it)
	{
		if (!(*it)->getTemplate()->isKindOf(47))
			break;
	}
	return it;
}

// retail 0x005946F0: the next such drawable after it
static DrawableList::const_iterator rva005946f0(const DrawableList *list, DrawableList::const_iterator it)
{
	++it;
	DrawableList::const_iterator end = list->end();
	for (; it != end; ++it)
	{
		if (!(*it)->getTemplate()->isKindOf(47))
			break;
	}
	return it;
}

void AptPalantir::rva00594740(Object *object)
{
	Rva00593440Record record;

	if (object)
	{
		record = rva00593440(object);
	}
	else
	{
		const DrawableList *list = TheInGameUI->getAllSelectedDrawables();
		DrawableList::const_iterator it = rva005946a0(list);
		if (it != list->end())
		{
			record = rva00593440((*it)->getObject());
			if (record.dword_0 != 2)
			{
				while ((it = rva005946f0(list, it)) != list->end())
				{
					Rva00593440Record other = rva00593440((*it)->getObject());
					if (other.dword_0 != record.dword_0 || other.dword_4 != record.dword_4 ||
						!(fabs(other.float_8 - record.float_8) < 0.1f))
					{
						record.dword_0 = 2;
						break;
					}
				}
			}
		}
	}

	if (record.dword_0 != dword_4)
	{
		if (byte_0)
		{
			Rva00563E30::go();
			byte_0 = false;
		}
		dword_4 = record.dword_0;
	}

	if (dword_4 != 2)
	{
		Bool wasShown = byte_0;
		if (!wasShown)
		{
			Rva00563E00::go();
			byte_0 = true;
			byte_8 = false;
			m_rankProgress = -1.0f;
		}

		if (dword_4 == 0)
		{
			Int value = record.dword_4;
			if (!byte_8 || value != dword_c)
			{
				if (bfmeHeroRankZE(value))
				{
					byte_8 = true;
					dword_c = value;
				}
			}
		}
		else if (dword_4 == 1 && !wasShown)
		{
			static AsciiString aptHeroRank("APT:HeroRank");
			static AsciiString aptPalantirTimeRemaining("APT:PalantirTimeRemaining");
			UnicodeString text = TheGameText->fetch(aptPalantirTimeRemaining);
			g_theWindowManager->bfme_setAptText(aptHeroRank, text);
		}

		if (record.float_8 != m_rankProgress)
			setRankProgress(record.float_8);
	}
	else if (byte_0)
	{
		Rva00563E30::go();
		byte_0 = false;
	}
}
