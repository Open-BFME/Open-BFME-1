// ?d_00147600@@YAXXZ
// partial score=0.24 date=2026-09-20
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ob1 /D_STLP_USE_STATIC_LIB /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// The BFME constructor uses the expanded 0x4d4-byte ThingTemplate layout.

#include <map>
#include <vector>
#include "Common/AsciiString.h"
#include "Common/UnicodeString.h"

template <typename T>
class StringBase
{
public:
	void releaseBuffer();
};

enum GeometryType
{
	GEOMETRY_SPHERE = 0
};

class GeometryInfo
{
public:
	GeometryInfo(GeometryType type, bool isSmall, float height,
		float majorRadius, float minorRadius);
	~GeometryInfo();

	unsigned char m_data[0x58];
};

class BFMERetailAsciiString
{
public:
	BFMERetailAsciiString() : m_data(0) {}
	BFMERetailAsciiString(const char *text);
	~BFMERetailAsciiString() { releaseBuffer(); }
	void releaseBuffer();

	void *m_data;
};

class Overridable
{
public:
	Overridable() : m_nextOverride(0), m_isOverride(false) {}
	~Overridable() {}

	unsigned int m_vftable;
	void *m_nextOverride;
	bool m_isOverride;
};

struct KindOfBlock
{
	KindOfBlock() : m0(0), m1(0), m2(0), m3(0), m4(0), m5(0) {}
	unsigned int m0;
	unsigned int m1;
	unsigned int m2;
	unsigned int m3;
	unsigned int m4;
	unsigned int m5;
};

struct Raw12
{
	Raw12() : m0(0), m1(0), m2(0) {}
	unsigned int m0;
	unsigned int m1;
	unsigned int m2;
};

class Rva0077CDE0ArrElem
{
public:
	Rva0077CDE0ArrElem();
	~Rva0077CDE0ArrElem();

	unsigned char m_data[0x14];
};

struct Payload12
{
	unsigned int m_words[3];
};

struct Payload70
{
	unsigned char m_bytes[0x70];
};

typedef std::map<int, int> Map18;
typedef std::map<int, Payload12> Map20;
typedef std::map<AsciiString, Payload70> Map84;
typedef std::map<AsciiString, void *> MapAscii18;

class ThingTemplate : public Overridable
{
public:
	ThingTemplate();

private:
	UnicodeString m_displayName;
	UnicodeString m_description;
	UnicodeString m_recruitText;
	UnicodeString m_reviveText;

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
	BFMERetailAsciiString m_experienceScalarTableName;
	AsciiString m_unknownString5c;

	GeometryInfo m_geometryInfo;
	std::vector<void *> m_unknownVector;
	KindOfBlock m_kindOf;
	unsigned int m_unknownE0[0x6d];

	Raw12 m_behaviorModuleInfo;
	Raw12 m_drawModuleInfo;
	Raw12 m_clientUpdateModuleInfo;
	Raw12 m_clientBehaviorModuleInfo;
	Raw12 m_unknownModule2c4;
	Raw12 m_unknownMid2d0;
	Raw12 m_unknownMid2dc;
	Raw12 m_unknownMid2e8;
	unsigned int m_unknown2f4;
	Raw12 m_unknown2f8;
	Map18 m_unknown304;
	Raw12 m_unknown310;
	Map18 m_unknown31c;
	Map84 m_unitSpecificSounds;
	MapAscii18 m_unitSpecificFX;
	Map18 m_unknown340;
	Map20 m_unknown34c;
	Raw12 m_browser;
	Rva0077CDE0ArrElem m_bfmeBVA[2];

	unsigned char m_tail[0x4d4 - 0x38c];
};

typedef char ThingTemplateSizeCheck[sizeof(ThingTemplate) == 0x4d4 ? 1 : -1];

