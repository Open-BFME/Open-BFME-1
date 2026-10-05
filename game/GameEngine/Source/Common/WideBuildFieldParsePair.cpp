// cl: /DNDEBUG /MD /EHsc -D_OPERATOR_NEW_DEFINED_ -D_STLP_USE_STATIC_LIB -D_STLP_NO_EXCEPTIONS -Iinputs/reference/shims/ini_bfme -Iinputs/reference/shims/sweep -Iinputs/reference/CnC_Generals_Zero_Hour/Generals/Code/GameEngine/Include -Iinputs/reference/CnC_Generals_Zero_Hour/Generals/Code/Libraries/Include
// stlport
// Thirty-three 35-byte __cdecl statics that append TWO tables instead of one:
//
//     push esi / mov esi,[esp+8]
//     push IMM8 / push offset TABLE_A / mov ecx,esi / call 0x00850920
//     push IMM8 / push offset TABLE_B / mov ecx,esi / call 0x00850920
//     pop esi / ret
//
// WHAT THE BYTES SHOW.  Same single __cdecl pointer argument and the same
// callee as the one-table builders in WideBuildFieldParse.cpp -- 0x00850920,
// the bounded pair-of-arrays appender (count at [this+0x80], refuses at 16,
// two 16-entry arrays at [this] and [this+0x40], ret 8).  BOTH calls in every
// one of the thirty-three members go to that same address; there is NO base
// class call here, so this is a builder that contributes two field-parse
// tables of its own rather than chaining to a parent.
//
// THE VARYING AXIS IS THE TWO IMM8 SECOND ARGUMENTS.  Everything else is
// either constant (both rel32 targets) or a DIR32 site read from retail (the
// two table addresses).  The observed second arguments are 0, 8, 16 and 40 --
// byte offsets added to every record's field offset, which is exactly what a
// shared sub-block of parse records embedded at a fixed offset needs.  One
// member (0x002D6D60) carries the shared table SECOND rather than first, and
// twenty-one of the 0x00427xxx members share one table as their second
// argument, which is what makes the "shared block plus own block" reading
// concrete rather than decorative.
//
// Builder names remain address-derived. Recovered tables use the verified
// FieldParse declarations below; the remaining tables are unresolved externs.
//
// The receiver stays spelled WideMulti because every member body here is
// matched under a name carrying it; respelling the parameter type would rename
// the enclosing bodies and unmatch those rows. The appender they call is
// retail's MultiIniFieldParse::add at 0x00850920, so the call goes through the
// defining class, taken from the real Common/INI.h.

#include "Common/INI.h"

class WideFieldParse
{
public:
	const char *m_token;
	void (*m_parse)();
	const void *m_userData;
	unsigned int m_offset;
};

class WideMulti
{
};

#define WIDE_FIELD_PARSE_PAIR( NAME, FIRST, SECOND )                      	extern const WideFieldParse WideTblA##NAME[];                         	extern const WideFieldParse WideTblB##NAME[];                         	class Rva##NAME                                                       	{                                                                     	public:                                                               		static void buildFieldParse( WideMulti &p );                      	};                                                                    	void Rva##NAME::buildFieldParse( WideMulti &p )                       	{                                                                     		MultiIniFieldParse &m = reinterpret_cast<MultiIniFieldParse &>( p ); 	m.add( reinterpret_cast<const FieldParse *>( WideTblA##NAME ), FIRST );	m.add( reinterpret_cast<const FieldParse *>( WideTblB##NAME ), SECOND );	}

