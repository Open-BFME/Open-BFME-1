// W3DRadar::refreshTerrain at 0x006C4280 calls this body through ILT
// 0x0003A21A before rebuilding its device texture.  That matched caller and
// the original Radar/W3DRadar declarations identify the virtual pointer ABI.
class TerrainLogic;

class Radar
{
public:
	virtual void refreshTerrain(TerrainLogic *terrain);

private:
	char m_unmodeled04[0x1468 - 4];
	unsigned int m_reconstructTerrain;
};

void Radar::refreshTerrain(TerrainLogic *)
{
	m_reconstructTerrain = 0;
}
