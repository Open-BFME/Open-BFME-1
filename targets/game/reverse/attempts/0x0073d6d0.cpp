// ?apply@Rva0073D6D0@@UAEXI@Z
// partial score=0.9608 date=2026-10-09
// cl: /DNDEBUG /MD /Igame/Libraries/Include/Lib
// Retail 0x0073D6D0 uses an address-derived receiver and camera view.
#include <math.h>

#include "Coord3D.h"
class Rva006DF550 {
public:
    virtual void slot00();
    virtual float slot01() const;
    virtual float slot02() const;
    virtual float slot03() const;
};
class Rva0073D6D0Terrain {
public:
    virtual void slot00();
    virtual void slot01();
    virtual void slot02();
    virtual void slot03();
    virtual void slot04();
    virtual void slot05();
    virtual float getGroundHeight(float x, float y, Coord3D *normal = 0) const;
};
class TerrainLogic;
extern TerrainLogic *TheTerrainLogic;
extern float Rva012F9DD0;
extern float Rva012F9DD4;
extern float Rva012F9DD8;
extern Coord3D Rva012F9DE4;

class Rva0073D6D0ViewBase {
public:
    virtual ~Rva0073D6D0ViewBase();
    virtual void slot001();
    virtual void slot002();
    virtual void slot003();
    virtual void slot004();
    virtual void slot005();
    virtual void slot006();
    virtual void slot007();
    virtual void slot008();
    virtual void slot009();
    virtual void slot010();
    virtual void slot011();
    virtual void slot012();
    virtual void slot013();
    virtual void slot014();
    virtual void slot015();
    virtual void slot016();
    virtual void slot017();
    virtual void slot018();
    virtual void slot019();
    virtual void slot020();
    virtual void slot021();
    virtual void slot022();
    virtual void slot023();
    virtual void slot024();
    virtual void slot025();
    virtual void slot026();
    virtual void slot027();
    virtual void slot028();
    virtual void slot029();
    virtual void slot030();
    virtual void slot031();
    virtual void slot032();
    virtual void slot033();
    virtual void slot034();
    virtual void slot035();
    virtual void slot036();
    virtual void slot037();
    virtual void slot038();
    virtual void slot039();
    virtual void slot040();
    virtual void slot041();
    virtual void slot042();
    virtual void slot043();
    virtual void slot044();
    virtual void slot045();
    virtual void slot046();
    virtual void slot047();
    virtual void slot048();
    virtual void slot049();
    virtual void slot050();
    virtual void slot051();
    virtual void slot052();
    virtual void slot053();
    virtual void slot054();
    virtual void slot055();
    virtual void slot056();
    virtual void slot057();
    virtual void slot058();
    virtual void slot059();
    virtual void slot060();
    virtual void slot061();
    virtual void slot062();
    virtual void slot063();
    virtual void slot064();
    virtual void slot065();
    virtual void slot066();
    virtual void slot067();
    virtual void slot068();
    virtual void slot069();
    virtual void slot070();
    virtual void slot071();
    virtual void slot072();
    virtual void slot073();
    virtual void slot074();
    virtual void slot075();
    virtual void slot076();
    virtual void slot077();
    virtual void slot078();
    virtual void slot079();
    virtual void slot080();
    virtual void slot081();
    virtual void slot082();
    virtual void slot083();
    virtual void slot084();
    virtual void slot085();
    virtual void slot086();
    virtual void slot087();
    virtual void slot088();
    virtual void slot089();
    virtual void slot090();
    virtual void slot091();
    virtual void slot092();
    virtual void slot093();
    virtual void slot094();
    virtual void slot095();
    virtual void slot096();
    virtual void slot097();
    virtual void slot098();
    virtual void slot099();
    virtual void slot100();
    virtual void slot101();
    virtual void slot102();
    virtual void slot103();
    virtual void slot104();
    virtual void slot105();
    virtual void slot106();
    virtual void slot107();
    virtual void slot108();
    virtual void slot109();
    virtual void slot110();
    virtual void slot111();
    virtual void slot112();
    virtual void slot113();
    virtual void slot114();
    virtual void slot115();
    virtual void slot116();
    virtual void slot117(unsigned value);
    char pad0004[0x0c-0x04];
    Coord3D field000C;
    char pad0018[0x3c-0x18];
    float field003C;
    float field0040;
    char pad0044[0x50-0x44];
    float field0050;
    char pad0054[0x6c-0x54];
    float field006C;
    float field0070;
    char pad0074[0xB4-0x74];
};
class Rva0073D6D0SecondaryBase {
public:
    virtual void slot00();
    char pad0004[0x48-4];
};
class SubsystemInterface {
public:
    virtual ~SubsystemInterface();
    char *m_name;
};
class Rva0073D6D0 : public Rva0073D6D0ViewBase, public Rva0073D6D0SecondaryBase, public SubsystemInterface {
public:
    virtual void slot118();
    virtual void slot119();
    virtual void slot120();
    virtual void slot121();
    virtual void slot122();
    virtual void slot123();
    virtual void slot124();
    virtual void slot125();
    virtual void slot126();
    virtual void slot127();
    virtual void slot128();
    virtual void slot129();
    virtual void slot130();
    virtual void slot131();
    virtual void slot132();
    virtual void slot133();
    virtual void slot134();
    virtual void slot135();
    virtual void slot136();
    virtual void slot137();
    virtual void slot138();
    virtual void slot139();
    virtual void slot140();
    virtual void slot141();
    virtual void slot142();
    virtual void slot143();
    virtual void slot144();
    virtual void slot145();
    virtual void slot146();
    virtual void slot147();
    virtual void slot148();
    virtual void slot149();
    virtual void apply(unsigned unused);
    char pad0104[0x23d8-0x104];
    Coord3D field23D8;
    char pad23E4[0x23f8-0x23e4];
    float field23F8;
    char pad23FC[0x240c-0x23fc];
    bool field240C;
    char pad240D[0x2434-0x240d];
    float field2434;
    char pad2438;
    bool field2439;
    char pad243A[0x24b8-0x243a];
    Rva006DF550 field24B8;
};

// ?apply@Rva0073D6D0@@UAEXI@Z
void Rva0073D6D0::apply(unsigned unused)
{
    slot103();
    if (field2439) {
        field006C = Rva012F9DD8;
        field000C = Rva012F9DE4;
        field003C = Rva012F9DD4;
        field0040 = Rva012F9DD0;
        field2439 = false;
        field0070 = 1.0f;
        field0050 = field0040;
        slot117(false);
    }
    if (TheTerrainLogic) {
        field23F8 = ((Rva0073D6D0Terrain *)TheTerrainLogic)->getGroundHeight(field000C.x, field000C.y, 0);
        if (field23F8 > 700.0f)
            field23F8 = 700.0f;
    } else {
        field23F8 = 10.0f;
    }
    Coord3D offset;
    offset.z = field24B8.slot01();
    offset.y = -(offset.z / tan(field24B8.slot02() * (3.14159265358979323846f / 180.0)));
    offset.x = -(offset.y * tan(field24B8.slot03() * (3.14159265358979323846f / 180.0)));
    field23D8 = offset;
    field240C = false;
    field2434 = 1.0f;
}
