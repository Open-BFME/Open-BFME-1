// cl: /O2 /Igame/Libraries/Source/WWVegas/WWLib

#include "../../../Libraries/Source/WWVegas/WWMath/vector3.h"

class Rva00412FC0
{
	unsigned char m_pad[0x1C];
	Vector3 m_pos;

public:
	void set(const Vector3 *p);
};

void Rva00412FC0::set(const Vector3 *p)
{
	Vector3 tmp = *p;
	m_pos = tmp;
}