// Retail tables and pointer spellings are verified in identity_evidence/010f2480-FXListFieldParse.md.
extern "C" void __identifier("?Rva00369AD0@@YAXPAVGen008509C0@@HPAVGen000140D8@@@Z")(INI *, int, void *);
extern "C" void __identifier("?parse@EvaParseMessageFromIniShim@@SAXPAVINI@@PAX1PBX@Z")(INI *, void *, void *, const void *);
extern "C" void __identifier("?parseAsciiString@INI@@SAXPAV1@PAX1PBX@Z")(INI *, void *, void *, const void *);
extern "C" void __identifier("?parseBool@INI@@SAXPAV1@PAX1PBX@Z")(INI *, void *, void *, const void *);
extern "C" void __identifier("?parseCoord2D@INI@@SAXPAV1@PAX1PBX@Z")(INI *, void *, void *, const void *);
extern "C" void __identifier("?parseCoord3D@INI@@SAXPAV1@PAX1PBX@Z")(INI *, void *, void *, const void *);
extern "C" void __identifier("?parseDurationUnsignedInt@INI@@SAXPAV1@PAX1PBX@Z")(INI *, void *, void *, const void *);
extern "C" void __identifier("?parseIndexList@INI@@SAXPAV1@PAX1PBX@Z")(INI *, void *, void *, const void *);
extern "C" void __identifier("?parsePercentToReal@INI@@SAXPAV1@PAX1PBX@Z")(INI *, void *, void *, const void *);
extern "C" void __identifier("?parseRGBColor@INI@@SAXPAV1@PAX1PBX@Z")(INI *, void *, void *, const void *);
extern "C" void __identifier("?parseReal@INI@@SAXPAV1@PAX1PBX@Z")(INI *, void *, void *, const void *);
extern "C" void __identifier("?parseUnsignedInt@INI@@SAXPAV1@PAX1PBX@Z")(INI *, void *, void *, const void *);
extern "C" void __identifier("?run@IniParseObjectFilterShim@@SAXPAVINI@@PAX1PBX@Z")(INI *, void *, void *, const void *);
extern const char *const DynamicDecalShaderNames012B52E0[];
extern const char *const BuffTypeNames010F04BC[];

