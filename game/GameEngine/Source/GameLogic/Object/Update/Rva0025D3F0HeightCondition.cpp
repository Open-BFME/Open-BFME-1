// Full295B 25D3F0..25D517 RET0. Incoming update interface is primary+10;
// original module name remains unresolved. Primary slots3C/2C and AI slots
// 180/198 are left address-labelled. BFME terrain slot18 is getGroundHeight.
// GeometryInfo is the real 5C-byte owning class: matched copy194B FFD10,
// destructor80B FFCA0 destroys its vectors38/2C then restores Snapshot's table.
// Native model-condition accessor layers keep the two branch-local word loads;
// raw word expressions merge those loads and produce289B. Separate ground and
// height locals preserve retail's x87 subtraction and cleanup sequence.
// Shipped model-condition name table VA12A6918 index233 is SPECIAL_WEAPON_ONE.
// cl: /DNDEBUG /MD /EHsc /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include
#include "Lib/BaseType.h"
// stlport
#define _STLP_NO_EXCEPTIONS 1
#define _STLP_USE_STATIC_LIB 1
#include <bitset>
template<int N> class BitFlags {
public:
    bool test(int i) const { return bits.test(i); }
    void set(int i) { bits.set(i); }
    void reset(int i) { bits.reset(i); }
private:
    _STL::bitset<N> bits;
};

class GeometryInfo {
public:
    GeometryInfo(const GeometryInfo &);
    virtual ~GeometryInfo();
    char prefix[0x10];
    float m_boundingSphereRadius;
    char remainder[0x44];
};
typedef char GeometrySize[(sizeof(GeometryInfo)==0x5C)?1:-1];

class Rva0025D3F0AI {
public:
#define AI_SLOT(N) virtual void slot##N();
#define AI_TEN(A,B,C,D,E,F,G,H,I,J) AI_SLOT(A) AI_SLOT(B) AI_SLOT(C) AI_SLOT(D) AI_SLOT(E) AI_SLOT(F) AI_SLOT(G) AI_SLOT(H) AI_SLOT(I) AI_SLOT(J)
    AI_TEN(00,01,02,03,04,05,06,07,08,09)
    AI_TEN(10,11,12,13,14,15,16,17,18,19)
    AI_TEN(20,21,22,23,24,25,26,27,28,29)
    AI_TEN(30,31,32,33,34,35,36,37,38,39)
    AI_TEN(40,41,42,43,44,45,46,47,48,49)
    AI_TEN(50,51,52,53,54,55,56,57,58,59)
    AI_TEN(60,61,62,63,64,65,66,67,68,69)
    AI_TEN(70,71,72,73,74,75,76,77,78,79)
    AI_TEN(80,81,82,83,84,85,86,87,88,89)
    AI_SLOT(90) AI_SLOT(91) AI_SLOT(92) AI_SLOT(93) AI_SLOT(94) AI_SLOT(95)
    virtual bool query180();
    AI_SLOT(97) AI_SLOT(98) AI_SLOT(99) AI_SLOT(100) AI_SLOT(101)
    virtual bool query198();
#undef AI_TEN
#undef AI_SLOT
};

class Object {
public:
    void notifyModelConditionChanged();
    char prefix[0x38];
    Coord3D position;
    char gap44[0x68];
    GeometryInfo geometry;
    char gap108[8];
    BitFlags<320> m_modelConditionFlags;
    char gap138[0xCC];
    Rva0025D3F0AI *ai;
};

class Rva0025D3F0Primary {
public:
    virtual void slot00(); virtual void slot04(); virtual void slot08();
    virtual void slot0C(); virtual void slot10(); virtual void slot14();
    virtual void slot18(); virtual void slot1C(); virtual void slot20();
    virtual void slot24(); virtual void slot28();
    virtual void call2C(void *,void *);
    virtual void slot30(); virtual void slot34(); virtual void slot38();
    virtual void call3C();
    void *data;
    Object *object;
};

class TerrainLogic {
public:
    virtual void slot00(); virtual void slot04(); virtual void slot08();
    virtual void slot0C(); virtual void slot10(); virtual void slot14();
    virtual float getGroundHeight(float,float,Coord3D *) const;
};
extern TerrainLogic *TheTerrainLogic;

enum { BFME_SPECIAL_WEAPON_ONE=233 };

static __forceinline void setModelCondition(Object *object,int bit) {
    if (!object->m_modelConditionFlags.test(bit)) {
        object->m_modelConditionFlags.set(bit);
        object->notifyModelConditionChanged();
    }
}
static __forceinline void clearModelCondition(Object *object,int bit) {
    if (object->m_modelConditionFlags.test(bit)) {
        object->m_modelConditionFlags.reset(bit);
        object->notifyModelConditionChanged();
    }
}

class Rva0025D3F0Update {
public:
    unsigned int updateAt0025D3F0();
    char prefix[0xD8];
    bool initialized;
};

unsigned int Rva0025D3F0Update::updateAt0025D3F0()
{
    if (!initialized) {
        reinterpret_cast<Rva0025D3F0Primary *>(reinterpret_cast<char *>(this)-0x10)->call3C();
        initialized=true;
    } else {
        Object *object=reinterpret_cast<Rva0025D3F0Primary *>(reinterpret_cast<char *>(this)-0x10)->object;
        Rva0025D3F0AI *ai=object->ai;
        if (ai && (ai->query180() || ai->query198())) {
            reinterpret_cast<Rva0025D3F0Primary *>(reinterpret_cast<char *>(this)-0x10)->call2C(0,0);
            return 0x3FFFFFFF;
        }
        float ground=TheTerrainLogic->getGroundHeight(object->position.x,object->position.y,0);
        float height=object->position.z;
        height-=ground;
        GeometryInfo geometry(object->geometry);
        if (height<geometry.m_boundingSphereRadius) {
            setModelCondition(object,BFME_SPECIAL_WEAPON_ONE);
        } else {
            clearModelCondition(object,BFME_SPECIAL_WEAPON_ONE);
        }
    }
    return 1;
}

