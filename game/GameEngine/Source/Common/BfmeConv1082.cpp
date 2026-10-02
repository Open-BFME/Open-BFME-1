// Open-BFME5 conversions.

class BfmeA1082
{
public:
	virtual void bfmeSlot1082A_0(void);
	virtual void bfmeSlot1082A_1(void);
	virtual void bfmeSlot1082A_2(void);
	virtual void bfmeSlot1082A_3(void);
	virtual void bfmeSlot1082A_4(void);
	virtual void bfmeSlot1082A_5(void);
	virtual void bfmeSlot1082A_6(void);
	virtual void bfmeSlot1082A_7(void);
	virtual void bfmeSlot1082A_8(void);
	virtual void bfmeSlot1082A_9(void);
	virtual void bfmeSlot1082A_10(void);
	virtual void bfmeSlot1082A_11(void);
	virtual void bfmeSlot1082A_12(void);
	virtual void bfmeSlot1082A_13(void);
	virtual void bfmeSlot1082A_14(void);
	virtual void bfmeSlot1082A_15(void);
	virtual void bfmeSlot1082A_16(void);
	virtual void bfmeSlot1082A_17(void);
	virtual void bfmeSlot1082A_18(void);
	virtual void bfmeSlot1082A_19(int a);
};

// Retail's global at 0x012ED668 is EA's `AudioManager *TheAudio`, defined once in
// Common/Audio/GameAudio.cpp. BfmeA1082 above is this TU's vslot view of it, so the
// canonical global takes an opaque forward declaration and the casts at the two uses
// are the whole translation.
class AudioManager;

extern AudioManager *TheAudio;

static inline BfmeA1082 *localTheAudio()
{
	return (BfmeA1082 *)TheAudio;
}

struct BfmeB1082
{
	char m_bfmePad[0x74];
	char m_bfme74;
};

// Retail's singleton at 0x012F0898 is GameLogic *TheGameLogic; BfmeB1082 is
// this TU's view of that pointee.
class GameLogic;
extern GameLogic *TheGameLogic;

class BfmeC1082
{
public:
	virtual void bfmeSlot1082C_0(void);
	virtual void bfmeSlot1082C_1(void);
	virtual void bfmeSlot1082C_2(void);
	virtual void bfmeSlot1082C_3(void);
	virtual void bfmeSlot1082C_4(void);
	virtual void bfmeSlot1082C_5(void);
	virtual void bfmeSlot1082C_6(void);
	virtual void bfmeSlot1082C_7(void);
	virtual void bfmeSlot1082C_8(void);
	virtual void bfmeSlot1082C_9(void);
	virtual void bfmeSlot1082C_10(void);
	virtual void bfmeSlot1082C_11(void);
	virtual void bfmeSlot1082C_12(void);
	virtual void bfmeSlot1082C_13(void);
	virtual void bfmeSlot1082C_14(void);
	virtual void bfmeSlot1082C_15(void);
	virtual void bfmeSlot1082C_16(void);
	virtual void bfmeSlot1082C_17(void);
	virtual void bfmeSlot1082C_18(void);
	virtual void bfmeSlot1082C_19(void);
	virtual void bfmeSlot1082C_20(void);
	virtual void bfmeSlot1082C_21(void);
	virtual void bfmeSlot1082C_22(void);
	virtual void bfmeSlot1082C_23(void);
	virtual void bfmeSlot1082C_24(void);
	virtual void bfmeSlot1082C_25(void);
	virtual void bfmeSlot1082C_26(void);
	virtual void bfmeSlot1082C_27(void);
	virtual void bfmeSlot1082C_28(void);
	virtual void bfmeSlot1082C_29(void);
	virtual void bfmeSlot1082C_30(void);
	virtual void bfmeSlot1082C_31(void);
	virtual void bfmeSlot1082C_32(void);
	virtual void bfmeSlot1082C_33(void);
	virtual void bfmeSlot1082C_34(void);
	virtual void bfmeSlot1082C_35(void);
	virtual void bfmeSlot1082C_36(void);
	virtual void bfmeSlot1082C_37(void);
	virtual void bfmeSlot1082C_38(void);
	virtual void bfmeSlot1082C_39(void);
	virtual void bfmeSlot1082C_40(void);
	virtual void bfmeSlot1082C_41(void);
	virtual void bfmeSlot1082C_42(void);
	virtual void bfmeSlot1082C_43(void);
	virtual void bfmeSlot1082C_44(void);
	virtual void bfmeSlot1082C_45(void);
	virtual void bfmeSlot1082C_46(void);
	virtual void bfmeSlot1082C_47(void);
	virtual void bfmeSlot1082C_48(void);
	virtual void bfmeSlot1082C_49(void);
	virtual void bfmeSlot1082C_50(void);
	virtual void bfmeSlot1082C_51(void);
	virtual void bfmeSlot1082C_52(void);
	virtual void bfmeSlot1082C_53(void);
	virtual void bfmeSlot1082C_54(void);
	virtual void bfmeSlot1082C_55(void);
	virtual void bfmeSlot1082C_56(void);
	virtual void bfmeSlot1082C_57(void);
	virtual void bfmeSlot1082C_58(void);
	virtual void bfmeSlot1082C_59(void);
	void bfmeStop1082(void);
};

