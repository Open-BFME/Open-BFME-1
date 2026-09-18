// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/locomotor /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
//
// Locomotor/LocomotorSet accessors that need the corrected (single-vtable)
// BFME Locomotor layout to byte-match retail. The private
// /Ireference/shims/locomotor include makes only this TU see the
// reconstructed layout (see reference/shims/locomotor/GameLogic/Locomotor.h
// for the proof); every other TU including GameLogic/Locomotor.h -- notably
// Locomotor.cpp itself, whose ??1Locomotor@@MAE@XZ/??_GLocomotor@@MAEPAXI@Z
// rows are icf-owner claims against the ZH dual-vtable shape -- still
// resolves the real ZH-derived header. Split into its own TU (same pattern
// as ScriptEngineFields.cpp / GameWindowFields.cpp) specifically so that
// dropping Locomotor's Snapshot base here cannot change what Locomotor.cpp
// compiles for the implicit dtor/scalar-deleting-dtor.

#include "PreRTS.h"	// This must go first in EVERY cpp file in the GameEngine

#include "GameLogic/Locomotor.h"

//-------------------------------------------------------------------------------------------------
Locomotor* LocomotorSet::findLocomotor(LocomotorSurfaceTypeMask surfaceMask)
{
	for (LocomotorVector::iterator locomotorIt = m_locomotors.begin(); locomotorIt != m_locomotors.end(); ++locomotorIt)
	{
		Locomotor* locomotor = *locomotorIt;
		if (locomotor && (locomotor->getLegalSurfaces() & surfaceMask))
			return locomotor;
	}
	return NULL;
}
