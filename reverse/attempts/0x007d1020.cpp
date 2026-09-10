// ?set@ScreenBWFilter@@MAEHW4FilterModes@@@Z
// partial score=0.95 date=2026-09-07
// cl: /DNDEBUG /MD /EHsc
// Retail 0x007D1020, 1206 bytes.  Constructor 0x007D0CB0 installs
// vtable 0x0112898C; its named slots are ScreenBWFilter::init,
// preRender and postRender at 0x007D0AF0/0x007D0B70/0x007D0CE0.
// Slot 5 is the target, so this is the base BW filter's set method.  The
// neighbouring vtable 0x011289B0 belongs to ScreenBWFilterDOT3 and routes
// its slot 5 to the separate 0x007D1AA0 bank.

#include <string.h>
#include "d3dx8math.h"

typedef int Int;
typedef float Real;
typedef bool Bool;

struct TextureBaseClass;

// DX8Wrapper stores constants as WW3D2 Vector4 records, while the filter's
// source locals are D3DXVECTOR4 values with the same four-float layout.
class Vector4
{
public:
	float X;
	float Y;
	float Z;
	float W;
};



class StringClass
{
	char *m_Buffer;
	static char *m_EmptyString;
	static char m_NullChar;
	void Get_String(int, bool);
	void Free_String();

public:
	StringClass(int n = 0, bool temp = false) : m_Buffer(m_EmptyString)
	{
		Get_String(n, temp);
		m_Buffer[0] = m_NullChar;
	}
	~StringClass()
	{
		Free_String();
	}
};

class VertexMaterialClass
{
public:
	virtual void Delete_This();
	int refs;
	enum PresetType { PRELIT_DIFFUSE };
	static VertexMaterialClass *Get_Preset(PresetType);
	void Release_Ref()
	{
		if (!--refs)
			Delete_This();
	}
};

class TextureClass
{
public:
	void Release_Ref();
};

class TextureHandle
{
public:
	TextureClass *p;
	TextureHandle() : p(0) {}
	~TextureHandle()
	{
		if (p)
			p->Release_Ref();
	}
};

void BoxSetTexture(unsigned int, TextureBaseClass *&);

struct BfmeDevice;
struct BfmeDeviceVtable
{
	void *reserved000[57];
	long (__stdcall *SetRenderState)(BfmeDevice *, unsigned long,
		unsigned int);
	void *reserved0e8[49];
	long (__stdcall *SetPixelShader)(BfmeDevice *, unsigned int);
	void *reserved1ac[1];
	long (__stdcall *SetPixelShaderConstant)(BfmeDevice *, unsigned int,
		const void *, unsigned int);
};

struct BfmeDevice
{
	BfmeDeviceVtable *v;
};

extern VertexMaterialClass *ScreenMaterial;
extern unsigned int TheBoxTextureDirtyMask;
extern bool ScreenShaderDirty;
extern unsigned int ScreenOpaqueShader;
extern unsigned int ScreenCurrentShader;
extern bool ScreenSnapshot;
extern unsigned int ScreenRenderStates[];
extern BfmeDevice *ScreenDevice;
extern unsigned int ScreenStateChanges;
extern unsigned int ScreenTotalChanges;
extern unsigned int number_of_DX8_calls;

class DX8Wrapper
{
public:
	static void Apply_Render_State_Changes();
	static void Get_DX8_Render_State_Value_Name(StringClass &,
		unsigned long, unsigned int);
	static BfmeDevice *_Get_D3D_Device8()
	{
		return D3DDevice;
	}

	static __forceinline void Set_DX8_Render_State(unsigned long state,
		unsigned int value)
	{
		if (ScreenRenderStates[state] == value)
			return;
		if (ScreenSnapshot)
		{
			StringClass s(0, true);
			Get_DX8_Render_State_Value_Name(s, state, value);
		}
		ScreenRenderStates[state] = value;
		ScreenDevice->v->SetRenderState(ScreenDevice, state, value);
		++ScreenTotalChanges;
		++ScreenStateChanges;
	}

	static __forceinline void Set_Pixel_Shader_Constant(int reg,
		const void *data, int count)
	{
		int memsize = sizeof(Vector4) * count;
		if (memcmp(data, &Pixel_Shader_Constants[reg], memsize) == 0)
			return;
		memcpy(&Pixel_Shader_Constants[reg], data, memsize);
		_Get_D3D_Device8()->v->SetPixelShaderConstant(
			_Get_D3D_Device8(), reg, data, count);
		++number_of_DX8_calls;
	}

private:
	static BfmeDevice *D3DDevice;
	static Vector4 Pixel_Shader_Constants[8];
};

