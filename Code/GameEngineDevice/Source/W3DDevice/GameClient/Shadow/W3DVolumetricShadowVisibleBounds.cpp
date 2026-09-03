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

extern const float BfmeZeroRange;

class W3DVolumetricShadow
{
private:
	unsigned char m_unreconstructed_000[ 0x74 ];
	RenderObjClass *m_robj;
	unsigned char m_unreconstructed_078[ 8 ];
	float m_robjExtent;
	float m_extraExtrusionPadding;
	unsigned char m_unreconstructed_088[ 8 ];
	float m_lightOffsetX;
	float m_lightOffsetY;
	float m_lightOffsetZ;

public:
	bool bfmeIntersectsVisibleBounds(const AABoxClass &box) const;
};

bool W3DVolumetricShadow::bfmeIntersectsVisibleBounds(const AABoxClass &box) const
{
	Vector3 pos = m_robj->Get_Position();

	if (pos.Z + m_extraExtrusionPadding < box.Center.Z)
		return 0;

	return ((m_lightOffsetX > BfmeZeroRange ? m_lightOffsetX : BfmeZeroRange) +
				m_robjExtent + pos.X > box.Center.X &&
				pos.X - m_robjExtent +
					(m_lightOffsetX < BfmeZeroRange ? m_lightOffsetX : BfmeZeroRange) < box.Center.X &&
				(m_lightOffsetY > BfmeZeroRange ? m_lightOffsetY : BfmeZeroRange) +
					m_robjExtent + pos.Y > box.Center.Y &&
				pos.Y - m_robjExtent +
					(m_lightOffsetY < BfmeZeroRange ? m_lightOffsetY : BfmeZeroRange) < box.Center.Y)
		;
}
