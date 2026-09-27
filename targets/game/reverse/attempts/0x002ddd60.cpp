// ?handleMatch@BfmeBaseDF9@@QAEXPAX0@Z
// partial score=0.9 date=2026-09-27
// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWDebug
#include "matrix3d.h"
#include "coord3d.h"

struct BfmeHandleDF9
{
	unsigned char m_pad000[8];
	int m_objectID;
};

struct BfmePointDF9
{
	float x;
	float y;
	float z;

	void set(const BfmePointDF9 *point)
	{
		x = point->x;
		y = point->y;
		z = point->z;
	}

	void sub(const BfmePointDF9 *point)
	{
		x -= point->x;
		y -= point->y;
		z -= point->z;
	}
};

struct BfmeTargetDF9
{
	unsigned char m_pad000[8];
	float m_matrixRow00;
	unsigned char m_pad00C[0x0C];
	float m_matrixRow10;
	unsigned char m_pad01C[0x0C];
	float m_matrixRow20;
	unsigned char m_pad02C[0x0C];
	BfmePointDF9 m_position;
};

class Object;

class GameLogic
{
public:
	Object *findObjectByID(int objectID);
	unsigned char m_pad000[0x3C];
	unsigned int m_frame;
};

enum DisabledType
{
	DISABLED_DF9 = 4
};

class Object
{
public:
	void setDisabledUntil(DisabledType type, unsigned int frame);
};

class FXList
{
public:
	bool bfmeIsBlocked() const;
	void doFXPos(const Coord3D *position, const Matrix3D *transform,
		float speed, const Coord3D *secondary) const;
};

class BfmeBaseDF9
{
public:
	virtual void v0();
	virtual bool vfn1(void *, void *);
	virtual void v2();
	virtual void v3();
	virtual void v4();
	virtual void v5();
	virtual void vfn6(void *, void *);
	unsigned char m_pad004[0x58 - 4];
	float m_58;
	unsigned int m_5c;
	float m_60;
	FXList *m_64;
	void handleMatch(void *owner, void *target);
};

#define TheBfmeGameLogic (*(GameLogic **)0x012F0898)
#define BfmePi (*(const float *)0x01087B14)
#define BfmeZeroRange (*(const float *)0x01075350)

namespace BfmeCrtDF9
{
	extern "C" float __cdecl cosf(float value);
}

void BfmeBaseDF9::handleMatch(void *owner, void *target)
{
	BfmeHandleDF9 *handle = (BfmeHandleDF9 *)owner;
	BfmeTargetDF9 *object = (BfmeTargetDF9 *)
		TheBfmeGameLogic->findObjectByID(handle->m_objectID);

	if (m_60 < BfmePi && object != 0)
	{
		BfmePointDF9 *targetPosition = (BfmePointDF9 *)((unsigned char *)target + 0x38);
		BfmePointDF9 delta;
		delta.set(targetPosition);
		delta.sub(&object->m_position);
		Vector3 sourceVector;
		((Matrix3D *)((unsigned char *)object + 8))->Get_X_Vector(&sourceVector);
		Vector3 damageVector(delta.x, delta.y, delta.z);
		float sourceLength = sourceVector.Length2();
		if (BfmeZeroRange < sourceLength)
		{
			float inverseSourceLength = WWMath::Inv_Sqrt(sourceLength);
			sourceVector *= inverseSourceLength;
		}
		float damageLength = damageVector.Length2();
		if (BfmeZeroRange < damageLength)
		{
			float inverseDamageLength = WWMath::Inv_Sqrt(damageLength);
			damageVector *= inverseDamageLength;
		}
		if (Vector3::Dot_Product(sourceVector, damageVector) <
			BfmeCrtDF9::cosf(m_60))
			return;
	}

	((Object *)target)->setDisabledUntil(
		DISABLED_DF9, TheBfmeGameLogic->m_frame + m_5c);
	FXList *effects = m_64;
	if (effects != 0 && !effects->bfmeIsBlocked())
	{
		effects->doFXPos((Coord3D *)((unsigned char *)target + 0x38), 0, 0.0f, 0);
	}
}
