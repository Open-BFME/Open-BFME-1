// cl: /DNDEBUG /MD /EHsc
// Open-BFME: GeometryInfo::getMaxHeightBelowPosition, retail 0x0087E070,
// 84 bytes.
//
// BFME's GeometryInfo holds a run of shapes.  This body walks
// [this+0x2C, this+0x30) with a 0x24 stride and returns the largest enabled
// sphere radius.  Cylinders and boxes do not extend below their canonical
// position, matching the original GeometryInfo implementation.

typedef float Real;

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

class GeometryInfo
{
public:
	Real getMaxHeightBelowPosition(void) const;

private:
	struct BfmeShape
	{
		Real getMaxHeightBelowPosition(void) const
		{
			switch (m_type)
			{
				case GEOMETRY_SPHERE:
					return m_majorRadius;
				case GEOMETRY_CYLINDER:
				case GEOMETRY_BOX:
					return 0.0f;
			}
			return 0.0f;
		}

		GeometryType m_type;
		Real m_height;
		Real m_majorRadius;
		unsigned char m_unmodelled_00c[0x20 - 0x0C];
		bool m_enabled;
		unsigned char m_unmodelled_021[0x24 - 0x21];
	};

	unsigned char m_unmodelled_000[0x2C];
	BfmeShape *m_shapes;
	BfmeShape *m_shapesEnd;
};

Real GeometryInfo::getMaxHeightBelowPosition(void) const
{
	Real best = 0.0f;

	for (const BfmeShape *shape = m_shapes; shape != m_shapesEnd; ++shape)
	{
		if (!shape->m_enabled)
			continue;

		Real below = shape->getMaxHeightBelowPosition();

		best = bfmeMax(below, best);
	}

	return best;
}
