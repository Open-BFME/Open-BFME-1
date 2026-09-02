// ??0DefaultPhysicsModuleInfo@FXParticleSystem@@QAE@XZ
// partial score=0.55 date=2026-09-01
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include/Common /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWLib

#include "fx_particle_system.h"

namespace FXParticleSystem {

DefaultPhysicsModuleInfo::DefaultPhysicsModuleInfo()
	: m_field0(0.0f), m_field1(0.0f), m_field2(0.0f), m_field3(0)
{
	m_var1.setRange(0.0f, 0.0f, GameClientRandomVariable::UNIFORM);
}

}

