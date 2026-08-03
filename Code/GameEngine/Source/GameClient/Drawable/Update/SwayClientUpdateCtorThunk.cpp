// cl: /DNDEBUG /MD /GX- /O2 /Ob2

// Open-BFME5: SwayClientUpdate ctor - ClientUpdateModule base then field inits.

class Thing;
class ModuleData;

class ClientUpdateModule
{
public:
	ClientUpdateModule(Thing *, const ModuleData *);
	virtual ~ClientUpdateModule();

private:
	unsigned char m_base[8];
};

class SwayClientUpdate : public ClientUpdateModule
{
public:
	SwayClientUpdate(Thing *thing, const ModuleData *moduleData);
	virtual ~SwayClientUpdate();
	virtual void clientUpdate(void);

private:
	float m_curValue;
	float m_curAngle;
	float m_curDelta;
	float m_curAngleLimit;
	float m_leanAngle;
	short m_curVersion;
	bool m_swaying;
	bool m_unused;
	unsigned int m_pad0;
	unsigned int m_pad1;
};

// ??0SwayClientUpdate@@QAE@PAVThing@@PBVModuleData@@@Z
SwayClientUpdate::SwayClientUpdate(Thing *thing, const ModuleData *moduleData)
	: ClientUpdateModule(thing, moduleData)
{
	m_curValue = 0;
	m_curAngle = 0;
	m_curDelta = 0;
	m_curAngleLimit = 0;
	m_leanAngle = 0;
	m_unused = false;
	m_pad0 = 0;
	m_pad1 = 0;
	m_curVersion = -1;
	m_swaying = true;
}
