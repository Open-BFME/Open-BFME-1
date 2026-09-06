// Fuzzy twin (tools/fuzzy_twin_scan.py) of CollisionManagerConstructor.cpp: retail
// 0x008F7510 is the same SubsystemInterface+Snapshot constructor shape whose only
// work is `m_data = new Impl` -- here the 0x70-byte object whose constructor is
// the matched ??0ShroudManagerImpl008FBA40@@QAE@XZ, so this is the shroud
// manager subsystem; its class name is not otherwise recovered.
// cl: /DNDEBUG /MD /EHsc

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/SubsystemInterface.h
class SubsystemInterface
{
public:
	SubsystemInterface();
	virtual ~SubsystemInterface();
	virtual void init() = 0;
	virtual void reset() = 0;
	virtual void update() = 0;

private:
	void *m_name;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Snapshot.h
class Snapshot
{
public:
	virtual ~Snapshot();
	virtual void crc(void *xfer) = 0;
	virtual void xfer(void *xfer) = 0;
	virtual void loadPostProcess() = 0;
};

class ShroudManagerImpl008FBA40
{
public:
	ShroudManagerImpl008FBA40();

private:
	unsigned char m_data[0x70];
};

class Rva008F7510ShroudManager : public SubsystemInterface, public Snapshot
{
public:
	Rva008F7510ShroudManager();
	virtual ~Rva008F7510ShroudManager();
	virtual void init();
	virtual void reset();
	virtual void update();
	virtual void crc(void *xfer);
	virtual void xfer(void *xfer);
	virtual void loadPostProcess();

private:
	ShroudManagerImpl008FBA40 *m_data;
};

Rva008F7510ShroudManager::Rva008F7510ShroudManager()
{
	m_data = new ShroudManagerImpl008FBA40;
}
