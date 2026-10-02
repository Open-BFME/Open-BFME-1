// cl: /Ob0 /DNDEBUG /MD /EHsc /DBFME_MODULE_NO_MPO /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
#define Matrix4x4 Matrix4
#include "Common/DrawModule.h"

// Retail DrawModule's inherited null interface getters (slots 38 through 45).
// Identity: targets/game/reverse/identity_evidence/drawmodule-interface-accessors.md
// /Ob0 and qualified calls emit the unmodified upstream inline bodies.
// The emission anchors below are not retail claims.

ObjectDrawInterface *rva007500E0Emission(DrawModule *self)
{
	return self->DrawModule::getObjectDrawInterface();
}

const ObjectDrawInterface *rva007500F0Emission(const DrawModule *self)
{
	return self->DrawModule::getObjectDrawInterface();
}

DebrisDrawInterface *rva00750100Emission(DrawModule *self)
{
	return self->DrawModule::getDebrisDrawInterface();
}

const DebrisDrawInterface *rva00750110Emission(const DrawModule *self)
{
	return self->DrawModule::getDebrisDrawInterface();
}

RopeDrawInterface *rva00750120Emission(DrawModule *self)
{
	return self->DrawModule::getRopeDrawInterface();
}

const RopeDrawInterface *rva00750130Emission(const DrawModule *self)
{
	return self->DrawModule::getRopeDrawInterface();
}

LaserDrawInterface *rva00750140Emission(DrawModule *self)
{
	return self->DrawModule::getLaserDrawInterface();
}

const LaserDrawInterface *rva00750150Emission(const DrawModule *self)
{
	return self->DrawModule::getLaserDrawInterface();
}
