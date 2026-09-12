// cl: /DNDEBUG /MD /EHsc /O2
// BFME helper at RVA 0x001EB100, 45 bytes. Descriptive helper name;
// original spelling is unknown. The matched chooseBestWeaponForTarget body
// independently establishes WeaponSet's override bytes at +0x2e and its
// template's four command-source masks at +0x18.
enum WeaponSlotType;
enum CommandSourceType;

class WeaponTemplateSet
{
public:
    char m_head[0x18];
    unsigned int m_autoChooseMask[4];
};

class WeaponSet
{
public:
    bool bfmeCanAutoChoose(WeaponSlotType slot, CommandSourceType source) const;
    void *m_vptr;
    const WeaponTemplateSet *m_curWeaponTemplateSet;
    char m_padding[0x2e - 8];
    bool m_autoChooseOverride[4];
};

bool WeaponSet::bfmeCanAutoChoose(WeaponSlotType slot, CommandSourceType source) const
{
    if (m_autoChooseOverride[slot])
        return true;
    unsigned int mask = 1u << source;
    if (mask & m_curWeaponTemplateSet->m_autoChooseMask[slot])
        return true;
    return false;
}
