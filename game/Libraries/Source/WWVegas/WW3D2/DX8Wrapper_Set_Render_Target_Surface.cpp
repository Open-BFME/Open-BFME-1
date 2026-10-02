// cl: /DNDEBUG /MD /EHsc
// BFME's Direct3D device keeps the D3D8 type name but uses the D3D9 render-target
// slots, so this local ABI slice avoids changing the shared legacy SDK shim.

struct IDirect3DSurface8;
struct IDirect3DDevice8;

struct IDirect3DSurface8Vtbl
{
	void *QueryInterface;
	long (__stdcall *AddRef)(IDirect3DSurface8 *self);
	long (__stdcall *Release)(IDirect3DSurface8 *self);
};

struct IDirect3DSurface8
{
	IDirect3DSurface8Vtbl *lpVtbl;
};

struct IDirect3DDevice8Vtbl
{
	void *reserved[37];
	long (__stdcall *SetRenderTarget)(IDirect3DDevice8 *self, unsigned int index, IDirect3DSurface8 *renderTarget);
	long (__stdcall *GetRenderTarget)(IDirect3DDevice8 *self, unsigned int index, IDirect3DSurface8 **renderTarget);
	long (__stdcall *SetDepthStencilSurface)(IDirect3DDevice8 *self, IDirect3DSurface8 *depthStencil);
	long (__stdcall *GetDepthStencilSurface)(IDirect3DDevice8 *self, IDirect3DSurface8 **depthStencil);
};

struct IDirect3DDevice8
{
	IDirect3DDevice8Vtbl *lpVtbl;
};

extern unsigned int number_of_DX8_calls;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/dx8wrapper.h
class DX8Wrapper
{
public:
	static void Set_Render_Target(IDirect3DSurface8 *renderTarget, bool useDefaultDepthBuffer);

private:
	static IDirect3DDevice8 *D3DDevice;
	static IDirect3DSurface8 *CurrentRenderTarget;
	static IDirect3DSurface8 *CurrentDepthBuffer;
	static IDirect3DSurface8 *DefaultRenderTarget;
	static IDirect3DSurface8 *DefaultDepthBuffer;
	static bool IsRenderToTexture;
};

// ?Set_Render_Target@DX8Wrapper@@SAXPAUIDirect3DSurface8@@_N@Z
void DX8Wrapper::Set_Render_Target(IDirect3DSurface8 *renderTarget, bool useDefaultDepthBuffer)
{
	if (renderTarget == 0 || renderTarget == DefaultRenderTarget) {
		if (DefaultRenderTarget != 0) {
			D3DDevice->lpVtbl->SetRenderTarget(D3DDevice, 0, DefaultRenderTarget);
			++number_of_DX8_calls;
			D3DDevice->lpVtbl->SetDepthStencilSurface(D3DDevice, DefaultDepthBuffer);
			++number_of_DX8_calls;
			DefaultRenderTarget->lpVtbl->Release(DefaultRenderTarget);
			DefaultRenderTarget = 0;
			if (DefaultDepthBuffer != 0) {
				DefaultDepthBuffer->lpVtbl->Release(DefaultDepthBuffer);
				DefaultDepthBuffer = 0;
			}
		}

		if (CurrentRenderTarget != 0) {
			CurrentRenderTarget->lpVtbl->Release(CurrentRenderTarget);
			CurrentRenderTarget = 0;
		}
		if (CurrentDepthBuffer != 0) {
			CurrentDepthBuffer->lpVtbl->Release(CurrentDepthBuffer);
			CurrentDepthBuffer = 0;
		}
	} else if (renderTarget != CurrentRenderTarget) {
		if (DefaultDepthBuffer == 0) {
			D3DDevice->lpVtbl->GetDepthStencilSurface(D3DDevice, &DefaultDepthBuffer);
			++number_of_DX8_calls;
		}
		if (DefaultRenderTarget == 0) {
			D3DDevice->lpVtbl->GetRenderTarget(D3DDevice, 0, &DefaultRenderTarget);
			++number_of_DX8_calls;
		}

		if (CurrentRenderTarget != 0) {
			CurrentRenderTarget->lpVtbl->Release(CurrentRenderTarget);
			CurrentRenderTarget = 0;
		}
		if (CurrentDepthBuffer != 0) {
			CurrentDepthBuffer->lpVtbl->Release(CurrentDepthBuffer);
			CurrentDepthBuffer = 0;
		}

		CurrentRenderTarget = renderTarget;
		CurrentRenderTarget->lpVtbl->AddRef(CurrentRenderTarget);
		if (useDefaultDepthBuffer) {
			D3DDevice->lpVtbl->SetRenderTarget(D3DDevice, 0, CurrentRenderTarget);
			++number_of_DX8_calls;
			D3DDevice->lpVtbl->SetDepthStencilSurface(D3DDevice, DefaultDepthBuffer);
			++number_of_DX8_calls;
		} else {
			D3DDevice->lpVtbl->SetRenderTarget(D3DDevice, 0, CurrentRenderTarget);
			++number_of_DX8_calls;
		}
	}

	IsRenderToTexture = false;
}
