// ?Rva00531DE0RefreshSelectedIndices@@YAHPAVGameWindow@@AAV?$vector@HV?$allocator@H@_STL@@@_STL@@@Z
// partial score=0.4 date=2026-09-21
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/ini /Iinputs/reference/shims/weapon /Iinputs/reference/shims/iniexception /Iinputs/reference/shims/ini_noinline /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
// Address-derived: no proven owner/name. Reloads the listbox's current
// selection into the caller's vector<Int> every pass (retail hoists the
// GadgetListBoxGetSelected call above the loop as invariant), stopping at
// the negative sentinel.
#include "PreRTS.h"

class GameWindow;

extern Int GadgetListBoxGetNumEntries( GameWindow *listbox );
extern void GadgetListBoxGetSelected( GameWindow *listbox, Int *selectList );

Int Rva00531DE0RefreshSelectedIndices( GameWindow *listbox, std::vector<Int> &vec )
{
	Int count = GadgetListBoxGetNumEntries( listbox );
	vec.clear();

	if ( count > 0 )
	{
		Int *selected;
		GadgetListBoxGetSelected( listbox, (Int *)&selected );

		for ( Int i = 0; i < count; ++i )
		{
			if ( selected[ i ] < 0 )
				break;

			vec.push_back( selected[ i ] );
		}
	}

	return (Int)vec.size();
}
