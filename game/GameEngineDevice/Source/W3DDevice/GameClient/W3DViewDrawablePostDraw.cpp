// cl: /O2 /DNDEBUG /MD

#include "../../../../GameEngine/Include/Common/ScalarTypes.h"

#include "../../../../Libraries/Include/Lib/Coord3D.h"
enum ObjectShroudStatus
{
    OBJECTSHROUD_INVALID,
    OBJECTSHROUD_CLEAR,
    OBJECTSHROUD_PARTIAL_CLEAR,
    OBJECTSHROUD_FOGGED,
    OBJECTSHROUD_SHROUDED
};

class Object
{
public:
    ObjectShroudStatus getShroudedStatus(int playerIndex) const;
};

class Drawable
{
public:
    void drawIconUI();
    const Coord3D *getPosition() const;
    bool isDrawableEffectivelyHidden() const;
};

#include "../../../../Libraries/Include/Lib/ICoord2D.h"

#define V(n) virtual void slot##n();
class TerrainLogic
{
public:
    V(0) V(1) V(2) V(3) V(4) V(5)
    virtual Real getGroundHeight(Real x, Real y, Coord3D *normal);
};

class View
{
public:
    V(0) V(1) V(2) V(3) V(4) V(5) V(6) V(7) V(8) V(9)
    V(10) V(11) V(12) V(13) V(14) V(15) V(16) V(17) V(18) V(19)
    V(20) V(21) V(22) V(23) V(24) V(25) V(26) V(27) V(28) V(29)
    V(30) V(31) V(32) V(33) V(34) V(35) V(36) V(37) V(38) V(39)
    V(40) V(41) V(42) V(43) V(44) V(45) V(46) V(47) V(48) V(49)
    V(50) V(51) V(52) V(53) V(54) V(55) V(56) V(57) V(58) V(59)
    V(60) V(61) V(62) V(63) V(64) V(65) V(66) V(67) V(68) V(69)
    V(70) V(71) V(72) V(73) V(74) V(75) V(76) V(77) V(78) V(79)
    V(80) V(81) V(82) V(83) V(84) V(85) V(86)
    virtual int worldToScreen(const Coord3D *w, ICoord2D *s);
};

class Display
{
public:
    V(0) V(1) V(2) V(3) V(4) V(5) V(6) V(7) V(8) V(9)
    V(10) V(11) V(12) V(13) V(14) V(15) V(16) V(17) V(18) V(19)
    V(20) V(21) V(22) V(23) V(24) V(25) V(26) V(27) V(28) V(29)
    V(30) V(31) V(32) V(33) V(34) V(35) V(36) V(37) V(38) V(39)
    V(40) V(41) V(42) V(43)
    virtual void slot44();
    V(45)
    virtual void drawLine(Real startX, Real startY, Real endX, Real endY, Real lineWidth, UnsignedInt lineColor);
    V(47) V(48) V(49) V(50) V(51) V(52) V(53) V(54)
    virtual void slot55();
    void drawLine0073AD70(Real startX, Real startY, Real endX, Real endY, Real lineWidth, UnsignedInt lineColor)
    {
        slot44();
        drawLine(startX, startY, endX, endY, lineWidth, lineColor);
        slot55();
    }
};
#undef V

extern TerrainLogic *TheTerrainLogic;
extern Display *TheDisplay;

struct BFMEDrawableAIChain
{
    char m_padding[0xFC];
    Object *m_object;
};

struct Rva0073AED0Player
{
    char m_pad00[0x24];
    int m_playerIndex;
};

struct Rva0073AED0PlayerList
{
    char m_pad00[0x0C];
    Rva0073AED0Player *m_local;
};

class Rva0073AED0View
{
public:
#define V(n) virtual void slot##n();
    V(0) V(1) V(2) V(3) V(4) V(5) V(6) V(7) V(8) V(9)
    V(10) V(11) V(12) V(13) V(14) V(15) V(16) V(17) V(18) V(19)
    V(20) V(21) V(22) V(23) V(24) V(25) V(26) V(27) V(28) V(29)
    V(30) V(31) V(32) V(33) V(34) V(35) V(36) V(37) V(38) V(39)
    V(40) V(41) V(42) V(43) V(44) V(45) V(46) V(47) V(48) V(49)
    V(50) V(51) V(52) V(53) V(54) V(55) V(56) V(57) V(58) V(59)
    V(60) V(61) V(62) V(63) V(64) V(65) V(66) V(67) V(68) V(69)
    V(70) V(71) V(72) V(73) V(74) V(75) V(76) V(77) V(78) V(79)
    V(80) V(81) V(82) V(83) V(84) V(85) V(86) V(87) V(88) V(89)
    V(90) V(91) V(92) V(93) V(94) V(95) V(96) V(97) V(98) V(99)
    V(100) V(101) V(102) V(103) V(104) V(105) V(106)
#undef V
    virtual Real getPitch();
};

