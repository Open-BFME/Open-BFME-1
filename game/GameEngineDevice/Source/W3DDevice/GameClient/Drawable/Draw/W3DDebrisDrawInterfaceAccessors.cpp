// cl: /Ob0 /DNDEBUG /MD /EHsc /DBFME_MODULE_NO_MPO /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
#define Matrix4x4 Matrix4
#include "W3DDevice/GameClient/Module/W3DDebrisDraw.h"
// The upstream inline overloads are the retail bodies (11 bytes each).
// BFME_MODULE_NO_MPO gives DrawModule its retail 12-byte base layout.
// /Ob0 and qualified calls force emission of both overloads without duplicating
// the upstream class. These two emission anchors are not retail claims.
// Identity: targets/game/reverse/identity_evidence/drawmodule-interface-accessors.md
DebrisDrawInterface *rva00750680Emission(W3DDebrisDraw *self)
{
    return self->W3DDebrisDraw::getDebrisDrawInterface();
}
const DebrisDrawInterface *rva00750690Emission(const W3DDebrisDraw *self)
{
    return self->W3DDebrisDraw::getDebrisDrawInterface();
}
