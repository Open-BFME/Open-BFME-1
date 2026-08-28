// cl: /DNDEBUG /MD /EHs-c-
// Lift the ScriptActions::doUnitReceiveUpgrade __emit thunk to clean C++.
//
// Zero Hour's body is three lines: resolve the unit, resolve the upgrade, call
// Object::giveUpgrade. BFME kept that as the else branch and added a player-wide
// path in front of it -- if the named unit is KindOf 108 the upgrade is applied
// to whatever the accessor at 0x001BFE20 returns instead of to the object.
//
// Three of the four callees were already pinned by earlier work and their
// signatures settle the shape: UpgradeCenter::findUpgrade is a const member
// returning a const UpgradeTemplate *, Thing::isKindOf takes a KindOfType, and
// Object::giveUpgrade takes the template. Only the fourth is unnamed.
//
// That fourth callee is the trap in this function. ILT 0x0000D3B9 lands on
// 0x001BFE20, which reads a pointer at Object+0x1FC and tail-calls its virtual
// at +0x68; ?getControllingPlayer@Object@@QBEPAVPlayer@@XZ is already pinned to
// a DIFFERENT body at 0x001BE3F0 that reads m_team at Object+0x23C and tail-calls
// the pinned Team::getControllingPlayer. The two accessors have the same shape
// and would silently resolve to each other, so this one carries an address-derived
// name and is pinned separately.
//
// The returned object is polymorphic and is used only through vtable +0xA8 and
// +0xAC: +0xA8 takes the dword at UpgradeTemplate+0x20 and returns a Bool that
// aborts the grant, +0xAC takes the template itself. Those roles are read off the
// call sites -- the slot names below are descriptive, not attested.

typedef int Int;
typedef bool Bool;
typedef unsigned int UnsignedInt;

class AsciiString;
class Upgrade;

enum KindOfType
{
	KINDOF_UNRECONSTRUCTED_108 = 108					///< the only value this function uses
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Upgrade.h
class UpgradeTemplate
{
public:
	UnsignedInt getUpgradeMask(void) const { return m_upgradeMask; }

private:
	unsigned char m_unreconstructed_00[0x20];
	UnsignedInt m_upgradeMask;						///< retail this+0x20
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Upgrade.h
class UpgradeCenter
{
public:
	const UpgradeTemplate *findUpgrade(const AsciiString &name) const;	///< ILT thunk at 0x0002F95A
};

// Reached only through the accessor at 0x001BFE20; nothing here is attested
// beyond the two slots the call sites use.
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Player.h
class Player
{
public:
	virtual void unused00();
	virtual void unused01();
	virtual void unused02();
	virtual void unused03();
	virtual void unused04();
	virtual void unused05();
	virtual void unused06();
	virtual void unused07();
	virtual void unused08();
	virtual void unused09();
	virtual void unused10();
	virtual void unused11();
	virtual void unused12();
	virtual void unused13();
	virtual void unused14();
	virtual void unused15();
	virtual void unused16();
	virtual void unused17();
	virtual void unused18();
	virtual void unused19();
	virtual void unused20();
	virtual void unused21();
	virtual void unused22();
	virtual void unused23();
	virtual void unused24();
	virtual void unused25();
	virtual void unused26();
	virtual void unused27();
	virtual void unused28();
	virtual void unused29();
	virtual void unused30();
	virtual void unused31();
	virtual void unused32();
	virtual void unused33();
	virtual void unused34();
	virtual void unused35();
	virtual void unused36();
	virtual void unused37();
	virtual void unused38();
	virtual void unused39();
	virtual void unused40();
	virtual void unused41();
	virtual Bool hasUpgrade(UnsignedInt mask);		///< vtable +0xA8
	virtual Upgrade *grantUpgrade(const UpgradeTemplate *upgrade);	///< vtable +0xAC
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Thing.h
class Thing
{
public:
	Bool isKindOf(KindOfType kind) const;			///< ILT thunk at 0x0003251F
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object : public Thing
{
public:
	void giveUpgrade(const UpgradeTemplate *upgrade);	///< ILT thunk at 0x0001A97E

	/// address-derived name -- do not treat as an identity. Body at 0x001BFE20
	/// reads Object+0x1FC and forwards to its virtual at +0x68.
	Player *unidentified_001BFE20(void) const;		///< ILT thunk at 0x0000D3B9
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptEngine.h
class ScriptEngine
{
public:
	virtual void unused00();
	virtual void unused01();
	virtual void unused02();
	virtual void unused03();
	virtual void unused04();
	virtual void unused05();
	virtual void unused06();
	virtual void unused07();
	virtual void unused08();
	virtual void unused09();
	virtual void unused10();
	virtual void unused11();
	virtual void unused12();
	virtual void unused13();
	virtual void unused14();
	virtual void unused15();
	virtual void unused16();
	virtual void unused17();
	virtual void unused18();
	virtual void unused19();
	virtual void unused20();
	virtual void unused21();
	virtual void unused22();
	virtual void unused23();
	virtual void unused24();
	virtual void unused25();
	virtual Object *getUnitNamed(const AsciiString &name);	///< vtable +0x68
};

extern ScriptEngine *TheScriptEngine;					///< retail [0x012F076C]
extern UpgradeCenter *TheUpgradeCenter;					///< retail [0x012EF188]

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptActions.h
class ScriptActions
{
protected:
	void doUnitReceiveUpgrade(const AsciiString &, const AsciiString &);
};

// ?doUnitReceiveUpgrade@ScriptActions@@IAEXABVAsciiString@@0@Z
void ScriptActions::doUnitReceiveUpgrade(const AsciiString &unitName, const AsciiString &upgradeName)
{
	Object *obj = TheScriptEngine->getUnitNamed(unitName);
	if (!obj) {
		return;
	}

	const UpgradeTemplate *templ = TheUpgradeCenter->findUpgrade(upgradeName);
	if (!templ) {
		return;
	}

	if (obj->isKindOf(KINDOF_UNRECONSTRUCTED_108)) {
		Player *player = obj->unidentified_001BFE20();
		if (!player) {
			return;
		}
		if (!player->hasUpgrade(templ->getUpgradeMask())) {
			player->grantUpgrade(templ);
		}
	} else {
		obj->giveUpgrade(templ);
	}
}
