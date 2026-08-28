// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: GODupBase's constructor, retail 0x001B0D20, 85 bytes. The body
// carried only a machine byte-dump row; reverse/reloc_names.csv holds the name
// with identity=real.
//
// The same two-base shape as W3DTerrainVisualBase at 0x00602C70: the root the
// ledger sees at vtable 0x01073744 with its constructor inlined to that store,
// then SubsystemInterface constructed on this + 4, then the class's own two
// vtables over both, the secondary first. Nothing else -- no members are
// touched at all.
//
// The frame carries one unwind state, for the root base, because the
// SubsystemInterface constructor is a call that can throw.

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

class GODupBase : public BfmeSnapshotBase, public SubsystemInterface
{
public:
	GODupBase();
};

// ??0GODupBase@@QAE@XZ
GODupBase::GODupBase()
{
}
