// cl: /DNDEBUG /MD /EHsc
//
// BaseHeightMapRenderObjClass::getMaximumVisibleBox
// ZH: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Source/W3DDevice/GameClient/BaseHeightMap.cpp
// Retail 0x006CC0A0, 1439 bytes. Compute_Intersection stays out of line (retail
// calls ?Compute_Intersection@PlaneClass@@QBE_NABVVector3@@0PAM@Z @ 0x001A1CF0).
// m_minHeight is at this+0x300C; FrustumClass::Corners at +0x90.

class Vector3
{
public:
	float X;
	float Y;
	float Z;

	Vector3(void) {}
	Vector3(const Vector3 &v)
	{
		X = v.X;
		Y = v.Y;
		Z = v.Z;
	}
	Vector3(float x, float y, float z)
	{
		X = x;
		Y = y;
		Z = z;
	}
	Vector3 &operator=(const Vector3 &v)
	{
		X = v.X;
		Y = v.Y;
		Z = v.Z;
		return *this;
	}
};

inline Vector3 operator+(const Vector3 &a, const Vector3 &b)
{
	return Vector3(a.X + b.X, a.Y + b.Y, a.Z + b.Z);
}

inline Vector3 operator-(const Vector3 &a, const Vector3 &b)
{
	return Vector3(a.X - b.X, a.Y - b.Y, a.Z - b.Z);
}

inline Vector3 operator*(const Vector3 &a, float k)
{
	return Vector3((a.X * k), (a.Y * k), (a.Z * k));
}

class PlaneClass
{
public:
	Vector3 N;
	float D;

	PlaneClass(const Vector3 &normal, float dist)
	{
		N = normal;
		D = dist;
	}

	bool Compute_Intersection(const Vector3 &p0, const Vector3 &p1, float *set_t) const;
};

class FrustumClass
{
public:
	char CameraTransformAndPlanes[0x90];
	Vector3 Corners[8];
};

class AABoxClass
{
public:
	Vector3 Center;
	Vector3 Extent;

	__forceinline void Init(Vector3 *points, int num)
	{
		Vector3 Min = points[0];
		Vector3 Max = points[0];

		for (int i = 1; i < num; i++)
		{
			if (Min.X > points[i].X)
				Min.X = points[i].X;
			if (Min.Y > points[i].Y)
				Min.Y = points[i].Y;
			if (Min.Z > points[i].Z)
				Min.Z = points[i].Z;

			if (Max.X < points[i].X)
				Max.X = points[i].X;
			if (Max.Y < points[i].Y)
				Max.Y = points[i].Y;
			if (Max.Z < points[i].Z)
				Max.Z = points[i].Z;
		}

		Center = (Max + Min) * 0.5f;
		Extent = (Max - Min) * 0.5f;
	}
};

class BaseHeightMapRenderObjClass
{
public:
	bool getMaximumVisibleBox(const FrustumClass &frustum, AABoxClass *box, bool ignoreMaxHeight);

private:
	char _pad[0x300C];
	float m_minHeight;
};

// ?getMaximumVisibleBox@BaseHeightMapRenderObjClass@@QAE_NABVFrustumClass@@PAVAABoxClass@@_N@Z
bool BaseHeightMapRenderObjClass::getMaximumVisibleBox(const FrustumClass &frustum, AABoxClass *box, bool ignoreMaxHeight)
{
	PlaneClass groundPlane(Vector3(0, 0, 1), m_minHeight);

	float clipFraction;
	Vector3 ClippedCorners[8];
	ClippedCorners[0] = frustum.Corners[0];
	for (int i = 0; i < 4; i++)
	{
		ClippedCorners[i] = frustum.Corners[i];
		if (groundPlane.Compute_Intersection(frustum.Corners[i], frustum.Corners[i + 4], &clipFraction))
		{
			ClippedCorners[i + 4] = frustum.Corners[i] + (frustum.Corners[i + 4] - frustum.Corners[i]) * clipFraction;
		}
		else
			ClippedCorners[i + 4] = frustum.Corners[i + 4];
	}

	if (box)
		box->Init(ClippedCorners, 8);

	return true;
}
