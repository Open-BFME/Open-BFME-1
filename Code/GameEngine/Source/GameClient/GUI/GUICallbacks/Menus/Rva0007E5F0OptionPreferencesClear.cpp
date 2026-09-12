// stlport
// Retail RVA 0x0007E5F0 / 758 bytes. Identity remains address-derived: the sole named caller is OptionsMenuInit, which passes this+0x260.
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/campaignmanagerascii /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWLib

#include "PreRTS.h"
#include "Common/UserPreferences.h"

void Rva0007E5F0OptionPreferencesClear(OptionPreferences *o)
{
	{
		AsciiString s("TextureReduction");
		o->erase(s);
	}
	{
		AsciiString s("3DShadows");
		o->erase(s);
	}
	{
		AsciiString s("2DShadows");
		o->erase(s);
	}
	{
		AsciiString s("UsePixelShader");
		o->erase(s);
	}
	{
		AsciiString s("BuildingOcclusion");
		o->erase(s);
	}
	{
		AsciiString s("MaxParticleCount");
		o->erase(s);
	}
	{
		AsciiString s("DynamicLOD");
		o->erase(s);
	}
	{
		AsciiString s("FPSLimit");
		o->erase(s);
	}
	{
		AsciiString s("TerrainLighting");
		o->erase(s);
	}
	{
		AsciiString s("AnisotropicTextureFiltering");
		o->erase(s);
	}
	{
		AsciiString s("SmoothWaterBorder");
		o->erase(s);
	}
	{
		AsciiString s("ExtraAnimations");
		o->erase(s);
	}
	{
		AsciiString s("GrassDrawSkip");
		o->erase(s);
	}
	{
		AsciiString s("UseHighQualityVideo");
		o->erase(s);
	}
	{
		AsciiString s("ShowProps");
		o->erase(s);
	}
}

