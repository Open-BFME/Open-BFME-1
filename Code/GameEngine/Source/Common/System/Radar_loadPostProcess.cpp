// cl: /DNDEBUG /MD /EHsc
// Radar::loadPostProcess, retail 0x00107270 (13 bytes). Radar's vftable
// 0x010888AC holds it in slot 1, which is where BFME's Snapshot-derived tables
// put loadPostProcess (AIAttackState, BuildListInfo, DockUpdate and Drawable
// all have their matched loadPostProcess there). Slot 3 is the matched
// Radar::xfer and slot 4 the matched Radar::refreshTerrain, which the body
// calls: Zero Hour Radar.cpp's loadPostProcess as written. Zero Hour's header
// puts refreshTerrain one slot earlier, so this TU states BFME's order.
class TerrainLogic;

extern TerrainLogic *TheTerrainLogic;

class Radar
{
public:
	virtual ~Radar();

protected:
	virtual void loadPostProcess(void);
	virtual void slot2();
	virtual void slot3();

public:
	virtual void refreshTerrain(TerrainLogic *terrain);
};

// ?loadPostProcess@Radar@@MAEXXZ
void Radar::loadPostProcess(void)
{
	// refresh the radar texture now that all the objects (specifically bridges) have
	// been loaded with their correct damage states from save game file
	refreshTerrain(TheTerrainLogic);
}
