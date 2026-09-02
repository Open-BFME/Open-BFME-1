// cl: /DNDEBUG /MD
// readable body of ?screenToWorldAtZ@W3DView@@: Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DView.cpp
// Separate TU so getPickRay is a REL32 call rather than same-TU inlined.

struct ICoord2D
{
	int x;
	int y;
};

struct Coord3D
{
	float x;
	float y;
	float z;
};

class Vector3
{
public:
	float X;
	float Y;
	float Z;

	static float Find_X_At_Z(float z, const Vector3 &p1, const Vector3 &p2)
	{
		return p1.X + ((z - p1.Z) * ((p2.X - p1.X) / (p2.Z - p1.Z)));
	}

	static float Find_Y_At_Z(float z, const Vector3 &p1, const Vector3 &p2)
	{
		return p1.Y + ((z - p1.Z) * ((p2.Y - p1.Y) / (p2.Z - p1.Z)));
	}
};

class W3DView
{
public:
	virtual void screenToWorldAtZ(const ICoord2D *s, Coord3D *w, float z);

private:
	void getPickRay(const ICoord2D *screen, Vector3 *rayStart, Vector3 *rayEnd);
};

void W3DView::screenToWorldAtZ(const ICoord2D *s, Coord3D *w, float z)
{
	Vector3 rayStart, rayEnd;

	getPickRay(s, &rayStart, &rayEnd);
	if (rayStart.Z - z < 120.0f)
		z = rayStart.Z - 120.0f;
	w->x = Vector3::Find_X_At_Z(z, rayStart, rayEnd);
	w->y = Vector3::Find_Y_At_Z(z, rayStart, rayEnd);
	w->z = z;
}
