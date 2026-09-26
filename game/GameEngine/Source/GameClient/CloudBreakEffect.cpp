// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/ini /Iinputs/reference/shims/iniexception /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
//
// The CloudBreakEffect block -- BFME-only, one AsciiString naming the sunbeam
// object. Same override bookkeeping as GlowEffect and friends in Drawable.cpp:
// copy saved into active, parse over active, write back only when this is not an
// override load. Two load types suppress the write-back, INI_LOAD_CREATE_OVERRIDES
// and BFME's fourth type with value 4.
//
// It then pokes the cloud system so the change takes effect, through vtable slot
// 9 as a tail call. Names: the block keyword gives the settings class; the two
// statics and the system pointer at 0x012F10F0 have no recoverable names, so
// those are ours. All three are DIR32 slots the verifier fills in from the
// target, so none of them affect the bytes.
//
// CloudEffect next door is the same shape. Its settings struct copies through a
// compiler-generated operator= that nothing in the image names - which is how
// it was landed: the generated body at 0x0040B430 spells the whole layout, so
// reconstructing the struct from it makes MSVC generate the same function and
// the pin names our own symbol. See CloudEffect.cpp.
#include "PreRTS.h"
#include "Common/INI.h"

static INILoadType retailLoadType( const INI *ini )
{
	struct RetailINI { char m_pad[ 0x08 ]; INILoadType m_loadType; };
	return reinterpret_cast<const RetailINI *>( ini )->m_loadType;
}

static const INILoadType INI_LOAD_BFME_TYPE_4 = (INILoadType)4;

struct CloudBreakEffect
{
	AsciiString m_sunbeamObject;		// 0x00  SunbeamObject

	static const FieldParse m_fieldParseTable[];
};

class CloudSystem
{
public:
	virtual void _bfme_pad_0() = 0;
	virtual void _bfme_pad_1() = 0;
	virtual void _bfme_pad_2() = 0;
	virtual void _bfme_pad_3() = 0;
	virtual void _bfme_pad_4() = 0;
	virtual void _bfme_pad_5() = 0;
	virtual void _bfme_pad_6() = 0;
	virtual void _bfme_pad_7() = 0;
	virtual void _bfme_pad_8() = 0;
	virtual void settingsChanged() = 0;		// slot 9, +0x24
};

extern CloudBreakEffect TheCloudBreakEffectSaved;		// 0x012F10F4
extern CloudBreakEffect TheCloudBreakEffectActive;		// 0x012F10F8
extern CloudSystem *TheCloudSystem;						// 0x012F10F0

void parseCloudBreakEffect( INI *ini )
{
	TheCloudBreakEffectActive = TheCloudBreakEffectSaved;
	ini->initFromINI( &TheCloudBreakEffectActive, CloudBreakEffect::m_fieldParseTable );

	const INILoadType loadType = retailLoadType( ini );
	if( loadType != INI_LOAD_CREATE_OVERRIDES && loadType != INI_LOAD_BFME_TYPE_4 )
		TheCloudBreakEffectSaved = TheCloudBreakEffectActive;

	if( TheCloudSystem )
		TheCloudSystem->settingsChanged();
}
