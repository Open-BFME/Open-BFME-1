// ??0ThingTemplate@@QAE@XZ
// BFME ThingTemplate default constructor, retail 0x00147600 (1718 bytes).
// Identity: ThingFactory::newOverride (matched, ThingFactory_newOverride.cpp)
// allocates the 0x4D4-byte object and calls this body through ILT 0x000343F9;
// the body installs vtable 0x01094988, the one the matched destructor at
// 0x00146BA0 (ThingTemplateBFMERetailDestructor.cpp) tears down. The member
// layout below is that destructor's, and the scalar tail keeps the names the
// matched copy assignment (ThingTemplateCopyAssignment.cpp) uses.
//
// Retail's EH state numbers count every destructible member in declaration
// order: 11 strings (states 0-10), the 5-string array, three strings, the
// literal-initialised string at +0x58, one more string, the geometry, then
// TWELVE vectors, six maps and the two-element array (state 0x25), so the
// vectors here are real STLport vectors, not 12-byte blobs, and the kind-of
// block and the +0x2F4 word are plain data.
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib
// stlport

#include <map>
#include <set>
#include <vector>
#include <string.h>

#include "ascii_string.h"

typedef char AsciiStringMustBeFourBytes[sizeof(AsciiString) == 4 ? 1 : -1];

// The four wide strings at +0x0C..+0x18 are UnicodeString in the matched
// destructor. Retail builds them with an in-place zero store and clears two of
// them at the end with direct calls to StringBase<unsigned short>::releaseBuffer
// (0x008881D0), the body every UnicodeString destructor spelling pins to.
class ThingTemplateUnicodeString
{
public:
	ThingTemplateUnicodeString() : m_data(0) {}
	~ThingTemplateUnicodeString();
	void clear();

private:
	void *m_data;
};

// Overridable: vptr, next override, override flag (the witnessed 0x0C base).
class Overridable
{
public:
	Overridable() : m_nextOverride(0), m_isOverride(false) {}
	virtual ~Overridable();

private:
	Overridable *m_nextOverride;
	bool m_isOverride;
};

enum GeometryType
{
	GEOMETRY_SPHERE = 0
};

class GeometryInfo
{
public:
	GeometryInfo(GeometryType type, bool isSmall, float height, float majorRadius, float minorRadius);
	virtual ~GeometryInfo();

private:
	unsigned char m_data[0x58];
};

// ZH's BitFlags wraps a std::bitset; retail zeroes the six words through a
// pointer copy and copies KINDOFMASK_NONE word by word, the shapes of an
// inlined memset and a memberwise copy.
template <unsigned N>
class BitFlags
{
public:
	BitFlags()
	{
		memset(m_words, 0, sizeof(m_words));
	}

private:
	unsigned int m_words[N / 32];
};
typedef BitFlags<192> KindOfBlock;
extern const KindOfBlock KINDOFMASK_NONE;

class Rva00146BA0AudioItem;

// 0x6D per-event slots, zeroed with one rep stosd; destroyed by the matched destructor.
class ThingTemplateAudioSlots
{
public:
	ThingTemplateAudioSlots()
	{
		for (int i = 0; i < 0x6D; ++i)
			m_items[i] = 0;
	}
	~ThingTemplateAudioSlots();

private:
	Rva00146BA0AudioItem *m_items[0x6D];
};

struct Rva00142250Nugget
{
	AsciiString m_first;
	AsciiString m_second;
	unsigned char m_opaque_008[12];
};

struct Rva001439F0Element
{
	unsigned char m_body[0x24];
	~Rva001439F0Element();
};

struct Rva00141A00Element
{
	virtual ~Rva00141A00Element();
	unsigned char m_opaque_004[0x58];
};

struct Payload12 { unsigned char m_body[12]; };
struct Payload236 { unsigned char m_body[0xEC]; };
struct Payload70 { unsigned char m_bytes[0x70]; };

// The array element at +0x364 (two of 0x14 bytes): its constructor and
// destructor are the pinned 0x0002FB80 / 0x0000E746 thunks the eh vector
// constructor iterator receives.
class Rva00146BA0ArrayItem
{
public:
	Rva00146BA0ArrayItem();
	~Rva00146BA0ArrayItem();

private:
	unsigned char m_data[0x14];
};

