// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWDebug
// Retail 0x002DA770 (403 B), reached through ILT 0x0000E719 from BfmeBaseA97::checkAndDispatch.
// The cone test is Zero Hour Weapon.cpp's directional radius-damage check.

#include "matrix3d.h"

struct BfmeHandleA97
{
	unsigned char m_pad000[8];
	int m_objectID;
};

struct BfmeVector3A97
{
	float m_x;
	float m_y;
	float m_z;

	void set(const BfmeVector3A97 *a)
	{
		m_x = a->m_x;
		m_y = a->m_y;
		m_z = a->m_z;
	}

	void sub(const BfmeVector3A97 *a)
	{
		m_x -= a->m_x;
		m_y -= a->m_y;
		m_z -= a->m_z;
	}
};

struct BfmeFoundObjectA97
{
	unsigned char m_pad000[8];
	float m_axisA;
	unsigned char m_pad00C[0x0C];
	float m_axisB;
	unsigned char m_pad01C[0x0C];
	float m_axisC;
	unsigned char m_pad02C[0x0C];
	float m_positionX;
	float m_positionY;
	float m_positionZ;

	const Matrix3D *getTransformMatrix() const
	{
		return (const Matrix3D *)&m_axisA;
	}

	const BfmeVector3A97 *getPosition() const
	{
		return (const BfmeVector3A97 *)&m_positionX;
	}
};

struct BfmeDirectionA97
{
	unsigned char m_pad000[0x38];
	float m_x;
	float m_y;
	float m_z;

	const BfmeVector3A97 *getPosition() const
	{
		return (const BfmeVector3A97 *)&m_x;
	}
};

class Object;

class GameLogic
{
public:
	Object *findObjectByID(int objectID);
};

class Rva00367E30Sink
{
public:
	void apply(int *data, int delta);
};

// math.h makes cosf an inline over the cos intrinsic; retail calls _cosf.
namespace BfmeCrtA97
{
	extern "C" float __cdecl cosf(float value);
}
#define TheBfmeGameLogic (*(GameLogic **)0x012F0898)
#define BfmePi (*(const float *)0x01087B14)

class BfmeBaseA97
{
public:
	virtual void v0();
	virtual bool vfn1(void *, void *);
	virtual void v2();
	virtual void v3();
	virtual void v4();
	virtual void v5();
	virtual void vfn6(void *, void *);
	void handleMatch(void *owner, void *direction);

private:
	unsigned char m_pad000[0x64 - 4];
	float m_angle;
};

// ?handleMatch@BfmeBaseA97@@QAEXPAX0@Z
void BfmeBaseA97::handleMatch(void *owner, void *direction)
{
	BfmeDirectionA97 *sample = (BfmeDirectionA97 *)direction;
	BfmeHandleA97 *handle = (BfmeHandleA97 *)owner;
	BfmeFoundObjectA97 *object = (BfmeFoundObjectA97 *)
		TheBfmeGameLogic->findObjectByID(handle->m_objectID);

	if (m_angle < BfmePi && object != 0)
	{
		BfmeVector3A97 delta;
		delta.set(sample->getPosition());
		delta.sub(object->getPosition());
		Vector3 sourceVector = object->getTransformMatrix()->Get_X_Vector();
		Vector3 damageVector(delta.m_x, delta.m_y, delta.m_z);
		sourceVector.Normalize();
		damageVector.Normalize();
		if (Vector3::Dot_Product(sourceVector, damageVector) < BfmeCrtA97::cosf(m_angle))
			return;
	}
	((Rva00367E30Sink *)sample)->apply(
		(int *)((unsigned char *)this + 0x58), -1);
}
