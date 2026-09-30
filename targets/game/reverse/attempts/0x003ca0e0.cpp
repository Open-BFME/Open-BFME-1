// ?d_003ca0e0@@YAXXZ
// partial score=0.3547 date=2026-09-30
// ?d_003ca0e0@@YAXXZ
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// LivingWorldRegionManager slot 3 (vtable 0x010EE010) xfer; 682 of 685 bytes, frame 0x0C matches.

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
	void *m_vtable;
	AsciiString m_name;
	char m_unmodelled00[0x28];
	LivingWorldRegionVector m_regions;
};

struct LivingWorldRegionArmy
{
	char m_unmodelled00[0x24];
};

extern void j_00002e46();

class LivingWorldRegion
{
public:
	void *m_vtable;
	AsciiString m_name;
	AsciiString m_mapName;
	char m_unmodelled0c[0x90];
	LivingWorldRegionArmy *m_armyBegin;
	LivingWorldRegionArmy *m_armyEnd;
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
};

extern Glo012F1028Type *Glo012F1028;

class Rva003968A0
{
public:
	bool test();
};

class Rva003C0110Owner
{
public:
	struct Rva003C0110ElementResult
	{
		char m_unmodelled00[0x40];
		AsciiString m_name;
	};
	Rva003C0110ElementResult *findByName(StringBase<char> *key);
};

class GameInfo
{
public:
	void setMap(AsciiString mapName);
};

extern GameInfo *g_012F7090;

class Glo012F1028Sub
{
public:
	void consume(AsciiString *campaignName);
};

class LivingWorldRegionManager
{
public:
	void rva003CA0E0(Xfer *xfer);
	LivingWorldRegion *rva003C8A50(const AsciiString &regionName);
	void rva003C8D50(Xfer *xfer);
	void transfer003C9EF0(Xfer *xfer);

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

typedef void (LivingWorldRegion::*RegionAsciiCall)(const AsciiString &);

static __forceinline void regionAsciiCall(LivingWorldRegion *region, void (*raw)(),
	const AsciiString &value)
{
	union { void (*plain)(); RegionAsciiCall member; } call;
	call.plain = raw;
	(region->*call.member)(value);
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

	if (version.m_currentVersion >= 2 && xfer->isLoading() && Glo012F1028 != 0
		&& Glo012F1028->m_flag2c && !Glo012F1028->m_flag2d)
	{
		m_enabled = 0;
	}

	AsciiString campaignName;
	if (xfer->isLoading())
	{
		m_currentCampaign = 0;
		xfer->xferAsciiString(&campaignName);
		((Glo012F1028Sub *)this)->consume(&campaignName);
	}
	else
	{
		campaignName = m_currentCampaign->m_name;
		xfer->xferAsciiString(&campaignName);
	}

	if (xfer->isLoading())
	{
		xfer->xferAsciiString(&campaignName);
		m_selectedRegion = rva003C8A50(campaignName);

		if (version.m_currentVersion >= 2 && m_selectedRegion == 0)
		{
			Glo012F1028Type *logic = Glo012F1028;
			if (logic != 0 && logic->m_flag2c
				&& !((Rva003968A0 *)logic)->test())
			{
				campaignName = logic->m_field30;
				m_selectedRegion = rva003C8A50(campaignName);
			}
		}

		rva003C8D50(xfer);

		LivingWorldRegion *region = m_selectedRegion;
		if (region != 0)
		{
			if (region->m_armyEnd - region->m_armyBegin != 0
				&& Glo012F1028 != 0 && Glo012F1028->m_flag2c
				&& !((Rva003968A0 *)Glo012F1028)->test())
			{
				Rva003C0110Owner::Rva003C0110ElementResult *found;
				{
					AsciiString key(region->m_fieldB8);
					found = ((Rva003C0110Owner *)Glo012F1028)->findByName(&key);
				}
				if (found != 0)
					regionAsciiCall(m_selectedRegion, j_00002e46, found->m_name);
				else
					regionAsciiCall(m_selectedRegion, j_00002e46, AsciiString::TheEmptyString);
			}

			if (g_012F7090 != 0)
			{
				const char *mapName = m_selectedRegion->m_mapName.str();
				AsciiString path;
				path.format("maps\\%s\\%s.map", mapName, mapName);
				g_012F7090->setMap(path);
			}
		}
	}
	else if (xfer->isSaving())
	{
		if (m_selectedRegion != 0)
			campaignName = m_selectedRegion->m_name;
		else
			campaignName = "";
		xfer->xferAsciiString(&campaignName);
		rva003C8D50(xfer);
	}

	transfer003C9EF0(xfer);
}
