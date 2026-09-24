// cl: /DNDEBUG /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib
// Retail 0x001A7A90 (311 bytes), __stdcall with four arguments.  It looks for
// a tree draw module among a template's draw modules and hands the shrub to
// TheTerrainVisual's slot 0x98 (Zero Hour's addTree arguments plus the
// template's shadow type, shadow texture name and the string at +0x20) under a
// fresh drawable ID; without one it reports "Shrub <name> requires a
// W3DTreeDrawModule.".  No caller or declaration names it, so the address
// stays.  Retail tests draw module 0 on every pass of the loop.

#include "ascii_string.h"

extern "C" void _ReadWriteBarrier(void);
extern "C" void _WriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
#pragma intrinsic(_WriteBarrier)

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef float Real;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GameCommon.h
struct Coord3D
{
	Coord3D(const Coord3D &that) : x(that.x), y(that.y), z(that.z) {}
	~Coord3D() {}

	Real x;
	Real y;
	Real z;
};

enum DrawableID
{
	INVALID_DRAWABLE_ID = 0
};

class Rva001A7A90TreeDrawData;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Module.h
class ModuleData
{
public:
	virtual void slot00() const;
	virtual void slot01() const;
	virtual void slot02() const;
	virtual void slot03() const;
	virtual void slot04() const;
	virtual void slot05() const;
	virtual void slot06() const;
	virtual void slot07() const;
	virtual void slot08() const;
	virtual const Rva001A7A90TreeDrawData *getAsW3DTreeDrawModuleData() const;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Module.h
class ModuleInfo
{
public:
	struct Nugget
	{
		unsigned char m_names[8];
		const ModuleData *second;
		unsigned char m_rest[8];
	};

	Int getCount() const
	{
		return (Int)(m_end - m_begin);
	}

	const ModuleData *getNthData(Int i) const
	{
		if ((UnsignedInt)i < (UnsignedInt)getCount())
			return m_begin[i].second;
		return 0;
	}

private:
	Nugget *m_begin;
	Nugget *m_end;
	Nugget *m_capacity;
};

struct Rva001A7A90StringData
{
	Int m_refCount;
	UnsignedShort m_length;
	UnsignedShort m_capacity;
	char m_text[1];
};

extern char Rva006A16B0Empty[];

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ThingTemplate.h
class ThingTemplate
{
public:
	const ModuleInfo &getDrawModuleInfo() const { return m_drawModuleInfo; }

	const char *getString20() const
	{
		return m_string20 ? m_string20->m_text : Rva006A16B0Empty;
	}

	unsigned char m_pad00[0x20];
	Rva001A7A90StringData *m_string20;
	unsigned char m_pad24[0x4c - 0x24];
	AsciiString m_shadowTextureName;
	unsigned char m_pad50[0x2a0 - 0x50];
	ModuleInfo m_drawModuleInfo;
	unsigned char m_pad2ac[0x482 - 0x2ac];
	UnsignedShort m_shadowType;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GameClient.h
class GameClient
{
protected:
	DrawableID allocDrawableID();

	friend void __stdcall Rva001A7A90AddShrub(const ThingTemplate *, const Coord3D *, Real, Real);
};

extern GameClient *TheGameClient;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/TerrainVisual.h
class TerrainVisual
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
	virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
	virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
	virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
	virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27();
	virtual void v28(); virtual void v29(); virtual void v30(); virtual void v31();
	virtual void v32(); virtual void v33(); virtual void v34(); virtual void v35();
	virtual void v36(); virtual void v37();
	virtual void addTree(DrawableID id, Coord3D location, Real scale, Real angle,
		Real randomScaleAmount, const Rva001A7A90TreeDrawData *data,
		Int shadowType, const AsciiString *shadowTextureName, const void *string20);
};

extern TerrainVisual *TheTerrainVisual;

class BfmeAwakenLog
{
public:
	virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
	virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
	virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
	virtual void v30(); virtual void v34(); virtual BfmeAwakenLog *v38(const char *message);
	virtual void v3c(); virtual void v40(); virtual void v44(); virtual void v48();
	virtual void v4c(int value);
};

class BfmeAwakenDebug
{
public:
	virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
	virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
	virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
	virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
	virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
	virtual void v50(); virtual void v54(); virtual void v58(); virtual void v5c();
	virtual void v60();
	virtual void v64(); virtual void v68();
	virtual BfmeAwakenLog *v6c(int first, int second);
};

extern BfmeAwakenDebug *TheBfmeAwakenDebug;

// Typed view of the debug manager's table for the slot +0x60 call: the
// second register parameter carries the table so it stays in EDX, as retail
// loads it (docs/shape_levers.md, vtable register-temp call shape).
typedef void (__fastcall *BfmeAwakenDebugSlot60)(BfmeAwakenDebug *self, void *const *table);
extern bool _bfme_debugReportingEnabled(void);
extern void _bfme_debugRecordCallsite(int kind);

// ?Rva001A7A90AddShrub@@YGXPBVThingTemplate@@PBUCoord3D@@MM@Z
void __stdcall Rva001A7A90AddShrub(const ThingTemplate *tmpl, const Coord3D *pos,
	Real angle, Real scale)
{
	const ModuleInfo &info = tmpl->getDrawModuleInfo();
	for (Int i = 0; i < info.getCount(); ++i)
	{
		const ModuleData *data = info.getNthData(0);
		if (!data)
			continue;

		const Rva001A7A90TreeDrawData *treeData = data->getAsW3DTreeDrawModuleData();
		if (treeData)
		{
			DrawableID id = TheGameClient->allocDrawableID();
			Int shadowType = tmpl->m_shadowType;
			TheTerrainVisual->addTree(id, *pos, scale, angle, 0, treeData,
				shadowType, &tmpl->m_shadowTextureName, &tmpl->m_string20);
			_ReadWriteBarrier();
			return;
		}
	}

	if (!_bfme_debugReportingEnabled())
	{
		_ReadWriteBarrier();
		return;
	}

	_bfme_debugRecordCallsite(1);
	{
		void *const *table = *(void *const *const *)TheBfmeAwakenDebug;
		((BfmeAwakenDebugSlot60)table[0x60 / 4])(TheBfmeAwakenDebug, table);
	}
	TheBfmeAwakenDebug->v6c(0, 0)->v38("Shrub ")->v38(tmpl->getString20())
		->v38(" requires a W3DTreeDrawModule.\n")->v4c(2);
	_WriteBarrier();
}
