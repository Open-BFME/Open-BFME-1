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
// BFME DX8Wrapper::Enumerate_Devices, retail 0x00908680 (1996 bytes including
// the switch table at +0x7B8). Upstream body: WW3D2 dx8wrapper.cpp.
//
// BFME drives Direct3D 9 through the pointer the Zero Hour headers still type
// IDirect3D8, so this TU keeps the D3D9 layouts local instead of changing the
// shared D3D8 shim: GetAdapterCount +0x10, GetAdapterIdentifier +0x14,
// GetAdapterModeCount(adapter, format) +0x18, EnumAdapterModes(adapter, format,
// mode, out) +0x1C and GetDeviceCaps +0x38. The identifier it zeroes is the
// 0x44C-byte D3D9 one and the caps block is 0x130 bytes. Where Zero Hour
// enumerates one mode list per adapter, BFME walks the modes of five display
// formats collected in a DynamicVectorClass.

#include <stdio.h>
#include <string.h>

typedef long HRESULT;
typedef unsigned long DWORD;
typedef unsigned int UINT;

#define HIWORD(l) ((unsigned short)((DWORD)(l) >> 16))
#define LOWORD(l) ((unsigned short)((DWORD)(l) & 0xffff))

typedef enum _D3DFORMAT {
	D3DFMT_R8G8B8 = 20,
	D3DFMT_A8R8G8B8 = 21,
	D3DFMT_X8R8G8B8 = 22,
	D3DFMT_R5G6B5 = 23,
	D3DFMT_X1R5G5B5 = 24,
	D3DFMT_FORCE_DWORD = 0x7fffffff
} D3DFORMAT;

enum WW3DFormat { WW3D_FORMAT_UNKNOWN = 0 };

typedef struct _D3DDISPLAYMODE {
	UINT Width;
	UINT Height;
	UINT RefreshRate;
	D3DFORMAT Format;
} D3DDISPLAYMODE;

// D3DCAPS9, under the D3D8 tag the DX8Caps constructor symbol carries.
typedef struct _D3DCAPS8 {
	unsigned char opaque[0x130];
} D3DCAPS8;

// D3DADAPTER_IDENTIFIER9 (d3d9types.h packs to 4), under the D3D8 tag.
#pragma pack(push, 4)
typedef struct _D3DADAPTER_IDENTIFIER8 {
	char Driver[512];
	char Description[512];
	char DeviceName[32];
	struct { DWORD LowPart; long HighPart; } DriverVersion;
	DWORD VendorId;
	DWORD DeviceId;
	DWORD SubSysId;
	DWORD Revision;
	unsigned char DeviceIdentifier[16];
	DWORD WHQLLevel;
} D3DADAPTER_IDENTIFIER8;
#pragma pack(pop)

enum { D3D_OK = 0, WW3D_DEVTYPE = 1 /* D3DDEVTYPE_HAL */ };

struct IDirect3D8
{
	virtual HRESULT __stdcall QueryInterface(const void *, void **) = 0;
	virtual DWORD __stdcall AddRef() = 0;
	virtual DWORD __stdcall Release() = 0;
	virtual HRESULT __stdcall RegisterSoftwareDevice(void *) = 0;
	virtual UINT __stdcall GetAdapterCount() = 0;
	virtual HRESULT __stdcall GetAdapterIdentifier(UINT, DWORD, D3DADAPTER_IDENTIFIER8 *) = 0;
	virtual UINT __stdcall GetAdapterModeCount(UINT, D3DFORMAT) = 0;
	virtual HRESULT __stdcall EnumAdapterModes(UINT, D3DFORMAT, UINT, D3DDISPLAYMODE *) = 0;
	virtual HRESULT __stdcall GetAdapterDisplayMode(UINT, D3DDISPLAYMODE *) = 0;
	virtual HRESULT __stdcall CheckDeviceType(UINT, DWORD, D3DFORMAT, D3DFORMAT, int) = 0;
	virtual HRESULT __stdcall CheckDeviceFormat(UINT, DWORD, D3DFORMAT, DWORD, DWORD, D3DFORMAT) = 0;
	virtual HRESULT __stdcall CheckDeviceMultiSampleType(UINT, DWORD, D3DFORMAT, int, DWORD, DWORD *) = 0;
	virtual HRESULT __stdcall CheckDepthStencilMatch(UINT, DWORD, D3DFORMAT, D3DFORMAT, D3DFORMAT) = 0;
	virtual HRESULT __stdcall CheckDeviceFormatConversion(UINT, DWORD, D3DFORMAT, D3DFORMAT) = 0;
	virtual HRESULT __stdcall GetDeviceCaps(UINT, DWORD, D3DCAPS8 *) = 0;
};

void operator delete[](void *block) throw();

// upstream: WWLib wwstring.h
class StringClass
{
public:
	StringClass(const char *string, bool hint_temporary);
	~StringClass(void) { Free_String(); }

