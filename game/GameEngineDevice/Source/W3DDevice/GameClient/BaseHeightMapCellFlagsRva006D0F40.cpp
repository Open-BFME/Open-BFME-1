// cl: /DNDEBUG /MD /EHsc
// stlport
#include <vector>
// RVA 0x006D0F40: 332 bytes; five-argument thiscall ending ret 0x14.
// ZH BaseHeightMap::updateViewImpassableAreas is a control-flow donor,
// but that named method already owns 0x006D0DA0. Keep this owner opaque.
// Retail witnesses map+8/+12 extents, this+0x2FF4 map, this+0x3034 bitset
// and this+0x2FD4 angle. The ILT 0x0002B73D routes to 0x006C71C0.
// That landed callee casts its legacy float* output to char* and writes
// one byte only: out must be a byte local, not a float-sized object.

class BfmeOwnerZA
{
public:
    void bfmeDoZA(void *, void *, int, int, int, int, float *, char *);
};

struct Rva006D0F40Map
{
    char pad00[8];
    int width, height;
};

class Rva006D0F40
{
public:
    char pad00[0x2fd4];
    float field2fd4;
    char pad2fd8[0x1c];
    Rva006D0F40Map *m_map;
    char pad2ff8[0x3c];
    std::vector<bool> field3034;

    void method(bool, int, int, int, int);

    bool evaluate(int x, int y, float value)
    {
        char ok = 0;
        char out;
        ((BfmeOwnerZA *)this)->bfmeDoZA((void *)x, (void *)y,
            256, 0, (int)value, 0, reinterpret_cast<float *>(&out), &ok);
        return ok == 0;
    }
};

void Rva006D0F40::method(bool partial, int minX, int maxX, int minY, int maxY)
{
    int xSize = m_map->width;
    int ySize = m_map->height;
    if (field3034.size() != xSize * ySize)
        field3034.resize(xSize * ySize);

    if (!partial)
    {
        minX = 0;
        minY = 0;
        maxX = xSize;
        maxY = ySize;
    }

    for (int j = minY; j < maxY; ++j)
    {
        for (int i = minX; i < maxX; ++i)
        {
            field3034[i + j * xSize] = evaluate(i, j, field2fd4);
        }
    }
}
