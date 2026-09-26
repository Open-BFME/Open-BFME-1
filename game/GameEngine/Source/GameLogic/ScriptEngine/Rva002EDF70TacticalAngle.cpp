// ?rva002EDF70@@YGXMMMM@Z
// Retail 0x002EDF70, 115 bytes.  The caller is ScriptActions::executeAction;
// the action arm's semantic name is not established, so the entry remains
// address-derived.  Retail uses the TacticalView vtable at +0xFC and +0xC8.
//
// The +0xFC return is kept as a float because the retail x87 stack uses it as
// the second operand of the normalized angle calculation.  The +0xC8 ABI is
// the five-argument view operation proven by the adjacent camera wrappers.
// The three anonymous retail constants are deliberately addressed by their
// independently observed retail VAs rather than given unproven global names.

typedef float Real;
typedef int Int;

// The two calls use the existing View vtable. This view declares no virtual
// slots or object layout; the receiver and call signatures follow retail.
class View;
class Rva002EDF70Receiver {};
// MSVC represents a member pointer on this non-inheriting receiver as one
// function address; no instance or virtual table is emitted.

extern View *TheTacticalView;
extern Real normalizeAngle(Real angle);

#define RVA_01075C68 (*(const Real *)0x01075C68)
#define RVA_010D0010 (*(const Real *)0x010D0010)

void __stdcall rva002EDF70(Real angle, Real seconds, Real easeIn, Real easeOut)
{
    View *view = TheTacticalView;
    union ReadSlot { void *address; Real (Rva002EDF70Receiver::*method)(); };
    typedef char ReadSlotIsOneWord[sizeof(ReadSlot) == sizeof(void *) ? 1 : -1];
    ReadSlot *readSlot = *(ReadSlot **)view;
    Real current = (((Rva002EDF70Receiver *)view)->*readSlot[63].method)();
    Real scaledAngle = angle * (*(const Real *)0x01075954);
    Real normalized = normalizeAngle(scaledAngle - current);
    view = TheTacticalView;
    union ApplySlot { void *address; void (Rva002EDF70Receiver::*method)(Real, Int, bool, Real, Real); };
    typedef char ApplySlotIsOneWord[sizeof(ApplySlot) == sizeof(void *) ? 1 : -1];
    ApplySlot *applySlot = *(ApplySlot **)view;
    (((Rva002EDF70Receiver *)view)->*applySlot[50].method)(
        normalized * RVA_010D0010,
        (Int)(seconds * RVA_01075C68),
        false,
        easeIn * RVA_01075C68,
        easeOut * RVA_01075C68);
}
