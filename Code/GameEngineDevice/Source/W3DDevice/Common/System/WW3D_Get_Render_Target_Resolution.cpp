// cl: /DNDEBUG /MD /EHsc
// readable body of ?Get_Render_Target_Resolution@WW3D@@: Code/Libraries/Source/WWVegas/WW3D2/ww3d.cpp

// Retail 0x00906990, 195 bytes. An SEH frame with the 0/-1 unwind pair around
// the device branch, which is a guard object: the same lock and unlock pair
// HeightMapRenderObjClass::freeMapResources calls bare, only here it has to
// survive a throw, so it is scoped rather than called.
//
// Frame arithmetic pins the locals. After the four-word SEH prologue the frame
// takes 0x24 more, and the arguments start at esp+0x34 with the unwind slot at
// esp+0x2C. The struct handed to the device is at esp+4, so the guard sits in
// the four bytes below it -- an empty object, one byte rounded up -- and the
// struct is the remaining 0x20. Its two interesting words are at +0x18 and
// +0x1C.
//
// The device call pushes its argument and then the interface pointer before
// going through the vtable, which is the __stdcall virtual convention, not
// the thiscall one. Slot 0x30 is the twelfth.
//
// Both exits write the same bit depth and the same windowed flag out of
// globals; only the width and height differ between having a device and not.
// Every global here rides a DIR32 relocation copied from retail.

typedef int Int;
typedef bool Bool;

void W3DRadarResetLock(void);						// retail 0x00903090
void W3DRadarResetUnlock(void);						// retail 0x00905B10

class BfmeRadarResetGuard
{
public:
	BfmeRadarResetGuard() { W3DRadarResetLock(); }
	~BfmeRadarResetGuard() { W3DRadarResetUnlock(); }
};

struct BfmeDisplayModeInfo
{
	char m_bfmeHead[0x18];
	Int m_bfmeWidth;						// +0x18
	Int m_bfmeHeight;						// +0x1C
};

class BfmeRenderDevice
{
public:
	virtual long __stdcall bfmeSlot00(void) = 0;
	virtual long __stdcall bfmeSlot04(void) = 0;
	virtual long __stdcall bfmeSlot08(void) = 0;
	virtual long __stdcall bfmeSlot0C(void) = 0;
	virtual long __stdcall bfmeSlot10(void) = 0;
	virtual long __stdcall bfmeSlot14(void) = 0;
	virtual long __stdcall bfmeSlot18(void) = 0;
	virtual long __stdcall bfmeSlot1C(void) = 0;
	virtual long __stdcall bfmeSlot20(void) = 0;
	virtual long __stdcall bfmeSlot24(void) = 0;
	virtual long __stdcall bfmeSlot28(void) = 0;
	virtual long __stdcall bfmeSlot2C(void) = 0;
	virtual long __stdcall bfmeGetModeInfo(BfmeDisplayModeInfo *info) = 0;	// +0x30
};

extern BfmeRenderDevice *TheBfmeRenderDevice;				// 0x01340538

extern Int BfmeRenderWidth;						// 0x012D6DB4
extern Int BfmeRenderHeight;						// 0x012D6DB8
extern Int BfmeRenderBitDepth;						// 0x012D6DBC
extern Bool BfmeRenderWindowed;						// 0x0134050D

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/ww3d.h
class WW3D
{
public:
	static void Get_Render_Target_Resolution(Int &width, Int &height, Int &bitDepth, Bool &windowed);
};

// ?Get_Render_Target_Resolution@WW3D@@SAXAAH00AA_N@Z
void WW3D::Get_Render_Target_Resolution(Int &width, Int &height, Int &bitDepth, Bool &windowed)
{
	if (TheBfmeRenderDevice)
	{
		BfmeRadarResetGuard guard;
		BfmeDisplayModeInfo info;

		TheBfmeRenderDevice->bfmeGetModeInfo(&info);

		width = info.m_bfmeWidth;
		height = info.m_bfmeHeight;
		bitDepth = BfmeRenderBitDepth;
		windowed = BfmeRenderWindowed;
	}
	else
	{
		width = BfmeRenderWidth;
		height = BfmeRenderHeight;
		bitDepth = BfmeRenderBitDepth;
		windowed = BfmeRenderWindowed;
	}
}
