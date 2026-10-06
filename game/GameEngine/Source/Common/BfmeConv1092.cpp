// Open-BFME5 conversions.

class BfmeF1092
{
public:
	virtual void bfmeSlot1092F_0(void);
	virtual void bfmeSlot1092F_1(void);
	virtual void bfmeSlot1092F_2(void);
	virtual void bfmeSlot1092F_3(void);
	virtual void bfmeSlot1092F_4(void);
	virtual void bfmeSlot1092F_5(void);
	virtual void bfmeSlot1092F_6(void);
	virtual void bfmeSlot1092F_7(void);
	virtual void bfmeSlot1092F_8(void);
	virtual void bfmeSlot1092F_9(void);
	virtual void bfmeSlot1092F_10(void);
	virtual void bfmeSlot1092F_11(void);
	virtual void bfmeSlot1092F_12(void);
	virtual void bfmeSlot1092F_13(void);
	virtual void bfmeSlot1092F_14(void);
	virtual void bfmeSlot1092F_15(void);
	virtual void bfmeSlot1092F_16(void);
	virtual void bfmeSlot1092F_17(void);
	virtual void bfmeSlot1092F_18(void);
	virtual void bfmeSlot1092F_19(void);
	virtual void bfmeSlot1092F_20(void);
	virtual void bfmeSlot1092F_21(void);
	virtual void bfmeSlot1092F_22(void);
	virtual void bfmeSlot1092F_23(void);
	virtual void bfmeSlot1092F_24(void);
	virtual void bfmeSlot1092F_25(void);
	virtual void bfmeSlot1092F_26(void);
	virtual void bfmeSlot1092F_27(void);
	virtual void bfmeSlot1092F_28(void);
	virtual void bfmeSlot1092F_29(void);
	virtual void bfmeSlot1092F_30(void);
	virtual void bfmeSlot1092F_31(void);
	virtual void bfmeSlot1092F_32(void);
	virtual void bfmeSlot1092F_33(void);
	virtual void bfmeSlot1092F_34(void);
	virtual void bfmeSlot1092F_35(void);
	virtual void bfmeSlot1092F_36(void);
	virtual void bfmeSlot1092F_37(void);
	virtual void bfmeSlot1092F_38(void);
	virtual void bfmeSlot1092F_39(void);
	virtual void bfmeSlot1092F_40(void);
	virtual void bfmeSlot1092F_41(void);
	virtual void bfmeSlot1092F_42(void);
	virtual void bfmeSlot1092F_43(void);
	virtual void bfmeSlot1092F_44(void);
	virtual void bfmeSlot1092F_45(void);
	virtual void bfmeSlot1092F_46(void);
	virtual void bfmeSlot1092F_47(void);
	virtual void bfmeSlot1092F_48(void);
	virtual void bfmeSlot1092F_49(void);
	virtual void bfmeSlot1092F_50(void);
	virtual void bfmeSlot1092F_51(void);
	virtual void bfmeSlot1092F_52(void);
	virtual void bfmeSlot1092F_53(void);
	virtual void bfmeSlot1092F_54(void);
	virtual void bfmeSlot1092F_55(void);
	virtual void bfmeSlot1092F_56(void);
	virtual void bfmeSlot1092F_57(void);
	virtual void bfmeSlot1092F_58(void);
	virtual void bfmeSlot1092F_59(void);
	virtual void bfmeSlot1092F_60(void);
	virtual void bfmeSlot1092F_61(void);
	virtual void bfmeSlot1092F_62(void);
	virtual void bfmeSlot1092F_63(void);
	virtual void bfmeSlot1092F_64(void);
	virtual void bfmeSlot1092F_65(void);
	virtual void bfmeSlot1092F_66(void);
	virtual void bfmeSlot1092F_67(void);
	virtual void bfmeSlot1092F_68(void);
	virtual void bfmeSlot1092F_69(void);
	virtual void bfmeSlot1092F_70(void);
	virtual void bfmeSlot1092F_71(void);
	virtual void bfmeSlot1092F_72(void);
	virtual void bfmeSlot1092F_73(void);
	virtual void bfmeSlot1092F_74(void);
	virtual void bfmeSlot1092F_75(void);
	virtual int bfmeSlot1092F_76(void);
};

class BfmeR1092
{
public:
	char m_bfmePad[0x24];
	int m_bfme24;
};

class Player;
class Parameter;

// EA's ObjectShroudStatus: 1 and 2 are the two visible states.
enum ObjectShroudStatus
{
	OBJECTSHROUD_INVALID,
	OBJECTSHROUD_CLEAR,
	OBJECTSHROUD_PARTIAL_CLEAR
};

class Object
{
public:
	ObjectShroudStatus getShroudedStatus(int playerIndex) const;	// retail ILT 0x0002B81E -> 0x001C7B30
};

