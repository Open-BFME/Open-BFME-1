// cl: /DNDEBUG /MD /EHsc /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWLib

#include "vector3.h"

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/light.h
class LightClass
{
public:
	virtual void On_Frame_Update();

protected:
	unsigned char m_padding04[0xD4];
	Vector3 Ambient;
	Vector3 Diffuse;
	Vector3 Specular;
	float NearAttenStart;
	float NearAttenEnd;
	float FarAttenStart;
	float FarAttenEnd;
	float SpotAngle;
	float SpotAngleCos;
	float SpotExponent;
	Vector3 SpotDirection;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/W3DDynamicLight.h
class W3DDynamicLight : public LightClass
{
public:
	virtual void On_Frame_Update();

private:
	bool m_priorEnable;
	bool m_processMe;
	unsigned char m_padding126[2];
	int m_prevMinX;
	int m_prevMinY;
	int m_prevMaxX;
	int m_prevMaxY;
	int m_minX;
	int m_minY;
	int m_maxX;
	int m_maxY;
	bool m_enabled;
	bool m_decayRange;
	bool m_decayColor;
	unsigned char m_padding14B;
	unsigned int m_curDecayFrameCount;
	unsigned int m_curIncreaseFrameCount;
	unsigned int m_decayFrameCount;
	unsigned int m_increaseFrameCount;
	float m_targetRange;
	Vector3 m_targetAmbient;
	Vector3 m_targetDiffuse;
};

void W3DDynamicLight::On_Frame_Update()
{
	if (!m_enabled) {
		return;
	}

	float scale;
	if (m_curIncreaseFrameCount > 0 && m_increaseFrameCount > 0) {
		--m_curIncreaseFrameCount;
		scale = static_cast<float>(m_increaseFrameCount - m_curIncreaseFrameCount)
			/ static_cast<float>(m_increaseFrameCount);
	} else if (m_decayFrameCount == 0) {
		scale = 1.0f;
	} else {
		--m_curDecayFrameCount;
		if (m_curDecayFrameCount == 0) {
			m_enabled = false;
			return;
		}
		scale = static_cast<float>(m_curDecayFrameCount)
			/ static_cast<float>(m_decayFrameCount);
	}

	if (m_decayRange) {
		FarAttenEnd = scale * m_targetRange;
		if (FarAttenEnd < FarAttenStart) {
			FarAttenEnd = FarAttenStart;
		}
	}

	if (m_decayColor) {
		Ambient = m_targetAmbient * scale;
		Diffuse = m_targetDiffuse * scale;
	}
}
