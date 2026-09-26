// cl: /Igame/GameEngine/Source/Common/System /Igame/GameEngine/Include/Common /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWLib /DNDEBUG /MD /GX

#include "fx_particle_system.h"

namespace FXParticleSystem {

ConcreteModuleTemplate<ModuleTag<8, LIFE_EVENT_MODULE_KEY, LIFE_EVENT_MODULE_NAME, LifeEventModule, LifeEventModuleTemplate, ParticleLifeEventModule, ParticleLifeEventModuleTemplate> > &ConcreteModuleTemplate<ModuleTag<8, LIFE_EVENT_MODULE_KEY, LIFE_EVENT_MODULE_NAME, LifeEventModule, LifeEventModuleTemplate, ParticleLifeEventModule, ParticleLifeEventModuleTemplate> >::operator=(const ConcreteModuleTemplate<ModuleTag<8, LIFE_EVENT_MODULE_KEY, LIFE_EVENT_MODULE_NAME, LifeEventModule, LifeEventModuleTemplate, ParticleLifeEventModule, ParticleLifeEventModuleTemplate> > &that)
{
    ((LifeEventModuleTemplate *)this)->operator=(*(const LifeEventModuleTemplate *)&that);
    return *this;
}

}
