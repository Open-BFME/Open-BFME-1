// cl: /DNDEBUG /MD
// Retail Thing::isAboveTerrainOrWater at RVA 0x000C3F00.
// The shipped Thing header defines this inline check as a height comparison.
class Thing
{
public:
    float getHeightAboveTerrainOrWater() const;
    bool isAboveTerrainOrWater() const;
};

bool Thing::isAboveTerrainOrWater() const
{
    return getHeightAboveTerrainOrWater() > 0.0f;
}