// Map node sizes read from the header allocations: 0x18 (int payload), 0x84
// (an AsciiString key with a 0x70-byte payload, allocated with operator new),
// 0x18 (AsciiString key, pointer payload) and 0x20 (12-byte payload).
typedef std::map<int, int> Map18;
typedef std::map<AsciiString, Payload70> Map84;
typedef std::map<AsciiString, void *> MapAscii18;
typedef std::map<int, Payload12> Map20;

class GlobalData
{
public:
	unsigned char m_opaque_000[0x1B4];
	unsigned int m_defaultOcclusionDelay;
	unsigned char m_opaque_1B8[0xCD0 - 0x1B8];
	unsigned int m_thingDefault0CD0;
	unsigned int m_thingDefault0CD4;
	unsigned int m_thingDefault0CD8;
};
extern GlobalData *TheWritableGlobalData;	// ?TheWritableGlobalData@@3PAVGlobalData@@A @ 0x012ED5C8
extern const char g_Rva0107301CEmptyString[];

class ThingTemplate : public Overridable
{
public:
	ThingTemplate();

protected:
	virtual ~ThingTemplate();

private:
	ThingTemplateUnicodeString m_displayName;
	ThingTemplateUnicodeString m_description;
	ThingTemplateUnicodeString m_recruitText;
	ThingTemplateUnicodeString m_reviveText;

	AsciiString m_hotkey;
	AsciiString m_nameString;
	AsciiString m_editorName;
	AsciiString m_defaultOwningSide;
	AsciiString m_commandSetString;
	AsciiString m_selectedPortraitImageName;
	AsciiString m_buttonImageName;
	AsciiString m_upgradeCameoUpgradeNames[5];
	AsciiString m_shadowTextureName;
	AsciiString m_unknownString50;
	AsciiString m_unknownString54;
	AsciiString m_experienceScalarTableName;
	AsciiString m_unknownString5c;

	GeometryInfo m_geometryInfo;
	std::vector<Rva00141A00Element> m_vector_0BC;
	KindOfBlock m_kindOf;
	ThingTemplateAudioSlots m_audioSlots;

	std::vector<Rva00142250Nugget> m_behaviorModuleInfo;
	std::vector<Rva00142250Nugget> m_drawModuleInfo;
	std::vector<Rva00142250Nugget> m_clientUpdateModuleInfo;
	std::vector<Rva00142250Nugget> m_clientBehaviorModuleInfo;
	std::vector<Rva001439F0Element> m_prereqInfo;
	std::vector<AsciiString> m_vector_2D0;
	std::vector<AsciiString> m_vector_2DC;
	std::vector<AsciiString> m_vector_2E8;
	unsigned int m_unknown2f4;
	std::vector<Payload236> m_vector_2F8;
	Map18 m_weaponTemplateSetFinder;
	std::vector<Payload12> m_vector_310;
	Map18 m_armorTemplateSetFinder;
	Map84 m_unitSpecificSounds;
	MapAscii18 m_unitSpecificFX;
	Map18 m_unknown340;
	Map20 m_unknown34c;
	std::vector<void *> m_vector_358;
	Rva00146BA0ArrayItem m_bfmeBVA[2];

