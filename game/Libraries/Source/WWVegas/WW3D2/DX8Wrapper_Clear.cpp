// cl: /DNDEBUG /MD /EHsc
/*
**	Command & Conquer Generals Zero Hour(tm)
**	Copyright 2025 Electronic Arts Inc.
**
**	This program is free software: you can redistribute it and/or modify
**	it under the terms of the GNU General Public License as published by
**	the Free Software Foundation, either version 3 of the License, or
**	(at your option) any later version.
**
**	This program is distributed in the hope that it will be useful,
**	but WITHOUT ANY WARRANTY; without even the implied warranty of
**	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**	GNU General Public License for more details.
**
**	You should have received a copy of the GNU General Public License
**	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
// Retail 0x00904250 is BFME's seven-argument Clear helper.  The source
// header is the Zero Hour six-argument declaration, so this TU keeps the
// extra clear_stencil parameter and the BFME device slots local instead of
// changing the shared ABI.

typedef unsigned long D3DCOLOR;
typedef long HRESULT;

enum {
	D3DFMT_D15S1 = 0x49,
	D3DFMT_D24S8 = 0x4B,
	D3DFMT_D24X4S4 = 0x4F,
	D3DCLEAR_TARGET = 0x1,
	D3DCLEAR_ZBUFFER = 0x2,
	D3DCLEAR_STENCIL = 0x4
};

class Vector3;
struct IDirect3DDevice8;
extern unsigned number_of_DX8_calls;

// GetDesc writes into the 32-byte retail local buffer at EBP-0x28.
// Only the leading Format word is read here; the remaining fields are opaque.
struct BFME_Clear_SurfaceDesc
{
	unsigned long Format;
	unsigned long reserved[7];
};

// This is the upstream DX8Wrapper::Convert_Color implementation.  BFME's
// Clear body inlines the same x87 conversion. Its conditional control-word
// save/change/restore and four FISTP conversions are explicit upstream assembly
// (dx8wrapper.h Convert_Color), not a lifted retail dump. Standard C++ casts
// cannot express that control-word sequence; this is the x87 codegen blocker.
// Keeping this helper local also permits the extra BFME Clear argument.
static __forceinline unsigned long bfme_clear_convert_color(
	const Vector3 &color, float alpha)
{
	const float scale = 255.0f;
	unsigned long col;

	__asm
	{
		sub	esp,20
		fwait
		fstcw	[esp+16]
		mov	eax,[esp+16]
		mov	edi,eax
		and	eax,~(1024|2048)
		or	eax,(1024|2048)
		sub	edi,eax
		jz	bfme_clear_fpu_unchanged
		mov	[esp],eax
		fldcw	[esp]
bfme_clear_fpu_unchanged:
		mov	esi,dword ptr color
		fld	dword ptr[scale]
		fld	dword ptr[esi]
		fld	dword ptr[esi+4]
		fld	dword ptr[esi+8]
		fld	dword ptr[alpha]
		fld	st(4)
		fmul	st(4),st
		fmul	st(3),st
		fmul	st(2),st
		fmulp	st(1),st
		fistp	dword ptr[esp+0]
		fistp	dword ptr[esp+4]
		fistp	dword ptr[esp+8]
		fistp	dword ptr[esp+12]
		mov	ecx,[esp]
		mov	eax,[esp+4]
		mov	edx,[esp+8]
		mov	ebx,[esp+12]
		shl	ecx,24
		shl	ebx,16
		shl	edx,8
		or	eax,ecx
		or	eax,ebx
		or	eax,edx
		fstp	st(0)
		cmp	edi,0
		je	bfme_clear_fpu_restored
		fwait
		fldcw	[esp+16]
bfme_clear_fpu_restored:
		add	esp,20
		mov	col,eax
	}
	return col;
}

struct BFME_Clear_Surface;
struct BFME_Clear_Device;

struct BFME_Clear_Surface_Vtbl
{
	void *QueryInterface;
	unsigned long (__stdcall *AddRef)(BFME_Clear_Surface *self);
	unsigned long (__stdcall *Release)(BFME_Clear_Surface *self);
	void *reserved[9];
	long (__stdcall *GetDesc)(BFME_Clear_Surface *self, BFME_Clear_SurfaceDesc *desc);
};

struct BFME_Clear_Surface
{
	BFME_Clear_Surface_Vtbl *lpVtbl;
};

// These are the BFME device entries observed in this body:
// GetDepthStencilSurface is slot
// 40 and Clear is slot 43, matching the retail calls at +0xA0 and +0xAC.
struct BFME_Clear_Device_Vtbl
{
	void *reserved[40];
	long (__stdcall *GetDepthStencilSurface)(
		BFME_Clear_Device *self, BFME_Clear_Surface **surface);
	void *BeginScene;
	void *EndScene;
	long (__stdcall *Clear)(
		BFME_Clear_Device *self,
		unsigned long count,
		const void *rects,
		unsigned long flags,
		D3DCOLOR color,
		float z,
		unsigned long stencil);
};

struct BFME_Clear_Device
{
	BFME_Clear_Device_Vtbl *lpVtbl;
};

// Keep the static-data declaration's type tied to the existing DX8Wrapper
// definition so it resolves to ?D3DDevice@DX8Wrapper@@, while the calls use
// the BFME-only vtable view above.
class DX8Wrapper
{
public:
	static void Clear(
		bool clear_color,
		bool clear_z_stencil,
		bool clear_stencil,
		const Vector3 &color,
		float dest_alpha,
		float z,
		unsigned int stencil);

private:
	static IDirect3DDevice8 *D3DDevice;
};

// ?Clear@DX8Wrapper@@SAX_N00ABVVector3@@MMI@Z
void DX8Wrapper::Clear(
	bool clear_color,
	bool clear_z_stencil,
	bool clear_stencil,
	const Vector3 &color,
	float dest_alpha,
	float z,
	unsigned int stencil)
{
	bool has_stencil = false;
	BFME_Clear_Surface *depthbuffer;

	reinterpret_cast<BFME_Clear_Device *>(D3DDevice)->lpVtbl->GetDepthStencilSurface(
		reinterpret_cast<BFME_Clear_Device *>(D3DDevice), &depthbuffer);
	number_of_DX8_calls++;

	if (depthbuffer) {
		BFME_Clear_SurfaceDesc desc;
		depthbuffer->lpVtbl->GetDesc(depthbuffer, &desc);
		has_stencil =
			desc.Format == D3DFMT_D15S1 ||
			desc.Format == D3DFMT_D24S8 ||
			desc.Format == D3DFMT_D24X4S4;
		depthbuffer->lpVtbl->Release(depthbuffer);
	}

	unsigned long flags = 0;
	if (clear_color) flags |= D3DCLEAR_TARGET;
	if (clear_z_stencil) flags |= D3DCLEAR_ZBUFFER;
	if (clear_stencil && has_stencil) flags |= D3DCLEAR_STENCIL;
	if (flags) {
		BFME_Clear_Device *device = reinterpret_cast<BFME_Clear_Device *>(D3DDevice);
		D3DCOLOR converted_color =
			bfme_clear_convert_color(color, dest_alpha);
		device->lpVtbl->Clear(device, 0, 0, flags, converted_color, z, stencil);
		number_of_DX8_calls++;
	}
}
