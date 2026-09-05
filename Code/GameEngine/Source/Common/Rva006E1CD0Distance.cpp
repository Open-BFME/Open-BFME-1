// cl: /DNDEBUG /MD /EHsc
#include <math.h>

struct Rva006E1CD0Vec
{
	float x;
	float y;
	float z;
};

class Rva006E1CD0Obj
{
public:
	unsigned char m_pad[0xD4];
	Rva006E1CD0Vec m_pos;
	float m_radius;
};

extern Rva006E1CD0Obj *Data00EF8048;

float __stdcall rva006E1CD0(float x, float y, float z)
{
	Rva006E1CD0Obj *object = Data00EF8048;
	float result = 999999.0f;
	if (object)
	{
		Rva006E1CD0Vec pos = object->m_pos;
		const float *yp = &pos.y;
		float dx = (float)fabs(pos.x - x);
		float dy = (float)fabs(*yp - y);
		float dz = (float)fabs(pos.z - z);
		result = object->m_radius - (float)sqrt(dx * dx + dy * dy + dz * dz);
	}
	return result;
}
