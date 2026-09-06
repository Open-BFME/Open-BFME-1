// cl: /DNDEBUG /MD /EHsc
// readable body of ?createLightPulse@W3DDisplay@@UAEXPBUCoord3D@@PBURGBColor@@MMII@Z: Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DDisplay.cpp
// readable body of ?createVideoBuffer@W3DDisplay@@UAEPAVVideoBuffer@@_N@Z: Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DDisplay.cpp
//
// The two W3DDisplay overrides that hand back something newly made: a dynamic
// light taken from the scene's pool, and a video buffer in the best pixel
// format the device will accept. Neither reads a W3DDisplay field, which is why
// they can share a translation unit -- the object they are members of is stated
// here as the two slots and nothing else, and the two files this replaces each
// carried their own copy of exactly that.
//
// createLightPulse's own mangled name is the second line the old file carried:
// ?createLightPulse@W3DDisplay@@UAEXPAVCoord3D@@HHW4RGBColor@@M@Z is the Zero
// Hour signature, and the ledger's PBUCoord3D@@PBURGBColor@@MMII is BFME's.

struct Vector3
{
	float x, y, z;
	Vector3(float x_, float y_, float z_) : x(x_), y(y_), z(z_) {}
	Vector3(const Vector3 &other) : x(other.x), y(other.y), z(other.z) {}
	Vector3 &operator=(const Vector3 &other)
	{
		x = other.x;
		y = other.y;
		z = other.z;
		return *this;
	}
};

struct Coord3D { float x, y, z; };
struct RGBColor { float red, green, blue; };

class W3DDynamicLightPulseShim
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
	virtual void slot16(); virtual void slot17(); virtual void slot18(); virtual void slot19();
	virtual void slot20(); virtual void slot21();
	virtual void Set_Position(const Vector3 &position);

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
	void Set_Far_Attenuation_Range(float first, float last)
	{
		m_farAttenStart = first;
		m_farAttenEnd = last;
	}
	void setFrameFade(unsigned int increase, unsigned int decay);
	void setDecayRange() { m_decayRange = true; }
	void setDecayColor() { m_decayColor = true; }

private:
	unsigned char m_pad04[0xd4];
	Vector3 m_ambient;
	Vector3 m_diffuse;
	unsigned char m_padF0[0x14];
	float m_farAttenStart;
	float m_farAttenEnd;
	unsigned char m_pad10C[0x3c];
	volatile bool m_enabled;
	volatile bool m_decayRange;
	volatile bool m_decayColor;
	unsigned char m_pad14B[9];
	volatile unsigned int m_decayFrameCount;
	volatile unsigned int m_increaseFrameCount;
};

class RTS3DSceneLightPulseShim
{
public:
	W3DDynamicLightPulseShim *getADynamicLight();
};

extern RTS3DSceneLightPulseShim *g_lightPulseScene;

void __cdecl W3DRadarResetLock(void);
char __cdecl bfmeUnlock1179(void);

class W3DRadarResetGuard
{
public:
	W3DRadarResetGuard(void)
	{
		W3DRadarResetLock();
	}

	~W3DRadarResetGuard(void)
	{
		bfmeUnlock1179();
	}
};

enum WW3DFormat
{
	WW3D_FORMAT_UNKNOWN = 0
};

class W3DRadarFormatCaps
{
public:
	bool supportTextureFormat(WW3DFormat format);
};

extern W3DRadarFormatCaps *TheW3DRadarFormatCaps;

int Rva00903060Get(void);
int Rva00739D20(int format, bool allowAlpha);

class VideoBuffer
{
};

class W3DVideoBuffer : public VideoBuffer
{
public:
	W3DVideoBuffer(int format);

private:
	unsigned char m_pad[0x4C];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/W3DDisplay.h
class W3DDisplay
{
public:
	virtual void createLightPulse(const Coord3D *position, const RGBColor *color,
		float innerRadius, float attenuationWidth, unsigned int increaseTime,
		unsigned int decayTime);
	virtual VideoBuffer *createVideoBuffer(bool allowAlpha);
};

// ?createLightPulse@W3DDisplay@@UAEXPBUCoord3D@@PBURGBColor@@MMII@Z
void W3DDisplay::createLightPulse(const Coord3D *position, const RGBColor *color,
	float innerRadius, float attenuationWidth, unsigned int increaseTime,
	unsigned int decayTime)
{
	if (innerRadius + attenuationWidth < 21.0f)
		return;
	W3DDynamicLightPulseShim *light = g_lightPulseScene->getADynamicLight();
	light->setEnabled(true);
	light->Set_Ambient(Vector3(color->red, color->green, color->blue));
	light->Set_Diffuse(Vector3(color->red, color->green, color->blue));
	light->Set_Position(Vector3(position->x, position->y, position->z));
	light->Set_Far_Attenuation_Range(innerRadius, innerRadius + attenuationWidth);
	light->setFrameFade(increaseTime, decayTime);
	light->setDecayRange();
	light->setDecayColor();
}

// ?createVideoBuffer@W3DDisplay@@UAEPAVVideoBuffer@@_N@Z
VideoBuffer *W3DDisplay::createVideoBuffer(bool allowAlpha)
{
	W3DRadarResetGuard lock;
	int format = 0;

	if (allowAlpha && TheW3DRadarFormatCaps->supportTextureFormat((WW3DFormat)0x15))
		format = 5;
	else
	{
		int native = Rva00903060Get();
		if (TheW3DRadarFormatCaps->supportTextureFormat((WW3DFormat)native))
			format = Rva00739D20(native, allowAlpha);
		if (format == 0)
		{
			if (TheW3DRadarFormatCaps->supportTextureFormat((WW3DFormat)0x16))
				format = 2;
			else if (TheW3DRadarFormatCaps->supportTextureFormat((WW3DFormat)0x14))
				format = 1;
			else if (TheW3DRadarFormatCaps->supportTextureFormat((WW3DFormat)0x17))
				format = 3;
			else if (TheW3DRadarFormatCaps->supportTextureFormat((WW3DFormat)0x18))
				format = 4;
			else
				return 0;
		}
	}

	return new W3DVideoBuffer(format);
}
