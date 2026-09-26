// cl: /DNDEBUG /MD /EHsc

// W3DLightDraw's constructor, retail 0x007583A0.

class Thing;
class ModuleData;
class Drawable;

class DrawModule
{
public:
	DrawModule(Thing *, const ModuleData *);
	virtual ~DrawModule();
	virtual void drawModuleAnchor();

protected:
	const ModuleData *m_moduleData;
	Drawable *m_drawable;
};

class Vector3
{
public:
	float X;
	float Y;
	float Z;

	Vector3(void) { }
	Vector3(const Vector3 &value) { X = value.X; Y = value.Y; Z = value.Z; }
	Vector3(float x, float y, float z) { X = x; Y = y; Z = z; }
	Vector3 &operator=(const Vector3 &value)
	{
		X = value.X;
		Y = value.Y;
		Z = value.Z;
		return *this;
	}
};

class W3DDynamicLightPulseShim
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02();
	virtual void slot03(); virtual void slot04(); virtual void slot05();
	virtual void slot06(); virtual void slot07(); virtual void slot08();
	virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14();
	virtual void slot15(); virtual void slot16(); virtual void slot17();
	virtual void slot18(); virtual void slot19(); virtual void slot20();
	virtual void slot21();
	virtual void Set_Position(const Vector3 &position);

	void Add_Ref(void) { ++m_refCount; }

	void setEnabled(bool enabled)
	{
		m_enabled = enabled;
		m_decayRange = false;
		m_decayFrameCount = 0;
		m_decayColor = false;
		m_increaseFrameCount = 0;
	}

	void Set_Ambient(const Vector3 &color) { m_ambient = color; }
	void Set_Diffuse(const Vector3 &color) { m_diffuse = color; }
	void Set_Far_Attenuation_Range(double start, double end)
	{
		m_farAttenStart = (float)start;
		m_farAttenEnd = (float)end;
	}
	void setFrameFade(unsigned int increase, unsigned int decay);
	void setFarAttenuationEnabled(void)
	{
		*(unsigned int *)((char *)this + 0xcc) |= 1;
	}

private:
	unsigned int m_refCount;
	char m_lightPrefix[0xc4];
	unsigned int m_flags;
	char m_lightSuffix[8];
	Vector3 m_ambient;
	Vector3 m_diffuse;
	char m_specularAndNearSlice[0x14];
	float m_farAttenStart;
	float m_farAttenEnd;
	char m_spotAndCounterSlice[0x3c];
	bool m_enabled;
	bool m_decayRange;
	bool m_decayColor;
	char m_curFrameCountSlice[9];
	unsigned int m_decayFrameCount;
	unsigned int m_increaseFrameCount;
};

class W3DDynamicLight : public W3DDynamicLightPulseShim
{
};

class RTS3DScene
{
public:
	W3DDynamicLight *getADynamicLight(void);
};

class W3DDisplay
{
public:
	static RTS3DScene *m_3DScene;
};

class WWMath
{
public:
	static float Random_Float(void);
};

class W3DLightDrawModuleData
{
public:
	virtual void moduleDataAnchor();

	char m_base[4];
	float m_ambientX;
	float m_ambientY;
	float m_ambientZ;
	float m_diffuseX;
	float m_diffuseY;
	float m_diffuseZ;
	char m_unused20[0xc];
	float m_farAttenEnd;
};

class W3DLightDraw : public DrawModule
{
public:
	W3DLightDraw(Thing *, const ModuleData *);
	virtual ~W3DLightDraw();

private:
	W3DDynamicLight *m_light;
	float m_phase;
	float m_radius;
	float m_angle;
	float m_height;
};

// ??0W3DLightDraw@@QAE@PAVThing@@PBVModuleData@@@Z
W3DLightDraw::W3DLightDraw(Thing *thing, const ModuleData *moduleData)
	: DrawModule(thing, moduleData)
{
	m_radius = 0.0f;
	m_angle = 0.0f;
	m_height = 0.0f;
	m_phase = WWMath::Random_Float() * (*(const float *)0x0108615c);
	m_light = W3DDisplay::m_3DScene->getADynamicLight();
	if (m_light)
	{
		m_light->Add_Ref();
		const W3DLightDrawModuleData *data =
			(const W3DLightDrawModuleData *)moduleData;
		m_light->setEnabled(true);
		m_light->Set_Ambient(Vector3(data->m_ambientX, data->m_ambientY, data->m_ambientZ));
		m_light->Set_Diffuse(Vector3(data->m_diffuseX, data->m_diffuseY, data->m_diffuseZ));
		m_light->Set_Position(Vector3(0.0f, 0.0f, 0.0f));
		m_light->setFrameFade(0, 0);
		m_light->Set_Far_Attenuation_Range(1.0f, data->m_farAttenEnd);
		m_light->setFarAttenuationEnabled();
	}
}
