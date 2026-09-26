// LifeEvent-family virtual slot 1, RVA 0x005FC450 (184 bytes).
// Final primary table 0x01112190 and construction table 0x01113228
// both route this slot through ILT 0x0001DFF7. Historical method name unknown.
// TheGameClient is registered by GameEngine::init; its derived table
// 0x01120468 dispatches unsigned getFrame at slot 26 (+0x68).
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

typedef unsigned int UnsignedInt;
typedef float Real;

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

class ParticleSystem
{
public:
	void getPosition(Coord3D *position);

private:
	unsigned char m_pad00[0x128];

public:
	UnsignedInt m_frame;
	UnsignedInt m_finished;
};

ParticleSystem *Make00001B18();

class Matrix3D;

class FXList
{
public:
	bool bfmeIsBlocked();
	void doFXPos(const Coord3D *primary, const Matrix3D *primaryMtx,
		Real primarySpeed, const Coord3D *secondary) const;
};

class GameClient
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual void slot20();
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual void slot24();
	virtual void slot25();
	virtual UnsignedInt getFrame();
};

extern GameClient *TheGameClient;

class Rva005FC450LifeEventFamily
{
public:
	virtual void slot00();
	virtual void slot01();

private:
	ParticleSystem *m_system;
	unsigned char m_pad08[0x15];
	bool m_deactivate;
	unsigned char m_pad1e[0x16];
	FXList *m_eventFX;
	UnsignedInt m_frameDelay;
	bool m_active;
	unsigned char m_pad3d[3];
};

void Rva005FC450LifeEventFamily::slot01()
{
	if (!m_active)
		return;
	if (!m_eventFX)
		return;

	ParticleSystem *system = m_system;
	if (!system)
		system = Make00001B18();

	UnsignedInt frameAtStart = system->m_frame;
	UnsignedInt currentFrame = TheGameClient->getFrame();
	if (currentFrame - frameAtStart < m_frameDelay)
		return;

	system = m_system;
	if (!system)
		system = Make00001B18();

	Coord3D position;
	system->getPosition(&position);

	FXList *eventFX = m_eventFX;
	if (eventFX != 0 && !eventFX->bfmeIsBlocked())
		eventFX->doFXPos(&position, 0, 0.0f, 0);

	bool deactivate = m_deactivate;
	m_active = false;
	if (deactivate)
	{
		ParticleSystem *finished;
		if (!m_system)
			finished = Make00001B18();
		else
			finished = m_system;
		finished->m_finished = 1;
	}
}
