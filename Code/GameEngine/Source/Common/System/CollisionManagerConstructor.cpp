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

class Rva009A45A0CollisionData
{
public:
	Rva009A45A0CollisionData();

private:
	unsigned char m_data[0xc070];
};

class CollisionManager : public SubsystemInterface, public Snapshot
{
public:
	CollisionManager();
	virtual ~CollisionManager();
	virtual void init();
	virtual void reset();
	virtual void update();
	virtual void crc(void *xfer);
	virtual void xfer(void *xfer);
	virtual void loadPostProcess();

private:
	Rva009A45A0CollisionData *m_data;
};

CollisionManager::CollisionManager()
{
	m_data = new Rva009A45A0CollisionData;
}
