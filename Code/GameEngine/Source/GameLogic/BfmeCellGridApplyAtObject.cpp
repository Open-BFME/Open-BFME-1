// cl: /O2 /Ob2 /G6

typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

class Object
{
public:
	const Coord3D *getPosition() const { return &m_position; }

private:
	unsigned char m_pad000[0x38];
	Coord3D m_position;
};

class BfmeCell
{
public:
	void bfmeAdd(Real amount, Int firstIndex, Int secondIndex);

private:
	unsigned char m_data[0x88];
};

class BfmeCellGrid
{
public:
	void bfmeApplyAtObject(const Object *object,
		Real amount, Int firstIndex, Int secondIndex) const;

private:
	Int m_width;
	Int m_height;
	UnsignedInt m_cellCount;
	Real m_cellSize;
	Real m_offset;
	BfmeCell *m_cells;
	Int *m_cellValues;
};

void BfmeCellGrid::bfmeApplyAtObject(const Object *object,
	Real amount, Int firstIndex, Int secondIndex) const
{
	const Coord3D *position = object->getPosition();
	if (m_cellSize > 0.0f)
	{
		Int row = (Int)((position->y - m_offset) / m_cellSize);
		Int index = row * m_width;
		index += (Int)((position->x - m_offset) / m_cellSize);

		if ((UnsignedInt)index < m_cellCount && index != 0x7fffffff)
			m_cells[index].bfmeAdd(amount, firstIndex, secondIndex);
	}
}
