// cl: /DNDEBUG /MD
// Retail 0x0016FFD0: bounds-checked lookup through the path's STLport
// coordinate vector.  The surviving identity is address-derived.

struct Rva0016FFD0Coord3D
{
	float x;
	float y;
	float z;
};

template <class T> class Rva0016FFD0Vector
{
public:
	typedef unsigned int size_type;
	typedef T *iterator;
	typedef const T *const_iterator;
	typedef const T &const_reference;

	iterator begin() { return _M_start; }
	const_iterator begin() const { return _M_start; }
	iterator end() { return _M_finish; }
	const_iterator end() const { return _M_finish; }
	size_type size() const { return size_type(_M_finish - _M_start); }
	const_reference operator[](size_type n) const { return *(begin() + n); }

	iterator _M_start;
	iterator _M_finish;
};

class Rva0016FFD0Path
{
	char m_unknown[0x44];
	Rva0016FFD0Vector<Rva0016FFD0Coord3D> m_points;

public:
	Rva0016FFD0Coord3D *getPoint(int index);
};

Rva0016FFD0Coord3D *Rva0016FFD0Path::getPoint(int index)
{
	if (index >= 0)
	{
		if ((unsigned int)index < m_points.size())
			return const_cast<Rva0016FFD0Coord3D *>(&m_points[index]);
	}
	return 0;
}

class Rva0016FFD0PathOwner
{
	char m_unknown[0x30];
	Rva0016FFD0Path *m_path;

public:
	Rva0016FFD0Coord3D *getPoint(int index);
};

Rva0016FFD0Coord3D *Rva0016FFD0PathOwner::getPoint(int index)
{
	return m_path->getPoint(index);
}
