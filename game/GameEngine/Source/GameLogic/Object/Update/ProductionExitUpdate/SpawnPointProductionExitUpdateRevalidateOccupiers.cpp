// cl: /DNDEBUG /MD /GX- /O2 /Ob2
// Retail 0x002D2150, 59 bytes: walk m_spawnPointOccupier[m_spawnPointCount]
// at +0xCC / +0x28 and clear IDs whose GameLogic lookup returns null.
// Same flattened UpdateModule+ExitInterface prefix as
// SpawnPointProductionExitUpdateInitializeBonePositions.cpp.

class Object;

class GameLogic
{
public:
	Object *findObjectByID(int id);
};

extern GameLogic *TheGameLogic;

struct Coord3D
{
	float x;
	float y;
	float z;
};

class SpawnPointProductionExitUpdate
{
private:
	void revalidateOccupiers();
	void *m_vptr;
	void *m_moduleData;
	void *m_object;
	unsigned char m_updatePad[0x18];
	bool m_bonesInitialized;
	int m_spawnPointCount;
	Coord3D m_worldCoordSpawnPoints[10];
	float m_worldAngleSpawnPoints[10];
	unsigned int m_spawnPointOccupier[10];
};

void SpawnPointProductionExitUpdate::revalidateOccupiers()
{
	for (int positionIndex = 0; positionIndex < m_spawnPointCount; positionIndex++)
	{
		if (m_spawnPointOccupier[positionIndex] == 0)
			continue;

		if (TheGameLogic->findObjectByID(m_spawnPointOccupier[positionIndex]) == 0)
			m_spawnPointOccupier[positionIndex] = 0;
	}
}
