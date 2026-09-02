// cl: /DNDEBUG /MD

class Vector3
{
public:
	float X;
	float Y;
	float Z;
};

struct AABoxClass
{
	Vector3 Center;
	Vector3 Extent;
};

class RenderObjClass
{
public:
	Vector3 Get_Position() const;
};

class W3DVolumetricShadow
{
private:
	unsigned char m_unreconstructed_000[ 0x74 ];
	RenderObjClass *m_robj;
	unsigned char m_unreconstructed_078[ 8 ];
	float m_robjExtent;

public:
	int bfmeIntersectsVisibleBounds(const AABoxClass &box) const;
};

int W3DVolumetricShadow::bfmeIntersectsVisibleBounds(const AABoxClass &box) const
{
	Vector3 pos = m_robj->Get_Position();

	if (pos.X + m_robjExtent > box.Center.X - box.Extent.X &&
		pos.X - m_robjExtent < box.Center.X + box.Extent.X &&
		pos.Y + m_robjExtent > box.Center.Y - box.Extent.Y &&
		pos.Y - m_robjExtent < box.Center.Y + box.Extent.Y)
		return true;

	return false;
}
