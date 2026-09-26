// cl: /O2
// Retail RVA 0x001A59F0. The wrapper's scalar-destructor operand is ILT
// 0x00030652, which routes to the matched destructor at 0x0005CC00.
void operator delete[](void *block);

class BfmeHandleCX
{
public:
    ~BfmeHandleCX();
private:
    unsigned char m_data[0x04];
};

BfmeHandleCX *MakeBfmeHandleCXArray()
{ return new BfmeHandleCX[2]; }

void DeleteBfmeHandleCXArray(BfmeHandleCX *array)
{ delete[] array; }
