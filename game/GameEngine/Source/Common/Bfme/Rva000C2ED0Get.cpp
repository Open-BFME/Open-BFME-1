// cl: /DNDEBUG /MD /EHsc

struct FieldParse;

class TerrainRoadType
{
public:
	static const FieldParse m_terrainRoadFieldParseTable[];
};

void *Rva000C2ED0Get()
{
	return const_cast<FieldParse *>(TerrainRoadType::m_terrainRoadFieldParseTable);
}
