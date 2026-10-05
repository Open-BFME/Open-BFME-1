// readable body of ?evaluateMultiplayerPlayerDefeat@ScriptConditions@@IAE_NXZ: game/GameEngine/Source/GameLogic/ScriptEngine/ScriptConditions.cpp
struct BfmeGlobFFA
{
	virtual void bfmeV0();
	virtual void bfmeV1();
	virtual void bfmeV2();
	virtual void bfmeV3();
	virtual void bfmeV4();
	virtual void bfmeV5();
	virtual void bfmeV6();
	virtual void bfmeV7();
	virtual void bfmeV8();
	virtual void bfmeV9();
	virtual void bfmeV10();
	virtual void bfmeV11();
	virtual void bfmeV12();
	virtual void bfmeV13();
	virtual void bfmeV14();
	virtual void bfmeV15();
	virtual void bfmeV16();
	virtual void bfmeV17();
	virtual void bfmeV18();
	virtual void bfmeV19();
	virtual void bfmeV20();
	virtual void bfmeV21();
	virtual void bfmeV22();
	virtual void bfmeV23();
	virtual void bfmeV24();
	virtual void bfmeV25();
	virtual void bfmeV26();
	virtual void bfmeV27();
	virtual void bfmeV28();
	virtual void bfmeV29();
	virtual void bfmeV30();
	virtual void bfmeV31();
	virtual void bfmeV32();
	virtual void bfmeV33();
	virtual void bfmeV34();
	virtual void bfmeV35();
	virtual void bfmeV36();
	virtual void bfmeV37();
	virtual void bfmeV38();
	virtual void bfmeV39();
	virtual void bfmeV40();
	virtual void bfmeV41();
	virtual void bfmeV42();
	virtual void bfmeV43();
	virtual void bfmeV44();
	virtual void bfmeV45();
	virtual void bfmeV46();
	virtual void bfmeV47();
	virtual void bfmeV48();
	virtual void bfmeV49();
	virtual void bfmeV50();
	virtual void bfmeV51();
	virtual void bfmeV52();
	virtual void bfmeV53();
	virtual void bfmeV54();
	virtual void bfmeVirt55FFA(void *a, void *b, void *c, void *d, void *e, int z);
};

class AudioManager;
extern AudioManager *TheAudio;

void __stdcall bfmeGoFFA(void *a, void *b, void *c, void *d, void *e)
{
	BfmeGlobFFA *g = reinterpret_cast<BfmeGlobFFA *>(TheAudio);
	if (g)
		g->bfmeVirt55FFA(a, b, c, d, e, 0);
}

struct BfmeObjFFC;

struct BfmeGlobFFC
{
	virtual void bfmeV0();
	virtual void bfmeV1();
	virtual void bfmeV2();
	virtual void bfmeV3();
	virtual void bfmeV4();
	virtual void bfmeV5();
	virtual void bfmeV6();
	virtual void bfmeV7();
	virtual void bfmeV8();
	virtual void bfmeV9();
	virtual void bfmeV10();
	virtual void bfmeV11();
	virtual void bfmeV12();
	virtual void bfmeV13();
	virtual void bfmeV14();
	virtual void bfmeV15();
	virtual void bfmeV16();
	virtual void bfmeV17();
	virtual void bfmeV18();
	virtual void bfmeV19();
	virtual void bfmeV20();
	virtual void bfmeV21();
	virtual void bfmeV22();
	virtual void bfmeV23();
	virtual void bfmeV24();
	virtual void bfmeV25();
	virtual BfmeObjFFC *bfmeVirt26FFC(void *a);
};

class BfmeSubFFC
{
public:
	void bfmeTailFFC(int f);
};

struct BfmeHoldFFC
{
	unsigned char m_bfmeHead[0x20];
	BfmeSubFFC m_bfmeSub;
};

struct BfmeObjFFC
{
	unsigned char m_bfmeHead[0x204];
	BfmeHoldFFC *m_bfmeS;
};

