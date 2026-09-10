// ?Create_Device@DX8Wrapper@@KA_NXZ
// partial score=0.68 date=2026-09-10
// Banked complete reconstruction for ?Create_Device@DX8Wrapper@@KA_NXZ.
// The production TU supplies the project declarations and globals; this file
// preserves the evidence-backed BFME ABI view and control flow for the next
// converter after the nonmatching attempt is reverted.

struct BFMECreateDeviceCaps
{
	unsigned char opaque_00[0x1C];
	unsigned DevCaps;
	unsigned char opaque_20[0x110];
};

struct BFMECreateDeviceAdapterIdentifier
{
	char Driver[0x200];
	char Description[0x200];
	unsigned char opaque_400[0x4C];
};

struct BFMECreateDevice8;
typedef unsigned (__stdcall *BFMECreateDeviceGetAdapterCount)(BFMECreateDevice8 *);
typedef long (__stdcall *BFMECreateDeviceGetAdapterIdentifier)(BFMECreateDevice8 *, unsigned,
	unsigned, BFMECreateDeviceAdapterIdentifier *);
typedef long (__stdcall *BFMECreateDeviceGetDeviceCaps)(BFMECreateDevice8 *, unsigned,
	unsigned, BFMECreateDeviceCaps *);
typedef long (__stdcall *BFMECreateDeviceCreateDevice)(BFMECreateDevice8 *, unsigned,
	unsigned, HWND, unsigned, BFME_PRESENT_PARAMETERS *, IDirect3DDevice8 **);

struct BFMECreateDevice8Vtbl
{
	void *reserved_00[4];
	BFMECreateDeviceGetAdapterCount GetAdapterCount;
	BFMECreateDeviceGetAdapterIdentifier GetAdapterIdentifier;
	void *reserved_18[8];
	BFMECreateDeviceGetDeviceCaps GetDeviceCaps;
	void *reserved_3C;
	BFMECreateDeviceCreateDevice CreateDevice;
};

struct BFMECreateDevice8
{
	BFMECreateDevice8Vtbl *lpVtbl;
};

bool DX8Wrapper::Create_Device(void)
{
	WWASSERT(D3DDevice==NULL);

	BFMECreateDeviceCaps caps;
	if (reinterpret_cast<BFMECreateDevice8 *>(D3DInterface)->lpVtbl->GetDeviceCaps(
		reinterpret_cast<BFMECreateDevice8 *>(D3DInterface), CurRenderDevice, WW3D_DEVTYPE,
		&caps) < 0)
		return false;

	::ZeroMemory(&CurrentAdapterIdentifier, 0x44C);
	if (reinterpret_cast<BFMECreateDevice8 *>(D3DInterface)->lpVtbl->GetAdapterIdentifier(
		reinterpret_cast<BFMECreateDevice8 *>(D3DInterface), CurRenderDevice, 0,
		reinterpret_cast<BFMECreateDeviceAdapterIdentifier *>(&CurrentAdapterIdentifier)) < 0)
		return false;

	Vertex_Processing_Behavior = (caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT) ?
		D3DCREATE_MIXED_VERTEXPROCESSING : D3DCREATE_SOFTWARE_VERTEXPROCESSING;
	Vertex_Processing_Behavior |= 4;
	_DX8SingleThreaded = false;
	if (DX8Wrapper_PreserveFPU)
		Vertex_Processing_Behavior |= D3DCREATE_FPU_PRESERVE;

	int adapter = CurRenderDevice;
	unsigned device_type = D3DDEVTYPE_HAL;
	unsigned i = 0;
	if (i < reinterpret_cast<BFMECreateDevice8 *>(D3DInterface)->lpVtbl->GetAdapterCount(
		reinterpret_cast<BFMECreateDevice8 *>(D3DInterface))) {
		do {
			BFMECreateDeviceAdapterIdentifier adapter_identifier;
			if (reinterpret_cast<BFMECreateDevice8 *>(D3DInterface)->lpVtbl->GetAdapterIdentifier(
				reinterpret_cast<BFMECreateDevice8 *>(D3DInterface), i, 0, &adapter_identifier) >= 0 &&
				memcmp(adapter_identifier.Description, "NVIDIA NVPerfHUD", sizeof("NVIDIA NVPerfHUD")) == 0) {
				adapter = i;
				device_type = D3DDEVTYPE_REF;
				break;
			}
			++i;
		} while (i < reinterpret_cast<BFMECreateDevice8 *>(D3DInterface)->lpVtbl->GetAdapterCount(
			reinterpret_cast<BFMECreateDevice8 *>(D3DInterface)));
	}

	HRESULT hr = reinterpret_cast<BFMECreateDevice8 *>(D3DInterface)->lpVtbl->CreateDevice(
		reinterpret_cast<BFMECreateDevice8 *>(D3DInterface), adapter, device_type, _Hwnd,
		Vertex_Processing_Behavior,
		reinterpret_cast<BFME_PRESENT_PARAMETERS *>(&_PresentParameters), &D3DDevice);
	if (FAILED(hr)) {
		if ((_PresentParameters.BackBufferFormat == D3DFMT_R5G6B5 ||
			_PresentParameters.BackBufferFormat == D3DFMT_X1R5G5B5 ||
			_PresentParameters.BackBufferFormat == D3DFMT_A1R5G5B5) &&
			(_PresentParameters.AutoDepthStencilFormat == D3DFMT_D32 ||
			_PresentParameters.AutoDepthStencilFormat == D3DFMT_D24S8 ||
			_PresentParameters.AutoDepthStencilFormat == D3DFMT_D24X8)) {
			_PresentParameters.AutoDepthStencilFormat = D3DFMT_D16;
			hr = reinterpret_cast<BFMECreateDevice8 *>(D3DInterface)->lpVtbl->CreateDevice(
				reinterpret_cast<BFMECreateDevice8 *>(D3DInterface), adapter, device_type, _Hwnd,
				Vertex_Processing_Behavior,
				reinterpret_cast<BFME_PRESENT_PARAMETERS *>(&_PresentParameters), &D3DDevice);
			if (FAILED(hr))
				return false;
		} else {
			return false;
		}
	}

	Do_Onetime_Device_Dependent_Inits();
	return true;
}
