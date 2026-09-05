// cl: /DNDEBUG /DWIN32 /MD /EHsc
// partial score=0.75 date=2026-09-05
// Near-twin of W3DBridge::getModelIndices (0x006D89D0, in
// W3DBridgeBuffer.cpp): byte-identical except the maxBridgeIndex guard
// constant is 30000 here instead of 16000. No vtable calls in the retail
// body -- Peek_Model()/Get_Polygon_Count()/Get_Polygon_Array() are all
// inline field reads (model pointer at MeshClass+0xC8, polygon count at
// Model+0x24, polygon array at Model+0x2C), so only those offsets are
// modelled; the real sibling name is not recovered.

typedef int Int;
typedef unsigned short UnsignedShort;

struct TriIndex
{
	UnsignedShort I, J, K;
};

class ModelShim
{
public:
	Int Get_Polygon_Count() const { return m_polyCount; }
	const TriIndex *Get_Polygon_Array() const { return m_polyArray; }

private:
	char m_pad0[ 0x24 ];
	Int m_polyCount;               // +0x24
	char m_pad1[ 0x2c - 0x24 - 4 ];
	const TriIndex *m_polyArray;   // +0x2c
};

class MeshClass
{
public:
	ModelShim *Peek_Model() const { return m_model; }

private:
	char m_pad0[ 0xc8 ];
	ModelShim *m_model;            // +0xc8
};

class W3DBridge
{
protected:
	Int rva006F8720( UnsignedShort *destination_ib, Int curIndex, Int vertexOffset, MeshClass *pMesh );
};

// ?rva006f8720@W3DBridge@@IAEHPAGHHPAVMeshClass@@@Z
Int W3DBridge::rva006F8720( UnsignedShort *destination_ib, Int curIndex, Int vertexOffset, MeshClass *pMesh )
{
	if ( pMesh == 0 )
		return 0;
	const TriIndex *pPoly = pMesh->Peek_Model()->Get_Polygon_Array();
	Int numPoly = pMesh->Peek_Model()->Get_Polygon_Count();
	const Int maxBridgeIndex = 30000;
	if ( curIndex + 3 * numPoly + 6 >= maxBridgeIndex )
	{
		return 0;
	}
	UnsignedShort *curIb = destination_ib + curIndex;
	Int i;
	for ( i = 0; i < numPoly; i++ )
	{
		*curIb++ = vertexOffset + pPoly[ i ].I;
		*curIb++ = vertexOffset + pPoly[ i ].J;
		*curIb++ = vertexOffset + pPoly[ i ].K;
	}
	return numPoly * 3;
}
