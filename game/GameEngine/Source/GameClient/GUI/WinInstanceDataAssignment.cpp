// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/Generals/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/Generals/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/Generals/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/Generals/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/Generals/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/Generals/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/Generals/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/Generals/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/Generals/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/Generals/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/Generals/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/Generals/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/Generals/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
// Preserve the retail-proven implicit assignment at RVA 0x00478780 without
// linking the unrelated, incorrect GameWindow methods from its original TU.
// This retains an already verified base-Generals header instantiation, not a new
// port. The internal member-pointer anchor requests emission without a helper
// function; the compiler generates the same 999-byte assignment.
// Evidence: targets/game/reverse/identity_evidence/00479040-border-setter-link.md
#include "PreRTS.h"
#include "GameClient/WinInstanceData.h"

namespace {
typedef WinInstanceData &(WinInstanceData::*Assignment)(const WinInstanceData &);
Assignment Rva00478780Assignment = &WinInstanceData::operator=;
}
