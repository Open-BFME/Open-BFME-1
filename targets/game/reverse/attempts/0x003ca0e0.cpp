// ?d_003ca0e0@@YAXXZ
// partial score=0.37 date=2026-09-23
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib

#include "ascii_string.h"

typedef unsigned char UnsignedByte;
typedef bool Bool;

struct XferVersion
{
	UnsignedByte m_version;
	UnsignedByte m_currentVersion;
};

class Xfer
{
public:
	virtual void _pad00();
	virtual Bool isLoading();
	virtual Bool isSaving();
	virtual void _pad03(); virtual void _pad04(); virtual void _pad05();
	virtual void _pad06(); virtual void _pad07(); virtual void _pad08();
	virtual void _pad09();
	virtual void xferVersion(XferVersion *version);
	virtual void _pad0b(); virtual void _pad0c(); virtual void _pad0d();
	virtual void _pad0e(); virtual void _pad0f(); virtual void _pad10();
	virtual void _pad11(); virtual void _pad12(); virtual void _pad13();
	virtual void _pad14(); virtual void _pad15(); virtual void _pad16();
	virtual void _pad17(); virtual void _pad18(); virtual void _pad19();
	virtual void xferAsciiString(AsciiString *value);
	virtual void _pad1b(); virtual void _pad1c(); virtual void _pad1d();
	virtual void xferInt(int *value);
	virtual void _pad1f(); virtual void _pad20(); virtual void _pad21();
	virtual void _pad22();
	virtual void xferByte(UnsignedByte *value);
};

struct LivingWorldRegionVector
{
	void *m_begin;
	void *m_end;
	void *m_capacity;
};

class LivingWorldRegionCampaign
{
public:
	char m_unmodelled00[0x30];
	LivingWorldRegionVector m_regions;
	AsciiString m_name;
};

class LivingWorldRegion
{
public:
	void *m_vtable;
	AsciiString m_name;
	char m_unmodelled0c[0x94];
	void **m_armyBegin;
	void **m_armyEnd;
	char m_unmodelleda4[0x14];
	AsciiString m_fieldB8;
};

class Glo012F1028Type
{
public:
	char m_unmodelled00[0x2c];
	UnsignedByte m_flag2c;
	UnsignedByte m_flag2d;
	char m_unmodelled2e[2];
	AsciiString m_field30;

	Bool test();
};

extern Glo012F1028Type *Glo012F1028;

class LivingWorldRegionManager
{
public:
	void rva003CA0E0(Xfer *xfer);

private:
	void *m_vtable;
	LivingWorldRegionCampaign *m_currentCampaign;
	LivingWorldRegion *m_selectedRegion;
	int m_unmodelled0c;
	UnsignedByte m_enabled;
	char m_unmodelled11[3];
	LivingWorldRegionVector m_regions;
	int m_nextHandle;
	void *m_resource;
	void *m_campaignBegin;
	void *m_campaignEnd;
};

extern void j_00002e46();
extern void j_0000bb81();
extern void j_0001b5db();
extern void j_00028bb9();
extern void j_0002bf0d();
extern void j_00032a56();
extern void j_0003ac9c();
extern void j_00045b88();
extern void j_0004704b();

typedef void (LivingWorldRegionManager::*ManagerAsciiCall)(AsciiString *);
typedef LivingWorldRegion *(LivingWorldRegionManager::*ManagerLookupCall)(const AsciiString &);
typedef void (LivingWorldRegionManager::*ManagerXferCall)(Xfer *);
typedef Bool (Glo012F1028Type::*GuardCall)();
typedef void *(Glo012F1028Type::*FindCall)(AsciiString *);
typedef void (LivingWorldRegion::*RegionAsciiCall)(const AsciiString &);
typedef void (Glo012F1028Type::*MapCall)(AsciiString);

static __forceinline void managerAsciiCall(
	LivingWorldRegionManager *manager, void (*raw)(), AsciiString *value)
{
	union { void (*plain)(); ManagerAsciiCall member; } call;
	call.plain = raw;
	(manager->*call.member)(value);
}

static __forceinline LivingWorldRegion *managerLookupCall(
	LivingWorldRegionManager *manager, void (*raw)(), const AsciiString &value)
{
	union { void (*plain)(); ManagerLookupCall member; } call;
	call.plain = raw;
	return (manager->*call.member)(value);
}

