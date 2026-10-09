// ??RQ4Sort00755050@@QBEEPBURva00752B80Record@@0@Z
// partial score=0.1355 date=2026-10-09
// cl: /O2 /Ob2 /GR- /EHsc- /MD /DNDEBUG

class Drawable;
class Rva00765AC0;

struct Rva00752A20Entry
{
    unsigned int m_field00;
    float m_field04;
    char m_pad08[8];
    int m_field10;
    int m_field14;
    unsigned char m_field18;
    char m_pad19[3];
};

struct Q4Sort00751F50Record
{
    char m_pad00[8];
    Drawable *m_drawable;
    char m_pad0c[8];
    Rva00765AC0 *m_state;
    char m_pad18[0xdc - 0x18];
    Rva00752A20Entry m_entries[2];

    bool compare(const Q4Sort00751F50Record &other, int *outLeft, int *outRight) const;
};

struct Rva00752A20DrawableView
{
    char m_pad00[0x1f8];
    float m_field1f8;
};

struct Rva00752B80Record
{
    unsigned int m_field00;
    Q4Sort00751F50Record *m_field04;
    int m_field08;
    __forceinline unsigned char less(const Rva00752B80Record &other) const;
};

struct Q4Sort00755050
{
    void *m_state;
    unsigned char operator()(const Rva00752B80Record *left, const Rva00752B80Record *right) const;
};

// ?less@Rva00752B80Record@@QBEEABU1@Z absent-from-retail
__forceinline unsigned char Rva00752B80Record::less(const Rva00752B80Record &other) const
{
    if (this->m_field00 != other.m_field00)
        return this->m_field00 > other.m_field00;
    if (this->m_field00 == 0)
        return this->m_field04 < other.m_field04;
    if (this->m_field08 != other.m_field08)
        return this->m_field08 < other.m_field08;

    const Q4Sort00751F50Record *lhs = this->m_field04;
    const Q4Sort00751F50Record *rhs = other.m_field04;
    const Rva00752A20DrawableView *leftDrawable = (const Rva00752A20DrawableView *)lhs->m_drawable;
    const Rva00752A20DrawableView *rightDrawable = (const Rva00752A20DrawableView *)rhs->m_drawable;
    if (leftDrawable->m_field1f8 != rightDrawable->m_field1f8)
        return leftDrawable->m_field1f8 < rightDrawable->m_field1f8;
    if (lhs->m_state != rhs->m_state)
        return lhs->m_state < rhs->m_state;

    int outRight;
    int outLeft;
    if (lhs->compare(*rhs, &outLeft, &outRight))
    {
        if (outLeft != outRight)
            return outLeft < outRight;
        return this->m_field04 < other.m_field04;
    }

    for (int i = 0; i <= 1; ++i)
    {
        const Rva00752A20Entry *leftEntry = &this->m_field04->m_entries[i];
        const Rva00752A20Entry *rightEntry = &other.m_field04->m_entries[i];
        if (leftEntry->m_field00 != rightEntry->m_field00)
            return leftEntry->m_field00 < rightEntry->m_field00;
        if (leftEntry->m_field00)
        {
            if (leftEntry->m_field14 != rightEntry->m_field14)
                return leftEntry->m_field14 < rightEntry->m_field14;
            if (leftEntry->m_field10 != rightEntry->m_field10)
                return leftEntry->m_field10 < rightEntry->m_field10;
            if (leftEntry->m_field18 != rightEntry->m_field18)
                return leftEntry->m_field18 != 0;
        }
    }

    float leftValue = (this->m_field04->m_entries[1].m_field00 ? this->m_field04->m_entries[1].m_field04 : 0.0f) + this->m_field04->m_entries[0].m_field04;
    float rightValue = (other.m_field04->m_entries[1].m_field00 ? other.m_field04->m_entries[1].m_field04 : 0.0f) + other.m_field04->m_entries[0].m_field04;
    if (leftValue != rightValue)
        return rightValue > leftValue;
    return this->m_field04 < other.m_field04;
}

// ??RQ4Sort00755050@@QBEEPBURva00752B80Record@@0@Z
unsigned char Q4Sort00755050::operator()(const Rva00752B80Record *left, const Rva00752B80Record *right) const
{
    return left->less(*right);
}
