// cl: /DNDEBUG /DWIN32 /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
#include "PreRTS.h"
#include "GameLogic/AIStateMachine.h"

class AIInternalMoveToStateOnExitShim
{
public:
 void onExit(StateExitType status);
};

// Identity and complete boundaries: identity_evidence/0017a5f0-0017f110-state-exit.md.
// BFME storage views: the included Zero Hour header has different offsets.
struct Rva0017A5F0MachineView
{
 unsigned char m_unreconstructed00[0x40];
 bool m_locked;
};
struct Rva0017A5F0StateView
{
 unsigned char m_unreconstructed00[0x1c];
 Rva0017A5F0MachineView *m_machine;
};

void AIMoveAndDeleteState::onExit(StateExitType status)
{
 reinterpret_cast<Rva0017A5F0StateView *>(this)->m_machine->m_locked = false;
 reinterpret_cast<AIInternalMoveToStateOnExitShim *>(this)->onExit(status);
}

class Rva0017F110
{
public:
 virtual void method(StateExitType status);
};
void Rva0017F110::method(StateExitType status)
{
 reinterpret_cast<Rva0017A5F0StateView *>(this)->m_machine->m_locked = false;
 reinterpret_cast<AIInternalMoveToStateOnExitShim *>(this)->onExit(status);
}
