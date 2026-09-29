// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// Identity: ZH GarrisonContain::loadGarrisonPoints has the same three-state
// pristine/damaged/really-damaged traversal and mobile-garrison assertion.
// BFME 0x0021EB50 supplies passenger bone prefixes instead of FIREPOINT and
// records each returned count. The retail extent ends in ret at +0x38b.
// Layout witnesses: module data +4; owning Object +8; positions +0x3fc;
// returned counts +0x99c; initialization byte +0x9b4. Object position +0x38;
// getDrawable virtual +0x28; drawable condition flags +0x250 (40 bytes).
// These BFME offsets differ from the ZH headers used by GarrisonContain.cpp.
// Calls use existing address-only ILT symbols; no speculative pins added.
// stlport
#define _STLP_NO_EXCEPTIONS 1
#include <bitset>
#include "string_base.h"
#include "ascii_string.h"
struct Coord3D
{
    float x, y, z;
};
class Matrix3D;
template <int N> class BitFlags
{
    _STL::bitset<N> bits;

  public:
    void clear()
    {
        bits.reset();
    }
    void set(int i)
    {
        bits.set(i);
    }
};
typedef BitFlags<320> LoadFlags;
struct GarrisonLoadDrawable
{
    char pad[0x250];
    LoadFlags flags;
};
extern void j_000095ed();
extern void j_000107ad();
extern void j_00023277();
extern void j_00017607();
class GarrisonLoadObject
{
  public:
    virtual void slot00();
    virtual void slot04();
    virtual void slot08();
    virtual void slot0c();
    virtual void slot10();
    virtual void slot14();
    virtual void slot18();
    virtual void slot1c();
    virtual void slot20();
    virtual void slot24();
    virtual GarrisonLoadDrawable *getDrawable();
    char pad04[0x34];
    Coord3D position;
    void clearAndSetModelConditionFlags(const LoadFlags &a, const LoadFlags &b)
    {
        typedef void (GarrisonLoadObject::*Fn)(const LoadFlags &, const LoadFlags &);
        union {
            void (*raw)();
            Fn member;
        } call;
        call.raw = j_000095ed;
        return (this->*call.member)(a, b);
    }
    int getMultiLogicalBonePosition(const char *a, int b, Coord3D *c, Matrix3D *d, bool e,
                                    int f) const
    {
        typedef int (GarrisonLoadObject::*Fn)(const char *, int, Coord3D *, Matrix3D *, bool, int)
            const;
        union {
            void (*raw)();
            Fn member;
        } call;
        call.raw = j_000107ad;
        return (this->*call.member)(a, b, c, d, e, f);
    }
    void replaceModelConditionFlags(const LoadFlags &a, bool b)
    {
        typedef void (GarrisonLoadObject::*Fn)(const LoadFlags &, bool);
        union {
            void (*raw)();
            Fn member;
        } call;
        call.raw = j_00023277;
        return (this->*call.member)(a, b);
    }
    bool isMobile() const
    {
        typedef bool (GarrisonLoadObject::*Fn)() const;
        union {
            void (*raw)();
            Fn member;
        } call;
        call.raw = j_00017607;
        return (this->*call.member)();
    }
};
struct GarrisonLoadModuleData
{
    char pad[0x170];
    bool m_mobileGarrison;
};
class Object;
class OpenContain
{
  public:
    AsciiString getPassengerBoneName(Object *);
};
class GarrisonContain : public OpenContain
{
    void *vtable;
    GarrisonLoadModuleData *moduleData;
    GarrisonLoadObject *object;
    char pad00c[0x3fc - 0xc];
    Coord3D m_garrisonPoint[3][40];
    int m_boneCount_099c[3];
    Coord3D m_exitRallyPoint;
    bool m_garrisonPointsInitialized;

  protected:
    void loadGarrisonPoints();
};
void GarrisonContain::loadGarrisonPoints()
{
    const GarrisonLoadModuleData *modData = moduleData;
    GarrisonLoadObject *structure = object;
    int i, j;
    bool gBonesFound = false;
    for (i = 0; i < 3; ++i)
        for (j = 0; j < 40; ++j)
            m_garrisonPoint[i][j] = structure->position;
    {
        int count = 0;
        GarrisonLoadDrawable *draw = structure->getDrawable();
        const LoadFlags originalFlags = draw->flags;
        LoadFlags clearFlags;
        LoadFlags setFlags;
        clearFlags.clear();
        setFlags.clear();
        clearFlags.set(4);
        clearFlags.set(5);
        clearFlags.set(6);
        clearFlags.set(3);
        setFlags.set(10);
        structure->clearAndSetModelConditionFlags(clearFlags, setFlags);
        count = structure->getMultiLogicalBonePosition(getPassengerBoneName(0).str(), 40,
                                                       m_garrisonPoint[0], 0, true, 0);
        m_boneCount_099c[0] = count;
        if (count > 0)
            gBonesFound = true;
        clearFlags.clear();
        setFlags.clear();
        clearFlags.set(4);
        clearFlags.set(5);
        clearFlags.set(6);
        setFlags.set(3);
        structure->clearAndSetModelConditionFlags(clearFlags, setFlags);
        count = structure->getMultiLogicalBonePosition(getPassengerBoneName(0).str(), 40,
                                                       m_garrisonPoint[1], 0, true, 0);
        m_boneCount_099c[1] = count;
        if (count > 0)
            gBonesFound = true;
        clearFlags.clear();
        setFlags.clear();
        clearFlags.set(5);
        clearFlags.set(6);
        clearFlags.set(3);
        setFlags.set(4);
        structure->clearAndSetModelConditionFlags(clearFlags, setFlags);
        count = structure->getMultiLogicalBonePosition(getPassengerBoneName(0).str(), 40,
                                                       m_garrisonPoint[2], 0, true, 0);
        m_boneCount_099c[2] = count;
        if (count > 0)
            gBonesFound = true;
        structure->replaceModelConditionFlags(originalFlags, false);
    }
    m_garrisonPointsInitialized = true;
    if (gBonesFound && modData->m_mobileGarrison && object->isMobile())
    {
    }
}
