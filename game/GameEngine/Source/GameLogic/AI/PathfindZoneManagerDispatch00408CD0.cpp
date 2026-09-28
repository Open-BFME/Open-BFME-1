// cl: /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /MD /EHsc /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include
// stlport
// Retail RVA 0x00408CD0, 545 bytes through RET 12.
// Address-preserving name: this is the dirty-region zone dispatcher, distinct
// from calculateZonesIncremental at 0x00408AD0. Receiver identity follows the
// same manager passed to bfmeCollapseZones, bfmeFlattenZones and method00402F50;
// the bounds at +8 and the +0x23628 zone-column table agree with those bodies.
// +0x23618 is a 16-byte-element vector (sub pointers / 16 and the instantiated
// BitFlags<113> copy at the clear site). The original private name is unproved.
// Retail resets the file-local double at VA 0x012F10C0 from a verified 0.0.
// The helper pins name bodies reached by decoded ILTs, with RET 8 / RET 20;
// bfmeCollapseZones differs from its matched TU only by class/struct tag.
#include "Common/BitFlags.h"
#include "Lib/BaseType.h"
class PathfindCell;
class PathfindLayer;
struct LayerRecord403EC0;
class ZoneLayers403EC0 { public: void update(LayerRecord403EC0*); };
struct ZoneBlock00408CD0 { char bytes0[5]; bool flag5; char bytes6[0x222]; };
static double zoneTime00408CD0;
class PathfindZoneManager {
public:
 void dispatch00408CD0(PathfindCell**, PathfindLayer*, const IRegion2D&);
 void bfmeFlattenZones(int,int);
 void bfmeCollapseZones(PathfindCell**,const IRegion2D&,bool);
 void method00402F50(PathfindCell**,PathfindLayer*,const IRegion2D&);
private:
 void bfmeZonePhase004042C0(PathfindCell**,const IRegion2D&);
 void phase004085F0(PathfindCell**,const IRegion2D&);
 void phase00404B10(PathfindCell**,PathfindLayer*,const IRegion2D&,int,int);
 char bytes0[4]; int state4; IRegion2D bounds8;
 char bytes18[0x23618-0x18];
 std::vector<BitFlags<113> > regions23618;
 void* m_blockOfZoneBlocks;
 ZoneBlock00408CD0** columns23628;
};
void PathfindZoneManager::dispatch00408CD0(PathfindCell** map,
    PathfindLayer* layers, const IRegion2D& bounds)
{
    if (state4 == 0 || bounds.lo.x != bounds8.lo.x ||
        bounds.lo.y != bounds8.lo.y || bounds.hi.x != bounds8.hi.x ||
        bounds.hi.y != bounds8.hi.y)
    {
        state4 = 0;
        zoneTime00408CD0 = 0.0;
        bounds8 = bounds;
    }
    if (state4 >= 0 && state4 < 1)
    {
        IRegion2D blockBounds;
        blockBounds.lo.x = bounds.lo.x / 16;
        blockBounds.lo.y = bounds.lo.y / 16;
        blockBounds.hi.x = bounds.hi.x / 16;
        blockBounds.hi.y = bounds.hi.y / 16;
        for (int y = blockBounds.lo.y; y <= blockBounds.hi.y; ++y)
            for (int x = blockBounds.lo.x; x <= blockBounds.hi.x; ++x)
                columns23628[x][y].flag5 = false;
        if (regions23618.size())
            bfmeZonePhase004042C0(map, bounds);
    }
    else if (state4 >= 1 && state4 < 2)
    {
        if (regions23618.size())
            bfmeCollapseZones(map, bounds, true);
        ((ZoneLayers403EC0*)this)->update((LayerRecord403EC0*)layers);
    }
    else if (state4 >= 2 && state4 < 3)
    {
        if (regions23618.size())
            phase004085F0(map, bounds);
    }
    else if (state4 >= 3 && state4 < 4)
    {
        phase00404B10(map, layers, bounds, (state4 - 3) * 100, (state4 - 2) * 100);
    }
    else if (state4 >= 4 && state4 < 5)
    {
        bfmeFlattenZones((state4 - 4) * 100, (state4 - 3) * 100);
    }
    else
    {
        method00402F50(map, layers, bounds);
        state4 = -1;
        regions23618.clear();
    }
    if (state4 >= 0)
        ++state4;
}
