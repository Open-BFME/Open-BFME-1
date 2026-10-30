# 0x0020DE10 / 0x0020DE20 BodyParticleSystem destructors

Facts from BFME 1 retail:
- 0x0020DE10 (7 B) is `mov dword ptr [ecx],0x010A74E8 / ret`: a trivial
  virtual destructor re-seating vtable 0x010A74E8. 0x0020DE20 (31 B) is the
  matching scalar deleting destructor; vtable 0x010A74E8 has one slot, ILT
  0x000092D7 -> 0x0020DE20.
- ActiveBody::createParticleSystems 0x0020ED10 (matched,
  ActiveBody_createParticleSystems.cpp) allocates 0xC bytes with operator new
  and stores 0x010A74E8 at +0 (+0x172), then the system ID at +4 and the list
  link at +8 before linking it into ActiveBody::m_particleSystems.
- BodySnapshot 0x0020F330 (matched) walks the same list (id +4, next +8) and
  creates nodes with the same vtable.

Carried from the Zero Hour twin (GeneralsMD ActiveBody.cpp/ActiveBody.h):
createParticleSystems does `newInstance(BodyParticleSystem)` and fills
m_particleSystemID / m_next; BodyParticleSystem is a MemoryPoolObject whose
MEMORY_POOL_GLUE declares `protected: virtual ~BodyParticleSystem()` (EMPTY_DTOR).
BFME differs: `tools/ilt_oracle.py check` CONFIRMS `??_GBodyParticleSystem@@UAEPAXI@Z`
(exact) and CONTRADICTS the protected `MAEPAXI` spelling at 0x0020DE20, so the
BFME destructor is public (UAE).

The rows were address-derived (`Rva0020DE10Poly`); the createParticleSystems
unit already spelled the class BodyParticleSystem and so emitted a second
vtable COMDAT whose slot named an undefined destructor (link queue #30,
`??_7BodyParticleSystem@@6B@` losers, census 1d5131d3f1).
