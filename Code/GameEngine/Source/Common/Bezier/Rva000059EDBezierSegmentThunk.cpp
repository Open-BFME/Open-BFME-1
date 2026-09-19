// cl: /DNDEBUG /MD /EHsc
// Retail 0x000059ED is a five-byte tail jump to BezierSegment's matched
// evaluateBezSegmentAtT body. This wrapper keeps the ILT's address-derived
// identity and emits the proven route without duplicating that body.

typedef float Real;

struct Coord3D;

class BezierSegment
{
public:
	void evaluateBezSegmentAtT(Real tValue, Coord3D *outResult) const;
};

class Rva000059EDBezierSegmentThunk
{
public:
	void forward(Real tValue, Coord3D *outResult) const;
};

void Rva000059EDBezierSegmentThunk::forward(Real tValue, Coord3D *outResult) const
{
	((const BezierSegment *)this)->evaluateBezSegmentAtT(tValue, outResult);
}
