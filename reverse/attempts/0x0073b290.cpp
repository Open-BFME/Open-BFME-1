// ?d_0073b290@@YAXXZ
// partial score=0.85 date=2026-09-10
// ?getRegion@Rva0073B290View@@QAEXAAURegion3D@@@Z
// Projects the four far frustum corners onto the map's low and high z planes and
// bounds the result; falls back to the frustum bound when the camera is below it.

typedef float Real;
typedef int Int;

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

struct Region3D
{
	Coord3D lo;
	Coord3D hi;
};

struct Vector3
{
	Real X;
	Real Y;
	Real Z;
};

struct Matrix3D
{
	Real Row[3][4];
};

struct FrustumClass
{
	Matrix3D CameraTransform;
	Real Planes[6][4];
	Vector3 Corners[8];
	Vector3 BoundMin;
	Vector3 BoundMax;
};

struct Rva003FD060TerrainLogic
{
	virtual void terrainSlot00() = 0;
	virtual void terrainSlot04() = 0;
	virtual void terrainSlot08() = 0;
	virtual void terrainSlot0C() = 0;
	virtual void terrainSlot10() = 0;
	virtual void terrainSlot14() = 0;
	virtual void terrainSlot18() = 0;
	virtual void terrainSlot1C() = 0;
	virtual void getExtent(Region3D *region) = 0;
};

extern Rva003FD060TerrainLogic *TheTerrainLogic;

extern Real g_bfmeDefaultBU;
extern const Real BfmeZeroRange;

static const Real DRAWABLE_OVERSCAN = 75.0f;
static const Real MAP_Z_SAFE = 999999.0f;

struct Rva0073B290View;

class CameraClass
{
public:
	virtual void cameraSlot00() = 0;
	virtual void cameraSlot04() = 0;
	virtual void cameraSlot08() = 0;
	virtual void cameraSlot0C() = 0;
	virtual void cameraSlot10() = 0;
	virtual void cameraSlot14() = 0;
	virtual void cameraSlot18() = 0;
	virtual void cameraSlot1C() = 0;
	virtual void cameraSlot20() = 0;
	virtual void cameraSlot24() = 0;
	virtual void cameraSlot28() = 0;
	virtual void cameraSlot2C() = 0;
	virtual void cameraSlot30() = 0;
	virtual void cameraSlot34() = 0;
	virtual void cameraSlot38() = 0;
	virtual void cameraSlot3C() = 0;
	virtual void cameraSlot40() = 0;
	virtual void cameraSlot44() = 0;
	virtual void cameraSlot48() = 0;
	virtual void cameraSlot4C() = 0;
	virtual void cameraSlot50() = 0;

	unsigned char m_camHead[0x14];
	Matrix3D Transform;
	unsigned char m_camMid[0xBC];
	FrustumClass Frustum;

protected:
	void Update_Frustum() const;

	friend struct Rva0073B290View;
};

struct Rva0073B290View
{
	void getRegion(Region3D &region);

	unsigned char m_viewHead[0x104];
	CameraClass *m_3DCamera;
};

void Rva0073B290View::getRegion(Region3D &region)
{
	Region3D mapExtent;
	TheTerrainLogic->getExtent( &mapExtent );

	CameraClass *camera = m_3DCamera;
	camera->Update_Frustum();
	CameraClass *view = m_3DCamera;
	view->cameraSlot50();
	Vector3 camPos;
	camPos.X = view->Transform.Row[0][3];
	camPos.Y = view->Transform.Row[1][3];
	camPos.Z = view->Transform.Row[2][3];

	if( camPos.Z > camera->Frustum.BoundMax.Z )
	{
		Region3D bounds;
		bounds.lo.x = 0.0f;
		bounds.lo.y = 0.0f;
		bounds.lo.z = -1.0f;
		bounds.hi.x = 0.0f;
		bounds.hi.y = 0.0f;

		for( Int i = 0; i < 4; i++ )
		{
			const Vector3 &corner = camera->Frustum.Corners[ 4 + i ];

			for( Int j = 0; j < 2; j++ )
			{
				Real planeZ = (j == 0) ? mapExtent.lo.z : mapExtent.hi.z;
				if( planeZ > camPos.Z )
					planeZ = camPos.Z - g_bfmeDefaultBU;
				Real dz = planeZ - camPos.Z;

				Real py = (corner.Y - camPos.Y) / (corner.Z - camPos.Z) * dz + camPos.Y;
				Real px = (corner.X - camPos.X) / (corner.Z - camPos.Z) * dz + camPos.X;

				if( bounds.lo.z < BfmeZeroRange )
				{
					bounds.lo.x = bounds.hi.x = px;
					bounds.lo.y = bounds.hi.y = py;
					bounds.lo.z = 0.0f;
				}
				else
				{
					if( px < bounds.lo.x )
						bounds.lo.x = px;
					if( py < bounds.lo.y )
						bounds.lo.y = py;
					if( px > bounds.hi.x )
						bounds.hi.x = px;
					if( py > bounds.hi.y )
						bounds.hi.y = py;
				}
			}
		}

		region.lo.x = bounds.lo.x - DRAWABLE_OVERSCAN;
		region.lo.y = bounds.lo.y - DRAWABLE_OVERSCAN;
		region.lo.z = mapExtent.lo.z - MAP_Z_SAFE;
		region.hi.x = bounds.hi.x + DRAWABLE_OVERSCAN;
		region.hi.y = bounds.hi.y + DRAWABLE_OVERSCAN;
		region.hi.z = mapExtent.hi.z + MAP_Z_SAFE;
	}
	else
	{
		region.lo.x = camera->Frustum.BoundMin.X - DRAWABLE_OVERSCAN;
		region.lo.y = camera->Frustum.BoundMin.Y - DRAWABLE_OVERSCAN;
		region.lo.z = mapExtent.lo.z - MAP_Z_SAFE;
		region.hi.x = camera->Frustum.BoundMax.X + DRAWABLE_OVERSCAN;
		region.hi.y = camera->Frustum.BoundMax.Y + DRAWABLE_OVERSCAN;
		region.hi.z = mapExtent.hi.z + MAP_Z_SAFE;
	}
}
