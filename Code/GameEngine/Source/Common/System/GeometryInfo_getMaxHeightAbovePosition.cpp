// cl: /DNDEBUG /MD /EHsc
// Open-BFME: GeometryInfo::getMaxHeightAbovePosition, retail 0x0087E000,
// 101 bytes.
//
// BFME's GeometryInfo holds a run of shapes, not one: the body walks
// [this+0x2C, this+0x30) with a 0x24 stride and answers with the tallest
// enabled shape's height above the object's position.
//
// The shape's own contribution is the reference's geometry switch -- a sphere
// (type 0) contributes its major radius, a cylinder or a box (1 and 2) its
// height, anything else nothing -- and the z offset at +0x18 is added to it.
//
// The running maximum is a select, not a branch: MSVC picks the address of the
// candidate or of the running best and reloads through it, which is what the
// fcomp/fnstsw/test ah,0x41 pair feeds.

typedef float Real;

// The running maximum comes back as a REFERENCE: that is what makes MSVC pick
// the address of the candidate or of the running best and reload through it,
// rather than branching around a store.
inline const Real &bfmeMax(const Real &a, const Real &b)
{
	return (a > b) ? a : b;
}

enum GeometryType
{
	GEOMETRY_SPHERE = 0,
	GEOMETRY_CYLINDER,
	GEOMETRY_BOX
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Geometry.h
class GeometryInfo
{
public:
	Real getMaxHeightAbovePosition(void) const;

private:
	struct BfmeShape
	{
		GeometryType m_type;					// +0x00
		Real m_height;						// +0x04
		Real m_majorRadius;					// +0x08
		unsigned char m_unmodelled_00c[0x18 - 0x0C];
		Real m_offsetZ;						// +0x18
		unsigned char m_unmodelled_01c[0x20 - 0x1C];
		bool m_enabled;						// +0x20
		unsigned char m_unmodelled_021[0x24 - 0x21];
	};

	unsigned char m_unmodelled_000[0x2C];
	BfmeShape *m_shapes;						// this+0x2C
	BfmeShape *m_shapesEnd;						// this+0x30
};

Real GeometryInfo::getMaxHeightAbovePosition(void) const
{
	Real best = 0.0f;

	for (const BfmeShape *shape = m_shapes; shape != m_shapesEnd; ++shape)
	{
		if (!shape->m_enabled)
			continue;

		Real height = 0.0f;
		switch (shape->m_type)
		{
			case GEOMETRY_SPHERE:
				height = shape->m_majorRadius;
				break;
			case GEOMETRY_CYLINDER:
			case GEOMETRY_BOX:
				height = shape->m_height;
				break;
		}

		height += shape->m_offsetZ;
		best = bfmeMax(height, best);
	}

	return best;
}
