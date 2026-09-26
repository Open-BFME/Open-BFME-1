// cl: /DNDEBUG /MD /EHsc

// Free copyRect from GeneralsMD W3DSmudge.cpp, adapted to BFME's D3D9 device:
// GetRenderTarget(index, surface) at vtable +0x98, CreateRenderTarget at +0x70,
// StretchRect at +0x88 (CopyRects replacement), surface GetDesc/LockRect/UnlockRect
// at +0x30/+0x34/+0x38.

#include <string.h>

typedef int Int;
typedef unsigned int UINT;
typedef unsigned long DWORD;
typedef long HRESULT;
#define S_OK 0
#define D3DLOCK_READONLY 0x00000010L
#define D3DMULTISAMPLE_NONE 0
#define D3DTEXF_NONE 0
#define TRUE 1

struct RECT
{
	long left;
	long top;
	long right;
	long bottom;
};

struct D3DSURFACE_DESC
{
	unsigned Format;
	unsigned Type;
	unsigned Usage;
	unsigned Pool;
	unsigned MultiSampleType;
	unsigned MultiSampleQuality;
	unsigned Width;
	unsigned Height;
};

struct D3DLOCKED_RECT
{
	long Pitch;
	void *pBits;
};

struct IDirect3DSurface9
{
	virtual HRESULT __stdcall QueryInterface(void *, void **) = 0;
	virtual DWORD __stdcall AddRef() = 0;
	virtual DWORD __stdcall Release() = 0;
	virtual HRESULT __stdcall GetDevice(void **) = 0;
	virtual HRESULT __stdcall SetPrivateData(void *, const void *, DWORD, DWORD) = 0;
	virtual HRESULT __stdcall GetPrivateData(void *, void *, DWORD *) = 0;
	virtual HRESULT __stdcall FreePrivateData(void *) = 0;
	virtual DWORD __stdcall SetPriority(DWORD) = 0;
	virtual DWORD __stdcall GetPriority() = 0;
	virtual void __stdcall PreLoad() = 0;
	virtual DWORD __stdcall GetType() = 0;
	virtual HRESULT __stdcall GetContainer(void *, void **) = 0;
	virtual HRESULT __stdcall GetDesc(D3DSURFACE_DESC *) = 0;
	virtual HRESULT __stdcall LockRect(D3DLOCKED_RECT *, const RECT *, DWORD) = 0;
	virtual HRESULT __stdcall UnlockRect() = 0;
};

struct IDirect3DDevice9
{
	virtual HRESULT __stdcall QueryInterface(void *, void **) = 0;
	virtual DWORD __stdcall AddRef() = 0;
	virtual DWORD __stdcall Release() = 0;
	virtual HRESULT __stdcall unused03() = 0;
	virtual HRESULT __stdcall unused04() = 0;
	virtual HRESULT __stdcall unused05() = 0;
	virtual HRESULT __stdcall unused06() = 0;
	virtual HRESULT __stdcall unused07() = 0;
	virtual HRESULT __stdcall unused08() = 0;
	virtual HRESULT __stdcall unused09() = 0;
	virtual HRESULT __stdcall unused10() = 0;
	virtual HRESULT __stdcall unused11() = 0;
	virtual HRESULT __stdcall unused12() = 0;
	virtual HRESULT __stdcall unused13() = 0;
	virtual HRESULT __stdcall unused14() = 0;
	virtual HRESULT __stdcall unused15() = 0;
	virtual HRESULT __stdcall unused16() = 0;
	virtual HRESULT __stdcall unused17() = 0;
	virtual HRESULT __stdcall unused18() = 0;
	virtual HRESULT __stdcall unused19() = 0;
	virtual HRESULT __stdcall unused20() = 0;
	virtual HRESULT __stdcall unused21() = 0;
	virtual HRESULT __stdcall unused22() = 0;
	virtual HRESULT __stdcall unused23() = 0;
	virtual HRESULT __stdcall unused24() = 0;
	virtual HRESULT __stdcall unused25() = 0;
	virtual HRESULT __stdcall unused26() = 0;
	virtual HRESULT __stdcall unused27() = 0;
	virtual HRESULT __stdcall CreateRenderTarget(UINT Width, UINT Height, unsigned Format,
		unsigned MultiSample, DWORD MultisampleQuality, int Lockable,
		IDirect3DSurface9 **ppSurface, void **pSharedHandle) = 0;
	virtual HRESULT __stdcall unused29() = 0;
	virtual HRESULT __stdcall unused30() = 0;
	virtual HRESULT __stdcall unused31() = 0;
	virtual HRESULT __stdcall unused32() = 0;
	virtual HRESULT __stdcall unused33() = 0;
	virtual HRESULT __stdcall StretchRect(IDirect3DSurface9 *pSourceSurface, const RECT *pSourceRect,
		IDirect3DSurface9 *pDestSurface, const RECT *pDestRect, unsigned Filter) = 0;
	virtual HRESULT __stdcall unused35() = 0;
	virtual HRESULT __stdcall unused36() = 0;
	virtual HRESULT __stdcall unused37() = 0;
	virtual HRESULT __stdcall GetRenderTarget(DWORD RenderTargetIndex, IDirect3DSurface9 **ppRenderTarget) = 0;
};

extern IDirect3DDevice9 *g_d3dDevice;

Int copyRect(unsigned char *buf, Int bufSize, int oX, int oY, int width, int height)
{
	IDirect3DSurface9 *surface = 0;
	IDirect3DSurface9 *tempSurface = 0;
	Int result = 0;
	HRESULT hr = S_OK;
	RECT dstRect;

	IDirect3DDevice9 *m_pDev = g_d3dDevice;

	if (!m_pDev)
		goto error;

	m_pDev->GetRenderTarget(0, &surface);

	if (!surface)
		goto error;

	D3DSURFACE_DESC desc;
	surface->GetDesc(&desc);

	RECT srcRect;
	srcRect.left = oX;
	srcRect.top = oY;
	srcRect.right = oX + width;
	srcRect.bottom = oY + height;

	hr = m_pDev->CreateRenderTarget((UINT)width, (UINT)height, desc.Format,
		D3DMULTISAMPLE_NONE, 0, TRUE, &tempSurface, 0);

	if (hr != S_OK)
		goto error;

	dstRect.left = 0;
	dstRect.top = 0;
	dstRect.right = width;
	dstRect.bottom = height;

	hr = m_pDev->StretchRect(surface, &srcRect, tempSurface, &dstRect, D3DTEXF_NONE);

	if (hr != S_OK)
		goto error;

	D3DLOCKED_RECT lrect;
	hr = tempSurface->LockRect(&lrect, 0, D3DLOCK_READONLY);

	if (hr != S_OK)
		goto error;

	tempSurface->GetDesc(&desc);

	{
		Int copySize = lrect.Pitch * height;
		if (copySize < bufSize)
			bufSize = copySize;
		memcpy(buf, lrect.pBits, (unsigned int)bufSize);
		result = bufSize;
	}

	tempSurface->UnlockRect();

error:
	if (surface)
		surface->Release();
	if (tempSurface)
		tempSurface->Release();

	return result;
}
