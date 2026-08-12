// cl: /DNDEBUG /MD /EHsc

enum WeaponSlotType { };
class Object;

class TurretAI
{
public:
    bool isWeaponSlotOnTurret(WeaponSlotType) const;
    bool isTryingToAimAtTarget(const Object *) const;
};

class AIUpdateInterface
{
public:
    bool isWeaponSlotOnTurretAndAimingAtTarget(WeaponSlotType, const Object *) const;

private:
    unsigned char padding[0x1e8];
    TurretAI *turretAI[2];
};

// ?isWeaponSlotOnTurretAndAimingAtTarget@AIUpdateInterface@@QBE_NW4WeaponSlotType@@PBVObject@@@Z
bool AIUpdateInterface::isWeaponSlotOnTurretAndAimingAtTarget(WeaponSlotType slot, const Object *victim) const
{
    for (int i = 0; i < 2; ++i) {
        if (turretAI[i] && turretAI[i]->isWeaponSlotOnTurret(slot))
            return turretAI[i]->isTryingToAimAtTarget(victim);
    }
    return false;
}
