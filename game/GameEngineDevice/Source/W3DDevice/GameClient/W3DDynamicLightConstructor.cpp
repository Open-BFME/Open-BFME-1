// cl: /DNDEBUG /MD /EHsc
//
// W3DDynamicLight::W3DDynamicLight, retail 0x006F5C50.
// The ABI slice has RenderObjClass's two vptr words at this+0 and this+0x08;
// the LightClass subobject ends at this+0x124.  They are represented as
// ordinary words here so the constructor can reproduce the retail's explicit
// vptr stores without inventing a local vtable.
// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/light.h
class LightClass
{
public:
	enum LightType { POINT = 0 };
	LightClass(LightType type);

	volatile unsigned int m_vptr;
	unsigned char m_pad04[4];
	volatile unsigned int m_vptr2;
	unsigned char m_pad0c[0x118];
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/W3DDynamicLight.h
class W3DDynamicLight : public LightClass
{
public:
	W3DDynamicLight();

private:
	volatile bool m_priorEnable;
	bool m_processMe;
	unsigned char m_pad126[2];
	volatile int m_prevMinX;
	volatile int m_prevMinY;
	volatile int m_prevMaxX;
	volatile int m_prevMaxY;
	volatile int m_minX;
	volatile int m_minY;
	volatile int m_maxX;
	volatile int m_maxY;
	volatile bool m_enabled;
	volatile bool m_decayRange;
	volatile bool m_decayColor;
	unsigned char m_pad14b;
	volatile unsigned int m_curDecayFrameCount;
	volatile unsigned int m_curIncreaseFrameCount;
	volatile unsigned int m_decayFrameCount;
	volatile unsigned int m_increaseFrameCount;
	volatile float m_targetRange;
	volatile float m_targetAmbient[3];
	volatile float m_targetDiffuse[3];
};

extern "C" const void *bfmeVftRva006F5BE0MultiTailDtorRva0093BE00MultiBase[];
#pragma comment(linker, "/alternatename:_bfmeVftRva006F5BE0MultiTailDtorRva0093BE00MultiBase=??_7Rva006F5BE0MultiTailDtor@@6BRva0093BE00MultiBase@@@")
extern "C" const void *bfmeVftRva006F5BE0MultiTailDtorTailMixinA[];
#pragma comment(linker, "/alternatename:_bfmeVftRva006F5BE0MultiTailDtorTailMixinA=??_7Rva006F5BE0MultiTailDtor@@6BTailMixinA@@@")

// ??0W3DDynamicLight@@QAE@XZ
W3DDynamicLight::W3DDynamicLight() :
	LightClass(POINT)
{
	m_vptr = (unsigned int)bfmeVftRva006F5BE0MultiTailDtorRva0093BE00MultiBase;
	m_vptr2 = (unsigned int)bfmeVftRva006F5BE0MultiTailDtorTailMixinA;
	m_targetAmbient[0] = 0.0f;
	m_targetAmbient[1] = 0.0f;
	m_targetAmbient[2] = 0.0f;
	m_targetDiffuse[0] = 0.0f;
	m_targetDiffuse[1] = 0.0f;
	m_targetDiffuse[2] = 0.0f;
	m_priorEnable = false;
	m_prevMinX = 0;
	m_prevMinY = 0;
	m_prevMaxX = 0;
	m_prevMaxY = 0;
	m_minX = 0;
	m_minY = 0;
	m_maxX = 0;
	m_maxY = 0;
	m_decayRange = false;
	m_decayColor = false;
	m_curDecayFrameCount = 0;
	m_curIncreaseFrameCount = 0;
	m_decayFrameCount = 0;
	m_increaseFrameCount = 0;
	m_targetRange = 0.0f;
	m_enabled = true;
}
