// cl: /DNDEBUG /MD /EHsc
// Retail 00411730..00411800. Both exits RET 0x1c: seven stack arguments.
// The reference's eighth damageRadius argument is absent in BFME.
// Drawable +fc/+138 are layout-witness m_object/m_locoInfo. +150 is the
// module-array operand in retail. Virtual offsets below are read from calls.
enum WeaponSlotType;
class FXList;
struct Coord3D;
float Cos(float);
float Sin(float);
struct Rva00411730Recoil {
    char field00[0x1c];
    float field1c;
    char field20[4];
    float field24;
};
class Rva00411730Interface {
public:
    virtual void slot0();
    virtual void slot1();
    virtual void slot2();
    virtual void slot3();
    virtual void slot4();
    virtual void slot5();
    virtual void slot6();
    virtual void slot7();
    virtual void slot8();
    virtual void slot9();
    virtual void slot10();
    virtual void slot11();
    virtual void slot12();
    virtual void slot13();
    virtual void slot14();
    virtual void slot15();
    virtual void slot16();
    virtual void slot17();
    virtual void slot18();
    virtual void slot19();
    virtual void slot20();
    virtual bool slot21(WeaponSlotType, int, const FXList*, float, const Coord3D*);
};
class Rva00411730Module {
public:
    virtual void slot0();
    virtual void slot1();
    virtual void slot2();
    virtual void slot3();
    virtual void slot4();
    virtual void slot5();
    virtual void slot6();
    virtual void slot7();
    virtual void slot8();
    virtual void slot9();
    virtual void slot10();
    virtual void slot11();
    virtual void slot12();
    virtual void slot13();
    virtual void slot14();
    virtual void slot15();
    virtual void slot16();
    virtual void slot17();
    virtual void slot18();
    virtual void slot19();
    virtual void slot20();
    virtual void slot21();
    virtual void slot22();
    virtual void slot23();
    virtual void slot24();
    virtual void slot25();
    virtual void slot26();
    virtual void slot27();
    virtual void slot28();
    virtual void slot29();
    virtual void slot30();
    virtual void slot31();
    virtual void slot32();
    virtual void slot33();
    virtual void slot34();
    virtual void slot35();
    virtual void slot36();
    virtual void slot37();
    virtual void slot38();
    virtual Rva00411730Interface *slot39();
};
class Drawable {
public:
    bool handleWeaponFireFX(WeaponSlotType, int, const FXList*, float, float, float, const Coord3D*);
private:
    char field00[0xfc];
    const char *m_object;
    char field100[0x38];
    Rva00411730Recoil *m_locoInfo;
    char field13c[0x14];
    Rva00411730Module **field150;
};
bool Drawable::handleWeaponFireFX(WeaponSlotType wslot, int specificBarrelToUse,
    const FXList *fxl, float weaponSpeed, float recoilAmount, float recoilAngle,
    const Coord3D *victimPos)
{
    if (recoilAmount != 0.0f) {
        if (m_object)
            recoilAngle -= *reinterpret_cast<const float*>(m_object + 0x44);
        recoilAngle += 3.14159265358979323846f;
        if (m_locoInfo) {
            m_locoInfo->field1c += recoilAmount * Cos(recoilAngle);
            m_locoInfo->field24 += recoilAmount * Sin(recoilAngle);
        }
    }
    for (Rva00411730Module **dm = field150; *dm; ++dm) {
        Rva00411730Interface *di = (*dm)->slot39();
        if (di && di->slot21(wslot, specificBarrelToUse, fxl, weaponSpeed, victimPos))
            return true;
    }
    return false;
}
