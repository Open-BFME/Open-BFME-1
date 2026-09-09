// ?drawHealthBar@Drawable@@AAEXXZ
// partial score=0.62 date=2026-09-09
// cl: /O2 /Ob1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// Drawable::drawHealthBar is the no-argument BFME icon-stage body at retail
// 0x0041CA50 (511 bytes).  Its ILT is named by drawIconUI's case-0 caller.
// The small views below describe only the retail offsets and virtual slots
// used by this body; they are deliberately TU-local so they do not claim a
// broader reconstructed class layout.

typedef bool Bool;
typedef unsigned int UnsignedInt;
typedef float Real;

enum KindOfType
{
	KINDOF_DRAW_HEALTHBAR_SENTINEL = 0
};

class Drawable;
class Object;

struct BfmeBody
{
	virtual void f00();
	virtual void f04();
	virtual void f08();
	virtual void f0c();
	virtual Real getHealth();
	virtual void f14();
	virtual Real getMaxHealth();
};

// This is the vtable slot at +0x28 used by the raw 0x0041CA50 body.  The
// object fields are the retail +0x200 body and +0x214 contained-by links.
class Object
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0c();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1c();
	virtual void slot20();
	virtual void slot24();
	virtual Drawable *getDrawable() const;

	Bool isKindOf(KindOfType kind) const;

	unsigned char m_pad04[0x1fc];
	BfmeBody *m_body;
	unsigned char m_pad204[0x10];
	Object *m_containedBy;
};

// The call target is Thing::isKindOf's retail ILT.  This view uses Object's
// this-pointer because the raw call sites pass the Object address unchanged.
#pragma comment(linker, "/alternatename:?isKindOf@Object@@QBE_NW4KindOfType@@@Z=?j_0003251f@@YAXXZ")

class InGameUI
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0c();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1c();
	virtual void slot20();
	virtual void slot24();
	virtual void slot28();
	virtual void slot2c();
	virtual void slot30();
	virtual void slot34();
	virtual void slot38();
	virtual void slot3c();
	virtual void slot40();
	virtual void slot44();
	virtual void slot48();
	virtual void slot4c();
	virtual void slot50();
	virtual void slot54();
	virtual void slot58();
	virtual void slot5c();
	virtual void slot60();
	virtual void slot64();
	virtual void slot68();
	virtual void slot6c();
	virtual void slot70();
	virtual void slot74();
	virtual void slot78();
	virtual void slot7c();
	virtual void slot80();
	virtual void slot84();
	virtual void slot88();
	virtual void slot8c();
	virtual void slot90();
	virtual void slot94();
	virtual void slot98();
	virtual void slot9c();
	virtual void slota0();
	virtual void slota4();
	virtual void slota8();
	virtual void slotac();
	virtual void slotb0();
	virtual void slotb4();
	virtual void slotb8();
	virtual void slotbc();
	virtual void slotc0();
	virtual void slotc4();
	virtual void slotc8();
	virtual void slotcc();
	virtual void slotd0();
	virtual void slotd4();
	virtual void slotd8();
	virtual void slotdc();
	virtual void slote0();
	virtual void slote4();
	virtual void slote8();
	virtual void slotec();
	virtual void slotf0();
	virtual void slotf4();
	virtual void slotf8();
	virtual void slotfc();
	virtual void slot100();
	virtual void slot104();
	virtual void slot108();
	virtual void slot10c();
	virtual void slot110();
	virtual void slot114();
	virtual void slot118();
	virtual void slot11c();
	virtual void slot120();
	virtual void slot124();
	virtual void slot128();
	virtual void slot12c();
	virtual void slot130();
	virtual void slot134();
	virtual void slot138();
	virtual void slot13c();
	virtual void slot140();
	virtual void slot144();
	virtual void slot148();
	virtual UnsignedInt getMousedOverDrawableID() const;
};

struct BfmeGlobalData
{
	unsigned char m_pad00[0xa8d];
	unsigned char m_showObjectHealth;
	unsigned char m_showObjectHealthSecondary; // unnamed second retail flag
};

