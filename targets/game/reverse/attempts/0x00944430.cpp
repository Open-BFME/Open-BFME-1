// ?rva00944430@Rva00944430@@AAEXPAPAXPAVCameraClass@@PBM@Z
// partial score=0.61 date=2026-09-27
// ?rva00944430@Rva00944430@@AAEXPAPAXPAVCameraClass@@PBM@Z
// cl: /DNDEBUG /MD /EHs-c-

class Vector3
{
public:
	float X;
	float Y;
	float Z;

	Vector3(void) {}
	Vector3(float x, float y, float z) : X(x), Y(y), Z(z) {}
	Vector3(const Vector3 &v) : X(v.X), Y(v.Y), Z(v.Z) {}
	Vector3 &operator=(const Vector3 &v)
	{
		X = v.X;
		Y = v.Y;
		Z = v.Z;
		return *this;
	}
};

inline Vector3 operator-(const Vector3 &a, const Vector3 &b)
{
	return Vector3(a.X - b.X, a.Y - b.Y, a.Z - b.Z);
}

inline Vector3 operator+(const Vector3 &a, const Vector3 &b)
{
	return Vector3(a.X + b.X, a.Y + b.Y, a.Z + b.Z);
}

inline Vector3 operator*(const Vector3 &a, float scale)
{
	return Vector3(a.X * scale, a.Y * scale, a.Z * scale);
}

class FrustumClass
{
public:
	char _frustum_prefix[0xa0];
	Vector3 Corners[8];
};

class CameraClass
{
public:
	const FrustumClass &Get_View_Space_Frustum(void) const;

protected:
	void Update_Frustum(void) const;

	char _camera_prefix[0xf4];
	FrustumClass ViewSpaceFrustum;
};

const FrustumClass &CameraClass::Get_View_Space_Frustum(void) const
{
	Update_Frustum();
	return ViewSpaceFrustum;
}

class PlaneClass
{
public:
	Vector3 N;
	float D;

	PlaneClass(void) : N(0.0f, 0.0f, 1.0f), D(0.0f) {}
	bool Compute_Intersection(const Vector3 &p0, const Vector3 &p1,
		float *set_t) const;
};

class Gen_009431F0
{
public:
	void collect(void *object, const float *bounds, const float *padding);
};

class Rva00944430
{
	void rva00944430(void **head, CameraClass *camera, const float *padding);
};

void Rva00944430::rva00944430(void **head, CameraClass *camera,
	const float *padding)
{
	const FrustumClass &frustum = camera->Get_View_Space_Frustum();
	Vector3 *base = (Vector3 *)frustum.Corners;

	float bounds[6];
	const Vector3 *corner = base;
	float first_x = (corner + 1)->X;
	bounds[3] = corner->X;
	bounds[4] = corner->Y;
	bounds[5] = corner->Z;
	bounds[0] = corner->X;
	bounds[1] = corner->Y;
	bounds[2] = corner->Z;
	if (bounds[0] > first_x)
		bounds[0] = first_x;
	else if (bounds[3] < first_x)
		bounds[3] = first_x;
	if (bounds[1] > (corner + 1)->Y)
		bounds[1] = (corner + 1)->Y;
	else if (bounds[4] < (corner + 1)->Y)
		bounds[4] = (corner + 1)->Y;
	corner += 2;
	for (int i = 2; i < 4; ++i, ++corner) {
		if (bounds[0] > corner->X)
			bounds[0] = corner->X;
		else if (bounds[3] < corner->X)
			bounds[3] = corner->X;
		if (bounds[1] > corner->Y)
			bounds[1] = corner->Y;
		else if (bounds[4] < corner->Y)
			bounds[4] = corner->Y;
	}

	{
		PlaneClass ground;
		const Vector3 *near_corner = base;
		const Vector3 *far_corner = base + 4;
		for (int i = 0; i < 4; ++i) {
			float fraction;
			if (!ground.Compute_Intersection(*near_corner, *far_corner,
				&fraction))
				fraction = 1.0f;
			Vector3 point;
			point.X = near_corner->X +
				(far_corner->X - near_corner->X) * fraction;
			point.Y = near_corner->Y +
				(far_corner->Y - near_corner->Y) * fraction;
			if (bounds[0] > point.X)
				bounds[0] = point.X;
			else if (bounds[3] < point.X)
				bounds[3] = point.X;
			if (bounds[1] > point.Y)
				bounds[1] = point.Y;
			else if (bounds[4] < point.Y)
				bounds[4] = point.Y;
			++near_corner;
			++far_corner;
		}
	}

	((Gen_009431F0 *)this)->collect(head, bounds, padding);
}
