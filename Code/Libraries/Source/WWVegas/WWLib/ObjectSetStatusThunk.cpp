// readable body of ?estimateWeaponDamage@Weapon@@IAEMPBVObject@@0PBUCoord3D@@@Z: Code/GameEngine/Source/GameLogic/Object/Weapon.cpp
// readable body of ?setStatus@Object@@QAEXV?$BitFlags@$0CN@@@_N@Z: Code/GameEngine/Source/GameLogic/Object/Object.cpp
template <int Bits>
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/BitFlags.h
class BitFlags
{
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
    void setStatus(BitFlags<45>, bool);
};

class ObjectSetStatusShim
{
public:
    void set(BitFlags<45> flags, bool value);
};

void Object::setStatus(BitFlags<45> flags, bool value)
{
    ((ObjectSetStatusShim *)this)->set(flags, value);
}
