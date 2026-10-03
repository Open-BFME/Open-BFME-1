// ?d_00594ad0@@YAXXZ
// partial score=0.5095 date=2026-10-03
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib /Igame/GameEngine/Include /Igame/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include
#define private public
#include "ascii_string.h"
#include "unicode_string.h"
#undef private

typedef int NameKeyType;
class NameKeyGenerator { public: NameKeyType nameToKey(const char *); };
extern NameKeyGenerator *TheNameKeyGenerator;
class Object;
class Player;
class Module;
class PlayerList { public: bool isLocalAlliedWith(Object *); };
extern PlayerList *g_mgr12ED748;

class Object
{
public:
	Module *findModule(NameKeyType) const;
	Player *getControllingPlayer() const;
};

class Overridable
{
public:
	const Overridable *getFinalOverride() const;
};

class Rva0058B590Value
{
public:
	long get(Player *) const;
private:
	char pad[4];
	void *m_data;
};

class BfmeOtherDQC : public AsciiString
{
public:
	BfmeOtherDQC() : AsciiString() { }
	void bfmeCallDQC(void *);
	~BfmeOtherDQC() { }
};
class BfmeSubDQC { public: char pad[0x84]; char tail[4]; };
class BfmeThingDQC
{
public:
	BfmeOtherDQC *bfmeGoDQC(BfmeOtherDQC *);
private:
	void *vptr;
	BfmeSubDQC *m_sub;
};

class BFMERetailAsciiString : private StringBase<char>
{
public:
	BFMERetailAsciiString(const char *text) : StringBase<char>(text) { }
	BFMERetailAsciiString(const BFMERetailAsciiString &other) : StringBase<char>(other) { }
	~BFMERetailAsciiString() { releaseBuffer(); }
};

class GameTextInterface
{
public:
	virtual void slot00() = 0; virtual void slot01() = 0; virtual void slot02() = 0;
	virtual void slot03() = 0; virtual void slot04() = 0; virtual void slot05() = 0;
	virtual void slot06() = 0; virtual void slot07() = 0; virtual void slot08() = 0;
	virtual UnicodeString fetch(AsciiString label, bool *exists = 0) = 0;
};
extern GameTextInterface *TheGameText;

class WindowManager
{
public:
	void setAptText(const AsciiString &, const UnicodeString &);
};
extern WindowManager *g_rva012F19E8WindowManager;
extern unsigned int g_Va012F4C14;

class Rva00563F50 { public: static void go(); };
class Rva00563F80 { public: static void go(); };

class Rva00594AD0
{
public:
	void method(Object *object);
	unsigned char m_visible;
	unsigned char m_valid;
	unsigned char m_kind;
	unsigned char m_pad3;
	int m_zero;
	int m_value;
};

void Rva00594AD0::method(Object *object)
{
	Overridable *final = *(Overridable **)((char *)object + 4);
	if (final)
	{
		Overridable *overridable = *(Overridable **)((char *)final + 4);
		if (overridable)
			final = (Overridable *)overridable->getFinalOverride();
	}
	if (*(signed char *)((char *)final + 0xC8) >= 0)
	{
		if (m_visible)
			Rva00563F80::go();
		m_visible = 0;
		return;
	}

	static NameKeyType costModifierKey =
		TheNameKeyGenerator->nameToKey("CostModifierUpgrade");
	Module *module = object->findModule(costModifierKey);
	Player *player = object->getControllingPlayer();
	if (!module || !player || !g_mgr12ED748->isLocalAlliedWith(object))
	{
		if (m_visible)
			Rva00563F80::go();
		m_visible = 0;
		return;
	}

	if (!m_visible)
	{
		Rva00563F50::go();
		m_visible = 1;
		m_valid = 0;
	}

	unsigned char kind = *(unsigned char *)((char *)*(void **)((char *)module + 4) + 0x80);
	BfmeOtherDQC valueView;
	((BfmeThingDQC *)module)->bfmeGoDQC(&valueView);
	int currentValue = ((Rva0058B590Value *)module)->get(player);
	if (m_valid && kind == m_kind &&
		(kind != 0 || m_zero == 0) && currentValue == m_value)
		return;

	m_valid = 0;
	UnicodeString text;
	text.format(TheGameText->fetch((const AsciiString &)valueView, 0), module, currentValue);
	static BFMERetailAsciiString aptText("APT:CostModifierUpgrade");
	g_rva012F19E8WindowManager->setAptText((const AsciiString &)aptText, text);
	m_valid = 1;
	m_kind = kind;
	m_zero = 0;
	m_value = currentValue;
}
