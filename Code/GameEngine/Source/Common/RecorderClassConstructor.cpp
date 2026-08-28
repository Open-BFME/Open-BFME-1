// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: RecorderClass's constructor, retail 0x000993E0, 103 bytes. The
// body carried only a machine byte-dump row; the symbols.csv pin names it, and
// the member constructor and the init it ends with are pinned with this row.
//
// SubsystemInterface is the base -- the same constructor at 0x009A1A30
// W3DTerrainVisualBase calls -- and the class puts its own vtable over it.
// Then two pointers at +0x10 and +0x1C are nulled, the member at +0x20 is
// constructed through its own constructor, the word at +0x2B0 is cleared and
// init runs on this.
//
// The unwind slot goes 0, 2, 3 rather than counting every step, because the two
// nulled members cannot throw: the compiler only writes the state where a call
// follows, and by then those two are already accounted for.

class BfmeRecorderStore
{
public:
	BfmeRecorderStore();					// ILT 0x00016D47
	~BfmeRecorderStore();

private:
	char m_bfmeBody[0x2B0 - 0x20];
};

class BfmeRecorderSlot
{
public:
	BfmeRecorderSlot() { m_bfmePointer = 0; }
	~BfmeRecorderSlot();

private:
	void *m_bfmePointer;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/SubsystemInterface.h
class SubsystemInterface
{
public:
	SubsystemInterface();					// retail 0x009A1A30
	~SubsystemInterface();
	virtual void bfmeSlot0(void);

private:
	int m_bfmeState;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Recorder.h
class RecorderClass : public SubsystemInterface
{
public:
	RecorderClass();

private:
	void bfmeInit(void);					// ILT 0x0000B721

	char m_bfmeHeadA[0x10 - 0x08];
	BfmeRecorderSlot m_bfmeFirst;				// +0x10
	char m_bfmeHeadB[0x1C - 0x14];
	BfmeRecorderSlot m_bfmeSecond;				// +0x1C
	BfmeRecorderStore m_bfmeStore;				// +0x20
	int m_bfme2B0;						// +0x2B0
};

// ??0RecorderClass@@QAE@XZ
RecorderClass::RecorderClass()
{
	m_bfme2B0 = 0;

	bfmeInit();
}
