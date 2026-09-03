// cl: /DNDEBUG /MD /EHsc

class Rva0076F980Mid
{
public:
	Rva0076F980Mid(const Rva0076F980Mid &other);

private:
	unsigned char m_data[12];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SpawnBehavior.h
class SpawnBehaviorModuleData
{
public:
	void setSpawnData(
		const Rva0076F980Mid &names,
		unsigned int spawnNumber,
		unsigned int startNumber,
		unsigned int replaceDelay,
		unsigned char oneShot,
		unsigned char reclaimOrphans,
		unsigned char requireSpawner);

private:
	unsigned char m_beforeSpawnData[0xc4];
	unsigned int m_spawnNumber;
	unsigned int m_startNumber;
	unsigned int m_replaceDelay;
	unsigned char m_oneShot;
	unsigned char m_reclaimOrphans;
	unsigned char m_alignment[2];
	Rva0076F980Mid m_names;
	unsigned char m_beforeRequireSpawner[8];
	unsigned char m_requireSpawner;
};

void SpawnBehaviorModuleData::setSpawnData(
	const Rva0076F980Mid &names,
	unsigned int spawnNumber,
	unsigned int startNumber,
	unsigned int replaceDelay,
	unsigned char oneShot,
	unsigned char reclaimOrphans,
	unsigned char requireSpawner)
{
	m_names.Rva0076F980Mid::Rva0076F980Mid(names);
	m_spawnNumber = spawnNumber;
	m_startNumber = startNumber;
	m_replaceDelay = replaceDelay;
	m_oneShot = oneShot;
	m_reclaimOrphans = reclaimOrphans;
	m_requireSpawner = requireSpawner;
}
