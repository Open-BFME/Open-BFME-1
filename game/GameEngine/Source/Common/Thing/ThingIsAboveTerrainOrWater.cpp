// cl: /DNDEBUG /MD
// Retail Thing::isAboveTerrainOrWater at RVA 0x000C3F00.
// The shipped Thing header defines this inline check as a height comparison.
// Retail reaches getHeightAboveTerrainOrWater through its ILT thunk at
// 0x00001C30 (the body is the matched 0x001324A0), so route the call the same way.
class Thing
{
public:
    float getHeightAboveTerrainOrWater() const;
    bool isAboveTerrainOrWater() const;
};

extern void j_00001c30();

bool Thing::isAboveTerrainOrWater() const
{
    union HeightRoute
    {
        void (*raw)();
        float (Thing::*member)() const;
    } route;
    route.raw = j_00001c30;
    return (this->*route.member)() > 0.0f;
}
