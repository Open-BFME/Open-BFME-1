// cl: /DNDEBUG /MD /EHsc

struct FieldParse;

// TerrainRoads.cpp emits the table as a protected static (@1).
class TerrainRoadType
{
	friend void *Rva000C2D30Get();

protected:
	static const FieldParse m_terrainBridgeFieldParseTable[];
};

void *Rva000C2D30Get()
{
	return const_cast<FieldParse *>(TerrainRoadType::m_terrainBridgeFieldParseTable);
}
