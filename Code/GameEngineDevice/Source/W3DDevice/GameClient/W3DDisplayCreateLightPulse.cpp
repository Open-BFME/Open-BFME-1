// ?createLightPulse@W3DDisplay@@UAEXPAVCoord3D@@HHW4RGBColor@@M@Z

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

class W3DDisplay
{
public:
	virtual void createLightPulse(const Coord3D *position, const RGBColor *color,
		float innerRadius, float attenuationWidth, unsigned int increaseTime,
		unsigned int decayTime);
};

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
