// ?accepts@Rva2225E0Filter@@QAE_NPAVObject@@PAVPlayer@@@Z
// Matched filtered-count caller 002225E0 proves this wrapper signature.
// The push before getControllingPlayer belongs to the later three-argument call.
// Evidence: identity_evidence/003a04a0-filter-player-abi.md
// cl: /O2 /EHs-c- /Igame/GameEngine/Source
class Player;
#define OBJECT_TU_MEMBERS Player *getControllingPlayer() const;
#include "GameLogic/Object/object.h"

// Preserve the bank's established ABI-view names. The existing ILT reaches
// the matched Overridable::getFinalOverride at RVA 00087A80; the next-override
// link is at +4, as in the upstream Overridable declaration.
extern void j_000022bb();
struct BfmeOverridable
{
    unsigned char m_bfmeHead[4];
    BfmeOverridable *m_bfmeNextOverride;
    const void *resolve() const
    {
        typedef const void *(BfmeOverridable::*Method)() const;
        union { void (*raw)(); Method method; } call = { j_000022bb };
        return (this->*call.method)();
    }
};
class Rva0039F0A0
{
public:
    bool accepts(const void *thing, Player *player, Player *observer);
};
struct Rva2225E0Filter
{
    bool accepts(Object *object, Player *player);
};

bool Rva2225E0Filter::accepts(Object *object, Player *player)
{
    if (!object)
        return false;
    const BfmeOverridable *overrides = (const BfmeOverridable *)object->m_template;
    const void *walked;
    if (!overrides)
        walked = 0;
    else if (overrides->m_bfmeNextOverride)
        walked = overrides->m_bfmeNextOverride->resolve();
    else
        walked = overrides;
    return ((Rva0039F0A0 *)this)->accepts(walked, object->getControllingPlayer(), player);
}
