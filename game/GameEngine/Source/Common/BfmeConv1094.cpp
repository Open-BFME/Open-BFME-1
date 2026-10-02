// Open-BFME5 conversions.

// Keep the retail ILT entry points, using the same member-pointer call form
// as the other matched callers. Their routes are, respectively:
// Object::getControllingPlayer, GameLogic::findObjectByID,
// PlayerList::getEachPlayerFromMask, and ScriptEngine::unidentified_0034DB40.
extern void j_00020824(void);
extern void j_0001f253(void);
extern void j_0002ee60(void);
extern void j_000230b5(void);

class BfmeR1094;

struct BfmeW1094
{
	char m_bfmePad[8];
	int m_bfme08;
};

class BfmeF1094
{
public:
	virtual void bfmeSlot1094F_0(void);
	virtual void bfmeSlot1094F_1(void);
	virtual void bfmeSlot1094F_2(void);
	virtual void bfmeSlot1094F_3(void);
	virtual void bfmeSlot1094F_4(void);
	virtual void bfmeSlot1094F_5(void);
	virtual void bfmeSlot1094F_6(void);
	virtual void bfmeSlot1094F_7(void);
	virtual void bfmeSlot1094F_8(void);
	virtual void bfmeSlot1094F_9(void);
	virtual void bfmeSlot1094F_10(void);
	virtual void bfmeSlot1094F_11(void);
	virtual void bfmeSlot1094F_12(void);
	virtual void bfmeSlot1094F_13(void);
	virtual void bfmeSlot1094F_14(void);
	virtual BfmeW1094 * bfmeSlot1094F_15(void);
};

struct BfmeE1094
{
	char m_bfmePad[0x200];
	BfmeF1094 *m_bfme200;
};

class BfmeK1094
{
};

class BfmeB1094
{
};

class BfmeD1094
{
};

class BfmeP1094
{
public:
	virtual void bfmeSlot1094P_0(void);
	virtual void bfmeSlot1094P_1(void);
	virtual void bfmeSlot1094P_2(void);
	virtual void bfmeSlot1094P_3(void);
	virtual void bfmeSlot1094P_4(void);
	virtual void bfmeSlot1094P_5(void);
	virtual void bfmeSlot1094P_6(void);
	virtual void bfmeSlot1094P_7(void);
	virtual void bfmeSlot1094P_8(void);
	virtual void bfmeSlot1094P_9(void);
	virtual void bfmeSlot1094P_10(void);
	virtual void bfmeSlot1094P_11(void);
	virtual void bfmeSlot1094P_12(void);
	virtual void bfmeSlot1094P_13(void);
	virtual void bfmeSlot1094P_14(void);
	virtual void bfmeSlot1094P_15(void);
	virtual void bfmeSlot1094P_16(void);
	virtual void bfmeSlot1094P_17(void);
	virtual void bfmeSlot1094P_18(void);
	virtual void bfmeSlot1094P_19(void);
	virtual void bfmeSlot1094P_20(void);
	virtual void bfmeSlot1094P_21(void);
	virtual void bfmeSlot1094P_22(void);
	virtual void bfmeSlot1094P_23(void);
	virtual void bfmeSlot1094P_24(void);
	virtual void bfmeSlot1094P_25(void);
	virtual BfmeE1094 * bfmeSlot1094P_26(int a);
};

class GameLogic;

extern GameLogic *TheGameLogic;				// retail 0x012F0898

// retail 0x012ED748: EA's `PlayerList *ThePlayerList`, defined once in
// game/GameEngine/Source/Common/RTS/PlayerList.cpp, so the reference carries
// the defining name ?ThePlayerList@@3PAVPlayerList@@A. BfmeD1094 is this TU's
// local view of the pointee; cast at the use.
class PlayerList;
extern PlayerList *ThePlayerList;

// retail 0x012F076C: EA's ScriptEngine *TheScriptEngine, defined once in
// game/GameEngine/Source/GameLogic/ScriptEngine/ScriptEngine.cpp. BfmeP1094 is
// this TU's local view of the pointee; cast at the use.
class ScriptEngine;
extern ScriptEngine *TheScriptEngine;

char __stdcall bfmeGo1094A(int a, int b)
{
	typedef BfmeK1094 *(BfmeB1094::*FindObject)(int);
	typedef BfmeR1094 *(BfmeK1094::*ControllingPlayer)(void) const;
	typedef BfmeR1094 *(BfmeD1094::*EachPlayer)(short *);
	typedef int (BfmeP1094::*PlayerMask)(int);
	union { void (*raw)(void); FindObject member; } findObject = { j_0001f253 };
	union { void (*raw)(void); ControllingPlayer member; } controllingPlayer = { j_00020824 };
	union { void (*raw)(void); EachPlayer member; } eachPlayer = { j_0002ee60 };
	union { void (*raw)(void); PlayerMask member; } playerMask = { j_000230b5 };

	BfmeE1094 *e = ((BfmeP1094 *)TheScriptEngine)->bfmeSlot1094P_26(a);
	BfmeW1094 *w;
	BfmeK1094 *k;

	if (!e)
		return 0;
	if (!e->m_bfme200)
		return 0;
	w = e->m_bfme200->bfmeSlot1094F_15();
	if (!w)
		return 0;
	k = (((BfmeB1094 *)TheGameLogic)->*findObject.member)(w->m_bfme08);
	if (!k)
		return 0;
	a = (((BfmeP1094 *)TheScriptEngine)->*playerMask.member)(b);
	while ((short)a) {
		BfmeR1094 *r = (((BfmeD1094 *)ThePlayerList)->*eachPlayer.member)((short *)&a);

		if ((k->*controllingPlayer.member)() == r)
			return 1;
	}
	return 0;
}
