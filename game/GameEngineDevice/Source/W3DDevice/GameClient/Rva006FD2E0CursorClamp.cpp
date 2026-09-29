// cl: /DNDEBUG /MD

// Retail 0x006FD2E0 (174 bytes): a W3DMouse vtable slot (rdata 0x00D20824 via
// ILT 0x000493B4, beside the mouse's byte-flag setters) that stores the
// cursor's world position and, while the tactical view reports it should
// (view slot 8), clamps x/y to the +0xD4..+0xE0 bounds -- the upper bounds
// first, then the lower, each through a reference-returning min/max.  The
// field-wise copy is what places this and the x/y addresses in retail's
// registers.  IDENTITY IS NOT RECOVERED: owner and method keep descriptive
// address-derived names.

typedef float Real;

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

class View
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0c() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1c() = 0;
	virtual bool slot20() = 0;
};

extern View *TheTacticalView;

template <class T>
static inline const T &lowerOf(const T &a, const T &b)
{
	return a < b ? a : b;
}

template <class T>
static inline const T &higherOf(const T &a, const T &b)
{
	return a > b ? a : b;
}

class Rva006FD2E0Mouse
{
public:
	void setCursorWorldPosition(const Coord3D *pos);

private:
	unsigned char m_head[0xa8];
	Coord3D m_worldPos;
	unsigned char m_padB4[0xd4 - 0xb4];
	Real m_minX;
	Real m_minY;
	Real m_maxX;
	Real m_maxY;
};

void Rva006FD2E0Mouse::setCursorWorldPosition(const Coord3D *pos)
{
	m_worldPos.x = pos->x;
	m_worldPos.y = pos->y;
	m_worldPos.z = pos->z;
	if (TheTacticalView->slot20())
	{
		m_worldPos.x = lowerOf(m_worldPos.x, m_maxX);
		m_worldPos.y = lowerOf(m_worldPos.y, m_maxY);
		m_worldPos.x = higherOf(m_worldPos.x, m_minX);
		m_worldPos.y = higherOf(m_worldPos.y, m_minY);
	}
}
