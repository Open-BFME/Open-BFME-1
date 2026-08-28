// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c-
// Lift the RenderDeviceDescClass::operator= naked dump to clean C++.
//
// Zero Hour's rddesc.h body, unchanged. The nine leading calls look wrong for a
// memberwise copy -- they push the source member's *value* rather than its
// address -- but that is exactly what ZH's source does: Get_Device_Name returns
// const char * through StringClass's conversion operator, and set_device_name
// assigns that pointer, so the call is StringClass::operator=(const char *).
//
// The rest of the body confirms the member list. Two rep movsd runs copy 0x130
// and 0x44C bytes, which are sizeof(D3DCAPS8) and
// sizeof(D3DADAPTER_IDENTIFIER8) exactly, and they sit contiguously at +0x24
// and +0x154. The tail calls VectorClass::operator= and then copies two dwords
// from +0x10 and +0x14 of that subobject, which is DynamicVectorClass's own
// inline operator= copying ActiveCount and GrowthStep after the base.

typedef char TCHAR;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib/wwstring.h
class StringClass
{
public:
	operator const TCHAR *(void) const { return m_Buffer; }

	const StringClass &operator=(const TCHAR *string);	///< ILT thunk at 0x000202E3

private:
	TCHAR *m_Buffer;
};

// Opaque D3D records; only their sizes matter here and both are confirmed by
// the lengths of the two rep movsd runs.
struct D3DCAPS8
{
	unsigned char m_unreconstructed_00[0x130];
};

struct D3DADAPTER_IDENTIFIER8
{
	unsigned char m_unreconstructed_00[0x44C];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/rddesc.h
class ResolutionDescClass
{
public:
	int Width;
	int Height;
	int BitDepth;
	int RefreshRate;
};

template <class T> class VectorClass
{
public:
	VectorClass<T> &operator=(const VectorClass<T> &rvalue);	///< retail body at 0x00905C80

protected:
	virtual ~VectorClass(void);							///< vtable at +0x00

	T *Vector;											///< retail this+0x04
	int VectorMax;										///< retail this+0x08
	bool IsValid;										///< retail this+0x0C
	bool IsAllocated;									///< retail this+0x0D
	bool VectorClassPad[2];
};

template <class T> class DynamicVectorClass : public VectorClass<T>
{
public:
	DynamicVectorClass<T> &operator=(DynamicVectorClass<T> const &rvalue)
	{
		VectorClass<T>::operator=(rvalue);
		ActiveCount = rvalue.ActiveCount;
		GrowthStep = rvalue.GrowthStep;
		return *this;
	}

protected:
	int ActiveCount;									///< retail this+0x10
	int GrowthStep;										///< retail this+0x14
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/rddesc.h
class RenderDeviceDescClass
{
public:
	RenderDeviceDescClass &operator=(const RenderDeviceDescClass &src);

	const char *Get_Device_Name() const			{ return DeviceName; }
	const char *Get_Device_Vendor() const		{ return DeviceVendor; }
	const char *Get_Device_Platform() const		{ return DevicePlatform; }

	const char *Get_Driver_Name() const			{ return DriverName; }
	const char *Get_Driver_Vendor() const		{ return DriverVendor; }
	const char *Get_Driver_Version() const		{ return DriverVersion; }

	const char *Get_Hardware_Name() const		{ return HardwareName; }
	const char *Get_Hardware_Vendor() const		{ return HardwareVendor; }
	const char *Get_Hardware_Chipset() const	{ return HardwareChipset; }

private:
	void set_device_name(const char * name)		{ DeviceName=name; }
	void set_device_vendor(const char * name)	{ DeviceVendor=name; }
	void set_device_platform(const char * name)	{ DevicePlatform=name; }
	void set_driver_name(const char * name)		{ DriverName=name; }
	void set_driver_vendor(const char * name)	{ DriverVendor=name; }
	void set_driver_version(const char * name)	{ DriverVersion=name; }
	void set_hardware_name(const char * name)	{ HardwareName=name; }
	void set_hardware_vendor(const char * name)	{ HardwareVendor=name; }
	void set_hardware_chipset(const char * name){ HardwareChipset=name; }

	StringClass DeviceName;								///< retail this+0x00
	StringClass DeviceVendor;							///< retail this+0x04
	StringClass DevicePlatform;							///< retail this+0x08
	StringClass DriverName;								///< retail this+0x0C
	StringClass DriverVendor;							///< retail this+0x10
	StringClass DriverVersion;							///< retail this+0x14
	StringClass HardwareName;							///< retail this+0x18
	StringClass HardwareVendor;							///< retail this+0x1C
	StringClass HardwareChipset;						///< retail this+0x20
	D3DCAPS8 Caps;										///< retail this+0x24
	D3DADAPTER_IDENTIFIER8 AdapterIdentifier;			///< retail this+0x154
	DynamicVectorClass<ResolutionDescClass> ResArray;	///< retail this+0x5A0
};

// ??4RenderDeviceDescClass@@QAEAAV0@ABV0@@Z
RenderDeviceDescClass & RenderDeviceDescClass::operator = (const RenderDeviceDescClass & src)
{
	set_device_name(src.Get_Device_Name());
	set_device_vendor(src.Get_Device_Vendor());
	set_device_platform(src.Get_Device_Platform());
	set_driver_name(src.Get_Driver_Name());
	set_driver_vendor(src.Get_Driver_Vendor());
	set_driver_version(src.Get_Driver_Version());
	set_hardware_name(src.Get_Hardware_Name());
	set_hardware_vendor(src.Get_Hardware_Vendor());
	set_hardware_chipset(src.Get_Hardware_Chipset());
	Caps=src.Caps;
	AdapterIdentifier=src.AdapterIdentifier;
	ResArray = src.ResArray;
	return *this;
}
