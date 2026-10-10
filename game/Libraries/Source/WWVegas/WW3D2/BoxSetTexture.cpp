// cl: /Igame/Libraries/Source/WWVegas/WW3D2 /DNDEBUG /DWIN32 /D_WINDOWS /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /MD /EHsc
#include "dx8wrapper.h"

// Retail 00905AC0 accesses RenderStateStruct::Textures at VA01340EC8
// (the matched render_state owner at VA01340EC0 +8), and the native
// DX8Wrapper dirty-state mask at VA0133F49C.
class Rva00905AC0 : public DX8Wrapper
{
public:
	using DX8Wrapper::render_state;
	using DX8Wrapper::render_state_changed;
};

// ?BoxSetTexture@@YAXIAAPAVTextureBaseClass@@@Z
void BoxSetTexture( unsigned int index, TextureBaseClass *&tex )
{
	if( tex != Rva00905AC0::render_state.Textures[ index ] )
	{
		if( tex )
			tex->Add_Ref();

		if( Rva00905AC0::render_state.Textures[ index ] )
			Rva00905AC0::render_state.Textures[ index ]->Release_Ref();

		Rva00905AC0::render_state.Textures[ index ] = tex;

		Rva00905AC0::render_state_changed |= 0x40 << index;
	}
}
