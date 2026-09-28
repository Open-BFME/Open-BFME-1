// ?d_003f0f40@@YAXXZ
// partial score=0.847 date=2026-09-28
// ?checkForAdjust@Pathfinder@@QAEEPAVObject@@ABVLocomotorSet@@EHHHHEPAUCoord3D@@PBU4@MPAPAVPathfindCell@@H@Z
// partial score=0.847 (normalised shape; prior bank measured 0.760 shape, 1466B, 1049 differing) date=2026-09-28 model=opus-5.5
// Retail 0x003F0F40, 1496 bytes
// cl: /O2 /Ob1 /DNDEBUG /DWIN32 /D_WINDOWS /MD
//
// BFME's 13-argument Pathfinder::checkForAdjust with tighten-path callback extensions.
// This bank: 1500B vs 1496, 1031 differing, 40 structural.  The first log block
// is rebuilt from the retail instructions:
//  - groupDest is copied into three block-scoped Real scalars (z, y, x order),
//    which retail spills into the dead x and groupDest parameter slots plus one
//    local -- not a Coord3D;
//  - the TRUE/FALSE labels must be ONE relocated symbol each (retail loads them
//    into EDI/EDX once and stores both ternaries branchily into [esp+14]/[esp+18]);
//    absolute-address macros give a neg/sbb/and select and separate "TRUE"
//    literals give no CSE.  Rva0107FA58True / Rva01080180False are address-derived
//    externs for the retail strings "TRUE" (0x0107FA58) and "FALSE" (0x01080180);
//    they still need symbols.csv pins before landing;
//  - the template walk is evaluated inside the argument list (right to left).
// Remaining: retail hoists obj into ECX before the flag branch and reads
// obj->m_id early (+A3), keeps y on the stack (reloaded +11C) where ours
// enregisters y in EBX, and holds the getCell result in EDI where ours spills it.
#include <math.h>
#pragma intrinsic(fabs)

typedef int Int;
typedef unsigned char Bool;
typedef float Real;

class CRCParameterCheck;

extern bool Glo012F0239;
extern CRCParameterCheck *TheCRCParameterCheck;
extern const Real BfmeZeroRange;
extern char Rva006A16B0Empty[];
extern const char Rva0107FA58True[];
extern const char Rva01080180False[];
extern "C" void __cdecl bfmeRetailCritterDesyncLog(
    CRCParameterCheck *context, const char *format, ...);

#define Rva0107FAA8Scale50 (*(const Real *)0x0107FAA8)
#define Rva0107FA58_MinasTirithMsg ((const char *)0x0107FA58)
#define Rva01080180_AltMsg ((const char *)0x01080180)

struct Coord3D
{
    Real x, y, z;
};

class AsciiString
{
public:
    char *m_data;

    __forceinline const char *str(void) const
    {
        return m_data != 0 ? m_data + 8 : Rva006A16B0Empty;
    }
};

class Overridable
{
public:
    virtual ~Overridable();
    const Overridable *getFinalOverride(void) const;

    Overridable *m_nextOverride;
    char m_pad08[0x18];
    AsciiString m_name;
};

struct ICoord2D
{
    Int x, y;
};

struct IRegion2D
{
    ICoord2D lo, hi;
};

enum PathfindLayerEnum
{
    PATHFIND_LAYER_UNKNOWN = 0
};

enum KindOfType
{
    KINDOF_AIRCRAFT = 12
};

class LocomotorSet
{
public:
    char m_pad00[0x18];
    AsciiString m_name;
};

class Thing
{
public:
    bool isKindOf(KindOfType kind) const;
};

class Object : public Thing
{
public:
    char m_pad00[4];
    Overridable *m_template;
    char m_pad08[0x30];
    Coord3D m_position;
    char m_pad44[0x30];
    Int m_id;

    const Overridable *getTemplate(void) const
    {
        const Overridable *t = m_template;
        if (t != 0 && t->m_nextOverride != 0)
            t = t->m_nextOverride->getFinalOverride();
        return t;
    }
};

class PathfindCell
{
public:
    Int getLayer(void) const { return (m_word >> 6) & 0x3f; }
    Int getType(void) const { return m_word & 7; }

private:
    char m_pad00[0x0c];
    unsigned int m_word;
};

