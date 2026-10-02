// cl: /Igame/Libraries/Source/WWVegas/WW3D2 /DNDEBUG /DWIN32 /D_WINDOWS /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /DNDEBUG /DWIN32 /MD /EHsc
#include "dx8wrapper.h"


// W3DShadowHelperManager::ReAcquireResources, retail 0x007B9810.
// The constructor at 0x007C10D0 zeros seven fields in the 0x1c-byte object
// allocated at 0x01306F18. The W3DShadowManager constructor calls that
// constructor for its first manager, and its ReAcquireResources wrapper calls
// this body through the same global.

typedef long HRESULT;
typedef bool Bool;

#define TRUE true
#define FALSE false

void W3DRadarResetLock(void);
void W3DRadarResetUnlock(void);

class BfmeRadarResetLock
{
public:
	BfmeRadarResetLock(void) { W3DRadarResetLock(); }
	~BfmeRadarResetLock(void) { W3DRadarResetUnlock(); }
};

class GenAlpha
{
public:
	__declspec(noinline) void h00024D2A(void);
};

class W3DBufferManager
{
public:
	Bool ReAcquireResources(void);
};

class BfmeD3DDevice
{
public:
	virtual void slot00(void);
	virtual void slot04(void);
	virtual void slot08(void);
	virtual void slot0c(void);
	virtual void slot10(void);
	virtual void slot14(void);
	virtual void slot18(void);
	virtual void slot1c(void);
	virtual void slot20(void);
	virtual void slot24(void);
	virtual void slot28(void);
	virtual void slot2c(void);
	virtual void slot30(void);
	virtual void slot34(void);
	virtual void slot38(void);
	virtual void slot3c(void);
	virtual void slot40(void);
	virtual void slot44(void);
	virtual void slot48(void);
	virtual void slot4c(void);
	virtual void slot50(void);
	virtual void slot54(void);
	virtual void slot58(void);
	virtual void slot5c(void);
	virtual void slot60(void);
	virtual void slot64(void);
	virtual HRESULT __stdcall CreateVertexBuffer(unsigned length, unsigned usage,
		unsigned fvf, unsigned pool, void **vertexBuffer, void *sharedHandle);
	virtual HRESULT __stdcall CreateIndexBuffer(unsigned length, unsigned usage,
		unsigned format, unsigned pool, void **indexBuffer, void *sharedHandle);
};

struct IDirect3DDevice8;
struct IDirect3DIndexBuffer8;
struct IDirect3DVertexBuffer8;



extern IDirect3DIndexBuffer8 *shadowIndexBufferD3D;
extern IDirect3DVertexBuffer8 *shadowVertexBufferD3D;
extern W3DBufferManager *TheW3DBufferManager; // 0x01306DE8
extern unsigned BfmeShadowIndexCount; // 0x012BBEC4
extern unsigned BfmeShadowVertexCount; // 0x012BBEC0

class W3DShadowHelperManager
{
public:
	Bool ReAcquireResources(void);
};

Bool W3DShadowHelperManager::ReAcquireResources(void)
{
	BfmeRadarResetLock guard;
	reinterpret_cast<GenAlpha *>(this)->h00024D2A();

	BfmeD3DDevice *device = (BfmeD3DDevice *)DX8Wrapper::_Get_D3D_Device8();
	if (device->CreateIndexBuffer(BfmeShadowIndexCount + BfmeShadowIndexCount,
		0x208, 101, 0,
		(void **)&shadowIndexBufferD3D, 0) < 0)
		return FALSE;

	if (shadowVertexBufferD3D == 0)
	{
		if (device->CreateVertexBuffer(BfmeShadowVertexCount * 3 * 4, 0x208, 0, 0,
			(void **)&shadowVertexBufferD3D, 0) < 0)
			return FALSE;
	}

	if (TheW3DBufferManager)
	{
		if (!TheW3DBufferManager->ReAcquireResources())
			return FALSE;
	}

	return TRUE;
}
