// ?contains@Rva003D5B70@@QAE_NHH@Z
// partial score=0.9 date=2026-09-06
// cl: /DNDEBUG /DWIN32 /MD /EHsc /O2 /Ob2

struct Rva003D5B70Cell
{
    char m_pad00[0x0C];
    unsigned int m_flags;
};

class Rva003D5B70Info
{
private:
    char m_pad00[0x10];

public:
    Rva003D5B70Cell **m_rows;
    int m_minX;
    int m_minY;
    int m_maxX;
    int m_maxY;
};

class Rva003D5B70
{
public:
    bool contains(int x, int y);

private:
    Rva003D5B70Info *m_info;
};

bool Rva003D5B70::contains(int x, int y)
{
    Rva003D5B70Info *info = m_info;
    if (x < info->m_minX || x > info->m_maxX ||
        y < info->m_minY || y > info->m_maxY)
        return true;

    Rva003D5B70Cell *cell = info->m_rows[x] + y;
    if (cell == 0)
        return true;

    unsigned int flags = cell->m_flags;
    unsigned int high = flags >> 21;
    if ((high & 1) != 0)
        return false;

    unsigned int type = flags & 7;
    if (type == 2)
        return false;
    if (type == 5)
        return false;
    if (type == 4)
        return false;
    if (type == 1)
        return false;
    return true;
}
