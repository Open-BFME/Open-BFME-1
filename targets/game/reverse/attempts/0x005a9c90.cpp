// ?rva005A9C90@CommandTranslator@@AAEXPBVGameMessage@@@Z
// partial score=0.96 date=2026-09-25
// cl: /DNDEBUG /MD
// CommandTranslator::rva005A9C90, retail 0x005A9C90, 159 bytes (ret 4).
//
// The matched CommandTranslator::translateGameMessage (CommandXlat.cpp) calls
// this private method for message 0x18 through ILT 0x00049120 at 0x005B091B,
// which proves the owner; the method keeps its address because nothing names it.
// Outside force-attack mode, a click whose pixel region is a single point picks
// a drawable (pick type 4). When its object has status 0x25 the selection moves
// to the object's container (m_containedBy, else a GameLogic lookup of its
// producer ID), provided that container's contain module answers slot +0x68.
// The chosen object then goes to ControlBar::objectSelectPredicate.
//
// Layout evidence: Drawable::m_object +0xFC and Object::m_producerID +0x78 and
// Object::m_contain +0x1FC are layout_witness (name_oracle, confidence 1.00);
// Object::m_containedBy +0x214 and m_status +0x90 match the matched Zero Hour
// twin Object::onDestroy (ObjectOnDestroy.cpp); InGameUI::m_forceAttackMode
// +0x12B1 and View::pickDrawable at vtable +0x24 match the matched CommandXlat.cpp.

typedef int Int;
typedef bool Bool;

struct ICoord2D { Int x; Int y; };
struct IRegion2D
{
	ICoord2D lo;
	ICoord2D hi;
	Int width() const { return hi.x - lo.x; }
	Int height() const { return hi.y - lo.y; }
};

union GameMessageArgumentType
{
	Int integer;
	ICoord2D pixel;
	IRegion2D pixelRegion;
};

class GameMessage
{
public:
	const GameMessageArgumentType *getArgument(Int argIndex) const;
};

class Object;
class Drawable;

class InGameUI
{
public:
	unsigned char m_pad000[0x12b1];
	Bool m_forceAttackMode;				///< +0x12B1
	Bool isInForceAttackMode() const { return m_forceAttackMode; }
};
extern InGameUI *TheInGameUI;

class View
{
public:
	virtual void rva005A9C90ViewSlot00();
	virtual void rva005A9C90ViewSlot04();
	virtual void rva005A9C90ViewSlot08();
	virtual void rva005A9C90ViewSlot0C();
	virtual void rva005A9C90ViewSlot10();
	virtual void rva005A9C90ViewSlot14();
	virtual void rva005A9C90ViewSlot18();
	virtual void rva005A9C90ViewSlot1C();
	virtual void rva005A9C90ViewSlot20();
	virtual Drawable *pickDrawable(const ICoord2D *screen, Bool forceAttack, Int pickType);	///< +0x24
};
extern View *TheTacticalView;

class ContainModuleInterface
{
public:
	virtual void rva005A9C90ContainSlot00();
	virtual void rva005A9C90ContainSlot04();
	virtual void rva005A9C90ContainSlot08();
	virtual void rva005A9C90ContainSlot0C();
	virtual void rva005A9C90ContainSlot10();
	virtual void rva005A9C90ContainSlot14();
	virtual void rva005A9C90ContainSlot18();
	virtual void rva005A9C90ContainSlot1C();
	virtual void rva005A9C90ContainSlot20();
	virtual void rva005A9C90ContainSlot24();
	virtual void rva005A9C90ContainSlot28();
	virtual void rva005A9C90ContainSlot2C();
	virtual void rva005A9C90ContainSlot30();
	virtual void rva005A9C90ContainSlot34();
	virtual void rva005A9C90ContainSlot38();
	virtual void rva005A9C90ContainSlot3C();
	virtual void rva005A9C90ContainSlot40();
	virtual void rva005A9C90ContainSlot44();
	virtual void rva005A9C90ContainSlot48();
	virtual void rva005A9C90ContainSlot4C();
	virtual void rva005A9C90ContainSlot50();
	virtual void rva005A9C90ContainSlot54();
	virtual void rva005A9C90ContainSlot58();
	virtual void rva005A9C90ContainSlot5C();
	virtual void rva005A9C90ContainSlot60();
	virtual void rva005A9C90ContainSlot64();
	virtual void *rva005A9C90ContainSlot68();	///< +0x68
};

class Object
{
public:
	Bool testStatus(Int status) const;

	unsigned char m_pad000[0x78];
	Int m_producerID;					///< +0x78
	unsigned char m_pad07C[0x1fc - 0x7c];
	ContainModuleInterface *m_contain;	///< +0x1FC
	unsigned char m_pad200[0x214 - 0x200];
	Object *m_containedBy;				///< +0x214
};

class Drawable
{
public:
	unsigned char m_pad000[0xfc];
	Object *m_object;					///< +0xFC
	Object *getObject() const { return m_object; }
};

class GameLogic
{
public:
	Object *findObjectByID(Int id);
};
extern GameLogic *TheGameLogic;

class ControlBar
{
public:
	Int objectSelectPredicate(Object *obj);
};
extern ControlBar *TheControlBar;

class CommandTranslator
{
private:
	void rva005A9C90(const GameMessage *msg);
};

void CommandTranslator::rva005A9C90(const GameMessage *msg)
{
	if (TheInGameUI->isInForceAttackMode())
		return;

	const GameMessageArgumentType *arg = msg->getArgument(0);
	if (arg->pixelRegion.height() != 0)
		return;
	if (arg->pixelRegion.width() != 0)
		return;

	Drawable *draw = TheTacticalView->pickDrawable(&arg->pixelRegion.lo, false, 4);
	Object *obj;
	if (!draw || !(obj = draw->getObject()))
		return;

	if (obj->testStatus(0x25))
	{
		Object *container = obj->m_containedBy;
		if (!container)
		{
			Object *found = TheGameLogic->findObjectByID(obj->m_producerID);
			if (!found)
				return;
			container = found;
		}

		ContainModuleInterface *contain = container->m_contain;
		if (!contain)
			return;
		if (!contain->rva005A9C90ContainSlot68())
			return;

		obj = container;
	}

	TheControlBar->objectSelectPredicate(obj);
}