// Retail's ScriptEngine global at 0x012F076C is ?TheScriptEngine@@3PAVScriptEngine@@A
// (defined in game/GameEngine/Source/GameLogic/ScriptEngine/ScriptEngine.cpp); the
// TU-local BfmeGlobFFC slot view above is reached through this cast helper.
class ScriptEngine;
extern ScriptEngine *TheScriptEngine;
static inline BfmeGlobFFC *bfmeViewFFC()
{
	return (BfmeGlobFFC *)TheScriptEngine;
}

void __stdcall bfmeGoFFC(void *a)
{
	BfmeObjFFC *o = bfmeViewFFC()->bfmeVirt26FFC(a);
	if (o)
	{
		BfmeHoldFFC *s = o->m_bfmeS;
		if (s)
			s->m_bfmeSub.bfmeTailFFC(1);
	}
}

struct BfmeGlobFFD
{
	virtual void bfmeV0();
	virtual void bfmeV1();
	virtual void bfmeV2();
	virtual void bfmeV3();
	virtual void bfmeV4();
	virtual void bfmeV5();
	virtual void bfmeV6();
	virtual void bfmeV7();
	virtual void bfmeV8();
	virtual void bfmeV9();
	virtual void bfmeV10();
	virtual void bfmeV11();
	virtual void bfmeV12();
	virtual void bfmeV13();
	virtual char bfmeAsk14FFD();
	virtual char bfmeAsk15FFD();
};

// Retail global 0x012F079C is EA's TheVictoryConditions, defined once in
// game/GameEngine/Source/GameLogic/ScriptEngine/VictoryConditions.cpp. The
// extern carries the canonical pointee type so the linked name is
// ?TheVictoryConditions@@3PAVVictoryConditionsInterface@@A; the TU-local
// BfmeGlobFFD slot view above is reached through this cast helper.
class VictoryConditionsInterface;
extern VictoryConditionsInterface *TheVictoryConditions;
static inline BfmeGlobFFD *g_bfmeObjFFD_view()
{
	return (BfmeGlobFFD *)TheVictoryConditions;
}

typedef bool Bool;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptConditions.h
class ScriptConditions
{
protected:
	Bool evaluateMultiplayerPlayerDefeat();
};

// ?evaluateMultiplayerPlayerDefeat@ScriptConditions@@IAE_NXZ
Bool ScriptConditions::evaluateMultiplayerPlayerDefeat()
{
	return g_bfmeObjFFD_view()->bfmeAsk15FFD() && !g_bfmeObjFFD_view()->bfmeAsk14FFD();
}

struct BfmeSubFFF
{
	unsigned char m_bfmeHead[4];
};

struct BfmeThingFFF
{
	void bfmeGoFFF();
	void bfmeStepFFF(BfmeSubFFF *s, void *p);
	unsigned char m_bfmeHead[4];
	BfmeSubFFF m_bfmeSub;
	void *m_bfmeP;
};

void BfmeThingFFF::bfmeGoFFF()
{
	while (m_bfmeP)
		bfmeStepFFF(&m_bfmeSub, m_bfmeP);
}

struct BfmeSubFFG
{
	unsigned char m_bfmeHead[4];
};

struct BfmeResFFG
{
	unsigned char m_bfmeHead[0x370];
	int m_bfmeK;
};

class BfmeMidFFG
{
public:
	BfmeResFFG *bfmeFindFFG(BfmeSubFFG *s);
};

struct BfmeHeldFFG
{
	BfmeMidFFG *bfmeGetFFG();
	unsigned char m_bfmeHead[0x38];
	BfmeSubFFG m_bfmeSub;
};

struct BfmeThingFFG
{
	int bfmeGoFFG();
	unsigned char m_bfmeHead[8];
	BfmeHeldFFG *m_bfmeP;
};

int BfmeThingFFG::bfmeGoFFG()
{
	BfmeHeldFFG *h = m_bfmeP;
	BfmeMidFFG *m = h->bfmeGetFFG();
	BfmeResFFG *r = m->bfmeFindFFG(&h->m_bfmeSub);
	if (r)
		return r->m_bfmeK;
	return -1;
}
