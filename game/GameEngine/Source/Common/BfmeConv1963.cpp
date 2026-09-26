// cl: /GX-
class Vector3
{
public:
	float X;
	float Y;
	float Z;
};

class RenderObjClass
{
public:
	Vector3 Get_Position() const;
};

class BfmeCacheERV
{
public:
	~BfmeCacheERV() throw() {}

	float m_bfmeXERV;
	float m_bfmeYERV;
	float m_bfmeZERV;
};

class BfmeHostERV
{
public:
	BfmeCacheERV *bfmeCachePosERV();

	unsigned char m_bfmeHeadERV[0x104];
	RenderObjClass *m_bfmeRenderERV;
};

BfmeCacheERV *BfmeHostERV::bfmeCachePosERV()
{
	Vector3 pos = m_bfmeRenderERV->Get_Position();

	static BfmeCacheERV s_bfmeCacheERV;

	s_bfmeCacheERV.m_bfmeXERV = pos.X;
	s_bfmeCacheERV.m_bfmeYERV = pos.Y;
	s_bfmeCacheERV.m_bfmeZERV = pos.Z;

	return &s_bfmeCacheERV;
}
