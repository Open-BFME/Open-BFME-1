// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD
// Retail 0x00711130, 296 bytes; caller-proven member ABI.
struct Triple006E2540
{
	float x;
	float y;
	float z;
	void sub(const Triple006E2540 *other)
	{
		x -= other->x; y -= other->y; z -= other->z;
	}
};

// Retail's multiplication constant is 0.5f at 0x0107533C.

class Rva00711130Target
{
public:
	char m_pad0[0xd8];
	Triple006E2540 m_pos1;		// +0xd8
	Triple006E2540 m_pos2;		// +0xe4
};

class Sink006E2540
{
public:
	void adjust(Triple006E2540 *point, bool subtract);

	char m_pad[0x12c];
	Rva00711130Target *m_target;
};

void Sink006E2540::adjust(Triple006E2540 *point, bool subtract)
{
	Triple006E2540 pos2, pos1;
	Rva00711130Target *target = m_target;
	const Rva00711130Target *source = target;
	// Retail copies these float bits as dwords. The unsigned views preserve
	// MSVC 7.1's raw transfer order; they are not portable C++ aliasing.
	*reinterpret_cast<unsigned *>(&pos2.y) =
		*reinterpret_cast<const unsigned *>(&source->m_pos2.y);
	float pos2x = source->m_pos2.x;
	pos2.z = source->m_pos2.z;
	pos1.x = source->m_pos1.x;
	pos1.y = source->m_pos1.y;
	pos1.z = source->m_pos1.z;
	Triple006E2540 scaled;
	float pos2xResult, pos2yResult;
	if (subtract)
	{
		pos2xResult = pos2x - point->x;
		pos2yResult = pos2.y - point->y;
		pos2.z -= point->z;
		scaled.x = point->x * 0.5f;
		scaled.y = point->y * 0.5f;
		scaled.z = point->z * 0.5f;
		pos1.sub(&scaled);
	}
	else
	{
		pos2xResult = pos2x + point->x;
		pos2yResult = pos2.y + point->y;
		pos2.z += point->z;
		scaled.x = point->x * 0.5f;
		scaled.y = point->y * 0.5f;
		scaled.z = point->z * 0.5f;
		pos1.x += scaled.x;
		pos1.y = scaled.y + pos1.y;
		pos1.z += scaled.z;
	}
	target->m_pos2.x = pos2xResult;
	*reinterpret_cast<unsigned *>(&target->m_pos2.z) =
		*reinterpret_cast<unsigned *>(&pos2.z);
	target->m_pos2.y = pos2yResult;
	m_target->m_pos1 = pos1;
}
