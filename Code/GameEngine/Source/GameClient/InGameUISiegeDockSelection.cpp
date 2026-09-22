// cl: /DNDEBUG /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib
// InGameUI::rva00447F10, retail 0x00447F10 (541 B).
//
// Owner: the only caller (0x005AE71E, through ILT 0x00022CCD) loads
// ecx = TheInGameUI (0x012F148C) and pushes one argument; the body never
// reads ecx and returns with `ret 4`. The name is address-derived because
// nothing names the method.
//
// Behaviour the body proves: the argument is an Object whose template
// carries KindOf bit 59; for every selected drawable's object that is not
// contained, pick "Command_SpecialAbilitySiegeLadderDeploy" (KindOf 0x8A)
// or "Command_SpecialAbilitySiegeDeploy", require the button to exist and
// be usable/ready. A qualifying unit with no AI (+0x204) answers true;
// otherwise the target's "SiegeDockingBehavior" module (interface at +0x20,
// slot 1, given the unit's id at +0x74) fills a position, and true is
// returned when that call fails or AIUpdateInterface::isQuickPathAvailable
// accepts the position. The KindOf/status numbers stay numeric: nothing in
// this tree names those enum values for BFME yet.

#include "ascii_string.h"

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;
typedef Int ObjectID;

enum KindOfType { KINDOF_INVALID = 0 };
enum NameKeyType { NAMEKEY_INVALID = 0 };

struct Coord3D { float x, y, z; };

class Module;
class CommandButton;
class Object;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Overridable.h
class Overridable
{
public:
	virtual ~Overridable();
	const Overridable *getFinalOverride(void) const;
	Overridable *m_nextOverride;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ThingTemplate.h
class ThingTemplate : public Overridable
{
public:
	Bool isKindOf(KindOfType t) const
	{
		return (m_kindof[(UnsignedInt)t >> 5] & (1 << ((UnsignedInt)t & 31))) != 0;
	}
private:
	unsigned char m_unreconstructed_08[0xC8 - 0x08];
	UnsignedInt m_kindof[3];
};

class AIUpdateInterface
{
public:
	Bool isQuickPathAvailable(const Coord3D *destination) const;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Thing.h
class Thing
{
public:
	const ThingTemplate *getTemplate(void) const
	{
		const ThingTemplate *tmpl = m_template;
		if (tmpl == 0)
			return 0;
		if (tmpl->m_nextOverride)
			tmpl = (const ThingTemplate *)tmpl->m_nextOverride->getFinalOverride();
		return tmpl;
	}
	Bool isKindOf(KindOfType t) const;

private:
	virtual ~Thing();
	const ThingTemplate *m_template;				// +0x04
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object : public Thing
{
public:
	Bool testStatus(Int bit) const;
	Bool bfmeCanUseCommandButton(const CommandButton *command) const;
	ObjectID getID() const { return m_id; }
	AIUpdateInterface *getAI() { return m_ai; }
	Object *getContainedBy() { return m_containedBy; }
	Module *findUpdateModule(NameKeyType key) const { return findModule(key); }

protected:
	Module *findModule(NameKeyType key) const;

private:
	unsigned char m_unreconstructed_08[0x74 - 0x08];
	ObjectID m_id;							// +0x74
	unsigned char m_unreconstructed_78[0x204 - 0x78];
	AIUpdateInterface *m_ai;					// +0x204
	unsigned char m_unreconstructed_208[0x214 - 0x208];
	Object *m_containedBy;						// +0x214
};

// the interface the "SiegeDockingBehavior" module carries at +0x20
class Rva00447F10SiegeDockingInterface
{
public:
	virtual void slot0() = 0;
	virtual Bool slot1(ObjectID docker, Coord3D *position) = 0;
};

class Module
{
public:
	virtual ~Module();
private:
	unsigned char m_unreconstructed_04[0x20 - 0x04];
};

class Rva00447F10SiegeDockingModule : public Module, public Rva00447F10SiegeDockingInterface
{
};

class CommandButton
{
public:
	Bool isReady(const Object *obj) const;
};

class ControlBar
{
public:
	const CommandButton *findCommandButton(const AsciiString &name);
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};

class Drawable;

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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/Drawable.h
class Drawable
{
public:
	Object *getObject() { return m_object; }
private:
	unsigned char m_unreconstructed_00[0xfc];
	Object *m_object;						// +0xfc
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
	virtual Int getSelectCount() = 0;				// slot 60, +0xF0
	BFME_UI_SLOT(61) BFME_UI_SLOT(62)
	virtual const DrawableList *getAllSelectedDrawables() const = 0;	// slot 63, +0xFC
#undef BFME_UI_SLOT

	Bool rva00447F10(Object *target);
};

extern InGameUI *TheInGameUI;
extern ControlBar *TheControlBar;
extern NameKeyGenerator *TheNameKeyGenerator;

Bool InGameUI::rva00447F10(Object *target)
{
	if (target == 0)
		return false;
	if (!target->getTemplate()->isKindOf((KindOfType)59))
		return false;
	if (TheInGameUI->getSelectCount() == 0)
		return false;

	const DrawableList *selected = TheInGameUI->getAllSelectedDrawables();
	for (DrawableList::const_iterator it = selected->begin(); it != selected->end(); ++it)
	{
		Object *obj = (*it)->getObject();
		if (obj == 0 || obj->getContainedBy() != 0)
			continue;

		const CommandButton *button;
		if (obj->isKindOf((KindOfType)0x8A))
			button = TheControlBar->findCommandButton(AsciiString("Command_SpecialAbilitySiegeLadderDeploy"));
		else
			button = TheControlBar->findCommandButton(AsciiString("Command_SpecialAbilitySiegeDeploy"));

		if (button == 0 || !obj->isKindOf((KindOfType)0x5C) || obj->testStatus(0x3A)
			|| !obj->bfmeCanUseCommandButton(button) || !button->isReady(obj))
			continue;

		if (obj->getAI() == 0)
			return true;

		static NameKeyType key_SiegeDockingBehavior = TheNameKeyGenerator->nameToKey("SiegeDockingBehavior");
		Rva00447F10SiegeDockingModule *dock =
			(Rva00447F10SiegeDockingModule *)target->findUpdateModule(key_SiegeDockingBehavior);
		if (dock == 0)
			continue;

		Coord3D pos;
		if (!dock->slot1(obj->getID(), &pos))
			return true;
		if (obj->getAI()->isQuickPathAvailable(&pos))
			return true;
	}
	return false;
}
