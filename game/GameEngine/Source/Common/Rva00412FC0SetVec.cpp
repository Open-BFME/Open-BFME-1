// cl: /O2

class Vector3
{
public:
	float X;
	float Y;
	float Z;

	Vector3(void) {};
	Vector3(const Vector3 &v) { X = v.X; Y = v.Y; Z = v.Z; }
	Vector3 &operator = (const Vector3 &v) { X = v.X; Y = v.Y; Z = v.Z; return *this; }
};

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