#define TheWritableGlobalData (*(BfmeGlobalData **)0x012ED5C8)
#define TheInGameUI (*(InGameUI **)0x012F148C)
#define BfmeZeroRange (*(const Real *)0x01075350)

class ModuleInterface
{
public:
	virtual Bool gate();
};

class Module
{
private:
	unsigned char m_pad00[0x24];

public:
	ModuleInterface m_interface;
};

// This is the matched real helper reached through ILT 0x00003A49.  The
// address-derived alias is used only to make the existing retail call target
// available to this TU; it does not assert a new semantic helper identity.
extern Module *rva002B21E0FindWallUpgradeUpdate(const Object *object);
#pragma comment(linker, "/alternatename:?rva002B21E0FindWallUpgradeUpdate@@YAPAVModule@@PBVObject@@@Z=?j_00003a49@@YAXXZ")

struct HealthBarRegionWords
{
	int first;
	int second;
};

class Drawable
{
public:
	virtual void slot00();

private:
	unsigned char m_pad04[0xf8];
	Object *m_object;
	UnsignedInt m_id;
	unsigned char m_pad104[0x2a8];
	volatile char m_selected;

	Bool isSelected() const
	{
		Bool result;
		if (m_selected)
			result = true;
		else
			result = false;
		return result;
	}
	void drawHealthBar();

	// Retail places a pointer to the second local region word before the
	// ratio on the stack.  The matched target is declared as int,int in the
	// shared TU, so this local pointer/float spelling is kept behind an
	// alternate-name ABI shim rather than changing that shared declaration.
	void bfmeRegionDispatch(void *regionWord, Real ratio);
};

#pragma comment(linker, "/alternatename:?bfmeRegionDispatch@Drawable@@QAEXPAXM@Z=?j_00030afd@@YAXXZ")

void Drawable::drawHealthBar()
{
	BfmeGlobalData *global = TheWritableGlobalData;
	if (!global->m_showObjectHealth)
		return;

	Bool selected = isSelected();
	if (!selected)
	{
		Object *object = m_object;
		if (object != 0)
		{
			Object *containedBy = object->m_containedBy;
			if (containedBy != 0 && containedBy->isKindOf((KindOfType)0x6c))
			{
				Drawable *containedDrawable = containedBy->getDrawable();
				if (containedDrawable != 0 && containedDrawable->m_selected)
					selected = true;
			}
		}
		if (!selected)
		{
			InGameUI *ui = TheInGameUI;
			if (ui == 0 || ui->getMousedOverDrawableID() != m_id)
				return;
		}
	}

	Object *object = m_object;
	if (object == 0)
		return;
	if (object->isKindOf((KindOfType)0x59) ||
		object->isKindOf((KindOfType)0x0b) ||
		object->isKindOf((KindOfType)0x0a) ||
		object->isKindOf((KindOfType)0x36) ||
		object->isKindOf((KindOfType)0x07) ||
		object->isKindOf((KindOfType)0xa8))
		return;

	global = TheWritableGlobalData;
	if (!global->m_showObjectHealthSecondary)
		return;
	if (!object->isKindOf((KindOfType)8) &&
		!object->isKindOf((KindOfType)9))
		return;
	if (!object->isKindOf((KindOfType)0x95))
		return;

	Module *module = rva002B21E0FindWallUpgradeUpdate(object);
	if (module == 0 || !module->m_interface.gate())
		return;
	if (object->isKindOf((KindOfType)0x3c) ||
		object->isKindOf((KindOfType)0x35) ||
		object->isKindOf((KindOfType)0x87) ||
		object->isKindOf((KindOfType)0x67) ||
		object->isKindOf((KindOfType)0x6c))
		return;

	BfmeBody *body = object->m_body;
	Real maxHealth = body->getMaxHealth();
	if (maxHealth == BfmeZeroRange)
		return;

	HealthBarRegionWords region = { 0, 0 };
	Real health = body->getHealth();
	if (health == BfmeZeroRange)
		return;

	bfmeRegionDispatch(&region.second, health / maxHealth);
}
