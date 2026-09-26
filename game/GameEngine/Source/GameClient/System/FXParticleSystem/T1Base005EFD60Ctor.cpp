// cl: /EHsc /Igame/GameEngine/Source/GameClient/System/FXParticleSystem /Igame/GameEngine/Source/Common/System /Igame/GameEngine/Include/Common /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWLib
//
// Retail RVA 0x005EFD60, 404 B.  The four-base constructor that
// game/GameEngine/Source/Common/T1BaseForwardingCtors.cpp already declares as
// `T1Base_005EFD60( void *, void * )` and forwards to from T1Derived_005E2EF0
// (0x005E2EF0).  The same body is the base call of the matched DefaultModule<0>
// constructor at 0x005E5FC0, which stamps ITS OWN vtables 0x01111FCC/FC8/FC4/FB0
// over the ones written here -- so this is a BASE of DefaultModule<0>, not
// DefaultModule<0> itself, and the class keeps its address-derived name.
//
// WHAT THE BYTES SHOW.  Four bases: the out-of-line 0x14-wide T1A1_005DD290 at
// +0 (one `call`, two re-pushed arguments), two bare-vptr bases at +0x14 and
// +0x18 whose own vptrs 0x0111081C/0x01073760 survive because their
// constructors inline to nothing, and FXParticleSystem::DefaultColorModuleInfo
// at +0x1C (`lea ecx,[esi+0x1C]` then the matched 147-byte constructor at
// 0x005EF600).  The derived stamps 0x01113070/8C/88/84 afterwards.  The body
// then copies the eight 16-byte RGBColorKeyframe slots out of the template's
// own DefaultColorModuleInfo at source+8 and converts its colour-scale range by
// the 1/255 constant at 0x0107C64C -- the Zero Hour twin of that tail is
// ParticleSys.cpp:1094-1099 (`for(i..MAX_KEYFRAMES) m_colorKey[i] = ...;`
// `m_colorScale.setRange( low / 255.0f, hi / 255.0f )`).
//
// The DefaultColorModuleInfo constructor is defined here as well as in
// fx_particle_system_bulk.cpp on purpose: docs/shape_levers.md "Compiler-private
// ABI: compile the static helper with its caller".  Only with the definition in
// the TU does VC7.1 observe that the callee preserves ECX, which is what lets
// `mov [ecx],0x01113070` reuse the `lea ecx,[esi+0x1C]` receiver instead of
// spending a `push ebx`.  Both bodies are byte-exact here (404 B and 147 B).
#include "fx_particle_system.h"

class T1A1_005DD290
{
public:
    T1A1_005DD290(void *a, void *b);
    virtual void s0();
    int m_storage[4];
};

// The two bare-vptr bases at +0x14 and +0x18.  Only their width and the fact
// that each owns one vptr is witnessed; their identities are not.
class T1P1_005EFD60
{
public:
    virtual void s0();
};

class T1P2_005EFD60
{
public:
    virtual ~T1P2_005EFD60() {}
};

class T1Base_005EFD60
    : public T1A1_005DD290,
      public T1P1_005EFD60,
      public T1P2_005EFD60,
      public FXParticleSystem::DefaultColorModuleInfo
{
public:
    T1Base_005EFD60(void *a, void *b);
};

namespace FXParticleSystem {

// ??0DefaultColorModuleInfo@FXParticleSystem@@QAE@XZ -- retail 0x005EF600, 147 B.
// Same body as fx_particle_system_bulk.cpp; present so VC7.1 can see the callee.
DefaultColorModuleInfo::DefaultColorModuleInfo()
{
}

}  // namespace FXParticleSystem

T1Base_005EFD60::T1Base_005EFD60(void *a, void *b)
    : T1A1_005DD290(a, b),
      DefaultColorModuleInfo()
{
    const FXParticleSystem::DefaultColorModuleInfo *info =
        (const FXParticleSystem::DefaultColorModuleInfo *)((const unsigned char *)b + 8);
    struct ColorKeyBlock {
        unsigned int word_0;
        unsigned int word_4;
        unsigned int word_8;
        unsigned int word_c;
    };

    for (int i = 0; i < 8; i++)
        *(ColorKeyBlock *)&m_colorKey[i] = *(const ColorKeyBlock *)&info->m_colorKey[i];

    m_colorScale.setRange(
        info->m_colorScale.minimum * *(const float *)0x0107c64c,
        info->m_colorScale.maximum * *(const float *)0x0107c64c,
        GameClientRandomVariable::UNIFORM);
}
