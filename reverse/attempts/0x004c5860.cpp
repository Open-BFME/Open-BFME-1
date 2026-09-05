// ?Rva004C5860@@YA_NPAXIII@Z
// partial score=0.55 date=2026-09-05
// cl: /DNDEBUG /MD /EHsc
//
// Address-derived candidate for retail 0x004C5860 (680 B). Message constants
// recovered from reference/.../GameClient/GameWindow.h and Gadget.h:
//   msg==2      -> GWM_DESTROY
//   msg==0x17   -> GWM_INPUT_FOCUS
//   msg==0x4008 -> GBM_SELECTED
// Globals identified via reverse/symbols.csv: 0x012ED600 = TheNameKeyGenerator,
// 0x012F1B40 = TheWindowManager. The GBM_SELECTED branch is the classic MSVC
// function-local-static lazy-init pattern: four separate `static` NameKeyType
// locals share one guard byte (0x012F392C, one bit per static), each seeded
// once from TheNameKeyGenerator->bfmeConv1060(literal.m_data), then compared
// against a child window's id (winGetWindowId) to invoke an optional callback
// slot on the node returned by bfmeFindAWB, and finally reach a
// GameWindowManager virtual call at vtable+0x78 (slot 30, generic name -- not
// proven to be winDestroy). See --notes on the banked attempt for open
// questions (literal string bytes for the four keys are unknown; DIR32
// verification will need the real text).

class BfmeNodeAWB;
class BfmeKeyAWB
{
public:
	BfmeNodeAWB *bfmeFindAWB();
};

class BfmeNodeLC;
class BfmeKeyLC
{
public:
	void bfmeUse926B(BfmeNodeLC *node);
};

class BfmeQ1060
{
public:
	int bfmeConv1060(int name);
};

class GameWindow
{
public:
	int winGetWindowId();
};
extern "C" void *g_theNameKeyGenerator; // @0x012ED600 == TheNameKeyGenerator

class GameWindowManager
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
	virtual void slot16(); virtual void slot17(); virtual void slot18(); virtual void slot19();
	virtual void slot20(); virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void slot24(); virtual void slot25(); virtual void slot26(); virtual void slot27();
	virtual void slot28(); virtual void slot29();
	virtual void winDestroyGuess(void *window); // slot30, offset 0x78 -- not proven
};
extern GameWindowManager *TheWindowManager;

class BFMERetailAsciiString
{
public:
	BFMERetailAsciiString(const char *text);
	~BFMERetailAsciiString() { releaseBuffer(); }

	void releaseBuffer();
	char *m_data;
};

static inline int keyOf(BFMERetailAsciiString &s)
{
	return s.m_data ? (int)(s.m_data + 8) : 0x0107388b;
}

struct NodeCallbacks
{
	void (*cb0)();
	void (*cb1)();
	void (*cb2)();
	void (*cb3)();
};

bool __cdecl Rva004C5860(void *self, unsigned int msg, unsigned int mData1, unsigned int mData2)
{
	switch (msg)
	{
	case 2: // GWM_DESTROY
	{
		BfmeNodeAWB *node = ((BfmeKeyAWB *)self)->bfmeFindAWB();
		delete node;
		((BfmeKeyLC *)self)->bfmeUse926B(0);
		return true;
	}

	case 0x17: // GWM_INPUT_FOCUS
		if (mData1 == 1)
			*(bool *)mData2 = true;
		return true;

	case 0x4008: // GBM_SELECTED
	{
		GameWindow *child = (GameWindow *)mData1;
		unsigned int childId = (unsigned int)child->winGetWindowId();

		static int keyA;
		static bool doneA;
		if (!doneA)
		{
			doneA = true;
			BFMERetailAsciiString s("Key1"); // literal text unknown -- placeholder
			keyA = ((BfmeQ1060 *)g_theNameKeyGenerator)->bfmeConv1060(keyOf(s));
		}

		static int keyB;
		static bool doneB;
		if (!doneB)
		{
			doneB = true;
			BFMERetailAsciiString s("Key2");
			keyB = ((BfmeQ1060 *)g_theNameKeyGenerator)->bfmeConv1060(keyOf(s));
		}

		static int keyC;
		static bool doneC;
		if (!doneC)
		{
			doneC = true;
			BFMERetailAsciiString s("Key3");
			keyC = ((BfmeQ1060 *)g_theNameKeyGenerator)->bfmeConv1060(keyOf(s));
		}

		static int keyD;
		static bool doneD;
		if (!doneD)
		{
			doneD = true;
			BFMERetailAsciiString s("Key4");
			keyD = ((BfmeQ1060 *)g_theNameKeyGenerator)->bfmeConv1060(keyOf(s));
		}

		BfmeNodeAWB *node = ((BfmeKeyAWB *)self)->bfmeFindAWB();
		NodeCallbacks *cbs = (NodeCallbacks *)node;

		if (childId == (unsigned int)keyA)
		{
			if (cbs->cb0) cbs->cb0();
		}
		else if (childId == (unsigned int)keyB)
		{
			if (cbs->cb1) cbs->cb1();
		}
		else if (childId == (unsigned int)keyC)
		{
			if (cbs->cb2) cbs->cb2();
		}
		else if (childId == (unsigned int)keyD)
		{
			if (cbs->cb3) cbs->cb3();
		}
		else
		{
			return true;
		}

		TheWindowManager->winDestroyGuess(self);
		return true;
	}

	default:
		return false;
	}
}
