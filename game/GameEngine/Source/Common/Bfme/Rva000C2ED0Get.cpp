// cl: /DNDEBUG /MD /EHsc

struct FieldParse;

void *Rva000C2ED0Get();

class TerrainRoadType
{
	// Match TerrainRoads.h: MSVC encodes this access level in the symbol name.
protected:
	static const FieldParse m_terrainRoadFieldParseTable[];
	friend void *Rva000C2ED0Get();
};

void *Rva000C2ED0Get()
{
	return const_cast<FieldParse *>(TerrainRoadType::m_terrainRoadFieldParseTable);
}
