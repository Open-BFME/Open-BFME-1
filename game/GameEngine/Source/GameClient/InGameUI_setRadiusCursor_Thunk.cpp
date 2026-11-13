// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Include
//
// InGameUI::setRadiusCursor, retail RVA 0x0043DBE0, 461 bytes (ret 0x10),
// with its jump table at 0x0043DDB0. BFME added a fourth Bool argument:
// tools/ilt_oracle.py CONFIRMS
// ?setRadiusCursor@InGameUI@@UAEXW4RadiusCursorType@@PBVSpecialPowerTemplate@@W4WeaponSlotType@@_N@Z
// at its ILT 0x0003F2CE, and InGameUI.cpp's matched command-button code
// already calls it through vtable +0x118 with TRUE as the fourth argument.
// The body is Zero Hour's (GameClient/InGameUI.cpp) with BFME's changes: the
// pending shortcut commands 0x1F and 0x24 take the object from two local-player
// queries, the cursor kinds are renumbered (2 scatter, 3 continue-attack,
// 4 guard, 5..52 special power), and the new decal is tinted by the fourth
// argument. Shape: the same-type early-out jumps to the shared tint tail, so
// the body sits inside `if (cursorType != m_curRcType)`; the tint is an
// explicit if/else (a ternary is sunk past the decal null test).

#include "Lib/Coord3D.h"

typedef float Real;
typedef int Int;
typedef bool Bool;

enum RadiusCursorType { RADIUSCURSOR_NONE = 0 };
enum WeaponSlotType { PRIMARY_WEAPON = 0 };

class Object;

// The two local-player queries reached by the shortcut commands; the ledger
// names their bodies 0x000D4400 (Player::findNaturalCommandCenter) and
// 0x000D4490 (still address-derived).
class Player
{
public:
	Object *findNaturalCommandCenter();
};
class BfmeOwnerXF
{
public:
	Object *bfmeFindXF();
};

class PlayerList
{
public:
	Player *getLocalPlayer() { return m_local; }
private:
	unsigned char m_unmodelled_00[0x0C];
	Player *m_local;					// +0x0C
};
extern PlayerList *ThePlayerList;

class WeaponTemplate
{
public:
	Real getScatterRadius() const { return m_scatterRadius; }
	Real getScatterTargetScalar() const { return m_scatterTargetScalar; }
	Real getContinueAttackRange() const { return m_continueAttackRange; }
private:
	unsigned char m_unmodelled_000[0x28];
	Real m_scatterRadius;				// +0x28
	Real m_scatterTargetScalar;			// +0x2C
	unsigned char m_unmodelled_030[0x510 - 0x30];
	Real m_continueAttackRange;			// +0x510
};

class Weapon
{
public:
	Real getScatterRadius() const { return m_template->getScatterRadius(); }
	Real getScatterTargetScalar() const { return m_template->getScatterTargetScalar(); }
	Real getContinueAttackRange() const { return m_template->getContinueAttackRange(); }
private:
	void *m_vtbl;
	const WeaponTemplate *m_template;	// +0x04
};

class WeaponSet
{
public:
	Weapon *getWeaponInWeaponSlot(WeaponSlotType wslot) const;
};

class Object
{
public:
	Player *getControllingPlayer() const;
	Weapon *getWeaponInWeaponSlot(WeaponSlotType wslot) const { return m_weaponSet.getWeaponInWeaponSlot(wslot); }
private:
	unsigned char m_unmodelled_000[0x264];
	WeaponSet m_weaponSet;				// +0x264
};

class Drawable
{
public:
	__declspec(dllimport) __forceinline Object *getObject() { return m_object; }
private:
	unsigned char m_unmodelled_000[0xFC];
	Object *m_object;					// +0x0FC
};

class AIGuardMachine
{
public:
	static Real _bfme_getStdGuardRange(const Object *obj);
};

class SpecialPowerTemplate;

// The special-power radius getter; the ledger names its body 0x000C4670.
class BfmeThingEOG
{
public:
	Real bfmeGoEOG();
};

// The decal's tint setter; the ledger names its body 0x00459880.
class BfmeColourABK
{
public:
	void bfmeSetABK(Int color);
};

class RadiusDecal
{
public:
	void clear();
	void setColor(Int color)
	{
		if (m_decal)
			m_decal->bfmeSetABK(color);
	}
	void *m_template;
	BfmeColourABK *m_decal;				// +0x04
	unsigned char m_unmodelled_08[0x08];
};

class RadiusDecalTemplate
{
public:
	void createRadiusDecal(const Coord3D &pos, Real radius, const Player *owningPlayer, RadiusDecal &result) const;
private:
	unsigned char m_unmodelled_00[0x30];
};

class CommandButton
{
public:
	Int getCommandType() const { return m_commandType; }
private:
	unsigned char m_unmodelled_00[0x10];
	Int m_commandType;					// +0x10
};

