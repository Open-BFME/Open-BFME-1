// ?Cull_Box@CameraClass@@QBE_NABVAABoxClass@@@Z
// partial score=0.93 date=2026-09-02
// cl: /DNDEBUG /MD /EHsc
// CameraClass::Cull_Box inlined against the six world-space frustum
// planes at this+0x134. Fast_Is_Float_Positive and the integer-copy
// positive extent path match; the loop pointer sits on N.X (this+0x134)
// instead of N.Y (this+0x138), and the positive path extra-flds the
// stored extent. 194B vs retail 193B.

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
public:
	bool Cull_Box(const AABoxClass &box) const;

protected:
	void Update_Frustum(void) const;

	char pad[0x134];
	PlaneClass Planes[6];
};

static float g_cullZero = 0.0f;

// ?Cull_Box@CameraClass@@QBE_NABVAABoxClass@@@Z
bool CameraClass::Cull_Box(const AABoxClass &box) const
{
	Update_Frustum();

	float tmp[3];
	for (int i = 0; i < 6; i++)
	{
		const float *p = &Planes[i].N.Y;

		if (Fast_Is_Float_Positive(p[-1]))
			*(int *)&tmp[0] = *(int *)&box.Extent.X;
		else
			tmp[0] = -box.Extent.X;

		if (Fast_Is_Float_Positive(p[0]))
			*(int *)&tmp[1] = *(int *)&box.Extent.Y;
		else
			tmp[1] = -box.Extent.Y;

		if (Fast_Is_Float_Positive(p[1]))
			tmp[2] = box.Extent.Z;
		else
			tmp[2] = -box.Extent.Z;

		float dx = box.Center.X - tmp[0];
		float dy = box.Center.Y - tmp[1];
		float dz = box.Center.Z - tmp[2];
		float delta = dx * p[-1] + dy * p[0] + dz * p[1] - p[2];
		if (delta > g_cullZero)
			return true;
	}
	return false;
}
