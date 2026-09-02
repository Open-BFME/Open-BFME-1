// cl: /DNDEBUG /MD /EHsc
// DX8Wrapper::Set_Render_Target(surface, depth) retail 0x00905470.
// Sibling of the bool overload at 0x009052B0; D3D9 split SetRenderTarget /
// SetDepthStencilSurface, IsRenderToTexture = true.

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

class DX8Wrapper
{
public:
	static void Set_Render_Target(IDirect3DSurface8 *renderTarget, IDirect3DSurface8 *depthBuffer);

private:
	static IDirect3DDevice8 *D3DDevice;
	static IDirect3DSurface8 *CurrentRenderTarget;
	static IDirect3DSurface8 *CurrentDepthBuffer;
	static IDirect3DSurface8 *DefaultRenderTarget;
	static IDirect3DSurface8 *DefaultDepthBuffer;
	static bool IsRenderToTexture;
	static unsigned int D3DCallCount;
};

// ?Set_Render_Target@DX8Wrapper@@SAXPAUIDirect3DSurface8@@0@Z
void DX8Wrapper::Set_Render_Target(IDirect3DSurface8 *renderTarget, IDirect3DSurface8 *depthBuffer)
{
	if (renderTarget == 0 || renderTarget == DefaultRenderTarget) {
		if (DefaultRenderTarget != 0) {
			D3DDevice->lpVtbl->SetRenderTarget(D3DDevice, 0, DefaultRenderTarget);
			++D3DCallCount;
			D3DDevice->lpVtbl->SetDepthStencilSurface(D3DDevice, DefaultDepthBuffer);
			++D3DCallCount;
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
			++D3DCallCount;
		}
		if (DefaultRenderTarget == 0) {
			D3DDevice->lpVtbl->GetRenderTarget(D3DDevice, 0, &DefaultRenderTarget);
			++D3DCallCount;
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
		CurrentDepthBuffer = depthBuffer;
		CurrentRenderTarget->lpVtbl->AddRef(CurrentRenderTarget);
		CurrentDepthBuffer->lpVtbl->AddRef(CurrentDepthBuffer);
		D3DDevice->lpVtbl->SetRenderTarget(D3DDevice, 0, CurrentRenderTarget);
		++D3DCallCount;
		D3DDevice->lpVtbl->SetDepthStencilSurface(D3DDevice, CurrentDepthBuffer);
		++D3DCallCount;
	}

	IsRenderToTexture = true;
}
