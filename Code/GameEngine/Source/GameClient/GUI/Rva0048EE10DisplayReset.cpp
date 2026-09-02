// cl: /DNDEBUG /MD
// Retail display-object reset at 0x0048EE10.  The owning concrete UI class is
// not recovered; the member layout and called child reset are byte-proven.

struct Rva0048EE10Bounds
{
	int unused0;
	int unused4;
	int lowX;
	int lowY;
	int highX;
	int highY;
};

class Rva0048EE10Child
{
public:
	void reset();
};

class Rva0048EE10Display
{
public:
	void resetBounds();

private:
	void *m_unused0;
	void *m_unused4;
	Rva0048EE10Bounds *m_bounds;
	Rva0048EE10Child **m_begin;
	Rva0048EE10Child **m_end;
};

void Rva0048EE10Display::resetBounds()
{
	Rva0048EE10Bounds *bounds = m_bounds;
	int bound = 0xffff;
	bounds->lowY = bound;
	bounds->lowX = bound;
	bound = -1;
	bounds->highY = bound;
	bounds->highX = bound;

	Rva0048EE10Child **it = m_begin;
	Rva0048EE10Child **end = m_end;
	while( it != end ) {
		(*it)->reset();
		++it;
	}
}
