// ?Rva00531DE0RefreshSelectedIndices@@YAHPAVGameWindow@@AAV?$vector@HV?$allocator@H@_STL@@@_STL@@@Z
// partial score=0.4 date=2026-09-21
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/ini /Ireference/shims/weapon /Ireference/shims/iniexception /Ireference/shims/ini_noinline /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
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