	const StringClass &operator=(const StringClass &string);
	const StringClass &operator=(const char *string);

	int Get_Length(void) const;

private:
	typedef struct _HEADER
	{
		int allocated_length;
		int length;
	} HEADER;

	void Get_String(int length, bool is_temp);
	void Uninitialised_Grow(int length);
	void Free_String(void);

	void Store_Length(int length)
	{
		if (m_Buffer != m_EmptyString) {
			Get_Header()->length = length;
		}
	}
	HEADER *Get_Header(void) const { return reinterpret_cast<HEADER *>(m_Buffer) - 1; }

	char *m_Buffer;

	static char *m_EmptyString;
};

inline StringClass::StringClass(const char *string, bool hint_temporary)
	: m_Buffer(m_EmptyString)
{
	int len = string ? strlen(string) : 0;
	if (hint_temporary || len > 0) {
		Get_String(len + 1, hint_temporary);
	}
	(*this) = string;
}

inline int StringClass::Get_Length(void) const
{
	int length = 0;
	if (m_Buffer != m_EmptyString) {
		HEADER *header = Get_Header();
		length = header->length;
		if (length == 0) {
			length = strlen(m_Buffer);
			((StringClass *)this)->Store_Length(length);
		}
	}
	return length;
}

inline const StringClass &StringClass::operator=(const StringClass &string)
{
	int len = string.Get_Length();
	Uninitialised_Grow(len + 1);
	Store_Length(len);
	::memcpy(m_Buffer, string.m_Buffer, len + 1);
	return (*this);
}

inline const StringClass &StringClass::operator=(const char *string)
{
	if (string != 0) {
		int len = strlen(string);
		Uninitialised_Grow(len + 1);
		Store_Length(len);
		::memcpy(m_Buffer, string, len + 1);
	}
	return (*this);
}

// upstream: WWLib vector.h
template<class T> class VectorClass
{
public:
	VectorClass(int size = 0, T const *array = 0)
		: Vector(0), VectorMax(size), IsValid(true), IsAllocated(false) {}
	virtual ~VectorClass(void) { VectorClass<T>::Clear(); }

	T &operator[](int index) { return (Vector[index]); }
	T const &operator[](int index) const { return (Vector[index]); }

	virtual bool operator==(VectorClass<T> const &) const;
	virtual bool Resize(int newsize, T const *array = 0);
	virtual void Clear(void)
	{
		if (Vector && IsAllocated) {
			delete[] Vector;
			Vector = 0;
		}
		IsAllocated = false;
		VectorMax = 0;
	}
	virtual int ID(T const *ptr);
	virtual int ID(T const &ptr);

	int Length(void) const { return VectorMax; }

protected:
	T *Vector;
	int VectorMax;
	bool IsValid;
	bool IsAllocated;
};

template<class T> class DynamicVectorClass : public VectorClass<T>
{
public:
	DynamicVectorClass(unsigned size = 0, T const *array = 0)
		: VectorClass<T>(size, array)
	{
		GrowthStep = 10;
		ActiveCount = 0;
	}

	virtual bool Resize(int newsize, T const *array = 0);
	virtual void Clear(void);
	virtual int ID(T const *ptr);
	virtual int ID(T const &ptr);

	int Count(void) const { return (ActiveCount); }

	bool Add(T const &object)
	{
		if (ActiveCount >= Length()) {
			if ((IsAllocated || !VectorMax) && GrowthStep > 0) {
				if (!Resize(Length() + GrowthStep)) {
					return (false);
				}
			} else {
				return (false);
			}
		}
		(*this)[ActiveCount++] = object;
		return (true);
	}

	void Delete_All(void)
	{
		int len = VectorMax;
		Clear();
		Resize(len);
	}

protected:
	int ActiveCount;
	int GrowthStep;
};

// upstream: WW3D2 rddesc.h
class ResolutionDescClass
{
public:
	int Width;
	int Height;
	int BitDepth;
};

class RenderDeviceDescClass
{
public:
	RenderDeviceDescClass(void);
	~RenderDeviceDescClass(void);

	RenderDeviceDescClass &operator=(const RenderDeviceDescClass &src);

	const DynamicVectorClass<ResolutionDescClass> &Enumerate_Resolutions(void) const { return ResArray; }

private:
	void set_device_name(const char *name) { DeviceName = name; }
	void set_driver_name(const char *name) { DriverName = name; }
	void set_driver_version(const char *name) { DriverVersion = name; }

	void reset_resolution_list(void) { ResArray.Delete_All(); }
	void add_resolution(int w, int h, int bits);

	StringClass DeviceName;
	StringClass DeviceVendor;
	StringClass DevicePlatform;

	StringClass DriverName;
	StringClass DriverVendor;
	StringClass DriverVersion;

	StringClass HardwareName;
	StringClass HardwareVendor;
	StringClass HardwareChipset;

