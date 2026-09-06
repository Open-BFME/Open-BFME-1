class Rva00106F20Radar
{
public:
	void computeAspect(float *xRatio, float *yRatio);

private:
	struct Coord3D
	{
		float x;
		float y;
		float z;
	};

	struct Region3D
	{
		Coord3D lo;
		Coord3D hi;
	};

	unsigned char m_pad[0x143c];
	Region3D m_mapExtent;
};

void Rva00106F20Radar::computeAspect(float *xRatio, float *yRatio)
{
	if (m_mapExtent.hi.x - m_mapExtent.lo.x > m_mapExtent.hi.y - m_mapExtent.lo.y)
	{
		*xRatio = 1.0f;
		*yRatio = (m_mapExtent.hi.y - m_mapExtent.lo.y) /
			(m_mapExtent.hi.x - m_mapExtent.lo.x);
	}
	else
	{
		*yRatio = 1.0f;
		*xRatio = (m_mapExtent.hi.x - m_mapExtent.lo.x) /
			(m_mapExtent.hi.y - m_mapExtent.lo.y);
	}
}
