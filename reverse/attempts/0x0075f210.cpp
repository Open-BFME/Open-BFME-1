// ?rva0075f210@Rva0075F210Owner@@QAE_NPAM@Z
// partial score=0.4 date=2026-09-21
// Open-BFME: retail RVA 0x0075F210, 349 bytes. Address-derived; no named
// caller or vtable evidence. Callee identity is proven by the ledger:
// AIUpdateInterface::getCurrentVictim (0x002739D0), the
// AssistedTargetingObjectShim::find weapon accessor (0x001BE270, itself the
// same forty-seven bytes as Object::getCurrentWeapon -- see
// AssistedTargetingObjectShim_find.cpp), Weapon::isWithinAttackRange
// (0x001E8930), Matrix3D::Obj_Look_At / Get_Z_Rotation (matrix3d.cpp), and
// the address-derived stepAngleToward (0x0075B550, StepAngleToward.cpp).
//
// Shape: guard a chain of pointer fields (this->m_08, ->m_FC, ->m_204),
// fetch the current victim and current weapon, bail unless the weapon is in
// range; then build a horizontal-plane look-at matrix from this actor's
// position (m_FC-object's +0x14/+0x24) toward a cached target position
// (AIUpdateInterface's +0x30 record, +0x24/+0x28), read the resulting Z
// rotation, step this object's own +0x70 angle toward it, and write the
// delta (new angle minus the caller's *result) back through *result.

struct Vector3
{
	float X, Y, Z;
};

class Matrix3D
{
public:
	Matrix3D(bool init)
	{
		if (init)
		{
			m[0] = 1.0f; m[1] = 0.0f; m[2] = 0.0f; m[3] = 0.0f;
			m[4] = 0.0f; m[5] = 1.0f; m[6] = 0.0f; m[7] = 0.0f;
			m[8] = 0.0f; m[9] = 0.0f; m[10] = 1.0f; m[11] = 0.0f;
		}
	}

	void Obj_Look_At(const Vector3 &p, const Vector3 &t, float roll);
	float Get_Z_Rotation(void) const;

private:
	float m[12];
};

void stepAngleToward(float *p, float target);

class Object;

class TargetRecord
{
public:
	unsigned char m_pad[0x24];
	float m_x;   // +0x24
	float m_y;   // +0x28
};

class AIUpdateInterface
{
public:
	Object *getCurrentVictim(void) const;

	unsigned char m_pad[0x30];
	TargetRecord *m_target;   // +0x30
};

class Object
{
public:
	unsigned char m_pad00[0x14];
	float m_x;   // +0x14
	unsigned char m_pad18[0x24 - 0x18];
	float m_y;   // +0x24
	unsigned char m_pad28[0x204 - 0x28];
	AIUpdateInterface *m_aiUpdate;   // +0x204
};

class AssistedTargetingObjectShim
{
public:
	void *find(int slotOut);
};

class Weapon
{
public:
	bool isWithinAttackRange(const Object *a, const Object *b, int c) const;
};

class Rva0075F210Link
{
public:
	unsigned char m_pad[0xFC];
	Object *m_object;   // +0xFC
};

class Rva0075F210Owner
{
public:
	bool rva0075f210(float *result);

	unsigned char m_pad0[8];
	Rva0075F210Link *m_link;   // +8
	unsigned char m_pad1[0x70 - 0xC];
	float m_angle;   // +0x70
};

bool Rva0075F210Owner::rva0075f210(float *result)
{
	Rva0075F210Link *link = m_link;
	if (!link)
		return false;

	Object *obj = link->m_object;
	if (!obj)
		return false;

	AIUpdateInterface *ai = obj->m_aiUpdate;
	if (!ai)
		return false;

	Object *victim = ai->getCurrentVictim();
	if (!victim)
		goto fail;

	{
		Weapon *weapon = (Weapon *)((AssistedTargetingObjectShim *)obj)->find(0);
		if (!weapon)
			goto fail;

		if (!weapon->isWithinAttackRange(obj, victim, 0))
			goto fail;
	}

	{
		TargetRecord *targetRecord = ai->m_target;

		Vector3 t;
		t.Y = targetRecord->m_y;
		t.X = targetRecord->m_x;
		t.Z = 0.0f;

		Vector3 p;
		p.X = obj->m_x;
		p.Y = obj->m_y;
		p.Z = 0.0f;

		Matrix3D mtx(true);
		mtx.Obj_Look_At(p, t, 0.0f);

		float zRotation = mtx.Get_Z_Rotation();
		stepAngleToward(&m_angle, zRotation);

		*result = m_angle - *result;

		return true;
	}

fail:
	return false;
}