static __forceinline void managerXferCall(
	LivingWorldRegionManager *manager, void (*raw)(), Xfer *xfer)
{
	union { void (*plain)(); ManagerXferCall member; } call;
	call.plain = raw;
	(manager->*call.member)(xfer);
}

static __forceinline Bool guardCall(Glo012F1028Type *guard, void (*raw)())
{
	union { void (*plain)(); GuardCall member; } call;
	call.plain = raw;
	return (guard->*call.member)();
}

static __forceinline void *findCall(
	Glo012F1028Type *owner, void (*raw)(), AsciiString *value)
{
	union { void (*plain)(); FindCall member; } call;
	call.plain = raw;
	return (owner->*call.member)(value);
}

static __forceinline void regionAsciiCall(
	LivingWorldRegion *region, void (*raw)(), const AsciiString &value)
{
	union { void (*plain)(); RegionAsciiCall member; } call;
	call.plain = raw;
	(region->*call.member)(value);
}

static __forceinline void mapCall(Glo012F1028Type *owner, void (*raw)(),
	AsciiString value)
{
	union { void (*plain)(); MapCall member; } call;
	call.plain = raw;
	(owner->*call.member)(value);
}

// ?rva003CA0E0@LivingWorldRegionManager@@QAEXPAVXfer@@@Z
void LivingWorldRegionManager::rva003CA0E0(Xfer *xfer)
{
	XferVersion version;
	version.m_version = 1;
	version.m_currentVersion = 2;
	xfer->xferVersion(&version);
	xfer->xferByte(&m_enabled);
	xfer->xferInt(&m_nextHandle);

	if (version.m_currentVersion >= 2 && xfer->isLoading())
	{
		if (Glo012F1028 != 0 && Glo012F1028->m_flag2c != 0
			&& Glo012F1028->m_flag2d == 0)
		{
			m_enabled = 0;
		}
	}

	AsciiString campaignName;
	if (xfer->isLoading())
	{
		xfer->xferAsciiString(&campaignName);
		managerAsciiCall(this, j_00045b88, &campaignName);
	}
	else
	{
		if (m_currentCampaign != 0)
			campaignName = m_currentCampaign->m_name;
		xfer->xferAsciiString(&campaignName);
	}

	if (xfer->isLoading())
	{
		xfer->xferAsciiString(&campaignName);
		m_selectedRegion = managerLookupCall(this, j_0002bf0d,
			campaignName);

		if (version.m_currentVersion >= 2 && m_selectedRegion == 0
			&& Glo012F1028 != 0 && Glo012F1028->m_flag2c != 0
			&& !guardCall(Glo012F1028, j_0000bb81))
		{
			campaignName = Glo012F1028->m_field30;
			m_selectedRegion = managerLookupCall(this, j_0002bf0d,
				campaignName);
		}

		managerXferCall(this, j_0003ac9c, xfer);

		LivingWorldRegion *region = m_selectedRegion;
		if (region != 0)
		{
			unsigned int count = (unsigned int)(
				((char *)region->m_armyEnd - (char *)region->m_armyBegin)
				/ 0x40);
			if (count != 0 && Glo012F1028 != 0
				&& Glo012F1028->m_flag2c != 0
				&& !guardCall(Glo012F1028, j_0000bb81))
			{
				AsciiString roomName(region->m_fieldB8);
				void *found = findCall(Glo012F1028, j_00032a56, &roomName);
				if (found != 0)
					regionAsciiCall(region, j_00002e46,
						*(const AsciiString *)((char *)found + 0x40));
				else
					regionAsciiCall(region, j_00002e46,
						*(const AsciiString *)0x01336E50);
			}

			if (*(void **)0x012F7090 != 0)
			{
				void *value = *(void **)((char *)region + 8);
				const char *first = (const char *)0x0107388B;
				if (value != 0)
				{
					value = *(void **)((char *)value + 8);
					if (value != 0)
						first = (const char *)((char *)value + 8);
				}

				AsciiString mapName;
				mapName.format(AsciiString((const char *)0x010EE048),
					(const char *)0x0107388B, (const char *)0x0107388B,
					first);
				mapCall(*(Glo012F1028Type **)0x012F7090, j_0001b5db, mapName);
			}
		}
	}
	else if (xfer->isSaving())
	{
		if (m_selectedRegion != 0)
			campaignName = m_selectedRegion->m_name;
		else
			campaignName = (const char *)0x0107301C;
		xfer->xferAsciiString(&campaignName);
		managerXferCall(this, j_0003ac9c, xfer);
	}

	managerXferCall(this, j_0004704b, xfer);
}
