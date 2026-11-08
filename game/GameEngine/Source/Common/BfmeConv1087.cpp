// Open-BFME5 conversions.

struct BfmeM1087
{
	char m_bfmePad[0x54];
	int m_bfme54;
	char m_bfme58;
};

struct BfmeB1087
{
	char m_bfmePad[0x93];
	char m_bfme93;
};

// Rows the ILTs retail calls: GameLODManager::findDynamicLODLevel (0x0007C440, float),
// BfmeThingAQ::bfmeChooseAQ (0x0007CA40) and W3DDisplay::calculateTerrainLOD (0x006E8E60).
enum DynamicGameLODLevel { DYNAMIC_GAME_LOD_UNKNOWN = -1 };

class GameLODManager
{
public:
	DynamicGameLODLevel findDynamicLODLevel(float value);
};

class BfmeThingAQ
{
public:
	unsigned char bfmeChooseAQ(int level);
};

class BfmeA1087;

// Retail 0x012ED5C8 is `GlobalData *TheWritableGlobalData` (GlobalData.cpp); BfmeM1087 is the view.
class GlobalData;
extern GlobalData *TheWritableGlobalData;
#define g_bfmeM1087 ((BfmeM1087 *)TheWritableGlobalData)
// Retail's global at 0x012F0898 is GameLogic.cpp's `GameLogic *TheGameLogic`;
// the TU keeps its own offset view and casts at each use.
class GameLogic;
extern GameLogic *TheGameLogic;
// Retail 0x012ED5AC is `GameLODManager *TheGameLODManager` (GameLOD.cpp).
extern GameLODManager *TheGameLODManager;
// Retail 0x012F7FE0 is ?TheTerrainRenderObject@@3PAVBaseHeightMapRenderObjClass@@A (data_rows.csv,
// W3DDevice/GameClient/BaseHeightMap.cpp); g_bfmeA1087 was only a pin.
class BaseHeightMapRenderObjClass;
extern BaseHeightMapRenderObjClass *TheTerrainRenderObject;
#define g_bfmeA1087 ( *(BfmeA1087 **)&TheTerrainRenderObject )

class BfmeQ1087;

class W3DDisplay
{
protected:
	void calculateTerrainLOD();
	friend class BfmeQ1087;
};

class BfmeQ1087
{
public:
	void bfmeGo1087A(void);
	char m_bfmePad[0x17c];
	float m_bfme17c;
};

void BfmeQ1087::bfmeGo1087A(void)
{
	if (g_bfmeM1087->m_bfme58 && ((BfmeB1087 *)TheGameLogic)->m_bfme93)
		((BfmeThingAQ *)TheGameLODManager)->bfmeChooseAQ(TheGameLODManager->findDynamicLODLevel(m_bfme17c));
	else
		((BfmeThingAQ *)TheGameLODManager)->bfmeChooseAQ(4);
	if (g_bfmeM1087->m_bfme54 == 8 && g_bfmeA1087)
		((W3DDisplay *)this)->calculateTerrainLOD();
}

// Rows at the ILTs: ScienceStore::getScienceFromInternalName (0x000E7460) and the
// player-mask resolver ScriptEngine::unidentified_0034DB40 (0x0034DB40).
enum ScienceType { SCIENCE_INVALID = -1 };
class AsciiString;

class ScienceStore
{
public:
	ScienceType getScienceFromInternalName(const AsciiString &name) const;
};

class Player
{
public:
	char m_bfmePad[0x24];
	int m_playerIndex;
};

class PlayerList
{
public:
	Player *getEachPlayerFromMask(unsigned short &mask);
};

class Parameter;

