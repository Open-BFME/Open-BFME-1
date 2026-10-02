// cl: /Ob0 /DNDEBUG /MD /EHsc /DBFME_MODULE_NO_MPO /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
#define Matrix4x4 Matrix4
#include "W3DDevice/GameClient/Module/W3DLaserDraw.h"

// Upstream inline empty virtual overrides, each one byte in retail.
// Evidence: targets/game/reverse/identity_evidence/drawmodule-noop-overrides.md
// /Ob0 and qualified calls emit the header bodies. Anchors are not retail claims.

void rva00757B50Emission(W3DLaserDraw *self)
{
	self->W3DLaserDraw::releaseShadows();
}

void rva00757B60Emission(W3DLaserDraw *self)
{
	self->W3DLaserDraw::allocateShadows();
}

void rva00757BA0Emission(W3DLaserDraw *self)
{
	self->W3DLaserDraw::reactToGeometryChange();
}
