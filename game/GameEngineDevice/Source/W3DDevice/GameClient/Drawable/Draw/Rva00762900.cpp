// 0x00762900 touches W3DModelDraw's witnessed m_curState at +0x14, but has
// no named caller or vtable entry. Keep the method address-derived.

class Object
{
public:
	float bfmeGetNonnegativePreferredLocomotorHeight() const;
};

struct RvaC4390First;

class RvaC4390Second
{
public:
	RvaC4390First *resolve(int allowLookup);
};

class BfmePrimaryGI
{
public:
	void bfmeApplyGI(float desiredDurationInMsec);
};

class Rva00762900
{
public:
	void method();
};

extern const float BfmeZeroRange;
extern const float g_01076C24;
extern const float g_bfmeScaleGI;

// ?method@Rva00762900@@QAEXXZ
void Rva00762900::method()
{
	char *self = (char *)this;
	*(float *)(self + 0x80) = 1.0f;

	char *state = *(char **)(self + 0x14);
	if (state == 0)
		return;

	int index = *(int *)(self + 0x28);
	if (index < 0)
		return;

	char *entries = *(char **)(state + 0x2C);
	float range = *(float *)(entries + index * 0x38 + 0x0C);
	if (!(range > BfmeZeroRange))
		return;

	char *owner = *(char **)(self + 0x08);
	Object *object = *(Object **)(owner + 0xFC);
	if (object == 0)
		return;

	float height = object->bfmeGetNonnegativePreferredLocomotorHeight();
	if (height == BfmeZeroRange)
	{
		RvaC4390First *resolved = ((RvaC4390Second *)object)->resolve(0);
		if (resolved != 0)
			height = ((Object *)resolved)->bfmeGetNonnegativePreferredLocomotorHeight();
	}

	if (height > g_01076C24)
	{
		float durationPart = range / height;
		float duration = durationPart * g_bfmeScaleGI;
		((BfmePrimaryGI *)this)->bfmeApplyGI(duration);
	}
}
