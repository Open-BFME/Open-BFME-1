// Retail RVA 0x0061D6C0: complete297B; one float argument and RET4.
// No direct calls or relocations. Unknown receiver identities retain addresses.
// Prepare +0x50 precedes the copy of the original receiver matrix at+0x18.
// Reload first receiver for its +0x48 scalar; cache the computed float across
// both callbacks and store it at owner+0x70. Reload each receiver after its
// +0x170 callback before applying the matrix through slot+0x54.
// Native Matrix3D copy and Scale reproduce all twelve copies and nine
// column-ordered multiplies; no matrix translation components are scaled.
// cl: /O2 /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath

#include "matrix3d.h"

class Rva0061D6C0MatrixOwner
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1C();
	virtual void slot20();
	virtual void slot24();
	virtual void slot28();
	virtual void slot2C();
	virtual void slot30();
	virtual void slot34();
	virtual void slot38();
	virtual void slot3C();
	virtual void slot40();
	virtual void slot44();
	virtual void slot48();
	virtual void slot4C();
	virtual void prepare(); // vtable byte offset +0x50
	virtual void apply(const Matrix3D &matrix); // vtable byte offset +0x54
	virtual void slot58();
	virtual void slot5C();
	virtual void slot60();
	virtual void slot64();
	virtual void slot68();
	virtual void slot6C();
	virtual void slot70();
	virtual void slot74();
	virtual void slot78();
	virtual void slot7C();
	virtual void slot80();
	virtual void slot84();
	virtual void slot88();
	virtual void slot8C();
	virtual void slot90();
	virtual void slot94();
	virtual void slot98();
	virtual void slot9C();
	virtual void slotA0();
	virtual void slotA4();
	virtual void slotA8();
	virtual void slotAC();
	virtual void slotB0();
	virtual void slotB4();
	virtual void slotB8();
	virtual void slotBC();
	virtual void slotC0();
	virtual void slotC4();
	virtual void slotC8();
	virtual void slotCC();
	virtual void slotD0();
	virtual void slotD4();
	virtual void slotD8();
	virtual void slotDC();
	virtual void slotE0();
	virtual void slotE4();
	virtual void slotE8();
	virtual void slotEC();
	virtual void slotF0();
	virtual void slotF4();
	virtual void slotF8();
	virtual void slotFC();
	virtual void slot100();
	virtual void slot104();
	virtual void slot108();
	virtual void slot10C();
	virtual void slot110();
	virtual void slot114();
	virtual void slot118();
	virtual void slot11C();
	virtual void slot120();
	virtual void slot124();
	virtual void slot128();
	virtual void slot12C();
	virtual void slot130();
	virtual void slot134();
	virtual void slot138();
	virtual void slot13C();
	virtual void slot140();
	virtual void slot144();
	virtual void slot148();
	virtual void slot14C();
	virtual void slot150();
	virtual void slot154();
	virtual void slot158();
	virtual void slot15C();
	virtual void slot160();
	virtual void slot164();
	virtual void slot168();
	virtual void slot16C();
	virtual void scale(float factor); // vtable byte offset +0x170
};

struct Rva0061D6C0Dispatcher
{
	unsigned char m_unmodelled_00[8];
	Rva0061D6C0MatrixOwner *m_first;
	Rva0061D6C0MatrixOwner *m_second;
	unsigned char m_unmodelled_10[0x60];
	float m_lastScale;
	void scale(float factor);
};

void Rva0061D6C0Dispatcher::scale(float factor)
{
	Rva0061D6C0MatrixOwner *owner = m_first;
	if (owner == 0)
		return;

	owner->prepare();
	Matrix3D matrix(*reinterpret_cast<const Matrix3D *>((char *)owner + 0x18));

	owner = m_first;
	float scaled = factor * *reinterpret_cast<float *>(
		reinterpret_cast<unsigned char *>(owner) + 0x48);
	m_lastScale = scaled;
	matrix.Scale(factor);
	owner->scale(scaled);
	owner = m_first;
	owner->apply(matrix);

	owner = m_second;
	if (owner == 0)
		return;
	owner->scale(scaled);
	owner = m_second;
	owner->apply(matrix);
}
