// The buffer constructor supplies the identity: its 200-element vector call
// uses this body and W3DBridge::~W3DBridge with an element size of 0x114.

class W3DBridge
{
public:
	W3DBridge(void);

private:
	float m_start[3];
	float m_end[3];
	float m_scale;
	float m_length;
	int m_bridgeType;
	float m_bounds[4];
	void *m_bridgeTexture;
	void *m_leftMesh;
	float m_leftTransform[12];
	float m_minY;
	float m_maxY;
	float m_leftMinX;
	float m_leftMaxX;
	void *m_sectionMesh;
	float m_sectionTransform[12];
	float m_sectionMinX;
	float m_sectionMaxX;
	void *m_rightMesh;
	float m_rightTransform[12];
	float m_rightMinX;
	float m_rightMaxX;
	int m_firstIndex;
	int m_numVertices;
	int m_firstVertex;
	int m_numPolygons;
	unsigned char m_visible;
	unsigned char m_alignment[3];
	void *m_templateNameData;
	int m_damageState;
	unsigned char m_enabled;
};

W3DBridge::W3DBridge(void)
{
	m_scale = 1.0f;
	m_length = 1.0f;
	m_bridgeType = 0;
	m_bridgeTexture = 0;
	m_leftMesh = 0;
	m_minY = 0;
	m_maxY = 0;
	m_leftMinX = 0;
	m_leftMaxX = 0;
	m_sectionMesh = 0;
	m_sectionMinX = 0;
	m_sectionMaxX = 0;
	m_rightMesh = 0;
	m_rightMinX = 0;
	m_rightMaxX = 0;
	m_firstIndex = 0;
	m_numVertices = 0;
	m_firstVertex = 0;
	m_numPolygons = 0;
	m_visible = 0;
	m_templateNameData = 0;
	m_damageState = 0;
	m_enabled = 0;
}