struct Rva0073AED0GlobalData
{
    char m_pad00[0xA81];
    bool m_showTerrainNormals;
};

struct Rva0073AED0GameClient
{
    char m_pad00[0xC0];
    unsigned int m_renderedObjectCount;
};

class PlayerList;
// data_rows.csv line 3 owns ?TheWritableGlobalData@@3PAVGlobalData@@A at
// retail 0x012ED5C8, so this declaration must spell GlobalData as a class to
// reach that definition (a struct spelling mangles to PAU and stays unresolved).
class GlobalData;
class GameClient;
extern View *TheTacticalView;
extern PlayerList *ThePlayerList;
extern GlobalData *TheWritableGlobalData;
extern GameClient *TheGameClient;

// drawTerrainNormal
// Retail 0x0073AD70 (277 bytes, ret at +0x114): the debug terrain-normal line
// drawablePostDraw draws when m_showTerrainNormals is set.  Zero Hour's
// W3DView.cpp names this file-static helper and its body (NORMLEN 20, yellow
// GameMakeColor(255,255,0,255)); the caller reaches it directly, not through
// the ILT, with the drawable in ECX.  BFME's Display wraps the line in two
// extra slots and takes float coordinates.
// Zero Hour's Coord3D carries set(const Coord3D *); the canonical layout does
// not, so this address-qualified view adds only that member.  Copying through
// it is what keeps retail's reload of pos.x/pos.y from the stack copy.
struct Coord3DSet0073AD70 : Coord3D
{
    void set(const Coord3D *a) { x = a->x; y = a->y; z = a->z; }
};

static void drawTerrainNormal(Drawable *draw)
{
    UnsignedInt color = 0xFFFFFF00;
    if (TheTerrainLogic)
    {
        Coord3DSet0073AD70 pos;
        pos.set(draw->getPosition());
        Coord3D normal;
        pos.z = TheTerrainLogic->getGroundHeight(pos.x, pos.y, &normal);
        const Real NORMLEN = 20;
        normal.x = pos.x + normal.x * NORMLEN;
        normal.y = pos.y + normal.y * NORMLEN;
        normal.z = pos.z + normal.z * NORMLEN;
        ICoord2D start, end;
        TheTacticalView->worldToScreen(&pos, &start);
        TheTacticalView->worldToScreen(&normal, &end);
        TheDisplay->drawLine0073AD70(start.x, start.y, end.x, end.y, 1.0f, color);
    }
}

// ?drawablePostDraw@@YAXPAVDrawable@@PAX@Z
// Ported from Open BFME 2 Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DViewDrawablePostDraw.cpp.
void drawablePostDraw(Drawable *draw, void *userData)
{
    Real pitch = reinterpret_cast<Rva0073AED0View *>(TheTacticalView)->getPitch();
    if (draw->isDrawableEffectivelyHidden() || pitch < 0.0f)
        return;
    Object *obj = reinterpret_cast<BFMEDrawableAIChain *>(draw)->m_object;
    int localPlayerIndex = ThePlayerList ? reinterpret_cast<Rva0073AED0PlayerList *>(ThePlayerList)->m_local->m_playerIndex : 0;
    ObjectShroudStatus ss = !obj ? OBJECTSHROUD_CLEAR : obj->getShroudedStatus(localPlayerIndex);
    if (ss > OBJECTSHROUD_PARTIAL_CLEAR)
        return;
    draw->drawIconUI();
    if (reinterpret_cast<Rva0073AED0GlobalData *>(TheWritableGlobalData)->m_showTerrainNormals)
        drawTerrainNormal(draw);
    ++reinterpret_cast<Rva0073AED0GameClient *>(TheGameClient)->m_renderedObjectCount;
}
