// cl: /O2 /Ob0

#include <stdlib.h>

struct Rva005A49E0Point
{
	int x;
	int y;
};

class Rva005A49E0RangeTest
{
public:
	bool isBeyondRange(const Rva005A49E0Point *first, const Rva005A49E0Point *second) const;

private:
	char m_padding[0x10EC];
	unsigned int m_range;
};

bool Rva005A49E0RangeTest::isBeyondRange(
	const Rva005A49E0Point *first,
	const Rva005A49E0Point *second) const
{
	Rva005A49E0Point delta;
	delta.x = first->x - second->x;
	delta.y = first->y - second->y;
	if ((unsigned int)abs(delta.x) > m_range ||
		(unsigned int)abs(delta.y) > m_range)
		return true;
	return false;
}
