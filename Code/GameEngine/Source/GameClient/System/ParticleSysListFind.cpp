// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// stlport
//
// ParticleSys.cpp stopped emitting STLport's generic __find over the
// particle-system list when friend_removeParticleSystem moved to its
// intrusive-list rewrite, but retail still carries the 36-byte helper at
// 0x0014AA80. This TU exists solely to re-emit that instantiation.
#include <list>
#include <algorithm>

class ParticleSystem;

typedef _STL::list<ParticleSystem *> ParticleSystemList;

ParticleSystemList::iterator particleSysListFindDriver(
	ParticleSystemList &list, ParticleSystem *const &value )
{
	return _STL::find( list.begin(), list.end(), value );
}
