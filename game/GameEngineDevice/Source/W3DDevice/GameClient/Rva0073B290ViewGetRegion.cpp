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
	Vector3() {}
	Vector3(const Vector3 &v) { X = v.X; Y = v.Y; Z = v.Z; }
	Vector3(Real x, Real y, Real z) { X = x; Y = y; Z = z; }
	Vector3 &operator=(const Vector3 &v) { X = v.X; Y = v.Y; Z = v.Z; return *this; }

	Real X;
	Real Y;
	Real Z;
};


struct Matrix3D
{
	Vector3 Get_Translation() const { return Vector3(Row[0][3], Row[1][3], Row[2][3]); }

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

	Vector3 Get_Position() { cameraSlot50(); return Transform.Get_Translation(); }

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

// Retail keeps these three in one address-exposed frame block, which stops the
// x-slope from being hoisted out of the plane loop.
struct GetRegionFrameBlock
{
	Region3D bounds;
	Coord3D pt;
	Region3D mapExtent;
};

void Rva0073B290View::getRegion(Region3D &region)
{
	GetRegionFrameBlock L;
	TheTerrainLogic->getExtent( &L.mapExtent );

	CameraClass *camera = m_3DCamera;
	camera->Update_Frustum();
	Vector3 camPos = m_3DCamera->Get_Position();

	if( camPos.Z > camera->Frustum.BoundMax.Z )
	{
		L.bounds.lo.x = 0.0f;
		L.bounds.lo.y = 0.0f;
		L.bounds.lo.z = -1.0f;
		L.bounds.hi.x = 0.0f;
		L.bounds.hi.y = 0.0f;

		for( Int i = 0; i < 4; i++ )
		{
			const Vector3 &corner = camera->Frustum.Corners[ 4 + i ];
			Real dy = corner.Y - camPos.Y;
			Real dzc = corner.Z - camPos.Z;

			for( Int j = 0; j < 2; j++ )
			{
				Real planeZ = (j == 0) ? L.mapExtent.lo.z : L.mapExtent.hi.z;
				if( planeZ > camPos.Z )
					planeZ = camPos.Z - g_bfmeDefaultBU;
				Real dz = planeZ - camPos.Z;

				Real px = (corner.X - camPos.X) / (corner.Z - camPos.Z) * dz + camPos.X;
				L.pt.y = dy / dzc * dz + camPos.Y;
				Real py = L.pt.y;

				if( L.bounds.lo.z < BfmeZeroRange )
				{
					L.bounds.lo.x = L.bounds.hi.x = px;
					L.bounds.lo.y = L.bounds.hi.y = py;
					L.bounds.lo.z = 0.0f;
				}
				else
				{
					if( px < L.bounds.lo.x )
						L.bounds.lo.x = px;
					if( px > L.bounds.hi.x )
						L.bounds.hi.x = px;
					if( py < L.bounds.lo.y )
						L.bounds.lo.y = py;
					if( py > L.bounds.hi.y )
						L.bounds.hi.y = py;
				}
			}
		}

		region.lo.x = L.bounds.lo.x - DRAWABLE_OVERSCAN;
		region.lo.y = L.bounds.lo.y - DRAWABLE_OVERSCAN;
		region.lo.z = L.mapExtent.lo.z - MAP_Z_SAFE;
		region.hi.x = L.bounds.hi.x + DRAWABLE_OVERSCAN;
		region.hi.y = L.bounds.hi.y + DRAWABLE_OVERSCAN;
		region.hi.z = L.mapExtent.hi.z + MAP_Z_SAFE;
	}
	else
	{
		region.lo.x = camera->Frustum.BoundMin.X - DRAWABLE_OVERSCAN;
		region.lo.y = camera->Frustum.BoundMin.Y - DRAWABLE_OVERSCAN;
		region.lo.z = L.mapExtent.lo.z - MAP_Z_SAFE;
		region.hi.x = camera->Frustum.BoundMax.X + DRAWABLE_OVERSCAN;
		region.hi.y = camera->Frustum.BoundMax.Y + DRAWABLE_OVERSCAN;
		region.hi.z = L.mapExtent.hi.z + MAP_Z_SAFE;
	}
}
