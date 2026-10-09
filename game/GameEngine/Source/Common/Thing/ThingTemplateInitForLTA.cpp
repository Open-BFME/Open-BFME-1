// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// stlport
//
// Retail 0x00147F10: ThingTemplate::initForLTA, the Zero Hour twin in
// ThingTemplate.cpp (GeneralsMD). Identity: the named lift row this body
// replaces and its matched ThingFactory callers; the body is the Zero Hour
// sequence (template and LTA names, three ModuleInfo clears, DestroyDie /
// InactiveBody / W3DDefaultDraw modules, defaults, display name, geometry).
//
// BFME differences: AsciiString::format takes its format by value; the
// armor/weapon "copied from default" bytes sit at +0x489/+0x48a; the rubble
// height default is gone and a byte at +0x497 is cleared instead; and a
// vector of 0x5C-byte polymorphic records at +0xBC is cleared at the end.
// Layout is BFME's, spelled TU-locally; ModuleInfo keeps the matched
// Zero Hour method names its callees are ledgered under.
#define _STLP_NO_EXCEPTIONS 1
#define __PLACEMENT_VEC_NEW_INLINE
#include "ascii_string.h"
#include "unicode_string.h"
#include <string.h>
#include <vector>

typedef int Int;
typedef bool Bool;
typedef float Real;

class INI;
class ModuleData;
class ThingTemplate;

enum ModuleType { MODULETYPE_BEHAVIOR = 0, MODULETYPE_DRAW = 1 };
enum
{
	MODULEINTERFACE_DIE = 0x02,
	MODULEINTERFACE_BODY = 0x20,
	MODULEINTERFACE_DRAW = 0x400
};
enum GeometryType { GEOMETRY_SPHERE = 0 };
enum ShadowType { SHADOW_VOLUME = 2 };

class ModuleFactory
{
public:
	ModuleData *newModuleDataFromINI( INI *ini, const AsciiString &name, ModuleType type, const AsciiString &moduleTag );
};
extern ModuleFactory *TheModuleFactory;

// The element type of ModuleInfo's vector, under the name its matched
// STLport __copy instance (0x0013EA50) is pinned as.
struct Rva001417F0ModuleInfo
{
	struct Nugget
	{
		AsciiString first;
		AsciiString m_moduleTag;
		const ModuleData *second;
		Int interfaceMask;
		Bool copiedFromDefault;
		Bool inheritable;
	};
};

class ModuleInfo
{
public:
	void addModuleInfo( ThingTemplate *thingTemplate, const AsciiString &name, const AsciiString &moduleTag,
		const ModuleData *data, Int interfaceMask, Bool inheritable, Bool overrideableByLikeKind );
	void clear( void ) { m_info.clear(); }

private:
	_STL::vector<Rva001417F0ModuleInfo::Nugget> m_info;
};

template <int NUMBITS> class BitFlags
{
public:
	unsigned int m_bits[6];							// BFME stores six words
};
typedef BitFlags<116> KindOfMaskType;

// The empty KindOf mask the whole game shares. Retail defines it once as
// `const BitFlags<192>` (mangled ?KINDOFMASK_NONE@@3V?$BitFlags@$0MA@@@B,
// VA 0x012ED8B8, 24 zero bytes) in Common/System/KindOf.cpp, so this is the
// only spelling that links in a retail-shaped build. This TU's own view type
// is BitFlags<116>, so the use below casts the address back to it; the byte
// gate masks DIR32 relocations, so the respelling is byte-neutral.
extern const BitFlags<192> KINDOFMASK_NONE;

class GeometryInfo
{
public:
	void set( GeometryType type, Bool isSmall, Real height, Real majorRadius, Real minorRadius );
};

// The 0x5C-byte polymorphic records ThingTemplate keeps at +0xBC. Their
// assignment is the out-of-line body at 0x00100300; nothing else in this
// body proves what they are.
struct Rva00147F10Record
{
	virtual ~Rva00147F10Record();
	Rva00147F10Record &operator=( const Rva00147F10Record &other );

	unsigned char m_body[0x58];
};

