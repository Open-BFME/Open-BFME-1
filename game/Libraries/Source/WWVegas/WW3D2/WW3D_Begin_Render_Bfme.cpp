// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main

// Clean BFME body for WW3D::Begin_Render at retail RVA 0x008FE280.
// The BFME flags use byte globals and the status result is returned through AL.

typedef unsigned int UnsignedInt;

class Vector3
{
	float X;
	float Y;
	float Z;
};

struct _D3DVIEWPORT8
{
	UnsignedInt X;
	UnsignedInt Y;
	UnsignedInt Width;
	UnsignedInt Height;
	float MinZ;
	float MaxZ;
};

extern int Rva00AFE950Get(void);
extern int Rva00AFE960Get(void);
extern void Rva00AFE940(void);

class BfmeD3DDevice
{
public:
	virtual long __stdcall slot00(void);
	virtual long __stdcall slot04(void);
	virtual long __stdcall slot08(void);
	virtual long __stdcall TestCooperativeLevel(void);
};

class DX8Wrapper
{
public:
	static bool Reset_Device(bool force);
	static void Set_Viewport(const _D3DVIEWPORT8 *viewport);
	static void Clear(bool clear_color, bool clear_z_stencil,
		bool clear_stencil, const Vector3 &color, float dest_alpha,
		float z, UnsignedInt stencil);
	static void Begin_Scene_Inner(void);
};

class DynamicVBAccessClass
{
public:
	static void _Reset(bool);
};

class DynamicIBAccessClass
{
public:
	static void _Reset(bool);
};

class Gen_00944c50
{
public:
	void __cdecl m(void);
};

namespace Debug_Statistics
{
	void Begin_Statistics(void);
}

class WW3D
{
public:
	static void Get_Render_Target_Resolution(int &, int &, int &, bool &);
	static void Update_Movie_Capture(void);
	static bool Begin_Render(bool, bool, const Vector3 &, float, void (*)(void));
};

bool WW3D::Begin_Render(bool clear, bool clearz, const Vector3 &color,
	float dest_alpha, void (*network_callback)(void))
{

	if (!*(unsigned char *)0x0133F428)
		return true;

	if (*(unsigned char *)0x0133F429)
		return false;

	{
		BfmeD3DDevice *device = *(BfmeD3DDevice **)0x01340534;
		if (device)
		{
			long hr = device->TestCooperativeLevel();
			if (hr != 0)
			{
				if (hr == 0x88760868)
					return false;
				if (hr != 0x88760869)
					return false;
				DX8Wrapper::Reset_Device(true);
				return false;
			}
		}
	}

	*(int *)0x0133F41C = Rva00AFE950Get();
	*(int *)0x0133F414 = Rva00AFE960Get();
	Rva00AFE940();
	DynamicVBAccessClass::_Reset(true);
	DynamicIBAccessClass::_Reset(true);
	((Gen_00944c50 *)1)->m();
	Debug_Statistics::Begin_Statistics();

	if (*(unsigned char *)0x0133F42A &&
		(!*(unsigned char *)0x0133F418 || *(unsigned char *)0x0133F410))
	{
		WW3D::Update_Movie_Capture();
		*(unsigned char *)0x0133F410 = 0;
	}

	if (clear)
	{
		*(unsigned char *)0x0133F429 = 1;
		goto clear_viewport;
	}
	*(unsigned char *)0x0133F429 = 1;
	if (clearz)
		goto clear_viewport;
	goto begin_scene;

clear_viewport:
	{
		_D3DVIEWPORT8 vp;
		int width, height, bits;
		bool windowed;
		WW3D::Get_Render_Target_Resolution(width, height, bits, windowed);
		vp.X = 0;
		vp.Y = 0;
		vp.Width = width;
		vp.Height = height;
		vp.MinZ = 0.0f;
		vp.MaxZ = 1.0f;
		DX8Wrapper::Set_Viewport(&vp);
		DX8Wrapper::Clear(clear, clearz, clearz, color, dest_alpha, 1.0f, 0);
	}

begin_scene:
	DX8Wrapper::Begin_Scene_Inner();
	return true;
}