extern const FieldParse FXNuggetFieldParse[] =
{
	{ "ObjectFilter", __identifier("?run@IniParseObjectFilterShim@@SAXPAVINI@@PAX1PBX@Z"), 0, 0xC },
	{ "SourceObjectFilter", __identifier("?run@IniParseObjectFilterShim@@SAXPAVINI@@PAX1PBX@Z"), 0, 0x8 },
	{ "RequiredSecondaryModelConditions", reinterpret_cast<INIFieldParseProc>(__identifier("?Rva00369AD0@@YAXPAVGen008509C0@@HPAVGen000140D8@@@Z")), 0, 0x60 },
	{ "ExcludedSecondaryModelConditions", reinterpret_cast<INIFieldParseProc>(__identifier("?Rva00369AD0@@YAXPAVGen008509C0@@HPAVGen000140D8@@@Z")), 0, 0x88 },
	{ "RequiredSourceModelConditions", reinterpret_cast<INIFieldParseProc>(__identifier("?Rva00369AD0@@YAXPAVGen008509C0@@HPAVGen000140D8@@@Z")), 0, 0x10 },
	{ "ExcludedSourceModelConditions", reinterpret_cast<INIFieldParseProc>(__identifier("?Rva00369AD0@@YAXPAVGen008509C0@@HPAVGen000140D8@@@Z")), 0, 0x38 },
	{ "StopIfNuggetPlayed", __identifier("?parseBool@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0xB0 },
	{ 0, 0, 0, 0 }
};

extern const FieldParse EvaEventFXNuggetFieldParse[] =
{
	{ "EvaEventOwner", __identifier("?parse@EvaParseMessageFromIniShim@@SAXPAVINI@@PAX1PBX@Z"), 0, 0xB4 },
	{ "EvaEventAlly", __identifier("?parse@EvaParseMessageFromIniShim@@SAXPAVINI@@PAX1PBX@Z"), 0, 0xB8 },
	{ "EvaEventEnemy", __identifier("?parse@EvaParseMessageFromIniShim@@SAXPAVINI@@PAX1PBX@Z"), 0, 0xBC },
	{ 0, 0, 0, 0 }
};

extern const FieldParse SoundFXNuggetFieldParse[] =
{
	{ "Name", __identifier("?parseAsciiString@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0xB4 },
	{ 0, 0, 0, 0 }
};

extern const FieldParse RayEffectFXNuggetFieldParse[] =
{
	{ "Name", __identifier("?parseAsciiString@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0xB4 },
	{ "PrimaryOffset", __identifier("?parseCoord3D@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0xB8 },
	{ "SecondaryOffset", __identifier("?parseCoord3D@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0xC4 },
	{ 0, 0, 0, 0 }
};

extern const FieldParse LightPulseFXNuggetFieldParse[] =
{
	{ "Color", __identifier("?parseRGBColor@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0xB4 },
	{ "Radius", __identifier("?parseReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0xC0 },
	{ "RadiusAsPercentOfObjectSize", __identifier("?parsePercentToReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0xC4 },
	{ "IncreaseTime", __identifier("?parseDurationUnsignedInt@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0xC8 },
	{ "DecreaseTime", __identifier("?parseDurationUnsignedInt@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0xCC },
	{ 0, 0, 0, 0 }
};

extern const FieldParse DynamicDecalFXNuggetFieldParse[] =
{
	{ "DecalName", __identifier("?parseAsciiString@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0xB4 },
	{ "Shader", __identifier("?parseIndexList@INI@@SAXPAV1@PAX1PBX@Z"), DynamicDecalShaderNames012B52E0, 0xB8 },
	{ "Size", __identifier("?parseReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0xBC },
	{ "Color", __identifier("?parseRGBColor@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0xC0 },
	{ "Offset", __identifier("?parseCoord2D@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0xCC },
	{ "OrientToObject", __identifier("?parseBool@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0xD4 },
	{ "OpacityStart", __identifier("?parseUnsignedInt@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0xD8 },
	{ "OpacityFadeTimeOne", __identifier("?parseReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0xDC },
	{ "OpacityPeak", __identifier("?parseUnsignedInt@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0xE0 },
	{ "OpacityPeakTime", __identifier("?parseReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0xE4 },
	{ "OpacityFadeTimeTwo", __identifier("?parseReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0xE8 },
	{ "OpacityEnd", __identifier("?parseUnsignedInt@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0xEC },
	{ "StartingDelay", __identifier("?parseReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0xF0 },
	{ "Lifetime", __identifier("?parseReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0xF4 },
	{ 0, 0, 0, 0 }
};

extern const FieldParse BuffNuggetFXNuggetFieldParse[] =
{
	{ "BuffType", __identifier("?parseIndexList@INI@@SAXPAV1@PAX1PBX@Z"), BuffTypeNames010F04BC, 0xB4 },
	{ "IsComplexBuff", __identifier("?parseBool@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0xB8 },
	{ "BuffThingTemplate", __identifier("?parseAsciiString@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0xC0 },
	{ "BuffOrcTemplate", __identifier("?parseAsciiString@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0xC4 },
	{ "BuffInfantryTemplate", __identifier("?parseAsciiString@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0xC8 },
	{ "BuffCavalryTemplate", __identifier("?parseAsciiString@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0xCC },
	{ "BuffTrollTemplate", __identifier("?parseAsciiString@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0xD0 },
	{ "BuffMumakilTemplate", __identifier("?parseAsciiString@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0xD4 },
	{ "BuffLifeTime", __identifier("?parseDurationUnsignedInt@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0xBC },
	{ "Extrusion", __identifier("?parseReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0xD8 },
	{ "Color", __identifier("?parseRGBColor@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0xDC },
	{ 0, 0, 0, 0 }
};

extern const FieldParse LaserFXNuggetFieldParse[] =
{
	{ "LaserName", __identifier("?parseAsciiString@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0xB4 },
	{ "LaserBackwards", __identifier("?parseBool@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0xB8 },
	{ "TargetPositionOffsetFallback", __identifier("?parseCoord3D@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0xBC },
	{ 0, 0, 0, 0 }
};

extern const FieldParse CameraShakerVolumeFXNuggetFieldParse[] =
{
	{ "Radius", __identifier("?parseReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0xC0 },
	{ "Duration_Seconds", __identifier("?parseReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0xC4 },
	{ "Amplitude_Degrees", __identifier("?parseReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0xC8 },
	{ 0, 0, 0, 0 }
};
#define NAMED_FIELD_PARSE_PAIR(NAME, TABLE_A, TABLE_B) \
    class Rva##NAME { public: static void buildFieldParse(WideMulti &p); }; \
    void Rva##NAME::buildFieldParse(WideMulti &p) \
    { \
        MultiIniFieldParse &m = reinterpret_cast<MultiIniFieldParse &>(p); \
        m.add(TABLE_A, 0); \
        m.add(TABLE_B, 0); \
    }

WIDE_FIELD_PARSE_PAIR( 001246A0, 8, 0 )
WIDE_FIELD_PARSE_PAIR( 001FAB70, 8, 0 )
WIDE_FIELD_PARSE_PAIR( 002800A0, 40, 0 )
WIDE_FIELD_PARSE_PAIR( 002D2E80, 8, 0 )
WIDE_FIELD_PARSE_PAIR( 002D37D0, 8, 0 )
WIDE_FIELD_PARSE_PAIR( 002D3E00, 8, 0 )
WIDE_FIELD_PARSE_PAIR( 002D4170, 8, 0 )
WIDE_FIELD_PARSE_PAIR( 002D4B00, 8, 0 )
WIDE_FIELD_PARSE_PAIR( 002D4FA0, 8, 0 )
WIDE_FIELD_PARSE_PAIR( 002D5580, 8, 0 )
WIDE_FIELD_PARSE_PAIR( 002D5EE0, 8, 0 )
WIDE_FIELD_PARSE_PAIR( 002D66A0, 8, 0 )
WIDE_FIELD_PARSE_PAIR( 002D6D60, 0, 16 )
WIDE_FIELD_PARSE_PAIR( 002D7740, 8, 0 )
WIDE_FIELD_PARSE_PAIR( 002D7A70, 8, 0 )
WIDE_FIELD_PARSE_PAIR( 002D9310, 8, 0 )
WIDE_FIELD_PARSE_PAIR( 002D93B0, 8, 0 )
WIDE_FIELD_PARSE_PAIR( 002D9730, 8, 0 )
NAMED_FIELD_PARSE_PAIR( 00427490, EvaEventFXNuggetFieldParse, FXNuggetFieldParse )
NAMED_FIELD_PARSE_PAIR( 004274C0, SoundFXNuggetFieldParse, FXNuggetFieldParse )
NAMED_FIELD_PARSE_PAIR( 004274F0, RayEffectFXNuggetFieldParse, FXNuggetFieldParse )
NAMED_FIELD_PARSE_PAIR( 00427520, LightPulseFXNuggetFieldParse, FXNuggetFieldParse )
NAMED_FIELD_PARSE_PAIR( 00427550, DynamicDecalFXNuggetFieldParse, FXNuggetFieldParse )
NAMED_FIELD_PARSE_PAIR( 00427580, BuffNuggetFXNuggetFieldParse, FXNuggetFieldParse )
NAMED_FIELD_PARSE_PAIR( 004275B0, LaserFXNuggetFieldParse, FXNuggetFieldParse )
NAMED_FIELD_PARSE_PAIR( 004275E0, CameraShakerVolumeFXNuggetFieldParse, FXNuggetFieldParse )
extern const WideFieldParse WideTblA00427640[];
NAMED_FIELD_PARSE_PAIR( 00427640, reinterpret_cast<const FieldParse *>(WideTblA00427640), FXNuggetFieldParse )
extern const WideFieldParse WideTblA00427780[];
NAMED_FIELD_PARSE_PAIR( 00427780, reinterpret_cast<const FieldParse *>(WideTblA00427780), FXNuggetFieldParse )
extern const WideFieldParse WideTblA004277B0[];
NAMED_FIELD_PARSE_PAIR( 004277B0, reinterpret_cast<const FieldParse *>(WideTblA004277B0), FXNuggetFieldParse )
extern const WideFieldParse WideTblA004277E0[];
NAMED_FIELD_PARSE_PAIR( 004277E0, reinterpret_cast<const FieldParse *>(WideTblA004277E0), FXNuggetFieldParse )
extern const WideFieldParse WideTblA00427810[];
NAMED_FIELD_PARSE_PAIR( 00427810, reinterpret_cast<const FieldParse *>(WideTblA00427810), FXNuggetFieldParse )
extern const WideFieldParse WideTblA00427C80[];
NAMED_FIELD_PARSE_PAIR( 00427C80, reinterpret_cast<const FieldParse *>(WideTblA00427C80), FXNuggetFieldParse )
extern const WideFieldParse WideTblA00427CB0[];
NAMED_FIELD_PARSE_PAIR( 00427CB0, reinterpret_cast<const FieldParse *>(WideTblA00427CB0), FXNuggetFieldParse )
