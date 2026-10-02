// cl: /Ob0 /Iinputs/reference/shims/multiplayer /DNDEBUG /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// stlport
#include "PreRTS.h"
#include "Common/MultiplayerSettings.h"

// The existing BFME header keeps the upstream empty lifecycle overrides.
// Identity: targets/game/reverse/identity_evidence/subsystem-lifecycle-slots.md
// /Ob0 and qualified calls emit each inline body; anchors are not retail claims.

void rva0008F080Emission(MultiplayerSettings *self)
{
	self->MultiplayerSettings::init();
}

void rva0008F090Emission(MultiplayerSettings *self)
{
	self->MultiplayerSettings::update();
}

void rva0008F0A0Emission(MultiplayerSettings *self)
{
	self->MultiplayerSettings::reset();
}
