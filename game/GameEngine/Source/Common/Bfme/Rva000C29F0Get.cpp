// cl: /DNDEBUG /MD /EHsc

struct FieldParse;

class TerrainType
{
public:
	static const FieldParse m_terrainTypeFieldParseTable[];
};

void *Rva000C29F0Get()
{
	return const_cast<FieldParse *>(TerrainType::m_terrainTypeFieldParseTable);
}