// Retail 0x012F1270 is EA's `Display *TheDisplay`, defined once in
// game/GameEngine/Source/GameClient/Display.cpp. This TU only drives the
// movie-playback path, so the reference carries the canonical spelling and the
// observed vtable slice stays a TU-local view cast at each use.
class Display;
extern Display *TheDisplay;

static inline BfmeC1082 *bfmeConv1082TheDisplay() { return (BfmeC1082 *)TheDisplay; }

class BfmeQ1082
{
public:
	void bfmeGo1082A(void);
	char m_bfmePad[8];
	int m_bfme08;
	char m_bfmePad1[0x10];
	int m_bfme1c;
	int m_bfme20;
};

void BfmeQ1082::bfmeGo1082A(void)
{
	if (m_bfme1c != 1) {
		localTheAudio()->bfmeSlot1082A_19(m_bfme1c);
		m_bfme1c = 1;
	}
	if (m_bfme20 != 1) {
		localTheAudio()->bfmeSlot1082A_19(m_bfme20);
		m_bfme20 = 1;
	}
	((BfmeB1082 *)TheGameLogic)->m_bfme74 = 0;
	bfmeConv1082TheDisplay()->bfmeSlot1082C_59();
	bfmeConv1082TheDisplay()->bfmeStop1082();
	m_bfme08 = 0;
}

class BfmeS1082
{
public:
	virtual void bfmeSlot1082S_0(void);
	virtual void bfmeSlot1082S_1(void);
};

extern BfmeS1082 *g_bfmeS1082_0;
extern BfmeS1082 *g_bfmeS1082_1;
extern BfmeS1082 *g_bfmeS1082_2;
extern BfmeS1082 *g_bfmeS1082_3;
extern BfmeS1082 *g_bfmeS1082_4;
extern BfmeS1082 *g_bfmeS1082_5;
extern BfmeS1082 *g_bfmeS1082_6;
extern BfmeS1082 *g_bfmeS1082_7;

void bfmeGo1082B(void)
{
	if (g_bfmeS1082_0) {
		g_bfmeS1082_0->bfmeSlot1082S_1();
		g_bfmeS1082_0 = 0;
	}
	if (g_bfmeS1082_1) {
		g_bfmeS1082_1->bfmeSlot1082S_1();
		g_bfmeS1082_1 = 0;
	}
	if (g_bfmeS1082_2) {
		g_bfmeS1082_2->bfmeSlot1082S_1();
		g_bfmeS1082_2 = 0;
	}
	if (g_bfmeS1082_3) {
		g_bfmeS1082_3->bfmeSlot1082S_1();
		g_bfmeS1082_3 = 0;
	}
}

void bfmeGo1082C(void)
{
	if (g_bfmeS1082_4) {
		g_bfmeS1082_4->bfmeSlot1082S_1();
		g_bfmeS1082_4 = 0;
	}
	if (g_bfmeS1082_5) {
		g_bfmeS1082_5->bfmeSlot1082S_1();
		g_bfmeS1082_5 = 0;
	}
	if (g_bfmeS1082_6) {
		g_bfmeS1082_6->bfmeSlot1082S_1();
		g_bfmeS1082_6 = 0;
	}
	if (g_bfmeS1082_7) {
		g_bfmeS1082_7->bfmeSlot1082S_1();
		g_bfmeS1082_7 = 0;
	}
}
