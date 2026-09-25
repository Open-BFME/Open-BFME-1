// ?d_0043e260@@YAXXZ
// partial score=0.221344 date=2026-09-25
// ?testPoint@Rva0043E260Owner@@QBE_NPBH@Z
// cl: /O2 /Ob2 /DNDEBUG /MD

struct Rva0043E260Node
{
	Rva0043E260Node *next;
	int unused;
	int x;
	int y;
};

class Rva0043E260Owner
{
public:
	bool testPoint(const int *point) const;

	char m_unknown0000[0x1304];
	Rva0043E260Node *m_sentinel;
	int m_minX;
	int m_minY;
	int m_maxX;
	int m_maxY;
};

bool Rva0043E260Owner::testPoint(const int *point) const
{
	const int pointX = point[0];
	if (pointX < m_minX)
		return false;

	const int pointY = point[1];
	if (pointY < m_minY)
		return false;
	if (pointX > m_maxX)
		return false;
	if (pointY > m_maxY)
		return false;

	Rva0043E260Node *sentinel = m_sentinel;
	Rva0043E260Node *node = sentinel->next;
	bool inside = false;
	while (node != sentinel)
	{
		Rva0043E260Node *next = node->next;
		int x0 = node->x;
		int y0 = node->y;
		int x1;
		int y1;
		if (next != sentinel)
		{
			x1 = next->x;
			y1 = next->y;
		}
		else
		{
			Rva0043E260Node *first = sentinel->next;
			x1 = first->x;
			y1 = first->y;
		}

		if (y0 != y1 &&
			((y0 < pointY && y1 >= pointY) ||
			 (y0 >= pointY && y1 < pointY)) &&
			(x0 >= pointX || x1 >= pointX))
		{
			int numerator = (pointY - y0) * (x1 - x0);
			int denominator = y1 - y0;
			float crossing = (float)numerator / (float)denominator + (float)x0;
			if ((float)pointX <= crossing)
				inside = !inside;
		}
		node = next;
	}
	return inside;
}