// The object the script engine's slot 26 returns, viewed for its fields.
class BfmeE1092
{
public:
	char m_bfmePad[0x1a4];
	int m_bfme1a4;
	char m_bfmePad1[0x54];
	BfmeF1092 *m_bfme1fc;
};

// Matched at 0x001CAEE0 under this address-derived owner; the caller passes
// the Player from getEachPlayerFromMask as its argument.
class BFMEObjectStealthQuery
{
public:
	bool isStealthedAndUndetected(const Object *viewer) const;		// retail ILT 0x00003B1B -> 0x001CAEE0
};

class PlayerList
{
public:
	Player *getPlayerFromMask(unsigned short mask);				// retail ILT 0x0001DDE5 -> 0x000DF440
	Player *getEachPlayerFromMask(unsigned short &maskToAdjust);	// retail ILT 0x0002EE60 -> 0x000DF4A0
};

class ScriptEngine
{
public:
	unsigned short unidentified_0034DB40(Parameter *pSideParm);	// retail ILT 0x000230B5 -> 0x0034DB40
};

class BfmeP1092
{
public:
	virtual void bfmeSlot1092P_0(void);
	virtual void bfmeSlot1092P_1(void);
	virtual void bfmeSlot1092P_2(void);
	virtual void bfmeSlot1092P_3(void);
	virtual void bfmeSlot1092P_4(void);
	virtual void bfmeSlot1092P_5(void);
	virtual void bfmeSlot1092P_6(void);
	virtual void bfmeSlot1092P_7(void);
	virtual void bfmeSlot1092P_8(void);
	virtual void bfmeSlot1092P_9(void);
	virtual void bfmeSlot1092P_10(void);
	virtual void bfmeSlot1092P_11(void);
	virtual void bfmeSlot1092P_12(void);
	virtual void bfmeSlot1092P_13(void);
	virtual void bfmeSlot1092P_14(void);
	virtual void bfmeSlot1092P_15(void);
	virtual void bfmeSlot1092P_16(void);
	virtual void bfmeSlot1092P_17(void);
	virtual void bfmeSlot1092P_18(void);
	virtual void bfmeSlot1092P_19(void);
	virtual void bfmeSlot1092P_20(void);
	virtual void bfmeSlot1092P_21(void);
	virtual void bfmeSlot1092P_22(void);
	virtual void bfmeSlot1092P_23(void);
	virtual void bfmeSlot1092P_24(void);
	virtual void bfmeSlot1092P_25(void);
	virtual BfmeE1092 * bfmeSlot1092P_26(int a);
};

// 0x012ED748 is retail's PlayerList singleton (game/GameEngine/Source/Common/RTS/PlayerList.cpp
// defines `PlayerList *ThePlayerList`).
extern PlayerList *ThePlayerList;	// retail [0x012ED748]
// 0x012F076C is retail's ScriptEngine singleton (defined once in
// GameLogic/ScriptEngine/ScriptEngine.cpp). Its virtual slot 26 is reached
// through the BfmeP1092 view by casting; bytes are unchanged.
extern ScriptEngine *TheScriptEngine;

static inline BfmeP1092 *theScriptEngineP1092() { return (BfmeP1092 *)TheScriptEngine; }

char __stdcall bfmeGo1092A(int a, int b)
{
	BfmeE1092 *e = theScriptEngineP1092()->bfmeSlot1092P_26(b);
	BfmeR1092 *r;
	int h;

	if (!e)
		return 0;
	if (!e->m_bfme1fc)
		return 0;
	h = e->m_bfme1fc->bfmeSlot1092F_76();
	if (!(short)h)
		return 0;
	r = (BfmeR1092 *)ThePlayerList->getPlayerFromMask((unsigned short)h);
	if (!r)
		return 0;
	unsigned short mask = TheScriptEngine->unidentified_0034DB40((Parameter *)a);
	while (mask) {
		if (r == (BfmeR1092 *)ThePlayerList->getEachPlayerFromMask(mask))
			return 1;
	}
	return 0;
}

char __stdcall bfmeGo1092B(int a, int b)
{
	BfmeE1092 *e = theScriptEngineP1092()->bfmeSlot1092P_26(a);

	if (!e)
		return 0;
	if (e->m_bfme1a4 & 8)
		return 0;
	unsigned short mask = TheScriptEngine->unidentified_0034DB40((Parameter *)b);
	while (mask) {
		BfmeR1092 *r = (BfmeR1092 *)ThePlayerList->getEachPlayerFromMask(mask);

		if (!((BFMEObjectStealthQuery *)e)->isStealthedAndUndetected((const Object *)r)) {
			int m = r->m_bfme24;
			ObjectShroudStatus k = ((const Object *)e)->getShroudedStatus(m);

			if (k == OBJECTSHROUD_CLEAR || k == OBJECTSHROUD_PARTIAL_CLEAR)
				return 1;
		}
	}
	return 0;
}
