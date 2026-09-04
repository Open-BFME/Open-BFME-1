// Retail 0x009330C0: BFME camera frustum box cull.
// The cursor is initialized at N.Y so the retail loop uses N.X at p[-1].
// The volatile stores preserve the retail x87 spill and reload schedule.
// cl: /DNDEBUG /MD /EHsc

class Vector3
{
public:
	float X;
	float Y;
	float Z;
};

class PlaneClass
{
public:
	Vector3 N;
	float D;
};

class AABoxClass
{
public:
	Vector3 Center;
	Vector3 Extent;
};

inline bool Fast_Is_Float_Positive(const float &val)
{
	return !((*(int *)(&val)) & 0x80000000);
}

class CameraClass
{
protected:
	void Update_Frustum(void) const;
};

class BFMECameraCullBox : public CameraClass
{
public:
	bool Cull_Box(const AABoxClass &box) const;

protected:
	char pad[0x133];
	PlaneClass Planes[6];
};

static float g_cullZero = 0.0f;

bool BFMECameraCullBox::Cull_Box(const AABoxClass &box) const
{
	Update_Frustum();

	float tmp[3];
	int i = 0;
	const float *p = &Planes[0].N.Y;
	for (; i < 6; )
	{
		if (Fast_Is_Float_Positive(p[-1]))
			*(volatile int *)&tmp[0] = *(int *)&box.Extent.X;
		else
			*(volatile float *)&tmp[0] = -box.Extent.X;

		if (Fast_Is_Float_Positive(p[0]))
			*(volatile int *)&tmp[1] = *(int *)&box.Extent.Y;
		else
			*(volatile float *)&tmp[1] = -box.Extent.Y;

		if (Fast_Is_Float_Positive(p[1]))
			tmp[2] = box.Extent.Z;
		else
			tmp[2] = -box.Extent.Z;

		*(volatile float *)&tmp[0] = box.Center.X - tmp[0];
		*(volatile float *)&tmp[1] = box.Center.Y - tmp[1];
		tmp[2] = box.Center.Z - tmp[2];
		float delta = tmp[2] * p[1]
			+ tmp[1] * p[0] + tmp[0] * p[-1] - p[2];
		if (delta > g_cullZero)
			return true;
		i++;
		p += 4;
	}
	return false;
}
