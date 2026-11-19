// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib
// stlport
// Open-BFME: W3DTerrainVisual::addProp, retail 0x00731B70 (397 bytes, ret 0x10).
// Identity: slot 32 of ??_7W3DTerrainVisual@@6BBfmeSnapshotBase@@@ (0x011212F0,
// entry 0x01121370 -> ILT 0x0002D1AA) and the Zero Hour twin in
// W3DTerrainVisual.cpp: snow/night model-condition state, the first draw
// module's model name, then BaseHeightMapRenderObjClass::addProp(1, *pos,
// angle, scale, modelName). BFME passes the scale in as a fourth argument
// instead of reading the template's asset scale.
// The ThingTemplate, ModuleData and GlobalData views are layout witnesses for
// this body only.

#include <bitset>
#include "ascii_string.h"

#include "../../../../GameEngine/Include/Common/ScalarTypes.h"



struct Coord3D
{
	Coord3D() {}
	Coord3D(const Coord3D &o) : x(o.x), y(o.y), z(o.z) {}
	Real x;
	Real y;
	Real z;
};

enum
{
	MODELCONDITION_NIGHT = 7,
	MODELCONDITION_SNOW = 8
};

enum
{
	WEATHER_SNOWY = 1,
	TIME_OF_DAY_NIGHT = 4
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/BitFlags.h
template <size_t NUMBITS>
class BitFlags
{
public:
	BitFlags() {}
	void clear() { m_bits.reset(); }
	void set(Int i, Int val = 1) { m_bits.set(i, val); }

private:
	_STL::bitset<NUMBITS> m_bits;
};

typedef BitFlags<304> ModelConditionFlags;

class GlobalData
{
public:
	char m_pad000[0x218];
	Int m_timeOfDay;	///< +0x218
	Int m_weather;		///< +0x21c
};
extern GlobalData *TheWritableGlobalData;

// Draw module data as this body uses it: virtual slot 8 (+0x20) returns the
// model name for a condition state, slot 12 (+0x30) an optional record whose
// model name sits at +8.
struct Rva00731B70NamedModuleData
{
	void *m_vtbl;
	Int m_field04;
	AsciiString m_modelName;
};

class Rva00731B70ModuleData
{
public:
	virtual void vslot00();
	virtual void vslot04();
	virtual void vslot08();
	virtual void vslot0C();
	virtual void vslot10();
	virtual void vslot14();
	virtual void vslot18();
	virtual void vslot1C();
	virtual AsciiString vslot20(const ModelConditionFlags &state) const;
	virtual void vslot24();
	virtual void vslot28();
	virtual void vslot2C();
	virtual const Rva00731B70NamedModuleData *vslot30() const;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Module.h
// ModuleInfo holds a vector of 20-byte nuggets with the data pointer at +8.
class ModuleInfo
{
public:
	struct Nugget
	{
		AsciiString first;
		AsciiString m_moduleTag;
		const Rva00731B70ModuleData *second;
		Int interfaceMask;
		Bool copiedFromDefault;
	};

	Int getCount() const { return m_infoEnd - m_info; }
	const Rva00731B70ModuleData *getNthData(Int i) const
	{
		if ((unsigned int)i < (unsigned int)(m_infoEnd - m_info))
			return m_info[i].second;
		return 0;
	}

private:
	Nugget *m_info;
	Nugget *m_infoEnd;
};

class ThingTemplate
{
public:
	static __forceinline const ModuleInfo &localDrawModuleInfo(const ThingTemplate *thing) { return thing->m_drawModuleInfo; }

private:
	char m_pad000[0x2a0];
	ModuleInfo m_drawModuleInfo;	///< +0x2a0
};

// Retail inlines StringBase<char>::isEmpty here; the tree's header keeps it
// out of line, so read the buffer header (length at +4) the same way.
static inline Bool inlineIsEmpty(const AsciiString &s)
{
	const char *text = *reinterpret_cast<const char *const *>(&s);
	return text == 0 || *reinterpret_cast<const unsigned short *>(text + 4) == 0;
}

class BaseHeightMapRenderObjClass
{
public:
	void addProp(Int id, Coord3D location, Real angle, Real scale, const AsciiString &modelName);
};

class W3DTerrainVisual
{
public:
	virtual void addProp(const ThingTemplate *tTemplate, const Coord3D *pos, Real angle, Real scale);

	char m_pad004[0xc];
	BaseHeightMapRenderObjClass *m_terrainRenderObject;	///< +0x10
};

void W3DTerrainVisual::addProp(const ThingTemplate *tTemplate, const Coord3D *pos, Real angle, Real scale)
{
	ModelConditionFlags state;
	state.clear();
	if (TheWritableGlobalData->m_weather == WEATHER_SNOWY)
		state.set(MODELCONDITION_SNOW);
	if (TheWritableGlobalData->m_timeOfDay == TIME_OF_DAY_NIGHT)
		state.set(MODELCONDITION_NIGHT);

	AsciiString modelName;
	const ModuleInfo &mi = ThingTemplate::localDrawModuleInfo(tTemplate);
	if (mi.getCount() > 0)
	{
		const Rva00731B70ModuleData *mdd = mi.getNthData(0);
		if (mdd)
		{
			modelName = mdd->vslot20(state);
			const Rva00731B70NamedModuleData *named = mdd->vslot30();
			if (named)
				modelName = named->m_modelName;
		}
	}

	if (m_terrainRenderObject && !inlineIsEmpty(modelName))
		m_terrainRenderObject->addProp(1, *pos, angle, scale, modelName);
}