class Pathfinder
{
public:
    Bool checkForAdjust(Object *obj, const LocomotorSet &set,
        Bool human, Int x, Int y, Int layer, Int radius, Bool center,
        Coord3D *dest, const Coord3D *groupDest, Real originalZ,
        PathfindCell **fromSlot, Int onlyIfLayer);

    PathfindCell *getCell(PathfindLayerEnum layer, Int x, Int y);
    bool bfmeInnerE6E90(void *a1, void *a2, void *a3, void *a4, void *a5,
        void *a6, void **a7, int a8);
    bool slowDoesPathExist(Object *obj, const Coord3D *from,
        const Coord3D *to, int ignoreObject);

protected:
    void adjustCoordToCell(Int x, Int y, Bool center, Coord3D &pos,
        PathfindLayerEnum layer);

    char m_pad00[0x24];
    IRegion2D m_logicalExtent;
};

Bool Pathfinder::checkForAdjust(Object *obj, const LocomotorSet &set,
    Bool human, Int x, Int y, Int layer, Int radius, Bool center,
    Coord3D *dest, const Coord3D *groupDest, Real originalZ,
    PathfindCell **fromSlot, Int onlyIfLayer)
{
    Coord3D adjustDest;
    if (Glo012F0239 && TheCRCParameterCheck)
    {
        Real groupX, groupY, groupZ;
        if (groupDest != 0)
        {
            groupZ = groupDest->z;
            groupY = groupDest->y;
            groupX = groupDest->x;
        }
        else
        {
            groupZ = -1.0f;
            groupY = -1.0f;
            groupX = -1.0f;
        }
        bfmeRetailCritterDesyncLog(TheCRCParameterCheck,
            "\t\t  Pathfinder::CheckForAdjust called with: obj=%s(%d), loco=%s, isHuman=%s, cell=%d,%d, layer=%d, iRadius=%d, center=%s, groupDest=%g,%g,%g, originalZ=%g, onlyIfLayer=%d",
            obj->getTemplate()->m_name.str(), obj->m_id, set.m_name.str(),
            human ? Rva0107FA58True : Rva01080180False, x, y, layer, radius,
            center ? Rva0107FA58True : Rva01080180False, groupX, groupY,
            groupZ, originalZ, onlyIfLayer);
    }
    // getCell((PathfindLayerEnum)layer, x, y)
    PathfindCell *cell = getCell((PathfindLayerEnum)layer, x, y);
    if (cell == 0)
    {
        if (Glo012F0239 && TheCRCParameterCheck)
            bfmeRetailCritterDesyncLog(TheCRCParameterCheck,
                "        cellP is NULL, return FALSE.");
        return 0;
    }
    if (cell->getType() == 2)
    {
        if (Glo012F0239 && TheCRCParameterCheck)
            bfmeRetailCritterDesyncLog(TheCRCParameterCheck,
                "        cellP is CLIFF, return FALSE.");
        return 0;
    }

    if (human && Glo012F0239 && TheCRCParameterCheck)
        bfmeRetailCritterDesyncLog(TheCRCParameterCheck,
            "        isHuman is TRUE");

    // Check logical extent for human players
    if (human && (x < m_logicalExtent.lo.x || y < m_logicalExtent.lo.y ||
        x > m_logicalExtent.hi.x || y > m_logicalExtent.hi.y))
    {
        if (Glo012F0239 && TheCRCParameterCheck)
            bfmeRetailCritterDesyncLog(TheCRCParameterCheck,
                "        cell %d,%d is outside m_logicalExtent lo:%d,%d hi:%d,%d",
                x, y, m_logicalExtent.lo.x, m_logicalExtent.lo.y,
                m_logicalExtent.hi.x, m_logicalExtent.hi.y);
        return 0;
    }

    // bfmeInnerE6E90(obj, x, y, layer, radius, center, fromSlot, 0)
    if (!bfmeInnerE6E90((void *)obj, (void *)x, (void *)y, (void *)layer,
        (void *)radius, (void *)center, (void **)fromSlot, 0))
    {
        if (Glo012F0239 && TheCRCParameterCheck)
            bfmeRetailCritterDesyncLog(TheCRCParameterCheck,
                "        CheckDestination failed, return false");
        return 0;
    }
    if (Glo012F0239 && TheCRCParameterCheck)
        bfmeRetailCritterDesyncLog(TheCRCParameterCheck,
            "        CheckDestination passed");

    // adjustCoordToCell(x, y, center, adjustDest, cell->getLayer())
    adjustCoordToCell(x, y, center, adjustDest,
        (PathfindLayerEnum)cell->getLayer());

    if (!obj->isKindOf(KINDOF_AIRCRAFT))
    {
        if (Glo012F0239 && TheCRCParameterCheck)
            bfmeRetailCritterDesyncLog(TheCRCParameterCheck,
                "        object is not kindof aircraft");

        if (onlyIfLayer)
        {
            if (Glo012F0239 && TheCRCParameterCheck)
                bfmeRetailCritterDesyncLog(TheCRCParameterCheck,
                    "        onlyIfLayer=%d", onlyIfLayer);

            Int x0 = x - radius;
            Int x1 = x + radius + (center ? 1 : 0);
            Int y0 = y - radius;
            Int y1 = y + radius + (center ? 1 : 0);

            for (Int ix = x0; ix < x1; ++ix)
            {
                for (Int iy = y0; iy < y1; ++iy)
                {
                    PathfindCell *near = getCell(
                        (PathfindLayerEnum)onlyIfLayer, ix, iy);
                    if (near == 0)
                    {
                        if (Glo012F0239 && TheCRCParameterCheck)
                            bfmeRetailCritterDesyncLog(TheCRCParameterCheck,
                                "        ground unit failed iteration: i=%d, j=%d, cell=NULL, onlyIfLayer",
                                ix, iy, onlyIfLayer);
                        return 0;
                    }
                    if (near->getLayer() != onlyIfLayer)
                    {
                        if (Glo012F0239 && TheCRCParameterCheck)
                            bfmeRetailCritterDesyncLog(TheCRCParameterCheck,
                                "        ground unit failed iteration: i=%d, j=%d, cell=VALID, cellLayer=%d, onlyIfLayer",
                                ix, iy, near->getLayer(), onlyIfLayer);
                        return 0;
                    }
                }
            }

            // MinasTirith height check: originalZ > 0 && fabs(adjustDest.z - originalZ) > 50
            if (originalZ > BfmeZeroRange &&
                fabs(adjustDest.z - originalZ) > Rva0107FAA8Scale50)
            {
                if (Glo012F0239 && TheCRCParameterCheck)
                    bfmeRetailCritterDesyncLog(TheCRCParameterCheck,
                        "        MinasTirith check failed, return FALSE: originalZ=%g, adjustDest.z=%g",
                        originalZ, adjustDest.z);
                return 0;
            }
        }

        const Coord3D *position = &obj->m_position;
        Bool adjustedPathExists = (Bool)slowDoesPathExist(
            obj, position, &adjustDest, 0);
        if (Glo012F0239 && TheCRCParameterCheck)
            bfmeRetailCritterDesyncLog(TheCRCParameterCheck,
                    "        adjustedPathExists=%s",
                    adjustedPathExists ? Rva0107FA58True : Rva01080180False);

        Bool pathExists = (Bool)slowDoesPathExist(obj, position, dest, 0);
        if (pathExists)
        {
            if (Glo012F0239 && TheCRCParameterCheck)
                bfmeRetailCritterDesyncLog(TheCRCParameterCheck,
                    "        QuickDoesPathExist1 succeeds");
        }
        else
        {
            if (Glo012F0239 && TheCRCParameterCheck)
                bfmeRetailCritterDesyncLog(TheCRCParameterCheck,
                    "        QuickDoesPathExist1 fails. Try adjusted destination");
            if (slowDoesPathExist(obj, dest, &adjustDest, 0))
            {
                adjustedPathExists = 1;
                if (Glo012F0239 && TheCRCParameterCheck)
                    bfmeRetailCritterDesyncLog(TheCRCParameterCheck,
                        "        QuickDoesPathExist2 succeeds. adjustedPathExists");
            }
        }
        if (!adjustedPathExists)
        {
            if (Glo012F0239 && TheCRCParameterCheck)
                bfmeRetailCritterDesyncLog(TheCRCParameterCheck,
                    "        returning false because adjustedPathExists is false");
            return 0;
        }
    }

    if (Glo012F0239 && TheCRCParameterCheck)
        bfmeRetailCritterDesyncLog(TheCRCParameterCheck,
            "        dest calculated to be %g,%g,%g and returning true",
            adjustDest.x, adjustDest.y, adjustDest.z);

    *dest = adjustDest;
    return 1;
}