// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: convert the SpecialAbilityUpdate abort callback ILT to clean C++.

// The retail callback is a five-byte ILT to the already matched body at
// 0x002A5A30. Its existing emitted member calls virtual slot11 with (0,1).
// The five-byte jump preserves ECX, matching this member ABI.
struct VirtualSlot11CallThunk
{
    void invokeZeroOne();
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SpecialAbilityUpdate.h
class SpecialAbilityUpdate
{
public:
    void bfmeAbortAbility();
};

// ?bfmeAbortAbility@SpecialAbilityUpdate@@QAEXXZ
void SpecialAbilityUpdate::bfmeAbortAbility()
{
    reinterpret_cast<VirtualSlot11CallThunk *>(this)->invokeZeroOne();
}
