// Open-BFME5 conversions.

struct BfmeSrc941B
{
	char m_bfmePad[0x50c];
	int m_bfmeVal;
};

class BfmeThing941B
{
public:
	int bfmeGo941B(void *a, void *b);
	int m_bfmePad;
	BfmeSrc941B *m_bfmeSrc;
};

int BfmeThing941B::bfmeGo941B(void *a, void *b)
{
	return (int)(float)m_bfmeSrc->m_bfmeVal;
}

class BfmeThing941F
{
public:
	void bfmeGo941F(void *a);
	void bfmeOne941F();
	void bfmeTwo941F(void *a);
};

void BfmeThing941F::bfmeGo941F(void *a)
{
	bfmeOne941F();
	bfmeTwo941F(a);
}

#include "../../../Libraries/Include/Lib/Coord3D.h"

// Matched callers DieMuxData::isDieApplicable (0x002551F0) and
// Object::rva001E3E40 (0x001E3E40) reach 0x001E3E20 through ILT 0x0000B069
// with ECX = this Object, the other Object pushed and a hidden Coord3D result
// slot. The body keeps ECX and forwards the result slot and the other
// Object's position (+0x38) to Object::bfmeDelta (ILT 0x0000B00F).
class Object
{
public:
	Coord3D bfmeDelta(const Coord3D *pos) const;
	Coord3D bfmeGo941G(const Object *other) const;

private:
	unsigned char m_bfmeHead[0x38];			// +0x00
	Coord3D m_position;				// +0x38
};

// ?bfmeGo941G@Object@@QBE?AUCoord3D@@PBV1@@Z
Coord3D Object::bfmeGo941G(const Object *other) const
{
	return bfmeDelta(&other->m_position);
}

