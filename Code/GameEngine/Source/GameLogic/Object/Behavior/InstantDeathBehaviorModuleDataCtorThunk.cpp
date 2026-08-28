// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: clean C++ reconstruction of the retail ModuleData constructor.
// The declarations below retain the BFME object layout while keeping this
// translation unit independent of the reference headers.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Snapshot.h
class Snapshot
{
public:
	Snapshot() {}
	virtual ~Snapshot() {}

private:
	unsigned char m_pad[4];
};

class InstantDeathDieMuxData
{
public:
	InstantDeathDieMuxData();

private:
	unsigned char m_data[0x2c];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/DieModule.h
class DieModuleData : public Snapshot
{
public:
	DieModuleData() {}
	virtual void dieModuleDataAnchor();

private:
	InstantDeathDieMuxData m_dieMuxData;
};

class VectorStorage
{
public:
	VectorStorage() : m_start(0), m_finish(0), m_endOfStorage(0), m_allocator(0)
	{
	}

private:
	void *m_start;
	void *m_finish;
	void *m_endOfStorage;
	void *m_allocator;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/InstantDeathBehavior.h
class InstantDeathBehaviorModuleData : public DieModuleData
{
public:
	InstantDeathBehaviorModuleData();

private:
	VectorStorage m_fx;
	VectorStorage m_ocls;
	VectorStorage m_weapons;
};

// ??0InstantDeathBehaviorModuleData@@QAE@XZ
InstantDeathBehaviorModuleData::InstantDeathBehaviorModuleData()
{
}