class InGameUI
{
public:
	virtual void v000();
	virtual void v004();
	virtual void v008();
	virtual void v00c();
	virtual void v010();
	virtual void v014();
	virtual void v018();
	virtual void v01c();
	virtual void v020();
	virtual void v024();
	virtual void v028();
	virtual void v02c();
	virtual void v030();
	virtual void v034();
	virtual void v038();
	virtual void v03c();
	virtual void v040();
	virtual void v044();
	virtual void v048();
	virtual void v04c();
	virtual void v050();
	virtual void v054();
	virtual void v058();
	virtual void v05c();
	virtual void v060();
	virtual void v064();
	virtual void v068();
	virtual void v06c();
	virtual void v070();
	virtual void v074();
	virtual void v078();
	virtual void v07c();
	virtual void v080();
	virtual void v084();
	virtual void v088();
	virtual void v08c();
	virtual void v090();
	virtual void v094();
	virtual void v098();
	virtual void v09c();
	virtual void v0a0();
	virtual void v0a4();
	virtual void v0a8();
	virtual void v0ac();
	virtual void v0b0();
	virtual void v0b4();
	virtual void v0b8();
	virtual void v0bc();
	virtual void v0c0();
	virtual void v0c4();
	virtual void v0c8();
	virtual void v0cc();
	virtual void v0d0();
	virtual void v0d4();
	virtual void v0d8();
	virtual void v0dc();
	virtual void v0e0();
	virtual void v0e4();
	virtual void v0e8();
	virtual void v0ec();
	virtual Int getSelectCount();
	virtual void v0f4();
	virtual void v0f8();
	virtual void v0fc();
	virtual void v100();
	virtual Drawable *getFirstSelectedDrawable();
	virtual void v108();
	virtual void v10c();
	virtual void v110();
	virtual void v114();
	virtual void setRadiusCursor(RadiusCursorType cursorType, const SpecialPowerTemplate *specPowTempl,
		WeaponSlotType weaponSlot, Bool fourth);

protected:
	void handleRadiusCursor();

private:
	void *m_vtbl_pad_end;
	unsigned char m_unmodelled_004[0x230 - 0x8];
	CommandButton *m_pendingGUICommand;		// +0x230
	unsigned char m_unmodelled_234[0x894 - 0x234];
	RadiusDecalTemplate m_radiusCursors[53];	// +0x894
	RadiusDecal m_curRadiusCursor;			// +0x1284
	RadiusCursorType m_curRcType;			// +0x1294
};

void InGameUI::setRadiusCursor(RadiusCursorType cursorType, const SpecialPowerTemplate *specPowTempl,
	WeaponSlotType weaponSlot, Bool fourth)
{
	if (cursorType != m_curRcType)
	{
		m_curRadiusCursor.clear();
		m_curRcType = RADIUSCURSOR_NONE;

		if (cursorType == RADIUSCURSOR_NONE)
			return;

		Object *obj = 0;
		if (m_pendingGUICommand)
		{
			if (m_pendingGUICommand->getCommandType() == 0x1F)
			{
				if (ThePlayerList && ThePlayerList->getLocalPlayer())
					obj = ThePlayerList->getLocalPlayer()->findNaturalCommandCenter();
			}
			else if (m_pendingGUICommand->getCommandType() == 0x24)
			{
				if (ThePlayerList && ThePlayerList->getLocalPlayer())
					obj = ((BfmeOwnerXF *)ThePlayerList->getLocalPlayer())->bfmeFindXF();
			}
		}

		if (obj == 0)
		{
			if (getSelectCount() == 0)
				return;

			Drawable *draw = getFirstSelectedDrawable();
			if (draw == 0)
				return;

			obj = draw->getObject();
			if (obj == 0)
				return;
		}

		Player *controller = obj->getControllingPlayer();
		if (controller == 0)
			return;

		Real radius = 0.0f;
		const Weapon *w = 0;
		switch (cursorType)
		{
		case 2:
			w = obj->getWeaponInWeaponSlot(weaponSlot);
			radius = w ? (w->getScatterRadius() + w->getScatterTargetScalar()) : 0.0f;
			break;
		case 3:
			w = obj->getWeaponInWeaponSlot(weaponSlot);
			radius = w ? w->getContinueAttackRange() : 0.0f;
			break;
		case 4:
			radius = AIGuardMachine::_bfme_getStdGuardRange(obj);
			break;
		case 5:
		case 6:
		case 7:
		case 8:
		case 9:
		case 10:
		case 11:
		case 12:
		case 13:
		case 14:
		case 15:
		case 16:
		case 17:
		case 18:
		case 19:
		case 20:
		case 21:
		case 22:
		case 23:
		case 24:
		case 25:
		case 26:
		case 27:
		case 28:
		case 29:
		case 30:
		case 31:
		case 32:
		case 33:
		case 34:
		case 35:
		case 36:
		case 37:
		case 38:
		case 39:
		case 40:
		case 41:
		case 42:
		case 43:
		case 44:
		case 45:
		case 46:
		case 47:
		case 48:
		case 49:
		case 50:
		case 51:
		case 52:
			radius = specPowTempl ? ((BfmeThingEOG *)specPowTempl)->bfmeGoEOG() : 0.0f;
			break;
		}

		if (radius <= 0.0f)
			return;

		Coord3D pos = { 0, 0, 0 };
		m_radiusCursors[cursorType].createRadiusDecal(pos, radius, controller, m_curRadiusCursor);
		m_curRcType = cursorType;

		handleRadiusCursor();
	}

	Int color;
	if (fourth)
		color = 0xFFFFFFFF;
	else
		color = 0xFFFF1414;
	m_curRadiusCursor.setColor(color);
}
