// cl: /DNDEBUG /MD /EHsc
// Lift the ObjectDefectionHelper::ObjectDefectionHelper(Thing*, const
// ModuleData*) constructor to clean C++. Retail forwards both arguments
// unchanged to the base ObjectHelper ctor (this is cached in esi across the
// call), zeroes the four timer/flag members the header initializes in its
// body, then restamps this class's own three vtable pointers (offsets
// 0x00, 0x0C, 0x10) over whatever the base ctor left there.

class Thing;
class ModuleData;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/ObjectHelper.h
class ObjectHelper
{
public:
	ObjectHelper(Thing *, const ModuleData *);	///< pinned at 0x00021BE8
};

extern "C" char ObjectDefectionHelper_vtbl0;	///< retail 0x0109E574
extern "C" char ObjectDefectionHelper_vtbl0C;	///< retail 0x0109E4B0
extern "C" char ObjectDefectionHelper_vtbl10;	///< retail 0x0109E4A0

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/ObjectDefectionHelper.h
class ObjectDefectionHelper : public ObjectHelper
{
public:
	ObjectDefectionHelper(Thing *thing, const ModuleData *modData);

private:
	unsigned char m_unreconstructed_00[0x20];		///< base ObjectHelper region, including the two vtable slots restamped below
	unsigned int  m_defectionDetectionStart;		///< retail this+0x20
	unsigned int  m_defectionDetectionEnd;			///< retail this+0x24
	float         m_defectionDetectionFlashPhase;	///< retail this+0x28
	bool          m_doDefectorFX;					///< retail this+0x2C
};

// ??0ObjectDefectionHelper@@QAE@PAVThing@@PBVModuleData@@@Z
ObjectDefectionHelper::ObjectDefectionHelper(Thing *thing, const ModuleData *modData) :
	ObjectHelper(thing, modData)
{
	m_defectionDetectionEnd = 0;
	m_defectionDetectionFlashPhase = 0.0f;
	m_defectionDetectionStart = 0;
	m_doDefectorFX = false;

	*reinterpret_cast<char **>(this) = &ObjectDefectionHelper_vtbl0;
	*reinterpret_cast<char **>(reinterpret_cast<char *>(this) + 0x0C) = &ObjectDefectionHelper_vtbl0C;
	*reinterpret_cast<char **>(reinterpret_cast<char *>(this) + 0x10) = &ObjectDefectionHelper_vtbl10;
}
