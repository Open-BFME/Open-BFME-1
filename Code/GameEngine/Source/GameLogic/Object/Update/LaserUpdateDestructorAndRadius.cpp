// cl: /DNDEBUG /MD /EHsc
// readable body of ??1LaserUpdate@@: Code/GameEngine/Source/GameLogic/Object/Update/LaserUpdate.cpp
// readable body of ?getCurrentLaserRadius@LaserUpdate@@: Code/GameEngine/Source/GameLogic/Object/Update/LaserUpdate.cpp
//
// LaserUpdate::~LaserUpdate (retail 0x00603820, 118 bytes) destroys the two
// particle-system ids at +0x28 and +0x2C through TheParticleSystemManager,
// then the ClientUpdateModule base. getCurrentLaserRadius (retail 0x00603A00,
// 63 bytes) walks the drawable's DrawModule list for a LaserDrawInterface and
// returns its template width times the scalar at +0x3C.
//
// They sat in two files with incompatible pictures of the same module: the
// destructor's had the real base chain but eight anonymous bytes at +0x04, the
// radius query had no bases at all and put the drawable at +0x08 inside them.
// Together they place the drawable where it belongs -- a ClientUpdateModule
// field at +0x08, which is why every client update module can reach it -- and
// give LaserUpdate's own fields one set of offsets: the two particle ids at
// +0x28 and +0x2C and the width scalar at +0x3C.
//
// The constructor at 0x00603790 installs the same vtable 0x01115370; the name
// getter at 0x00603810 returns "LaserUpdate". Const getDrawModules is the ILT
// at 0x00040A8E (ICF twin of the non-const getter at 0x00021472); both are
// `mov eax,[ecx+0x150]; ret`.

enum ParticleSystemID
{
	INVALID_PARTICLE_SYSTEM_ID = 0
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/ParticleSys.h
class ParticleSystemManager
{
public:
	void destroyParticleSystemByID(ParticleSystemID id);
};

extern ParticleSystemManager *TheParticleSystemManager;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/DrawModule.h
class LaserDrawInterface
{
public:
	virtual float getLaserTemplateWidth() const;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/DrawModule.h
class DrawModule
{
public:
	virtual void p00(); virtual void p01(); virtual void p02(); virtual void p03();
	virtual void p04(); virtual void p05(); virtual void p06(); virtual void p07();
	virtual void p08(); virtual void p09(); virtual void p10(); virtual void p11();
	virtual void p12(); virtual void p13(); virtual void p14(); virtual void p15();
	virtual void p16(); virtual void p17(); virtual void p18(); virtual void p19();
	virtual void p20(); virtual void p21(); virtual void p22(); virtual void p23();
	virtual void p24(); virtual void p25(); virtual void p26(); virtual void p27();
	virtual void p28(); virtual void p29(); virtual void p30(); virtual void p31();
	virtual void p32(); virtual void p33(); virtual void p34(); virtual void p35();
	virtual void p36(); virtual void p37(); virtual void p38(); virtual void p39();
	virtual void p40(); virtual void p41(); virtual void p42(); virtual void p43();
	virtual LaserDrawInterface *getLaserDrawInterface() const;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/Drawable.h
class Drawable
{
public:
	void **getDrawModules() const;
};

class Rva0002B8C8TailBase
{
public:
	virtual ~Rva0002B8C8TailBase();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ClientUpdateModule.h
class ClientUpdateModule : public Rva0002B8C8TailBase
{
public:
	virtual ~ClientUpdateModule() {}
	virtual void crc();
	virtual void xfer();
	virtual void loadPostProcess();
	virtual void clientUpdate();

protected:
	char m_pad04[4];
	Drawable *m_drawable;					// +0x08
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/LaserUpdate.h
class LaserUpdate : public ClientUpdateModule
{
public:
	virtual ~LaserUpdate();
	virtual void clientUpdate();

	float getCurrentLaserRadius() const;

private:
	char m_pad0C[0x28 - 0x0C];
	ParticleSystemID m_particleSystemID;			// +0x28
	ParticleSystemID m_targetParticleSystemID;		// +0x2C
	char m_pad30[0x3C - 0x30];
	float m_currentWidthScalar;				// +0x3C
};

// ??1LaserUpdate@@UAE@XZ
LaserUpdate::~LaserUpdate()
{
	if (m_particleSystemID)
		TheParticleSystemManager->destroyParticleSystemByID(m_particleSystemID);
	if (m_targetParticleSystemID)
		TheParticleSystemManager->destroyParticleSystemByID(m_targetParticleSystemID);
}

// ?getCurrentLaserRadius@LaserUpdate@@QBEMXZ
float LaserUpdate::getCurrentLaserRadius() const
{
	const Drawable *draw = m_drawable;
	for (DrawModule **d = (DrawModule **)draw->getDrawModules(); *d; ++d)
	{
		LaserDrawInterface *ldi = (*d)->getLaserDrawInterface();
		if (ldi)
			return ldi->getLaserTemplateWidth() * m_currentWidthScalar;
	}
	return 0.0f;
}
