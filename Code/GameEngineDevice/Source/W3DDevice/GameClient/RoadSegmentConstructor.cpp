// The 0xBC-byte layout and adjacency to RoadSegment::operator= identify this
// constructor; member names follow the upstream W3DRoadBuffer declaration.

class RoadSegment
{
public:
	RoadSegment(void);

private:
	float m_point1Location[2];
	float m_point1Top[2];
	float m_point1Bottom[2];
	int m_point1Count;
	unsigned char m_point1Flags[4];
	float m_point2Location[2];
	float m_point2Top[2];
	float m_point2Bottom[2];
	int m_point2Count;
	unsigned char m_point2Flags[4];
	float m_curveRadius;
	int m_type;
	float m_scale;
	float m_widthInTexture;
	int m_uniqueID;
	unsigned char m_visible;
	unsigned char m_alignment[3];
	int m_numVertices;
	void *m_vertexBuffer;
	int m_numIndices;
	void *m_indexBuffer;
	float m_infoLocation[2];
	float m_infoRoadNormal[2];
	float m_infoRoadVector[2];
	float m_infoCorners[4][2];
	float m_infoUOffset;
	float m_infoVOffset;
	float m_infoScale;
	float m_boundsCenter[3];
	float m_boundsRadius;
};

RoadSegment::RoadSegment(void)
{
	m_point1Location[0] = 0;
	m_point1Location[1] = 0;
	m_point1Top[0] = 0;
	m_point1Top[1] = 0;
	m_point1Bottom[0] = 0;
	m_point1Bottom[1] = 0;
	m_point1Count = 0;
	m_point1Flags[0] = 0;
	m_point1Flags[1] = 0;
	m_point1Flags[2] = 0;
	m_point1Flags[3] = 0;
	m_point2Location[0] = 0;
	m_point2Location[1] = 0;
	m_point2Top[0] = 0;
	m_point2Top[1] = 0;
	m_point2Bottom[0] = 0;
	m_point2Bottom[1] = 0;
	m_point2Count = 0;
	m_point2Flags[0] = 0;
	m_point2Flags[1] = 0;
	m_point2Flags[2] = 0;
	m_point2Flags[3] = 0;
	m_curveRadius = 0;
	m_type = 0;
	m_scale = 0;
	m_widthInTexture = 0;
	m_uniqueID = 0;
	m_visible = 0;
	m_numVertices = 0;
	m_vertexBuffer = 0;
	m_numIndices = 0;
	m_indexBuffer = 0;
	m_infoLocation[0] = 0;
	m_infoLocation[1] = 0;
	m_infoRoadNormal[0] = 0;
	m_infoRoadNormal[1] = 0;
	m_infoRoadVector[0] = 0;
	m_infoRoadVector[1] = 0;
	m_infoUOffset = 0;
	m_infoVOffset = 0;
	m_infoScale = 0;
	m_infoCorners[0][0] = 0;
	m_infoCorners[0][1] = 0;
	m_infoCorners[1][0] = 0;
	m_infoCorners[1][1] = 0;
	m_infoCorners[2][0] = 0;
	m_infoCorners[2][1] = 0;
	m_infoCorners[3][0] = 0;
	m_infoCorners[3][1] = 0;
	m_boundsCenter[0] = 0;
	m_boundsCenter[1] = 0;
	m_boundsCenter[2] = 0;
	m_boundsRadius = 0;
}
