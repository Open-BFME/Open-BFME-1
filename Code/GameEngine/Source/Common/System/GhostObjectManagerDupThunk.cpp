// cl: /DNDEBUG /MD /EHsc
// Trial: per-TU duplicate copy of GhostObjectManager's default constructor,
// retail 0x006BC530. Calls a combined Snapshot+SubsystemInterface base
// constructor then overwrites both vtables with GhostObjectManager's own.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Snapshot.h
class Snapshot
{
public:
	Snapshot();
	virtual void crc() {}
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/SubsystemInterface.h
class SubsystemInterface
{
public:
	SubsystemInterface();
	virtual void init() {}
};

class GODupBase : public Snapshot, public SubsystemInterface
{
public:
	GODupBase();
};

__declspec(noinline)
// ?GODupBase::GODupBase present-unmatched
GODupBase::GODupBase()
{
}

class Gen_006BC530 : public GODupBase
{
public:
	Gen_006BC530();
};

// ??0Gen_006BC530@@QAE@XZ present-unmatched
Gen_006BC530::Gen_006BC530()
{
}