// AsciiString::str() as retail inlines it here: the buffer follows an
// eight-byte header, and an empty string reads the shared "".
static inline const char *bfmeStr( const AsciiString &s )
{
	const char *data = *(const char *const *)&s;
	return data ? data + 8 : "";
}

class ThingTemplate
{
public:
	void initForLTA( const AsciiString &name );

private:
	unsigned char m_pad000[0x0c];
	UnicodeString m_displayName;					// +0x00C
	unsigned char m_pad010[0x20 - 0x10];
	AsciiString m_nameString;						// +0x020
	unsigned char m_pad024[0x5c - 0x24];
	AsciiString m_LTAName;							// +0x05C
	GeometryInfo m_geometryInfo;					// +0x060
	unsigned char m_pad061[0xbc - 0x61];
	_STL::vector<Rva00147F10Record> m_records;		// +0x0BC
	KindOfMaskType m_kindof;						// +0x0C8
	unsigned char m_pad0e0[0x294 - 0xe0];
	ModuleInfo m_behaviorModuleInfo;				// +0x294
	ModuleInfo m_drawModuleInfo;					// +0x2A0
	ModuleInfo m_clientUpdateModuleInfo;			// +0x2AC
	unsigned char m_pad2b8[0x3c0 - 0x2b8];
	Real m_assetScale;								// +0x3C0
	Real m_instanceScaleFuzziness;					// +0x3C4
	unsigned char m_pad3c8[0x482 - 0x3c8];
	unsigned short m_shadowType;					// +0x482
	unsigned char m_pad484[0x489 - 0x484];
	Bool m_armorCopiedFromDefault;					// +0x489
	Bool m_weaponsCopiedFromDefault;				// +0x48A
	unsigned char m_pad48b[0x497 - 0x48b];
	Bool m_structureRubbleHeight;									// +0x497
};

void ThingTemplate::initForLTA( const AsciiString &name )
{
	m_nameString = name;

	char buffer[1024];
	strncpy(buffer, bfmeStr(name), sizeof(buffer));
	int i;
	for (i=0; buffer[i]; i++) {
		if (buffer[i] == '/') {
			i++;
			break;
		}
	}
	m_LTAName = AsciiString(buffer+i);

	m_behaviorModuleInfo.clear();
	m_drawModuleInfo.clear();
	m_clientUpdateModuleInfo.clear();

	AsciiString moduleTag;

	moduleTag.format( "LTA_%sDestroyDie", bfmeStr(m_LTAName) );
	m_behaviorModuleInfo.addModuleInfo(this, "DestroyDie", moduleTag, TheModuleFactory->newModuleDataFromINI(NULL, "DestroyDie", MODULETYPE_BEHAVIOR, moduleTag), (MODULEINTERFACE_DIE), false, false);

	moduleTag.format( "LTA_%sInactiveBody", bfmeStr(m_LTAName) );
	m_behaviorModuleInfo.addModuleInfo(this, "InactiveBody", moduleTag, TheModuleFactory->newModuleDataFromINI(NULL, "InactiveBody", MODULETYPE_BEHAVIOR, moduleTag), (MODULEINTERFACE_BODY), false, false);

	moduleTag.format( "LTA_%sW3DDefaultDraw", bfmeStr(m_LTAName) );
	m_drawModuleInfo.addModuleInfo(this, "W3DDefaultDraw", moduleTag, TheModuleFactory->newModuleDataFromINI(NULL, "W3DDefaultDraw", MODULETYPE_DRAW, moduleTag), (MODULEINTERFACE_DRAW), false, false);

	m_armorCopiedFromDefault = false;
	m_weaponsCopiedFromDefault = false;

	m_kindof = *(const KindOfMaskType *)&KINDOFMASK_NONE;
	m_assetScale = 1.0f;
	m_instanceScaleFuzziness = 0.0f;
	m_structureRubbleHeight = false;
	m_displayName.translate( name );
	m_shadowType = SHADOW_VOLUME;

	m_geometryInfo.set(GEOMETRY_SPHERE, false, 10.0, 10.0, 10.0);

	m_records.clear();
}
