// cl: /DNDEBUG /MD /EHsc /O2 /Ob2 /Igame/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug
#include "shader.h"
//
// Open-BFME5: the default-material initialiser at retail 0x009569A0,
// 205 bytes.  Allocates a VertexMaterialClass, sets its six colour and
// lighting properties, copies one global into another and raises the ready
// flag.  The pointer is reloaded from the global before each call because the
// callees are external.

class VertexMaterialClass
{
public:
	VertexMaterialClass(void);

	void Set_Ambient(float red, float green, float blue);
	void Set_Diffuse(float red, float green, float blue);
	void Set_Specular(float red, float green, float blue);
	void Set_Emissive(float red, float green, float blue);
	void Set_Shininess(float value);
	void Set_Opacity(float value);

private:
	char m_bfmeRaw[0x6C];
};

VertexMaterialClass *_BoxMaterial = 0;			// retail 0x0134B210
extern int g_bfmeTargetXP;					// retail 0x012D7300
extern bool g_bfmeReadyXP;					// retail 0x0134B208

// ?bfmeInitMaterialXP@@YAXXZ
void bfmeInitMaterialXP(void)
{
	_BoxMaterial = new VertexMaterialClass;

	_BoxMaterial->Set_Ambient(0.0f, 0.0f, 0.0f);
	_BoxMaterial->Set_Diffuse(0.0f, 0.0f, 0.0f);
	_BoxMaterial->Set_Specular(0.0f, 0.0f, 0.0f);
	_BoxMaterial->Set_Emissive(1.0f, 1.0f, 1.0f);
	_BoxMaterial->Set_Opacity(1.0f);
	_BoxMaterial->Set_Shininess(0.0f);

	g_bfmeTargetXP = ShaderClass::_PresetAlphaSolidShader.Get_Bits();

	g_bfmeReadyXP = true;
}
