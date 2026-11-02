// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib /Igame/GameEngine/Include /Igame/GameEngine/Source /Iinputs/reference/shims/zhcanonascii /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include
// ?method@Rva00594AD0@@QAEXPAVObject@@@Z
// Cost-modifier Apt text for an embedded state whose owner remains unknown.
#include "ascii_string.h"
#include "unicode_string.h"

// ??0UnicodeString@@QAE@XZ
inline UnicodeString::UnicodeString() { m_text = 0; }
// ??1UnicodeString@@QAE@XZ
inline UnicodeString::~UnicodeString() { ((StringBase<unsigned short> *)this)->releaseBuffer(); }

enum NameKeyType { NAMEKEY_INVALID = 0 };
class NameKeyGenerator { public: NameKeyType nameToKey(const char *); };
extern NameKeyGenerator *TheNameKeyGenerator;
class Object;
class Player;
class Module;
class PlayerList { public: unsigned char isLocalAlliedWith(Object *); };
extern PlayerList *g_mgr12ED748;

class Object;
#define OBJECT_TU_MEMBERS friend class Rva00594AD0; protected: Module *findModule(NameKeyType) const; public: Player *getControllingPlayer() const;
#include "../../../GameLogic/Object/object.h"
#undef OBJECT_TU_MEMBERS

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

class BfmeSubDQC { public: char pad[0x80]; unsigned char m_kind; char pad81[3]; AsciiString tail; };
class Rva0058D740
{
public:
	__declspec(noinline) AsciiString rva0058D740();
	void *vptr;
	BfmeSubDQC *m_sub;
};

class BfmeThingDQC
{
public:
	__forceinline AsciiString bfmeGoDQC();
	// ?data00594AD0@BfmeThingDQC@@QBEPBVBfmeSubDQC@@XZ absent-from-retail
	__forceinline const BfmeSubDQC *data00594AD0() const { return m_sub; }
private:
	void *vptr;
	BfmeSubDQC *m_sub;
};

// ?bfmeGoDQC@BfmeThingDQC@@QAE?AVAsciiString@@XZ absent-from-retail
inline AsciiString BfmeThingDQC::bfmeGoDQC()
{
	return ((Rva0058D740 *)this)->rva0058D740();
}

typedef AsciiString BFMERetailAsciiString;

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
	void bfme_setAptText(const AsciiString &, const UnicodeString &);
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

// ?setAptText@WindowManager@@QAEXABVAsciiString@@ABVUnicodeString@@@Z absent-from-retail
__forceinline void WindowManager::setAptText(const AsciiString &label, const UnicodeString &text)
{
	bfme_setAptText(label, text);
}

// ?method@Rva00594AD0@@QAEXPAVObject@@@Z
void Rva00594AD0::method(Object *object)
{
	Overridable *final = *(Overridable **)((char *)object + 4);
	if (final)
	{
		Overridable *overridable = *(Overridable **)((char *)final + 4);
		if (overridable)
			final = (Overridable *)overridable->getFinalOverride();
	}
	if ((*(unsigned char *)((char *)final + 0xC8) & 0x80) == 0)
	{
		if (m_visible)
		{
			Rva00563F80::go();
			m_visible = 0;
		}
		return;
	}

	static NameKeyType costModifierKey =
		TheNameKeyGenerator->nameToKey("CostModifierUpgrade");
	Module *module = object->findModule(costModifierKey);
	Player *player = object->getControllingPlayer();
	if (module && player)
	{
		unsigned char allied = g_mgr12ED748->isLocalAlliedWith(object);
		if (allied)
		{
			if (!m_visible)
			{
				Rva00563F50::go();
				m_visible = 1;
				m_valid = 0;
			}

			unsigned char kind = ((BfmeThingDQC *)module)->data00594AD0()->m_kind;
			AsciiString valueView = ((Rva0058D740 *)module)->rva0058D740();
			int currentValue = ((Rva0058B590Value *)module)->get(player);
			if (m_valid)
			{
				if (kind != m_kind || (kind == 0 && m_zero != 0) || currentValue != m_value)
					m_valid = 0;
			}
			if (m_valid)
				return;
			UnicodeString text;
			text.format(TheGameText->fetch(valueView, 0), currentValue);
			static BFMERetailAsciiString aptText("APT:CostModifierUpgrade");
			g_rva012F19E8WindowManager->setAptText((const AsciiString &)aptText, text);
			m_valid = 1;
			m_kind = kind;
			m_zero = 0;
			m_value = currentValue;
			return;
		}
		else
		{
			if (m_visible)
			{
				Rva00563F80::go();
				m_visible = 0;
			}
			return;
		}
	}
	if (m_visible)
	{
		Rva00563F80::go();
		m_visible = 0;
	}
}
