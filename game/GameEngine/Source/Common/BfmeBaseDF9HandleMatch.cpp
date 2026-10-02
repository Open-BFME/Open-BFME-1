// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWDebug
// Retail 0x002DDD60 (443 B), reached through ILT 0x000240EB from BfmeBaseDF9::checkAndDispatch.
// Zero Hour Weapon.cpp's directional damage cone test, then a disable timer and an FXList.

#include "matrix3d.h"

struct Coord3D;

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

	const Matrix3D *getTransformMatrix() const
	{
		return (const Matrix3D *)&m_matrixRow00;
	}
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
	bool bfmeIsBlocked();
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

extern GameLogic *TheGameLogic;

// math.h makes cosf an inline over the cos intrinsic; retail calls _cosf.
namespace BfmeCrtDF9
{
	extern "C" float __cdecl cosf(float value);
}

// ?handleMatch@BfmeBaseDF9@@QAEXPAX0@Z
void BfmeBaseDF9::handleMatch(void *owner, void *target)
{
	BfmeHandleDF9 *handle = (BfmeHandleDF9 *)owner;
	BfmeTargetDF9 *object = (BfmeTargetDF9 *)
		TheGameLogic->findObjectByID(handle->m_objectID);

	if (m_60 < 3.14159265359f && object != 0)
	{
		BfmePointDF9 delta;
		delta.set((BfmePointDF9 *)((unsigned char *)target + 0x38));
		delta.sub(&object->m_position);
		Vector3 sourceVector = object->getTransformMatrix()->Get_X_Vector();
		Vector3 damageVector(delta.x, delta.y, delta.z);
		// The z, x, y term order sets MSVC's x87 operand order for this vector.
		float sourceLength = sourceVector.Z * sourceVector.Z +
			sourceVector.X * sourceVector.X + sourceVector.Y * sourceVector.Y;
		if (sourceLength != 0.0f)
		{
			float inverseSourceLength = WWMath::Inv_Sqrt(sourceLength);
			sourceVector.X *= inverseSourceLength;
			sourceVector.Y *= inverseSourceLength;
			sourceVector.Z *= inverseSourceLength;
		}
		damageVector.Normalize();
		if (sourceVector.X * damageVector.X + sourceVector.Y * damageVector.Y +
			sourceVector.Z * damageVector.Z < BfmeCrtDF9::cosf(m_60))
			return;
	}

	((Object *)target)->setDisabledUntil(
		DISABLED_DF9, TheGameLogic->m_frame + m_5c);
	FXList *effects = m_64;
	if (effects != 0 && !effects->bfmeIsBlocked())
	{
		effects->doFXPos((Coord3D *)((unsigned char *)target + 0x38), 0, 0.0f, 0);
	}
}
