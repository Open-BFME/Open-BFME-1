// ?applyAt0025C010@Rva0025C7C0Owner@@QAEPAXPAVRva0025C7C0Location@@ABVAsciiString@@@Z
// partial score=0.87 date=2026-09-15
// Full266B 25C7C0..25C8CA. File identity from shipped random-site filename;
// exact member name remains unresolved. The caller passes this unchanged to
// 25C010 through ILT28C5E with a location pointer and an AsciiString reference.
// That full382B callee returns a created object pointer or null and ends RET8.
// Indexed vector access preserves retail's extent reload and x87 accumulation;
// hoisting a separate entries pointer changes both the loop and register layout.
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/stringbaseascii /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include
// stlport
#define __PLACEMENT_VEC_NEW_INLINE
#include <vector>
#include "Common/AsciiString.h"
#include "Lib/BaseType.h"
#include "Common/BitFlags.h"
#include "matrix3d.h"
class Object;
extern "C" unsigned int __cdecl strlen(const char *);
#pragma intrinsic(strlen)
inline AsciiString::~AsciiString() { ((StringBase<char> *)this)->releaseBuffer(); }
template<> inline bool StringBase<char>::isEmpty() const {
    return m_data==0 || m_data->length==0;
}
template<> inline const char *StringBase<char>::str() const {
    return m_data ? m_data->data : "";
}
template<> inline void StringBase<char>::set(const char *s) {
    set(s,s ? strlen(s) : 0);
}
extern int GetGameLogicRandomValue(int,int,const char *,int);
struct Rva0025C7C0Entry { AsciiString name; float weight; };
struct Rva0025C7C0Data {
    char prefix[0x210];
    _STL::vector<Rva0025C7C0Entry> choices;
};
class Rva0025C7C0Location;
class Rva0025C7C0Owner {
public:
    void chooseAt0025C7C0(Rva0025C7C0Location *);
    void *applyAt0025C010(Rva0025C7C0Location *,const AsciiString &);
    void *vtable;
    Rva0025C7C0Data *data;
    Object *owner;
};
void Rva0025C7C0Owner::chooseAt0025C7C0(Rva0025C7C0Location *location)
{
    AsciiString chosen;
    Rva0025C7C0Data *settings=data;
    int random=GetGameLogicRandomValue(0,99,"F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Object\\SpecialPower\\ElvenWoodSpecialPower.cpp",232);
    int cumulative=0;
    for (unsigned int i=0;i<settings->choices.size();++i) {
        cumulative=static_cast<int>(cumulative+settings->choices[i].weight);
        if (random<cumulative) {
            if (settings->choices[i].name.isEmpty()) return;
            chosen.set(settings->choices[i].name.str());
            break;
        }
    }
    applyAt0025C010(location,chosen);
}

class Team;
class ThingTemplate {
public:
    char prefix[0xD0];
    unsigned int wordD0, wordD4;
    char gapD8[0x2E8];
    float m_assetScale;
};
class Object {
public:
#define OBJECT_SLOT(N) virtual void slot##N();
    OBJECT_SLOT(00) OBJECT_SLOT(01) OBJECT_SLOT(02) OBJECT_SLOT(03)
    OBJECT_SLOT(04) OBJECT_SLOT(05) OBJECT_SLOT(06) OBJECT_SLOT(07)
    OBJECT_SLOT(08) OBJECT_SLOT(09) OBJECT_SLOT(10) OBJECT_SLOT(11)
    OBJECT_SLOT(12) OBJECT_SLOT(13) OBJECT_SLOT(14) OBJECT_SLOT(15)
    OBJECT_SLOT(16) OBJECT_SLOT(17) OBJECT_SLOT(18) OBJECT_SLOT(19)
#undef OBJECT_SLOT
    virtual void slot50(Team *);
    void setPosition(const Coord3D *);
    char prefix4[0x238];
    Team *m_team;
};
class ThingFactory {
public:
    ThingTemplate *findTemplate(const AsciiString &);
    Object *newObject(const ThingTemplate *,Team *,const BitFlags<86> &,unsigned int);
};
extern ThingFactory *TheThingFactory;
class TerrainLogic {
public:
    void placeAt001AD080(const ThingTemplate *,const Coord3D *,const Matrix3D *,float);
    void placeAt001A7A90(const ThingTemplate *,const Coord3D *,const Matrix3D *,float);
    void placeAt001A34C0(const ThingTemplate *,const Coord3D *,const Matrix3D *,float);
};
extern TerrainLogic *TheTerrainLogic;
void *Rva0025C7C0Owner::applyAt0025C010(Rva0025C7C0Location *location,const AsciiString &name)
{
    ThingTemplate *thingTemplate=TheThingFactory->findTemplate(name);
    if (thingTemplate) {
        if (!(thingTemplate->wordD4&8) && !(thingTemplate->wordD0&0x60000000)) {
            BitFlags<86> status;
            Object *object=TheThingFactory->newObject(thingTemplate,0,status,0);
            if (object) {
                object->slot50(owner->m_team);
                object->setPosition(reinterpret_cast<const Coord3D *>(location));
                return object;
            }
        } else {
            Matrix3D matrix(true);
            float extra=thingTemplate->m_assetScale;
            if (thingTemplate->wordD0&0x20000000) {
                TheTerrainLogic->placeAt001AD080(thingTemplate,reinterpret_cast<const Coord3D *>(location),&matrix,extra);
            } else if (thingTemplate->wordD0&0x40000000) {
                TheTerrainLogic->placeAt001A7A90(thingTemplate,reinterpret_cast<const Coord3D *>(location),&matrix,extra);
            } else {
                TheTerrainLogic->placeAt001A34C0(thingTemplate,reinterpret_cast<const Coord3D *>(location),&matrix,extra);
            }
        }
        return 0;
    }
    return 0;
}