	unsigned int m_scalar038c;
	unsigned int m_scalar0390;
	unsigned int m_scalar0394;
	unsigned int m_fenceWidth;
	unsigned int m_fenceXOffset;
	unsigned int m_scalar03a0;
	unsigned int m_visionRange;
	unsigned int m_shroudClearingRange;
	unsigned int m_scalar03ac;
	unsigned int m_placementViewAngle;
	unsigned int m_factoryExitWidth;
	unsigned int m_factoryExtraBibWidth;
	unsigned int m_buildTime;
	unsigned int m_assetScale;
	unsigned int m_instanceScaleFuzziness;
	unsigned int m_shadowSizeX;
	unsigned int m_shadowSizeY;
	unsigned int m_shadowOffsetX;
	unsigned int m_shadowOffsetY;
	unsigned int m_scalar03d8;
	unsigned int m_scalar03dc;
	unsigned int m_scalar03e0;
	unsigned int m_scalar03e4;
	unsigned int m_scalar03e8;
	unsigned int m_scalar03ec;
	unsigned int m_scalar03f0;
	unsigned int m_scalar03f4;
	unsigned int m_scalar03f8;
	unsigned int m_scalar03fc;
	unsigned int m_scalar0400;
	unsigned int m_scalar0404;
	unsigned int m_scalar0408;
	unsigned int m_scalar040c;
	unsigned int m_scalar0410;
	unsigned int m_scalar0414;
	unsigned int m_energyProduction;
	unsigned int m_energyBonus;
	unsigned int m_displayColor;
	unsigned int m_occlusionDelay;
	unsigned int m_scalar0428;
	unsigned int m_scalar042c;
	unsigned int m_scalar0430;
	unsigned int m_scalar0434;
	unsigned int m_scalar0438;
	unsigned int m_scalar043c;
	unsigned int m_scalar0440;
	unsigned int m_scalar0444;
	unsigned int m_scalar0448;
	unsigned int m_scalar044c;
	unsigned int m_scalar0450;
	unsigned int m_scalar0454;
	unsigned int m_scalar0458;
	unsigned int m_scalar045c;
	unsigned int m_scalar0460;
	unsigned int m_scalar0464;
	unsigned int m_scalar0468;
	unsigned int m_scalar046c;
	unsigned int m_scalar0470;
	unsigned int m_scalar0474;

	unsigned short m_short0478;
	unsigned short m_buildCost;
	unsigned short m_refundValue;
	unsigned short m_threatValue;
	unsigned short m_maxSimultaneousOfType;
	unsigned short m_shadowType;

	unsigned char m_isPrerequisite;
	unsigned char m_isBridge;
	unsigned char m_byte0486;
	unsigned char m_isTrainable;
	unsigned char m_isForbidden;
	unsigned char m_byte0489;
	unsigned char m_byte048a;
	unsigned char m_byte048b;
	unsigned char m_byte048c;
	unsigned char m_byte048d;
	unsigned char m_byte048e;
	unsigned char m_byte048f;
	unsigned char m_radarPriority;
	unsigned char m_transportSlotCount;
	unsigned char m_byte0492;
	unsigned char m_buildCompletion;
	unsigned char m_editorSorting;
	unsigned char m_byte0495;
	unsigned char m_byte0496;
	unsigned char m_structureRubbleHeight;
	unsigned char m_byte0498;
	unsigned char m_crusherLevel;
	unsigned char m_crushableLevel;
	char m_byte049b;
	char m_byte049c;
	unsigned char m_byte049d;
	unsigned char m_opaque_49e[2];

	unsigned int m_dword04a0;
	unsigned int m_dword04a4;
	unsigned int m_dword04a8;
	unsigned int m_dword04ac;
	unsigned char m_byte04b0;
	unsigned char m_byte04b1;
	unsigned char m_opaque_4b2[2];
	unsigned int m_dword04b4;
	unsigned int m_dword04b8;			// left uninitialised by the constructor
	unsigned int m_liveCameraOffset[3];	// +0x4BC..+0x4C4
	unsigned char m_byte04c8;
	unsigned char m_byte04c9;
	unsigned char m_byte04ca;
	unsigned char m_byte04cb;
	unsigned char m_byte04cc;
	unsigned char m_byte04cd;
	unsigned char m_opaque_4ce[2];
	unsigned int m_dword04d0;
};

typedef char ThingTemplateMustBe0x4D4[sizeof(ThingTemplate) == 0x4D4 ? 1 : -1];

