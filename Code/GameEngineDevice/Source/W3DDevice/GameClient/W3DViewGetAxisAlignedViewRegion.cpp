// cl: /EHsc
// ?getAxisAlignedViewRegion@W3DView@@AAEXAAURegion3D@@@Z
// BFME's Coord3D carries an out-of-line empty constructor and destructor, so the
// four-corner array is built through the vector constructor iterator.

typedef float Real;
typedef int Int;

struct Coord3DData
{
	Real x;
	Real y;
	Real z;
};

struct Coord3D : public Coord3DData
{
	Coord3D();
	~Coord3D();
};

struct Coord2D
{
	Real x;
	Real y;
};

struct Region3D
{
	Coord3DData lo;
	Coord3DData hi;
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

static const Real DRAWABLE_OVERSCAN = 75.0f;

class W3DView
{
public:
	virtual void viewSlot00() = 0;
	virtual void viewSlot04() = 0;
	virtual void viewSlot08() = 0;
	virtual void viewSlot0C() = 0;
	virtual void viewSlot10() = 0;
	virtual void viewSlot14() = 0;
	virtual void viewSlot18() = 0;
	virtual void viewSlot1C() = 0;
	virtual void viewSlot20() = 0;
	virtual void viewSlot24() = 0;
	virtual void viewSlot28() = 0;
	virtual void viewSlot2C() = 0;
	virtual void viewSlot30() = 0;
	virtual void getScreenCornerWorldPointsAtZ(Coord3D *topLeft, Coord3D *topRight,
		Coord3D *bottomLeft, Coord3D *bottomRight, Real z) = 0;

private:
	void getAxisAlignedViewRegion(Region3D &axisAlignedRegion);

	unsigned char m_viewHead[0x74];
	Coord2D m_guardBandBias;
};

void W3DView::getAxisAlignedViewRegion(Region3D &axisAlignedRegion)
{
	//
	// get the 4 points in 3D space of the 4 corners of the view, we will use a z = 0.0f
	// value so that we can get everything ... even stuff below the terrain
	//
	Coord3D box[ 4 ];
	getScreenCornerWorldPointsAtZ( &box[ 0 ], &box[ 1 ], &box[ 2 ], &box[ 3 ], 0.0f );

	//
	// take those 4 corners projected into the world and create an axis aligned bounding
	// box, we will use this box to iterate the drawables in 3D space
	//
	axisAlignedRegion.lo = box[ 0 ];
	axisAlignedRegion.hi = box[ 0 ];
	for( Int i = 0; i < 4; i++ )
	{

		if( box[ i ].x < axisAlignedRegion.lo.x )
			axisAlignedRegion.lo.x = box[ i ].x;
		if( box[ i ].y < axisAlignedRegion.lo.y )
			axisAlignedRegion.lo.y = box[ i ].y;
		if( box[ i ].x > axisAlignedRegion.hi.x )
			axisAlignedRegion.hi.x = box[ i ].x;
		if( box[ i ].y > axisAlignedRegion.hi.y )
			axisAlignedRegion.hi.y = box[ i ].y;

	}  // end for i

	// low and high regions will be based of the extent of the map
	Region3D mapExtent;
	Real safeValue = 999999;
	TheTerrainLogic->getExtent( &mapExtent );
	axisAlignedRegion.lo.z = mapExtent.lo.z - safeValue;
	axisAlignedRegion.hi.z = mapExtent.hi.z + safeValue;

	// we want to overscan a little bit so that we get objects that are partially offscreen
	axisAlignedRegion.lo.x -= (DRAWABLE_OVERSCAN + m_guardBandBias.x);
	axisAlignedRegion.lo.y -= (DRAWABLE_OVERSCAN + m_guardBandBias.y + 60.0f );
	axisAlignedRegion.hi.x += (DRAWABLE_OVERSCAN + m_guardBandBias.x);
	axisAlignedRegion.hi.y += (DRAWABLE_OVERSCAN + m_guardBandBias.y);

}