	D3DCAPS8 Caps;
	D3DADAPTER_IDENTIFIER8 AdapterIdentifier;

	DynamicVectorClass<ResolutionDescClass> ResArray;

	friend class DX8Wrapper;
};

// upstream: WW3D2 dx8caps.h; BFME retail places the three strings at
// +0x29C, +0x2A4 and +0x2A8 of a 0x2AC-byte object.
class DX8Caps
{
public:
	DX8Caps(IDirect3D8 *direct3d, const D3DCAPS8 &caps, WW3DFormat display_format,
		const D3DADAPTER_IDENTIFIER8 &adapter_id);

	bool Is_Valid_Display_Format(int width, int height, WW3DFormat format);

private:
	unsigned char CapsState[0x29C];
	StringClass DriverDLL;
	IDirect3D8 *Direct3D;
	StringClass CapsLog;
	StringClass CompactLog;
};

class DX8Wrapper
{
protected:
	static void Enumerate_Devices(void);

	static IDirect3D8 *D3DInterface;
};

extern DynamicVectorClass<StringClass> _RenderDeviceNameTable;
extern DynamicVectorClass<StringClass> _RenderDeviceShortNameTable;
extern DynamicVectorClass<RenderDeviceDescClass> _RenderDeviceDescriptionTable;

// ?Enumerate_Devices@DX8Wrapper@@KAXXZ
void DX8Wrapper::Enumerate_Devices()
{
	int adapter_count = D3DInterface->GetAdapterCount();
	for (int adapter_index=0; adapter_index<adapter_count; adapter_index++) {

		D3DADAPTER_IDENTIFIER8 id;
		::memset(&id, 0, sizeof(D3DADAPTER_IDENTIFIER8));
		HRESULT res = D3DInterface->GetAdapterIdentifier(adapter_index,0,&id);

		if (res == D3D_OK) {

			/*
			** Set up the render device description
			*/
			RenderDeviceDescClass desc;
			desc.set_device_name(id.Description);
			desc.set_driver_name(id.Driver);

			char buf[64];
			sprintf(buf,"%d.%d.%d.%d",
				HIWORD(id.DriverVersion.HighPart),
				LOWORD(id.DriverVersion.HighPart),
				HIWORD(id.DriverVersion.LowPart),
				LOWORD(id.DriverVersion.LowPart));

			desc.set_driver_version(buf);

			D3DInterface->GetDeviceCaps(adapter_index,WW3D_DEVTYPE,&desc.Caps);
			D3DInterface->GetAdapterIdentifier(adapter_index,0,&desc.AdapterIdentifier);

			DX8Caps dx8caps(D3DInterface,desc.Caps,WW3D_FORMAT_UNKNOWN,desc.AdapterIdentifier);

			/*
			** Enumerate the resolutions of each accepted display format
			*/
			desc.reset_resolution_list();

			DynamicVectorClass<D3DFORMAT> formats;
			formats.Add(D3DFMT_R5G6B5);
			formats.Add(D3DFMT_X1R5G5B5);
			formats.Add(D3DFMT_R8G8B8);
			formats.Add(D3DFMT_A8R8G8B8);
			formats.Add(D3DFMT_X8R8G8B8);

			int format_count = formats.Count();
			for (int format_index=0; format_index<format_count; format_index++) {
				int mode_count = D3DInterface->GetAdapterModeCount(adapter_index,formats[format_index]);
				for (int mode_index=0; mode_index<mode_count; mode_index++) {
					D3DDISPLAYMODE d3dmode;
					::memset(&d3dmode, 0, sizeof(D3DDISPLAYMODE));
					HRESULT res = D3DInterface->EnumAdapterModes(adapter_index,formats[format_index],mode_index,&d3dmode);

					if (res == D3D_OK) {
						int bits = 0;
						switch (d3dmode.Format)
						{
							case D3DFMT_R8G8B8:
							case D3DFMT_A8R8G8B8:
							case D3DFMT_X8R8G8B8:		bits = 32; break;

							case D3DFMT_R5G6B5:
							case D3DFMT_X1R5G5B5:		bits = 16; break;
						}

						// Some cards fail in certain modes, DX8Caps keeps list of those.
						if (!dx8caps.Is_Valid_Display_Format(d3dmode.Width,d3dmode.Height,(WW3DFormat)d3dmode.Format)) {
							bits=0;
						}

						if (bits != 0) {
							desc.add_resolution(d3dmode.Width,d3dmode.Height,bits);
						}
					}
				}
			}

			// IML: If the device has one or more valid resolutions add it to the device list.
			if (desc.Enumerate_Resolutions().Count() > 0) {

				StringClass device_name(id.Description,true);
				_RenderDeviceNameTable.Add(device_name);
				_RenderDeviceShortNameTable.Add(device_name);

				_RenderDeviceDescriptionTable.Add(desc);
			}
		}
	}
}
