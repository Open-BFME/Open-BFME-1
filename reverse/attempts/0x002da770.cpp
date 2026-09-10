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
extern const float BfmeZeroRange;

#define TheBfmeGameLogic (*(GameLogic **)0x012F0898)

class BfmeBaseA97
{
public:
	void handleMatch(void *owner, void *direction);

private:
	unsigned char m_pad000[0x64];
	float m_angle;
};

void BfmeBaseA97::handleMatch(void *owner, void *direction)
{
	BfmeHandleA97 *handle = (BfmeHandleA97 *)owner;
	BfmeFoundObjectA97 *object = (BfmeFoundObjectA97 *)
		TheBfmeGameLogic->findObjectByID(handle->m_objectID);
	if (m_angle < 3.1415927f && object != 0)
	{
		BfmeDirectionA97 *sample = (BfmeDirectionA97 *)direction;
		float dx = sample->m_x - object->m_positionX;
		float dy = sample->m_y - object->m_positionY;
		float dz = sample->m_z - object->m_positionZ;

		float axisA = object->m_axisA;
		float axisB = object->m_axisB;
		float axisC = object->m_axisC;
		float objectLengthSquared = axisC * axisC + axisA * axisA
			+ axisB * axisB;
		if (objectLengthSquared != BfmeZeroRange)
		{
			float inverseLength = WWMath::Inv_Sqrt(objectLengthSquared);
			axisA *= inverseLength;
			axisB *= inverseLength;
			axisC *= inverseLength;
		}

		float deltaLengthSquared = dz * dz + dx * dx + dy * dy;
		if (deltaLengthSquared != BfmeZeroRange)
		{
			float inverseLength = WWMath::Inv_Sqrt(deltaLengthSquared);
			float normalizedX = dx * inverseLength;
			float normalizedY = dy * inverseLength;
			float normalizedZ = dz * inverseLength;
			float directionScore = normalizedZ * axisC
				+ normalizedY * axisB + normalizedX * axisA;
			if (cosf(m_angle) < directionScore)
				((Rva00367E30Sink *)sample)->apply(
					(int *)((unsigned char *)this + 0x58), -1);
		}
	}
}
