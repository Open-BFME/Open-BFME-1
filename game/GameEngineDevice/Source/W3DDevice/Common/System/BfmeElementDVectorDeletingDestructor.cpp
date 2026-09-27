// cl: /O2
// Retail RVA 0x0005E880: a vector deleting destructor for 0x24-byte elements
// whose destructor is ILT 0x00018FCF -> 0x0005DBF0 -> 0x008FC5B0. The ledger
// filed it as RoadType's, but W3DRoadBuffer's own new[]/delete[] of RoadType
// pass RoadType's destructor (ILT 0x0001DE49 -> 0x007070C0). Nothing in retail
// calls this body or its ILT thunk 0x00031FED. BfmeElementD is the existing
// placeholder for exactly this element: 0x24 bytes, destroyed by 0x00018FCF
// (S3ArrayOwnerDestructors.cpp).
void operator delete[](void *block);

class BfmeElementD
{
public:
    ~BfmeElementD();
private:
    char m_bfmeBytes[0x24];
};

BfmeElementD *MakeBfmeElementDArray()
{ return new BfmeElementD[2]; }

void DeleteBfmeElementDArray(BfmeElementD *array)
{ delete[] array; }