ThingTemplate::ThingTemplate()
	: m_experienceScalarTableName(g_Rva0107301CEmptyString)
	, m_geometryInfo(GEOMETRY_SPHERE, false, 1.0f, 1.0f, 1.0f)
	, m_unknown2f4(0)
{
	m_scalar03ec = 0x3c23d70a;
	m_scalar03f0 = 0;
	m_scalar03f4 = 0;
	m_scalar03f8 = 0x3f800000;
	m_scalar03fc = 0x3f800000;
	m_scalar0400 = 0;
	m_scalar0404 = 0;
	m_scalar0408 = 0xbf800000;
	m_scalar0410 = 0x3fc00000;
	m_scalar0414 = 0x41200000;
	m_scalar0438 = 0;
	m_scalar0444 = 0;
	m_scalar044c = 0xffffffff;
	m_scalar0450 = 0xffffffff;
	m_scalar0454 = 0xffffffff;
	m_scalar0458 = 0xffffffff;
	m_scalar045c = 0xffffffff;
	m_scalar0470 = 0xffffffff;
	m_scalar0474 = 0xffffffff;
	m_editorSorting = 0;
	m_byte0495 = 0;
	m_byte0496 = 0;
	m_byte04c9 = 0;
	m_byte04cc = 1;
	m_byte04cd = 0;
	m_dword04d0 = 0x7fffffff;
	m_byte0498 = 0;
	m_radarPriority = 0;
	m_scalar038c = 0;
	m_transportSlotCount = 0;
	m_byte0492 = 0;
	m_fenceWidth = 0;
	m_fenceXOffset = 0;
	m_visionRange = 0;
	m_scalar03a0 = 0;
	m_shroudClearingRange = 0xbf800000;
	m_buildCost = 0;
	m_scalar0448 = 0;
	m_buildTime = 0x3f800000;
	m_refundValue = 0;
	m_energyProduction = 0;
	m_energyBonus = 0;
	m_displayColor = 0xffffffff;
	m_buildCompletion = 1;
	m_scalar0440 = 1;
	m_scalar043c = 1;
	m_isTrainable = 1;
	m_isForbidden = 0;
	m_short0478 = 0;
	m_kindOf = KINDOFMASK_NONE;
	m_assetScale = 0x3f800000;
	m_isBridge = 0;
	m_byte0486 = 0;
	m_isPrerequisite = 0;
	m_placementViewAngle = 0;
	m_factoryExitWidth = 0;
	m_factoryExtraBibWidth = 0;
	m_byte0489 = 0;
	m_byte048a = 0;
	m_byte048b = 0;
	m_byte048c = 0;
	m_scalar0390 = 0;
	m_scalar0394 = 0;
	m_liveCameraOffset[0] = 0;
	m_liveCameraOffset[1] = 0;
	m_liveCameraOffset[2] = 0;
	m_shadowType = 0;
	m_shadowSizeX = 0;
	m_shadowSizeY = 0;
	m_shadowOffsetX = 0;
	m_shadowOffsetY = 0;
	m_scalar0460 = 0;
	m_scalar03d8 = 0;
	m_scalar0464 = 0xff;
	m_scalar03dc = 0;
	m_scalar0468 = 0;
	m_scalar03e0 = 0;
	m_scalar03e4 = 0x41a00000;
	m_byte048d = 0;
	m_byte048e = 0;
	m_byte048f = 1;
	m_occlusionDelay = TheWritableGlobalData->m_defaultOcclusionDelay;
	m_structureRubbleHeight = 0;
	m_instanceScaleFuzziness = 0;
	m_threatValue = 0;
	m_scalar040c = 0xbf800000;
	m_maxSimultaneousOfType = 0;
	m_crusherLevel = 0;
	m_crushableLevel = 0x7f;
	m_byte049b = -1;
	m_byte049c = -1;
	m_byte049d = 1;
	m_dword04a0 = 0;
	m_dword04a4 = 0;
	m_scalar046c = 0;
	m_dword04a8 = 0;
	m_dword04ac = 0x3f800000;
	m_byte04b0 = 0;
	m_byte04b1 = 0;
	m_dword04b4 = 0;
	m_scalar03ac = 0;
	m_byte04cb = 0;
	m_byte04c8 = 0;
	m_byte04ca = 0;
	if (TheWritableGlobalData)
	{
		m_scalar0428 = TheWritableGlobalData->m_thingDefault0CD0;
		m_scalar03e8 = TheWritableGlobalData->m_thingDefault0CD4;
		m_scalar042c = TheWritableGlobalData->m_thingDefault0CD8;
	}
	else
	{
		m_scalar0428 = 50;
		m_scalar03e8 = 0x42480000;
		m_scalar042c = 10;
	}
	m_scalar0430 = 5;
	m_scalar0434 = 0;
	m_recruitText.clear();
	m_reviveText.clear();
	m_hotkey.clear();
}
