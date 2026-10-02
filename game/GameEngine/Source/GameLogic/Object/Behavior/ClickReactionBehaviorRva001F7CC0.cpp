// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /I. /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include
// stlport
// ClickReactionBehavior secondary interface at +0x20, retail RVA 001F7CC0.
// The method keeps its address: no source-backed lexical method name is known.
// Evidence: identity_evidence/001f7cc0-clickreaction-owner.md.
#include "Lib/BaseType.h"
#include "Common/BitFlags.h"
#define OBJECT_TU_MEMBERS void clearAndSetModelConditionFlags(const BitFlags<320> &, const BitFlags<320> &);
#include "../object.h"
class ClickReactionBehavior;
class Drawable {
    friend class ClickReactionBehavior;
    void applyPendingModelConditionFlags(bool);
};
class Rva001F7CC0Primary {
public:
    virtual void primarySlot0() = 0;
protected:
    unsigned int m_unmodelled04;
    Object *m_object;
    unsigned char m_unmodelled0C[0x14];
};
class Rva001F7CC0Interface {
public:
    virtual void slot0() = 0;
    virtual void slot1() = 0;
    virtual void rva001F7CC0(bool) = 0;
};
class ClickReactionBehavior : public Rva001F7CC0Primary, public Rva001F7CC0Interface {
public:
    virtual void rva001F7CC0(bool apply);
private:
    unsigned int m_unmodelled24;
    unsigned int m_unmodelled28;
    Object *object() { return m_object; }
};
void ClickReactionBehavior::rva001F7CC0(bool apply)
{
    Drawable *drawable = object()->getDrawable();
    if (!drawable) return;
    m_unmodelled28 = 0;
    BitFlags<320> clear;
    clear.clear();
    clear.set(154); clear.set(155); clear.set(156);
    clear.set(157); clear.set(158); clear.set(159);
    BitFlags<320> set;
    object()->clearAndSetModelConditionFlags(clear, set);
    if (apply) drawable->applyPendingModelConditionFlags(false);
}