ThingTemplate::ThingTemplate()
	: Overridable()
	, m_displayName()
	, m_description()
	, m_recruitText()
	, m_reviveText()
	, m_hotkey()
	, m_nameString()
	, m_editorName()
	, m_defaultOwningSide()
	, m_commandSetString()
	, m_selectedPortraitImageName()
	, m_buttonImageName()
	, m_upgradeCameoUpgradeNames()
	, m_shadowTextureName()
	, m_unknownString50()
	, m_unknownString54()
	, m_experienceScalarTableName((const char *)0x0107301c)
	, m_unknownString5c()
	, m_geometryInfo(GEOMETRY_SPHERE, false, 1, 1, 1)
	, m_unknownVector()
	, m_kindOf()
	, m_unknownE0()
	, m_behaviorModuleInfo()
	, m_drawModuleInfo()
	, m_clientUpdateModuleInfo()
	, m_clientBehaviorModuleInfo()
	, m_unknownModule2c4()
	, m_unknownMid2d0()
	, m_unknownMid2dc()
	, m_unknownMid2e8()
	, m_unknown2f4(0)
	, m_unknown2f8()
	, m_unknown304()
	, m_unknown310()
	, m_unknown31c()
	, m_unitSpecificSounds()
	, m_unitSpecificFX()
	, m_unknown340()
	, m_unknown34c()
	, m_browser()
	, m_bfmeBVA()
{
	*(volatile unsigned int *)this = 0x01094988;
	unsigned char *base = (unsigned char *)this;
	*(unsigned int *)(base + 0x3ec) = 0x3c23d70a;
	*(unsigned int *)(base + 0x3f0) = 0;
	*(unsigned int *)(base + 0x3f4) = 0;
	*(unsigned int *)(base + 0x3f8) = 1;
	*(unsigned int *)(base + 0x3fc) = 1;
	*(unsigned int *)(base + 0x400) = 0;
	*(unsigned int *)(base + 0x404) = 0;
	*(unsigned int *)(base + 0x408) = 0xffffffff;
	*(float *)(base + 0x410) = 1.5f;
	*(float *)(base + 0x414) = 10.0f;
	*(unsigned int *)(base + 0x438) = 0;
	*(unsigned int *)(base + 0x444) = 0;
	*(unsigned int *)(base + 0x44c) = 0xffffffff;
	*(unsigned int *)(base + 0x450) = 0xffffffff;
	*(unsigned int *)(base + 0x454) = 0xffffffff;
	*(unsigned int *)(base + 0x458) = 0xffffffff;
	*(unsigned int *)(base + 0x45c) = 0xffffffff;
	*(unsigned int *)(base + 0x470) = 0xffffffff;
	*(unsigned int *)(base + 0x474) = 0xffffffff;
	*(unsigned short *)(base + 0x47a) = 0;
	*(unsigned int *)(base + 0x448) = 0;
	*(unsigned int *)(base + 0x3bc) = 1;
	*(unsigned short *)(base + 0x47c) = 0;
	*(unsigned int *)(base + 0x418) = 0;
	*(unsigned int *)(base + 0x41c) = 0;
	*(unsigned int *)(base + 0x420) = 0xffffffff;
	*(unsigned char *)(base + 0x493) = 1;
	*(unsigned int *)(base + 0x440) = 1;
	*(unsigned int *)(base + 0x43c) = 1;
	*(unsigned char *)(base + 0x487) = 1;
	*(unsigned char *)(base + 0x488) = 0;
	*(unsigned short *)(base + 0x478) = 0;

	const unsigned int *kindOfGlobals = (const unsigned int *)0x012ed8b8;
	unsigned int *kindOfTarget = (unsigned int *)(base + 0xc8);
	kindOfTarget[0] = kindOfGlobals[0];
	kindOfTarget[1] = kindOfGlobals[1];
	kindOfTarget[2] = kindOfGlobals[2];
	kindOfTarget[3] = kindOfGlobals[3];
	kindOfTarget[4] = kindOfGlobals[4];
	kindOfTarget[5] = kindOfGlobals[5];

	*(unsigned int *)(base + 0x3c0) = 1;
	*(unsigned char *)(base + 0x485) = 0;
	*(unsigned char *)(base + 0x486) = 0;
	*(unsigned char *)(base + 0x484) = 0;
	*(unsigned int *)(base + 0x3b0) = 0;
	*(unsigned int *)(base + 0x3b4) = 0;
	*(unsigned int *)(base + 0x3b8) = 0;
	*(unsigned char *)(base + 0x489) = 0;
	*(unsigned char *)(base + 0x48a) = 0;
	*(unsigned char *)(base + 0x48b) = 0;
	*(unsigned char *)(base + 0x48c) = 0;
	*(unsigned int *)(base + 0x390) = 0;
	*(unsigned int *)(base + 0x394) = 0;
	*(unsigned int *)(base + 0x4bc) = 0;
	*(unsigned int *)(base + 0x4c0) = 0;
	*(unsigned int *)(base + 0x4c4) = 0;
	*(unsigned short *)(base + 0x482) = 0;
	*(unsigned int *)(base + 0x3c8) = 0;
	*(unsigned int *)(base + 0x3cc) = 0;
	*(unsigned int *)(base + 0x3d0) = 0;
	*(unsigned int *)(base + 0x3d4) = 0;
	*(unsigned int *)(base + 0x460) = 0;
	*(unsigned int *)(base + 0x3d8) = 0;
	*(unsigned int *)(base + 0x464) = 0xff;
	*(unsigned int *)(base + 0x3dc) = 0;
	*(unsigned int *)(base + 0x468) = 0;
	*(unsigned int *)(base + 0x3e0) = 0;
	*(float *)(base + 0x3e4) = 20.0f;
	*(unsigned char *)(base + 0x48d) = 0;
	*(unsigned char *)(base + 0x48e) = 0;
	*(unsigned char *)(base + 0x48f) = 1;
	*(unsigned char *)(base + 0x494) = 0;
	*(unsigned char *)(base + 0x495) = 0;
	*(unsigned char *)(base + 0x496) = 0;
	*(unsigned char *)(base + 0x498) = 0;
	*(unsigned char *)(base + 0x4c9) = 0;
	*(unsigned char *)(base + 0x4cc) = 1;
	*(unsigned char *)(base + 0x4cd) = 0;
	*(unsigned int *)(base + 0x4d0) = 0x7fffffff;

	unsigned char *writable = *(unsigned char **)0x012ed5c8;
	*(unsigned int *)(base + 0x424) = *(unsigned int *)(writable + 0x1b4);
	*(unsigned char *)(base + 0x490) = 0;
	*(unsigned char *)(base + 0x491) = 0;
	*(unsigned char *)(base + 0x492) = 0;
	*(unsigned char *)(base + 0x497) = 0;
	*(unsigned int *)(base + 0x3c4) = 0;
	*(unsigned short *)(base + 0x47e) = 0;
	*(unsigned short *)(base + 0x480) = 0;
	*(float *)(base + 0x40c) = -1.0f;
	*(unsigned char *)(base + 0x499) = 0;
	*(unsigned char *)(base + 0x49a) = 0x7f;
	*(unsigned char *)(base + 0x49b) = 0;
	*(unsigned char *)(base + 0x49c) = 0;
	*(unsigned char *)(base + 0x49d) = 1;
	*(unsigned int *)(base + 0x4a0) = 0;
	*(unsigned int *)(base + 0x4a4) = 0;
	*(unsigned int *)(base + 0x46c) = 0;
	*(unsigned int *)(base + 0x4a8) = 0;
	*(unsigned int *)(base + 0x4ac) = 1;
	*(unsigned char *)(base + 0x4b0) = 0;
	*(unsigned char *)(base + 0x4b1) = 0;
	*(unsigned int *)(base + 0x4b4) = 0;
	*(unsigned int *)(base + 0x3ac) = 0;
	*(unsigned char *)(base + 0x4cb) = 0;
	*(unsigned char *)(base + 0x4c8) = 0;
	*(unsigned char *)(base + 0x4ca) = 0;
	if (writable)
	{
		*(unsigned int *)(base + 0x428) = *(unsigned int *)(writable + 0xcd0);
		*(unsigned int *)(base + 0x3e8) = *(unsigned int *)(writable + 0xcd4);
		*(unsigned int *)(base + 0x42c) = *(unsigned int *)(writable + 0xcd8);
	}
	else
	{
		*(unsigned int *)(base + 0x428) = 50;
		*(float *)(base + 0x3e8) = 50.0f;
		*(unsigned int *)(base + 0x42c) = 10;
		*(unsigned int *)(base + 0x430) = 5;
	}
	*(unsigned int *)(base + 0x434) = 0;
	((StringBase<unsigned short> *)(base + 0x14))->releaseBuffer();
	((StringBase<unsigned short> *)(base + 0x18))->releaseBuffer();
	((BFMERetailAsciiString *)(base + 0x1c))->releaseBuffer();
}
