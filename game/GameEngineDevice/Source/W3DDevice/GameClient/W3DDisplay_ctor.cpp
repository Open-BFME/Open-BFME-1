// cl: /DNDEBUG /MD /EHsc

// W3DParticleSystemManager constructor/destructor, retail 0x006FA630 and
// 0x006FA6F0. The installed primary vtable at 0x0112039C contains the
// independently proven particle-manager accessors, and the adjacent retail
// source path names W3DFXParticleSystem.cpp. The base calls resolve to the
// exact ParticleSystemManager constructor/destructor.

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/SubsystemInterface.h
class SubsystemInterface
{
public:
	virtual ~SubsystemInterface();
	int m_name;
};

class DisplaySecond
{
public:
	virtual void slot0();
	virtual void slot1();
	virtual void slot2();
	virtual void slot3();
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/Display.h
class ParticleSystemManager : public SubsystemInterface, public DisplaySecond
{
public:
	ParticleSystemManager();
	virtual ~ParticleSystemManager();

private:
	unsigned char m_unmodelled[0x90 - 12];
};

class W3DDisplayElem
{
public:
	W3DDisplayElem();
	~W3DDisplayElem();

private:
	int m_a;
	int m_b;
	int m_c;
};

class W3DParticleSystemManager : public ParticleSystemManager
{
public:
	W3DParticleSystemManager();
	virtual ~W3DParticleSystemManager();

private:
	int m_90;
	unsigned char m_unmodelled_94[0x28];
	unsigned char m_bc;
	W3DDisplayElem m_arr[2];
};

// ??0W3DParticleSystemManager@@QAE@XZ
W3DParticleSystemManager::W3DParticleSystemManager()
{
	m_bc = 0;
	m_90 = 0;
}

// ??1W3DParticleSystemManager@@UAE@XZ
W3DParticleSystemManager::~W3DParticleSystemManager()
{
}
