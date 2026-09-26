// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// BFME chipset probe, retail 0x007175E0.

typedef unsigned int Dword;
typedef unsigned char Byte;

extern void W3DRadarResetLock(void);
extern void W3DRadarResetUnlock(void);

class BfmeRadarResetGuard
{
public:
	BfmeRadarResetGuard() { W3DRadarResetLock(); }
	~BfmeRadarResetGuard() { W3DRadarResetUnlock(); }
};

struct BfmeAdapterIdentifier
{
	Byte bytes[0x428];
	Dword vendorId;
	Dword deviceId;
	Byte tail[0x1c];
};

struct BfmeDeviceCaps
{
	Byte bytes[0xcc];
	Dword pixelShaderVersion;
	Byte tail[0x60];
};

class BfmeD3D8
{
public:
	virtual long __stdcall slot00(void);
	virtual long __stdcall slot04(void);
	virtual long __stdcall slot08(void);
	virtual long __stdcall slot0c(void);
	virtual long __stdcall slot10(void);
	virtual long __stdcall GetAdapterIdentifier(unsigned adapter, unsigned flags,
		BfmeAdapterIdentifier *identifier);
	virtual long __stdcall slot18(void);
	virtual long __stdcall slot1c(void);
	virtual long __stdcall slot20(void);
	virtual long __stdcall slot24(void);
	virtual long __stdcall slot28(void);
	virtual long __stdcall slot2c(void);
	virtual long __stdcall slot30(void);
	virtual long __stdcall slot34(void);
	virtual long __stdcall GetDeviceCaps(unsigned adapter, unsigned deviceType,
		BfmeDeviceCaps *caps);
};

typedef long (__stdcall *BfmeGetDeviceCaps)(BfmeD3D8 *, unsigned, unsigned,
	BfmeDeviceCaps *);

struct BfmeD3D8Vtable
{
	void *slots[14];
	BfmeGetDeviceCaps getDeviceCaps;
};

class BfmeChipsetDetector
{
public:
	static void detect(void);
};

#define BfmeChipset (*(volatile int *)0x012F9CF8)
#define BfmeD3D8Interface (*(BfmeD3D8 **)0x01340530)

void BfmeChipsetDetector::detect(void)
{
	if (BfmeChipset != 0)
		return;

	BfmeRadarResetGuard guard;
	BfmeD3D8 *d3d8 = BfmeD3D8Interface;
	if (d3d8 == 0)
		return;

	BfmeAdapterIdentifier identifier;
	for (unsigned i = 0; i < sizeof(identifier); ++i)
		reinterpret_cast<Byte *>(&identifier)[i] = 0;
	d3d8->GetAdapterIdentifier(0, 0, &identifier);

	Dword device = identifier.deviceId;
	if (identifier.vendorId == 0x10de)
	{
		if (device >= 0x150 && device <= 0x18b)
		{
			BfmeChipset = 1;
			return;
		}
		if (device >= 0x321 && device <= 0x323)
		{
			BfmeChipset = 4;
			return;
		}
		if (device == 0x327 || device == 0x314)
		{
			BfmeChipset = 4;
			return;
		}
		if (device >= 0x200 && device <= 0x202)
		{
			BfmeChipset = 5;
			return;
		}
		if (device >= 0x250 && device <= 0x289)
		{
			BfmeChipset = 7;
			return;
		}
	}
	else if (identifier.vendorId == 0x1002)
	{
		if (device == 0x5144 || device == 0x5157 || device == 0x5159)
		{
			BfmeChipset = 2;
			return;
		}
		if (device == 0x514c || device == 0x4966 || device == 0x496e ||
			device == 0x514d || device == 0x5940 || device == 0x5941 ||
			device == 0x5d44 || (device >= 0x5960 && device <= 0x5964))
		{
			BfmeChipset = 6;
			return;
		}
	}
	else if (identifier.vendorId == 0x8086)
	{
		BfmeChipset = 1;
		return;
	}

	BfmeD3D8Vtable *d3d8Vtable = *reinterpret_cast<BfmeD3D8Vtable **>(d3d8);
	BfmeDeviceCaps caps;
	for (unsigned i = 0; i < sizeof(caps); ++i)
		reinterpret_cast<Byte *>(&caps)[i] = 0;
	d3d8Vtable->getDeviceCaps(d3d8, 0, 1, &caps);

	int pixelShaderVersion = caps.pixelShaderVersion & 0xffff;
	if (pixelShaderVersion >= 0x101)
		BfmeChipset = 3;
	if (pixelShaderVersion >= 0x104)
		BfmeChipset = 8;
	if (pixelShaderVersion >= 0x200)
		BfmeChipset = 9;
}