class ScriptEngine
{
public:
	virtual void bfmeSlot1087P_0(void);
	virtual void bfmeSlot1087P_1(void);
	virtual void bfmeSlot1087P_2(void);
	virtual void bfmeSlot1087P_3(void);
	virtual void bfmeSlot1087P_4(void);
	virtual void bfmeSlot1087P_5(void);
	virtual void bfmeSlot1087P_6(void);
	virtual void bfmeSlot1087P_7(void);
	virtual void bfmeSlot1087P_8(void);
	virtual void bfmeSlot1087P_9(void);
	virtual void bfmeSlot1087P_10(void);
	virtual void bfmeSlot1087P_11(void);
	virtual void bfmeSlot1087P_12(void);
	virtual void bfmeSlot1087P_13(void);
	virtual void bfmeSlot1087P_14(void);
	virtual void bfmeSlot1087P_15(void);
	virtual void bfmeSlot1087P_16(void);
	virtual void bfmeSlot1087P_17(void);
	virtual void bfmeSlot1087P_18(void);
	virtual void bfmeSlot1087P_19(void);
	virtual void bfmeSlot1087P_20(void);
	virtual void bfmeSlot1087P_21(void);
	virtual void bfmeSlot1087P_22(void);
	virtual void bfmeSlot1087P_23(void);
	virtual void bfmeSlot1087P_24(void);
	virtual void bfmeSlot1087P_25(void);
	virtual void bfmeSlot1087P_26(void);
	virtual void bfmeSlot1087P_27(void);
	virtual void bfmeSlot1087P_28(void);
	virtual void bfmeSlot1087P_29(void);
	virtual void bfmeSlot1087P_30(void);
	virtual void bfmeSlot1087P_31(void);
	virtual void bfmeSlot1087P_32(void);
	virtual void bfmeSlot1087P_33(void);
	virtual void bfmeSlot1087P_34(void);
	virtual void bfmeSlot1087P_35(void);
	virtual void bfmeSlot1087P_36(void);
	virtual void bfmeSlot1087P_37(void);
	virtual void bfmeSlot1087P_38(void);
	virtual void bfmeSlot1087P_39(void);
	virtual void bfmeSlot1087P_40(void);
	virtual void bfmeSlot1087P_41(void);
	virtual void bfmeSlot1087P_42(void);
	virtual void bfmeSlot1087P_43(void);
	virtual void bfmeSlot1087P_44(void);
	virtual void bfmeSlot1087P_45(void);
	virtual void bfmeSlot1087P_46(void);
	virtual void bfmeSlot1087P_47(void);
	virtual void bfmeSlot1087P_48(void);
	virtual char bfmeSlot1087P_49(int a, int b, int c);
	unsigned short unidentified_0034DB40(Parameter *parameter);
};

extern ScienceStore *TheScienceStore;
// Retail 0x012F076C is `ScriptEngine *TheScriptEngine`; the view above carries the vtable slot
// this body calls and the resolver row.
extern ScriptEngine *TheScriptEngine;

// Retail keeps the resolver's whole EAX (no zero-extension of the 16-bit mask),
// so the row is called through its own symbol with an int result view.
static __forceinline int nextPlayerMask(int parameter)
{
	typedef int (ScriptEngine::*Raw)(Parameter *);
	Raw raw = reinterpret_cast<Raw>(&ScriptEngine::unidentified_0034DB40);
	return (TheScriptEngine->*raw)((Parameter *)parameter);
}

// Retail's global at 0x012ED748 is PlayerList.cpp's `PlayerList *ThePlayerList`
// (mangled ?ThePlayerList@@3PAVPlayerList@@A).
extern PlayerList *ThePlayerList;

char __stdcall bfmeGo1087B(int a, int b)
{
	ScienceType e = TheScienceStore->getScienceFromInternalName(*(const AsciiString *)(b + 0x10));

	if (e == SCIENCE_INVALID)
		return 0;
	b = nextPlayerMask(a);
	while ((short)b) {
		Player *r = ThePlayerList->getEachPlayerFromMask(*(unsigned short *)&b);

		if (r) {
			int m = r->m_playerIndex;

			if (TheScriptEngine->bfmeSlot1087P_49(m, e, 1))
				return 1;
		}
	}
	return 0;
}
