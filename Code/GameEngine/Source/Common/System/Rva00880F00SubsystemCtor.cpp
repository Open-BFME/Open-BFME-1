// Fuzzy twin (tools/fuzzy_twin_scan.py) of CollisionManagerConstructor.cpp: retail
// 0x00880F00 is the same SubsystemInterface+Snapshot constructor shape whose only
// work is `m_data = new Impl` -- here a 0x30-byte object whose constructor is the
// matched ??0Gen_008812D0@@QAE@XZ (Bfme5SeventySix.cpp). The subsystem's own
// identity is not recovered, so it keeps an address-derived name.
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

class Gen_008812D0
{
public:
	Gen_008812D0();

private:
	unsigned char m_data[0x30];
};

class Rva00880F00Subsystem : public SubsystemInterface, public Snapshot
{
public:
	Rva00880F00Subsystem();
	virtual ~Rva00880F00Subsystem();
	virtual void init();
	virtual void reset();
	virtual void update();
	virtual void crc(void *xfer);
	virtual void xfer(void *xfer);
	virtual void loadPostProcess();

private:
	Gen_008812D0 *m_data;
};

Rva00880F00Subsystem::Rva00880F00Subsystem()
{
	m_data = new Gen_008812D0;
}