class FadeView
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual void slot14() = 0;
	virtual void slot15() = 0;
	virtual void slot16() = 0;
	virtual void slot17() = 0;
	virtual void slot18() = 0;
	virtual void slot19() = 0;
	virtual void slot20() = 0;
	virtual void slot21() = 0;
	virtual void slot22() = 0;
	virtual void slot23() = 0;
	virtual void slot24() = 0;
	virtual void slot25() = 0;
	virtual void slot26() = 0;
	virtual void slot27() = 0;
	virtual void slot28() = 0;
	virtual void slot29() = 0;
	virtual void slot30() = 0;
	virtual void slot31() = 0;
	virtual void slot32() = 0;
	virtual void slot33() = 0;
	virtual void slot34() = 0;
	virtual void slot35() = 0;
	virtual void slot36() = 0;
	virtual void slot37() = 0;
	virtual void slot38() = 0;
	virtual void slot39() = 0;
	virtual void slot40() = 0;
	virtual void slot41() = 0;
	virtual void slot42() = 0;
	virtual void slot43() = 0;
	virtual void setMode(int) = 0;
	virtual void slot45() = 0;
	virtual void setFilter(int) = 0;
};

extern FadeView *TheTacticalView;

enum FilterModes
{
	FM_NULL_MODE = 0,
	FM_VIEW_BW_BLACK_AND_WHITE = 1,
	FM_VIEW_BW_RED_AND_WHITE = 2,
	FM_VIEW_BW_GREEN_AND_WHITE = 3
};

struct Coord2D
{
	Real x;
	Real y;
};

class ScreenBWFilter
{
	unsigned int m_dwBWPixelShader;

public:
	virtual Int init();
	virtual Int shutdown();
	virtual Bool preRender(Bool &, Int &);
	virtual Bool postRender(FilterModes, Coord2D &, Bool &, Coord2D *);
	virtual Bool setup(FilterModes);
	static void setFadeParameters(Int, Int);

protected:
	virtual Int set(FilterModes);
	virtual void reset();
	static Int m_fadeFrames;
	static Int m_fadeDirection;
	static Int m_curFadeFrame;
	static Real m_curFadeValue;
};

Int ScreenBWFilter::set(FilterModes mode)
{
	if (mode > FM_NULL_MODE)
	{
		if (m_fadeDirection > 0)
		{
			m_curFadeFrame++;
			Int fade = m_curFadeFrame;
			if (fade < m_fadeFrames)
			{
				m_curFadeValue = (Real)fade / (Real)m_fadeFrames;
			}
			else
			{
				m_curFadeFrame = 0;
				m_curFadeValue = 1.0f;
				m_fadeDirection = 0;
			}
		}
		else if (m_fadeDirection < 0)
		{
			m_curFadeFrame++;
			Int fade = m_curFadeFrame;
			if (fade < m_fadeFrames)
			{
				m_curFadeValue = 1.0f - (Real)fade / (Real)m_fadeFrames;
			}
			else
			{
				m_curFadeValue = 0.0f;
				TheTacticalView->setMode(FM_NULL_MODE);
				TheTacticalView->setFilter(0);
				m_curFadeFrame = 0;
				m_fadeDirection = 0;
			}
		}

		VertexMaterialClass *vmat =
			VertexMaterialClass::Get_Preset(VertexMaterialClass::PRELIT_DIFFUSE);
		if (vmat)
			++vmat->refs;
		if (ScreenMaterial)
			ScreenMaterial->Release_Ref();
		ScreenMaterial = vmat;
		TheBoxTextureDirtyMask |= 0x4000;
		if (vmat)
			vmat->Release_Ref();

		if (ScreenShaderDirty || ScreenOpaqueShader != ScreenCurrentShader)
		{
			ScreenCurrentShader = ScreenOpaqueShader;
			TheBoxTextureDirtyMask |= 0x8000;
			StringClass s;
		}
		{
			TextureHandle tex;
			BoxSetTexture(0, (TextureBaseClass *&)tex.p);
		}

		DX8Wrapper::Apply_Render_State_Changes();
		DX8Wrapper::Set_DX8_Render_State(23, 8);
		DX8Wrapper::Set_DX8_Render_State(14, 0);
		DX8Wrapper::Apply_Render_State_Changes();

		DX8Wrapper::_Get_D3D_Device8()->v->SetPixelShader(
			DX8Wrapper::_Get_D3D_Device8(), m_dwBWPixelShader);

		D3DXVECTOR4 c0(0.3f, 0.59f, 0.11f, 1.0f);
		DX8Wrapper::Set_Pixel_Shader_Constant(0, &c0, 1);

		D3DXVECTOR4 color(1.0f, 1.0f, 1.0f, 1.0f);
		if (mode == FM_VIEW_BW_BLACK_AND_WHITE)
		{
			color.x = 1.0f;
			color.y = 1.0f;
			color.z = 1.0f;
		}
		if (mode == FM_VIEW_BW_RED_AND_WHITE)
		{
			color.x = 1.0f;
			color.y = 0.0f;
			color.z = 0.0f;
		}
		if (mode == FM_VIEW_BW_GREEN_AND_WHITE)
		{
			color.x = 0.0f;
			color.y = 1.0f;
			color.z = 0.0f;
		}

		DX8Wrapper::Set_Pixel_Shader_Constant(1, &color, 1);
		D3DXVECTOR4 c2(m_curFadeValue, m_curFadeValue,
			m_curFadeValue, 1.0f);
		DX8Wrapper::Set_Pixel_Shader_Constant(2, &c2, 1);
		return true;
	}
	return false;
}
