typedef float Real;

class TerrainRoadType
{
public:
	Real getRoadWidth();

private:
	unsigned char m_padding000[0x14];
	Real m_roadWidth;
};

Real TerrainRoadType::getRoadWidth()
{
	return m_roadWidth;
}
