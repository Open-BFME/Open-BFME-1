// ?getMaxHeightBelowPosition@GeometryInfo@@QBEMXZ
// partial score=0.85 date=2026-09-03
// cl: /DNDEBUG /MD /EHsc
// Open-BFME: GeometryInfo::getMaxHeightBelowPosition, retail 0x0087E070,
// 84 bytes.
//
// BFME's GeometryInfo holds a run of shapes, not one: the body walks
// [this+0x2C, this+0x30) with a 0x24 stride and answers with the deepest
// enabled shape's extent below the object's position.
//
// Only a sphere (type 0) extends below, contributing its major radius;
// anything else contributes nothing.
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
	Real getMaxHeightBelowPosition(void) const;

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

Real GeometryInfo::getMaxHeightBelowPosition(void) const
{
	Real best = 0.0f;
	Real depth = 0.0f;

	for (const BfmeShape *shape = m_shapes; shape != m_shapesEnd; ++shape)
	{
		if (!shape->m_enabled)
			continue;

		switch (shape->m_type)
		{
			case GEOMETRY_SPHERE:
				depth = shape->m_majorRadius;
				break;

			case GEOMETRY_BOX:
			case GEOMETRY_CYLINDER:
			default:
				depth = 0.0f;
				break;
		}

		best = bfmeMax(depth, best);
	}

	return best;
}
