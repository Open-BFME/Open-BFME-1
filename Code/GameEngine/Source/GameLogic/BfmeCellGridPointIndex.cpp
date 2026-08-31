// cl: /O2 /Ob2 /G6

typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;

struct BfmePoint1560
{
	Real X;
	Real Y;
};

class BfmeCellGrid
{
public:
	UnsignedInt bfmePointIndex(const BfmePoint1560 &point);

private:
	Int m_width;
	Int m_height;
	UnsignedInt m_cellCount;
	Real m_cellSize;
	Real m_origin;
};

UnsignedInt BfmeCellGrid::bfmePointIndex(const BfmePoint1560 &point)
{
	if (m_cellSize > 0.0f)
	{
		Int row = (Int)((point.Y - m_origin) / m_cellSize);
		Int index = row * m_width;
		index += (Int)((point.X - m_origin) / m_cellSize);
		if ((UnsignedInt)index < m_cellCount)
			return index;
	}
	return 0x7fffffff;
}
