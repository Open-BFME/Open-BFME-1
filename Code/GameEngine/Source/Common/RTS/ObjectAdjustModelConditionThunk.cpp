// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib
// readable body of ?adjustModelConditionForWeaponStatus@Object@@: Code/GameEngine/Source/GameLogic/Object/Object.cpp

template <int Bits>
class BitFlags;

typedef BitFlags<320> ModelConditionFlags;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
    void adjustModelConditionForWeaponStatus();
    void clearAndSetModelConditionFlags(const ModelConditionFlags &clear,
        const ModelConditionFlags &set);
};

class ObjectAdjustModelConditionShim
{
public:
    void adjust();

private:
    unsigned char m_unreconstructed_00[0x80];
    void *m_drawable;
    unsigned char m_unreconstructed_84[0x0c];
    unsigned int m_status;
    unsigned char m_unreconstructed_94[0x210];
    char m_lastWeaponCondition[4];
};

void Object::adjustModelConditionForWeaponStatus()
{
    ((ObjectAdjustModelConditionShim *)this)->adjust();
}

typedef unsigned int UnsignedInt;
typedef bool Bool;

enum WeaponSlotType
{
    PRIMARY_WEAPON,
    SECONDARY_WEAPON,
    TERTIARY_WEAPON,
    QUATERNARY_WEAPON,
    WEAPONSLOT_COUNT
};

enum WeaponStatus
{
    READY_TO_FIRE,
    OUT_OF_AMMO,
    BETWEEN_FIRING_SHOTS,
    RELOADING_CLIP,
    PRE_ATTACK,
    WEAPON_STATUS_UNUSED,
    WEAPON_STATUS_COUNT
};

enum WeaponSetConditionType
{
    WSF_INVALID = -1,
    WSF_NONE,
    WSF_FIRING,
    WSF_BETWEEN,
    WSF_RELOADING,
    WSF_UNUSED,
    WSF_PREATTACK,
    WSF_COUNT
};

template <int Bits>
class BitFlags
{
private:
    UnsignedInt m_bits[(Bits + 31) / 32];
};

class WeaponTemplate
{
public:
    int getIdleAfterFiringDelay() const
    {
        return *(const int *)((const char *)this + 0x68);
    }

    Bool getRequireFollowThru() const
    {
        return *(const unsigned char *)((const char *)this + 0x531) != 0;
    }

    int getClipSize() const
    {
        return *(const int *)((const char *)this + 0x4ac);
    }
};

class Weapon
{
public:
    const WeaponTemplate *getTemplate() const
    {
        return *(const WeaponTemplate * const *)((const char *)this + 4);
    }

    UnsignedInt getLastShotFrame() const
    {
        return *(const UnsignedInt *)((const char *)this + 0x2c);
    }

    WeaponStatus getStatus() const;
    UnsignedInt getRemainingAmmo(Bool countReloadingAsEmpty) const;

    WeaponSlotType getWeaponSlot() const
    {
        return *(const WeaponSlotType *)((const char *)this + 0x0c);
    }
};

class WeaponSet
{
public:
    Weapon *getWeaponInWeaponSlot(WeaponSlotType slot) const;
    static ModelConditionFlags getModelConditionForWeaponSlot(
        WeaponSlotType slot, WeaponSetConditionType condition);
};

class Drawable
{
public:
    void updateDrawableClipStatus(UnsignedInt shotsRemaining,
        UnsignedInt maxShots, WeaponSlotType slot);
};

static const ModelConditionFlags s_allWeaponFireFlags[WEAPONSLOT_COUNT] = {};
static const WeaponSetConditionType s_wsfLookup[WEAPON_STATUS_COUNT] =
{
    WSF_NONE,
    WSF_NONE,
    WSF_BETWEEN,
    WSF_RELOADING,
    WSF_UNUSED,
    WSF_FIRING
};

class BfmeClock
{
public:
    UnsignedInt getFrame() const
    {
        return *(const UnsignedInt *)((const char *)this + 0x3c);
    }
};

extern BfmeClock *TheGameLogic;

class Gen_001E1980
{
public:
    unsigned char bfmeIsWithin() const;
};

void ObjectAdjustModelConditionShim::adjust()
{
    UnsignedInt now = TheGameLogic->getFrame();
    const unsigned int status = m_status;
    const Bool isAimingWeapon = (status & (1u << 22)) != 0;
    const Bool isFiringWeapon = (status & (1u << 25)) != 0;
    const Bool isAttacking = (status & (1u << 13)) != 0;
    for (int i = 0; i < WEAPONSLOT_COUNT; ++i)
    {
        Weapon *weapon = ((WeaponSet *)((char *)this + 0x264))->getWeaponInWeaponSlot(
            (WeaponSlotType)i);
        WeaponSetConditionType condition = WSF_INVALID;

        if (weapon == 0)
        {
            condition = WSF_NONE;
        }
        else
        {
            UnsignedInt lastShot = weapon->getLastShotFrame();
            if (lastShot > 0)
            {
                int idleDelay = weapon->getTemplate()->getIdleAfterFiringDelay();
                if (idleDelay >= 0 && lastShot + idleDelay > now)
                    condition = WSF_FIRING;
            }

            if (condition == WSF_INVALID && lastShot == now)
                condition = WSF_FIRING;

            if (condition == WSF_INVALID && weapon->getTemplate()->getRequireFollowThru()
                    && now < *(const UnsignedInt *)((const char *)weapon + 0x24)
                    && now > *(const UnsignedInt *)((const char *)weapon + 0x1c))
                condition = WSF_PREATTACK;

            if (condition == WSF_INVALID && !(m_status & 0x400000))
            {
                if (!((const Gen_001E1980 *)weapon)->bfmeIsWithin())
                    condition = WSF_NONE;
            }

            if (condition == WSF_INVALID)
            {
                WeaponStatus newStatus = weapon->getStatus();
                condition = s_wsfLookup[newStatus];

                if (newStatus == READY_TO_FIRE && condition == WSF_NONE
                        && isAimingWeapon && (isAttacking || isFiringWeapon))
                    condition = WSF_BETWEEN;
            }
        }

        if (m_drawable != 0)
        {
            if (weapon != 0)
            {
                ((Drawable *)m_drawable)->updateDrawableClipStatus(
                    weapon->getRemainingAmmo(true),
                    weapon->getTemplate()->getClipSize(),
                    weapon->getWeaponSlot());
            }

            if (condition != WSF_INVALID && condition != (WeaponSetConditionType)m_lastWeaponCondition[i])
            {
                m_lastWeaponCondition[i] = (unsigned char)condition;
                ModelConditionFlags flags = WeaponSet::getModelConditionForWeaponSlot(
                    (WeaponSlotType)i, condition);
                // Object's BFME model-condition body takes both masks by reference.
                ((Object *)this)->clearAndSetModelConditionFlags(
                    s_allWeaponFireFlags[i], flags);
            }
        }
    }
}
