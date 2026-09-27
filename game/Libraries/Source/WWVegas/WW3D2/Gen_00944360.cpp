// cl: /DNDEBUG /MD /EHs-c-

class Gen_009431F0
{
public:
	int map_x(float x);
	int map_y(float y);
	void collect(void *object, const float *bounds, const float *padding);
	void recurse(void *object, void *nodes, int node_count, int min_x, int min_y,
		int max_x, int max_y, int unused_x, int unused_y, int count);

private:
	float origin_x;
	float origin_y;
	unsigned char pad[0x10];
	void *nodes;
	unsigned int node_count;
	float scale;
	int count;
};

void Gen_009431F0::collect(void *object, const float *bounds, const float *padding)
{
	float offset_x = padding ? padding[0] : 0.0f;
	int min_x = map_x(bounds[0] - offset_x);
	offset_x = padding ? padding[0] : 0.0f;
	int max_x = map_x(offset_x + bounds[3]);
	float offset_y = padding ? padding[1] : 0.0f;
	int min_y = map_y(bounds[1] - offset_y);
	offset_y = padding ? padding[1] : 0.0f;
	int max_y = map_y(offset_y + bounds[4]);

	recurse(object, nodes, node_count >> 2, min_x, min_y, max_x, max_y, 0, 0,
		count);
}

#pragma comment(linker, "/alternatename:?recurse@Gen_009431F0@@QAEXPAX0HHHHHHHH@Z=?d_009441d0@@YAXXZ")

class Vector3
{
public:
	float X;
	float Y;
	float Z;

	Vector3(void) {}
	Vector3(float x, float y, float z) : X(x), Y(y), Z(z) {}
};

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

// ?Get_View_Space_Frustum@CameraClass@@QBEABVFrustumClass@@XZ absent-from-retail
inline const FrustumClass &CameraClass::Get_View_Space_Frustum(void) const
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

// Min and max corners; Add widens only X and Y.
class Bounds00944430
{
public:
	Vector3 Min;
	Vector3 Max;

	__forceinline void Init(const Vector3 &p)
	{
		Max = p;
		Min = p;
	}
	__forceinline void Add(const Vector3 &p)
	{
		if (p.X < Min.X)
			Min.X = p.X;
		else if (p.X > Max.X)
			Max.X = p.X;
		if (p.Y < Min.Y)
			Min.Y = p.Y;
		else if (p.Y > Max.Y)
			Max.Y = p.Y;
	}
};

class Rva00944430
{
	void rva00944430(void **head, CameraClass *camera, const float *padding);
};

// Bounds the near frustum corners and their ground-plane hits, then collects.
void Rva00944430::rva00944430(void **head, CameraClass *camera,
	const float *padding)
{
	const Vector3 *corners = camera->Get_View_Space_Frustum().Corners;
	Bounds00944430 box;
	box.Init(corners[0]);
	box.Add(corners[1]);
	box.Add(corners[2]);
	box.Add(corners[3]);

	PlaneClass ground;
	for (int i = 0; i < 4; ++i) {
		float fraction;
		if (!ground.Compute_Intersection(corners[i], corners[i + 4], &fraction))
			fraction = 1.0f;
		Vector3 point;
		point.X = corners[i].X + (corners[i + 4].X - corners[i].X) * fraction;
		point.Y = corners[i].Y + (corners[i + 4].Y - corners[i].Y) * fraction;
		box.Add(point);
	}

	((Gen_009431F0 *)this)->collect(head, (const float *)&box, padding);
}
