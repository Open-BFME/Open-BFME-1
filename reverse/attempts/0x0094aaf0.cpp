// ??0LightEnvironmentClass@@QAE@XZ
// partial score=0.43 date=2026-09-06
// cl: /DNDEBUG /MD /EHsc

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/lightenvironment.h
// BFME diverged from the ZH member layout for LightEnvironmentClass; the extra 4 bytes
// between the (now byte-sized) light count and ObjectCenter, and the per-field zeroing
// of the InputLights/OutputLights arrays, are reconstructed from the retail disassembly
// (rva 0x0094AAF0).
struct Vector3Shim
{
	float X, Y, Z;
	void Set(float x, float y, float z) { X = x; Y = y; Z = z; }
};

struct InputLightStructShim
{
	Vector3Shim Direction;
	Vector3Shim Ambient;
	Vector3Shim Diffuse;
	bool DiffuseRejected;
	bool m_point;
	Vector3Shim m_center;
	float m_innerRadius;
	float m_outerRadius;
	Vector3Shim m_ambient;
	Vector3Shim m_diffuse;

	void Reset()
	{
		Direction.Set(0, 0, 0);
		Ambient.Set(0, 0, 0);
		Diffuse.Set(0, 0, 0);
		DiffuseRejected = false;
		m_point = false;
		m_center.Set(0, 0, 0);
		m_innerRadius = 0.0f;
		m_outerRadius = 0.0f;
		m_ambient.Set(0, 0, 0);
		m_diffuse.Set(0, 0, 0);
	}
};

struct OutputLightStructShim
{
	Vector3Shim Direction;
	Vector3Shim Diffuse;

	void Reset()
	{
		Direction.Set(0, 0, 0);
		Diffuse.Set(0, 0, 0);
	}
};

class LightEnvironmentClass
{
public:
	LightEnvironmentClass(void);
	~LightEnvironmentClass(void);

	enum { MAX_LIGHTS = 4 };

private:
	unsigned char LightCount;
	int _unknown4;
	Vector3Shim ObjectCenter;
	InputLightStructShim InputLights[MAX_LIGHTS];

	Vector3Shim OutputAmbient;
	OutputLightStructShim OutputLights[MAX_LIGHTS];

	InputLightStructShim FillLight;
	float FillIntensity;
};

LightEnvironmentClass::LightEnvironmentClass(void)
{
	LightCount = 0;
	_unknown4 = 0;
	ObjectCenter.Set(0, 0, 0);

	InputLightStructShim *p = InputLights;
	int n = MAX_LIGHTS;
	do {
		p->Reset();
		p++;
	} while (--n);

	OutputAmbient.Set(0, 0, 0);
	OutputLights[0].Reset();
	OutputLights[1].Reset();
	OutputLights[2].Reset();
	OutputLights[3].Reset();

	FillLight.Reset();
	FillIntensity = 0.0f;
}

LightEnvironmentClass::~LightEnvironmentClass(void)
{
}
