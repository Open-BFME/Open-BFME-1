// cl: /DNDEBUG /MD /EHsc
// Retail 0x00904230: DX8CALL(BeginScene()) wrapped by a matching enter/leave helper.

struct IDirect3DDevice8;

struct IDirect3DDevice8Vtbl
{
	void *reserved[41];
	long (__stdcall *BeginScene)(IDirect3DDevice8 *self);
};

struct IDirect3DDevice8
{
	IDirect3DDevice8Vtbl *lpVtbl;
};

void bfmeDebugTouch009588e0(void);

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/dx8wrapper.h
class DX8Wrapper
{
public:
	static void Begin_Scene_Inner(void);

private:
	static IDirect3DDevice8 *D3DDevice;
	static unsigned D3DCallCount;
};

// ?Begin_Scene_Inner@DX8Wrapper@@SAXXZ
void DX8Wrapper::Begin_Scene_Inner(void)
{
	bfmeDebugTouch009588e0();
	D3DDevice->lpVtbl->BeginScene(D3DDevice);
	++D3DCallCount;
	bfmeDebugTouch009588e0();
}
