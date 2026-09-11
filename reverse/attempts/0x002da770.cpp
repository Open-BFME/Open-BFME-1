// ?handleMatch@BfmeBaseA97@@QAEXPAX0@Z
// partial score=0.75 date=2026-09-10
// Research bank for retail 0x002DA770 (403 bytes).  The production claim was
// intentionally removed after the scoped probe remained non-exact.

struct BfmeHandleA97
{
	unsigned char m_pad000[8];
	int m_objectID;
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
};

struct BfmeDirectionA97
{
	unsigned char m_pad000[0x38];
	float m_x;
	float m_y;
	float m_z;
};

struct BfmeVector3A97
{
	float m_x;
	float m_y;
	float m_z;
};

class Object;

class GameLogic
{
public:
	Object *findObjectByID(int objectID);
};

class WWMath
{
public:
	static float __fastcall Inv_Sqrt(float value);
};

class Rva00367E30Sink
{
public:
	void apply(int *data, int delta);
};

extern "C" float __cdecl cosf(float value);
#define TheBfmeGameLogic (*(GameLogic **)0x012F0898)
#define BfmeZeroRange (*(const float *)0x01075350)
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

void BfmeBaseA97::handleMatch(void *owner, void *direction)
{
	BfmeDirectionA97 *sample = (BfmeDirectionA97 *)direction;
	BfmeBaseA97 *self = this;
	BfmeHandleA97 *handle = (BfmeHandleA97 *)owner;
	BfmeFoundObjectA97 *object = (BfmeFoundObjectA97 *)
		TheBfmeGameLogic->findObjectByID(handle->m_objectID);
	if (self->m_angle < BfmePi && object != 0)
	{
		BfmeVector3A97 delta;
		delta.m_x = sample->m_x - object->m_positionX;
		delta.m_y = sample->m_y - object->m_positionY;
		delta.m_z = sample->m_z - object->m_positionZ;
		BfmeVector3A97 axis;
		axis.m_x = object->m_axisA;
		axis.m_y = object->m_axisB;
		axis.m_z = object->m_axisC;

		float objectLengthSquared = axis.m_z * axis.m_z
			+ axis.m_x * axis.m_x + axis.m_y * axis.m_y;
		if (objectLengthSquared != BfmeZeroRange)
		{
			float inverseLength = WWMath::Inv_Sqrt(objectLengthSquared);
			axis.m_x *= inverseLength;
			axis.m_y *= inverseLength;
			axis.m_z *= inverseLength;
		}

		float deltaLengthSquared = delta.m_x * delta.m_x
			+ delta.m_y * delta.m_y + delta.m_z * delta.m_z;
		if (deltaLengthSquared != BfmeZeroRange)
		{
			float inverseLength = WWMath::Inv_Sqrt(deltaLengthSquared);
			BfmeVector3A97 normalized = delta;
			normalized.m_x *= inverseLength;
			normalized.m_y *= inverseLength;
			normalized.m_z *= inverseLength;
			float directionScore = normalized.m_z * axis.m_z
				+ normalized.m_y * axis.m_y + normalized.m_x * axis.m_x;
			if (cosf(self->m_angle) < directionScore)
				((Rva00367E30Sink *)sample)->apply(
					(int *)((unsigned char *)self + 0x58), -1);
		}
	}
}
