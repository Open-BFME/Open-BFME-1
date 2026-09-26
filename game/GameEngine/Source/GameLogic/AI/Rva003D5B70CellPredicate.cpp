// cl: /O2 /Ob2 /DNDEBUG /DWIN32 /D_WINDOWS /MD
// Retail 0x003D5B70, full boundary 0x003D5B70-0x003D5BCD (94 bytes), RET 8
// with two integer arguments; the receiver's semantic owner is unknown and the
// only caller (0x003DA3C0, via an ILT thunk) is itself unnamed.
//
// Same map subset as the landed sibling at 0x003D5B00: rows at +0x10, bounds
// at +0x14/+0x18/+0x1c/+0x20, 16-byte cells with a packed dword at +0x0c.
// Two levers recover retail's shape (docs/shape_levers.md):
// - "Nullable grid accessors: preserve the bounds helper": the inline nullable
//   cell lookup keeps the separate `test eax,eax` after the pointer add.
// - "Model-condition bit masks" (TU-local form): an inline bool test ending in
//   `!= 0` emits retail's `mov edx,eax; shr edx,0x15; test dl,1`.

typedef int Int;

struct Rva003D5B70Cell
{
    char m_pad[0x0C];
    unsigned int m_bits;

    __forceinline bool bit21() const { return ((m_bits >> 21) & 1) != 0; }
    __forceinline unsigned int low3() const { return m_bits & 7; }
};

class Rva003D5B70Map
{
public:
    __forceinline Rva003D5B70Cell *boundedCell(Int cellX, Int cellY)
    {
        if (cellX < m_minX || cellX > m_maxX ||
            cellY < m_minY || cellY > m_maxY)
            return 0;

        return (Rva003D5B70Cell *)((unsigned char *)m_rows[cellX] +
            cellY * sizeof(Rva003D5B70Cell));
    }

private:
    char m_pad[0x10];

public:
    Rva003D5B70Cell **m_rows;
    Int m_minX;
    Int m_minY;
    Int m_maxX;
    Int m_maxY;
};

class Rva003D5B70
{
public:
    bool check(Int cellX, Int cellY);

private:
    Rva003D5B70Map *m_map;
};

bool Rva003D5B70::check(Int cellX, Int cellY)
{
    Rva003D5B70Map *map = m_map;
    Rva003D5B70Cell *cell = map->boundedCell(cellX, cellY);
    if (cell != 0)
    {
        if (cell->bit21())
            return false;
        unsigned int type = cell->low3();
        if (type == 2 || type == 5 || type == 4 || type == 1)
            return false;
    }
    return true;
}
