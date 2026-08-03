// cl: /DNDEBUG /MD /EHsc

class Thing;
class ModuleData;

class DrawableModule
{
public:
	virtual ~DrawableModule();
	DrawableModule(Thing *, const ModuleData *);

private:
	unsigned char m_data[8];
};

class ClientUpdateModule : public DrawableModule
{
public:
	ClientUpdateModule(Thing *thing, const ModuleData *moduleData)
		: DrawableModule(thing, moduleData)
	{
	}
};

class SwayClientUpdate : public ClientUpdateModule
{
public:
	SwayClientUpdate(Thing *thing, const ModuleData *moduleData);
	virtual void clientUpdate();

private:
	float m_curValue;
	float m_curAngle;
	float m_curDelta;
	float m_curAngleLimit;
	float m_leanAngle;
	short m_curVersion;
	unsigned char m_swaying;
	unsigned char m_unused;
	unsigned int m_extra0;
	unsigned int m_extra1;
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
	m_unused = 0;
	m_extra0 = 0;
	m_extra1 = 0;
	m_curVersion = -1;
	m_swaying = 1;
}
