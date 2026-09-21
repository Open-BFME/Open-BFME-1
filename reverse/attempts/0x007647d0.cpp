// ?update@Rva007647D0@@QAEXXZ
// partial score=0.89 date=2026-09-21
// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD

// Retail 0x007647D0, 313B: a no-arg thiscall in the W3DScriptedModelDraw
// render-transform family. 'this'+4 holds an object whose +0x69 flag
// selects between copying only the translation column of the animated
// transform (from the BfmeCalc919G cache at 'this'+8, retail 0x0041CEC0,
// already landed as BfmeCalc919G.cpp) or copying the whole matrix; the
// result feeds a bounds-update helper (still-dump ILT at 0x00026350) and
// then RenderObjClass::Set_Transform on the render object at 'this'+0x34,
// followed by a one-arg-less virtual call on the object at 'this'+0x3c.

class Matrix3D
{
public:
	float m[12];
};

class BfmeCalc919GObj
{
public:
	int bfmeCalc919G();
};

class Rva007647D0BoundsTarget
{
public:
	void applyBounds(Matrix3D *transform);
};

#pragma comment(linker, "/alternatename:?applyBounds@Rva007647D0BoundsTarget@@QAEXPAVMatrix3D@@@Z=?j_00026350@@YAXXZ")

// Minimal RenderObjClass slice: only Set_Transform (retail slot 21, +0x54)
// is exercised at this call site.
class Rva007647D0RenderObject
{
public:
	virtual void _pad00(); virtual void _pad04(); virtual void _pad08();
	virtual void _pad0c(); virtual void _pad10(); virtual void _pad14();
	virtual void _pad18(); virtual void _pad1c(); virtual void _pad20();
	virtual void _pad24(); virtual void _pad28(); virtual void _pad2c();
	virtual void _pad30(); virtual void _pad34(); virtual void _pad38();
	virtual void _pad3c(); virtual void _pad40(); virtual void _pad44();
	virtual void _pad48(); virtual void _pad4c(); virtual void _pad50();
	virtual void Set_Transform(const Matrix3D &m);
};

// Minimal secondary object: only slot 1 (+4) is exercised.
class Rva007647D0SecondaryTarget
{
public:
	virtual void _pad00();
	virtual void notify();
};

class Rva007647D0
{
public:
	void update();
};

// ?rva007647d0@Rva007647D0@@QAEXXZ
void Rva007647D0::update()
{
	Rva007647D0SecondaryTarget **secondaryPtrSlot = (Rva007647D0SecondaryTarget **)((char *)this + 0x3c);
	if (*secondaryPtrSlot == 0)
		return;

	Rva007647D0RenderObject **renderObjSlot = (Rva007647D0RenderObject **)((char *)this + 0x34);
	if (*renderObjSlot == 0)
		return;

	BfmeCalc919GObj *calcObj = *(BfmeCalc919GObj *const *)((char *)this + 8);
	if (*(void *const *)((char *)calcObj + 0xfc) == 0)
		return;

	const unsigned char *flagObj = *(const unsigned char *const *)((char *)this + 4);

	Matrix3D localMatrix;
	localMatrix.m[0] = 1.0f; localMatrix.m[1] = 0.0f; localMatrix.m[2] = 0.0f; localMatrix.m[3] = 0.0f;
	localMatrix.m[4] = 0.0f; localMatrix.m[5] = 1.0f; localMatrix.m[6] = 0.0f; localMatrix.m[7] = 0.0f;
	localMatrix.m[8] = 0.0f; localMatrix.m[9] = 0.0f; localMatrix.m[10] = 1.0f; localMatrix.m[11] = 0.0f;

	if (flagObj[0x69])
	{
		Matrix3D *src = (Matrix3D *)calcObj->bfmeCalc919G();
		struct { float x, y, z; } translation;
		translation.x = src->m[3];
		translation.y = src->m[7];
		translation.z = src->m[11];
		localMatrix.m[3] = translation.x;
		localMatrix.m[7] = translation.y;
		localMatrix.m[11] = translation.z;
		(void)&translation;
	}
	else
	{
		Matrix3D *src = (Matrix3D *)calcObj->bfmeCalc919G();
		localMatrix.m[0] = src->m[0];
		localMatrix.m[1] = src->m[1];
		localMatrix.m[2] = src->m[2];
		localMatrix.m[3] = src->m[3];
		localMatrix.m[4] = src->m[4];
		localMatrix.m[5] = src->m[5];
		localMatrix.m[6] = src->m[6];
		localMatrix.m[7] = src->m[7];
		localMatrix.m[8] = src->m[8];
		localMatrix.m[9] = src->m[9];
		localMatrix.m[11] = src->m[11];
		localMatrix.m[10] = src->m[10];
	}

	((Rva007647D0BoundsTarget *)this)->applyBounds(&localMatrix);

	(*renderObjSlot)->Set_Transform(localMatrix);
	(*secondaryPtrSlot)->notify();
}
