// cl: /DNDEBUG /MD /EHsc

// Open-BFME: TerrainRoadCollection scalar-deleting destructor at retail
// 0x00601560 (30 bytes). The matched constructor at 0x00601430, complete
// destructor at 0x00601490, subsystem registration, and named road/bridge
// lookup methods establish the authentic class identity.

class TerrainRoadCollection
{
public:
	__declspec(noinline) virtual ~TerrainRoadCollection();
};

TerrainRoadCollection::~TerrainRoadCollection()
{
}

void Force_TerrainRoadCollection_Deleting_Destructor(TerrainRoadCollection *value)
{
	delete value;
}
