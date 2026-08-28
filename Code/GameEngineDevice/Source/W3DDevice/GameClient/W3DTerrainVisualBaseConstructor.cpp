// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: W3DTerrainVisualBase's constructor, retail 0x00602C70, 92 bytes.
// The body carried only a machine byte-dump row; the symbols.csv pin names it.
//
// Two bases. The first is the root the ledger already sees at vtable
// 0x01073744 across the ModuleData destructors; its constructor is inlined to
// nothing but that store. The second is SubsystemInterface, whose constructor
// at 0x009A1A30 is already ledgered and is called on this + 4. Then the class
// puts its own two vtables over both, the secondary first, and clears the word
// at +0x0C.
//
// The frame carries an unwind state for the first base, which is why the
// constructor has an SEH frame at all: if the SubsystemInterface constructor
// throws, that base has to come down again.

class BfmeSnapshotBase
{
public:
	virtual void bfmeSlot0(void);
	~BfmeSnapshotBase();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/SubsystemInterface.h
class SubsystemInterface
{
public:
	SubsystemInterface();					// retail 0x009A1A30
	virtual void bfmeSlot0(void);

private:
	int m_bfmeState;
};

class W3DTerrainVisualBase : public BfmeSnapshotBase, public SubsystemInterface
{
public:
	W3DTerrainVisualBase();

private:
	int m_bfme0C;						// +0x0C
};

// ??0W3DTerrainVisualBase@@QAE@XZ
W3DTerrainVisualBase::W3DTerrainVisualBase()
{
	m_bfme0C = 0;
}
