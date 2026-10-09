// The symbols.csv pin and matched WaterRenderObjClass::ReAcquireResources caller
// identify Gen_005D2040 as the return type.
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

int __cdecl Find_POT(int size);

typedef enum { WW3D_FORMAT_UNKNOWN = 0 } WW3DFormat;

struct D3DDISPLAYMODE { unsigned Width, Height, RefreshRate, Format; };
struct IDirect3DDevice8Vtbl
{
	void *reserved[8];
	long (__stdcall *GetDisplayMode)(void *self, unsigned swapChain, D3DDISPLAYMODE *mode);
};
struct IDirect3DDevice8 { IDirect3DDevice8Vtbl *lpVtbl; };

extern unsigned number_of_DX8_calls;

struct D3DCapsPrefix
{
	unsigned char reserved[0x58];
	unsigned int MaxTextureWidth;
	unsigned int MaxTextureHeight;
};

class DX8Caps
{
public:
	const D3DCapsPrefix &Get_DX8_Caps() const { return Caps; }

private:
	int MaxDisplayWidth;
	int MaxDisplayHeight;
	D3DCapsPrefix Caps;
	unsigned char m_layoutGap[0x13f];

public:
	unsigned char m_supportedRenderTargetFormat[100];
};

class TextureClass
{
public:
	void Release_Ref();
};

class TextureBaseClass
{
public:
	void Release_Ref();
};

class Rva006D6050
{
public:
	Rva006D6050() : m_texture(0) {}
	~Rva006D6050() { if (m_texture != 0) ((TextureBaseClass *)m_texture)->Release_Ref(); }
	void init(unsigned, unsigned, unsigned, unsigned, unsigned, unsigned);

private:
	TextureClass *m_texture;
};

class Gen_005D2040
{
public:
	Gen_005D2040(TextureClass *texture = 0) : m_texture(texture) {}
	Gen_005D2040(const Gen_005D2040 &other) : m_texture(other.m_texture)
	{
		if (m_texture != 0)
			++*reinterpret_cast<unsigned short *>(reinterpret_cast<char *>(m_texture) + 4);
	}
	~Gen_005D2040()
	{
		if (m_texture != 0)
			((TextureBaseClass *)m_texture)->Release_Ref();
	}

private:
	TextureClass *m_texture;
};

class DX8Wrapper
{
protected:
	static IDirect3DDevice8 *D3DDevice;
	static DX8Caps *CurrentCaps;

public:
	static Gen_005D2040 Create_Render_Target(int width, int height, WW3DFormat format);
};

Gen_005D2040 DX8Wrapper::Create_Render_Target(int width, int height, WW3DFormat format)
{
	++number_of_DX8_calls;

	if (format == WW3D_FORMAT_UNKNOWN)
	{
		D3DDISPLAYMODE mode;
		DX8Wrapper::D3DDevice->lpVtbl->GetDisplayMode(DX8Wrapper::D3DDevice, format, &mode);
		++number_of_DX8_calls;
		format = (WW3DFormat)mode.Format;
	}

	if (format < 0)
		goto unsupported;
	if (format >= 100)
		goto unsupported;
	if (!DX8Wrapper::CurrentCaps->m_supportedRenderTargetFormat[format])
		goto unsupported;
	goto supported;
unsupported:
	{
		return Gen_005D2040();
	}
supported:
	{
		const D3DCapsPrefix &caps = DX8Wrapper::CurrentCaps->Get_DX8_Caps();
		float poweroftwosize = (float)width;
		if (height > 0 && height < width)
			poweroftwosize = (float)height;
		int potInt = Find_POT((int)poweroftwosize);
		float potFloat = (float)potInt;
		if (potFloat > (float)caps.MaxTextureWidth)
			potFloat = (float)caps.MaxTextureWidth;
		if (potFloat > (float)caps.MaxTextureHeight)
			potFloat = (float)caps.MaxTextureHeight;
		width = height = (int)potFloat;

		Rva006D6050 tempHandle;
		tempHandle.init((unsigned)width, (unsigned)height, (unsigned)format, 1, 0, 1);
		return *reinterpret_cast<const Gen_005D2040 *>(&tempHandle);
	}
}
