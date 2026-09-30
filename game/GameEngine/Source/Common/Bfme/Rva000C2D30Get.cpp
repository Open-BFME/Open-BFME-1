// cl: /DNDEBUG /MD /EHsc

struct FieldParse;

class TerrainRoadType
{
public:
	static const FieldParse m_terrainBridgeFieldParseTable[];
};

void *Rva000C2D30Get()
{
	return const_cast<FieldParse *>(TerrainRoadType::m_terrainBridgeFieldParseTable);
}
