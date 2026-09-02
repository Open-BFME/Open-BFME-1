// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: convert the SpecialAbilityUpdate abort callback ILT to clean C++.

// The retail callback is a five-byte ILT to the already matched body at
// 0x002A5A30.  Its generated ledger name is the stable local spelling used by
// the byte verifier for that body.
void d_002a5a30();

class SpecialAbilityUpdate
{
public:
    void bfmeAbortAbility();
};

// ?bfmeAbortAbility@SpecialAbilityUpdate@@QAEXXZ
void SpecialAbilityUpdate::bfmeAbortAbility()
{
    d_002a5a30();
}
