// Retail 0x003D5B00, full boundary 0x003D5B00-0x003D5B4A (75 bytes).
// The next retail body begins at 0x003D5B60.  RET 8 consumes two integer
// arguments; the receiver's semantic owner is unknown.
//
// Retail's index shift proves the 16-byte cell stride; the sibling at
// 0x003D5AE0 also reads the packed dword at cell+0x0c. The map's ground subset
// uses rows at +0x10 and bounds at +0x14/+0x18/+0x1c/+0x20.
// The positive caller polarity is intentional: it leaves the computed-cell
// null test separate from the pointer add in the retail instruction shape.
// cl: /O2 /Ob2 /DNDEBUG /DWIN32 /D_WINDOWS /MD

typedef int Int;

struct Rva003D5B00Cell
{
    char m_pad[0x0C];
    unsigned int m_bits;
};

class Rva003D5B00Map
{
public:
    __forceinline Rva003D5B00Cell *getGroundCell(Int cellX, Int cellY)
    {
        if (cellX < m_minX || cellX > m_maxX ||
            cellY < m_minY || cellY > m_maxY)
            return 0;

        return (Rva003D5B00Cell *)((unsigned char *)m_rows[cellX] +
            cellY * sizeof(Rva003D5B00Cell));
    }

private:
    char m_pad[0x10];

public:
    Rva003D5B00Cell **m_rows;
    Int m_minX;
    Int m_minY;
    Int m_maxX;
    Int m_maxY;
};

class Rva003D5B00
{
public:
    Int check(Int cellX, Int cellY) const;

private:
    Rva003D5B00Map *m_map;
};

Int Rva003D5B00::check(Int cellX, Int cellY) const
{
    Rva003D5B00Map *map = m_map;
    Rva003D5B00Cell *cell = map->getGroundCell(cellX, cellY);
    if (cell != 0)
    {
        if ((cell->m_bits & 0xFC0u) == 0x40u)
            return 1;
    }
    return 0;
}
