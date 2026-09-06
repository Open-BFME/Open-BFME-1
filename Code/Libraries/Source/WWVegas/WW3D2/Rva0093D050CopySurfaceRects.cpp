// cl: /DNDEBUG /MD /EHsc
// Retail RVA 0x0093D050 is the five-argument BFME D3D9 UpdateSurface helper.
// It copies one source RECT to one destination POINT per count, advancing the
// source RECT array by 16 bytes and the destination POINT array by 8 bytes.
// The device call is the proven BFME slot 30 (+0x78), and every call records
// one DX8 wrapper call despite the underlying device being D3D9.

struct RECT
{
	long left;
	long top;
	long right;
	long bottom;
};

struct POINT
{
	long x;
	long y;
};

class IDirect3DSurface9;
class D3DDeviceInterface;

typedef long (__stdcall *UpdateSurfaceProc)(
	D3DDeviceInterface *device,
	IDirect3DSurface9 *source_surface,
	const RECT *source_rect,
	IDirect3DSurface9 *destination_surface,
	const POINT *destination_point);

struct D3DDeviceVTable
{
	void *m_slots_0_29[30];
	UpdateSurfaceProc UpdateSurface;
};

class D3DDeviceInterface
{
	public:
	D3DDeviceVTable *m_vtable;
};

extern D3DDeviceInterface *g_w3dMouseD3DDevice;
extern unsigned number_of_DX8_calls;

extern "C" void __cdecl rva0093D050(
	IDirect3DSurface9 *source_surface,
	const RECT *source_rects,
	unsigned count,
	IDirect3DSurface9 *destination_surface,
	const POINT *destination_points)
{
	if (count != 0 && source_rects != 0)
	{
		if (count > 0)
		{
			do
			{
				g_w3dMouseD3DDevice->m_vtable->UpdateSurface(
					g_w3dMouseD3DDevice, source_surface, source_rects,
					destination_surface, destination_points);
				++number_of_DX8_calls;
				destination_points += 1;
				source_rects += 1;
				--count;
			} while (count != 0);
		}
		return;
	}

	g_w3dMouseD3DDevice->m_vtable->UpdateSurface(
		g_w3dMouseD3DDevice, source_surface, 0, destination_surface, 0);
	++number_of_DX8_calls;
}
