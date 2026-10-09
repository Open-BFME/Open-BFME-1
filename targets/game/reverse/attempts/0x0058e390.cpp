// ?rva0058E390@Rva00592640Owner@@QAEXPBURva0058E390Point@@0II@Z
// partial score=0.9812 date=2026-10-09
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
#include "unicode_string.h"
inline UnicodeString::UnicodeString(const UnicodeString &s)
{
    ((StringBase<unsigned short>*)this)->StringBase<unsigned short>::StringBase(*(const StringBase<unsigned short>*)&s);
}
inline UnicodeString::~UnicodeString()
{
    ((StringBase<unsigned short>*)this)->~StringBase<unsigned short>();
}
template<> inline bool StringBase<unsigned short>::isEmpty() const { return !m_data || m_data->length == 0; }
extern "C" __declspec(dllimport) double __cdecl floor(double);
// Native rounding conversion after CRT floor avoids the truncation helper.
static __forceinline int fast_float2long_round(float value)
{
    int result;
    __asm fld value
    __asm fistp result
    return result;
}

struct Rva0058E390Point
{
    Rva0058E390Point(float a, float b) : x(a), y(b) {}
    Rva0058E390Point(const Rva0058E390Point &p) : x(p.x), y(p.y) {}
    float x, y;
};
class BfmeVec2EV
{
public:
    BfmeVec2EV() {}
    BfmeVec2EV(const BfmeVec2EV &v) : m_bfmeXEV(v.m_bfmeXEV), m_bfmeYEV(v.m_bfmeYEV) {}
    BfmeVec2EV &operator=(const BfmeVec2EV &v) { m_bfmeXEV=v.m_bfmeXEV; m_bfmeYEV=v.m_bfmeYEV; return *this; }
    float m_bfmeXEV, m_bfmeYEV;
};
struct Rva00579160Manager
{
	virtual void bfmeSlot0EV();
	virtual void bfmeSlot1EV();
	virtual void bfmeSlot2EV();
	virtual void bfmeSlot3EV();
	virtual void bfmeSlot4EV();
	virtual void bfmeSlot5EV();
	virtual void bfmeSlot6EV();
	virtual void bfmeSlot7EV();
	virtual void bfmeSlot8EV();
	virtual void bfmeSlot9EV();
	virtual const float *bfmeScaleEV();
};

// Retail WindowManager global; this view uses its witnessed scale slot.
class WindowManager;
extern WindowManager *g_rva012F19E8WindowManager;

static inline Rva00579160Manager *rva00579160TheManagerView(void)
{
	return (Rva00579160Manager *)g_rva012F19E8WindowManager;
}

class BfmeCellEV
{
public:
	unsigned char m_bfmeHeadEV[0x24];
	int m_bfmeWEV;
	int m_bfmeHEV;
};

class BfmeHostEV
{
public:
	void bfmeExtentsEV(BfmeVec2EV *a, BfmeVec2EV *b, BfmeVec2EV *out);

	unsigned char m_bfmeHeadEV[0x28];
	BfmeCellEV *m_bfmeFirstEV;
	BfmeCellEV *m_bfmeSecondEV;
};

__declspec(noinline) void BfmeHostEV::bfmeExtentsEV(BfmeVec2EV *a, BfmeVec2EV *b, BfmeVec2EV *out)
{
	const float *k = rva00579160TheManagerView()->bfmeScaleEV();

	if (m_bfmeFirstEV != 0)
	{
		a->m_bfmeXEV = m_bfmeFirstEV->m_bfmeWEV * k[0];
		a->m_bfmeYEV = m_bfmeFirstEV->m_bfmeHEV * k[1];
	}
	else
	{
		a->m_bfmeXEV = 0.0f;
		a->m_bfmeYEV = 0.0f;
	}

	if (m_bfmeSecondEV != 0)
	{
		b->m_bfmeXEV = m_bfmeSecondEV->m_bfmeWEV * k[0];
		b->m_bfmeYEV = m_bfmeSecondEV->m_bfmeHEV * k[1];
	}
	else
	{
		b->m_bfmeXEV = 0.0f;
		b->m_bfmeYEV = 0.0f;
	}

	out->m_bfmeXEV = a->m_bfmeXEV > b->m_bfmeXEV ? a->m_bfmeXEV : b->m_bfmeXEV;
	out->m_bfmeYEV = a->m_bfmeYEV > b->m_bfmeYEV ? a->m_bfmeYEV : b->m_bfmeYEV;
}

class Rva00589040Vec2 { public: float m_x, m_y; };
void Rva00589040Draw(int, float, float, const Rva00589040Vec2*, const Rva00589040Vec2*);

// DisplayString view retains the BFME-only virtual slots.
class Rva0058E390DisplayString
{
public:
    virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0C();
    virtual void slot10(); virtual void slot14(); virtual void slot18(); virtual void slot1C();
    virtual void setWordWrap(int);
    virtual void slot24(); virtual void slot28(); virtual void slot2C(); virtual void slot30();
    virtual void draw(int, int);
    virtual void slot38();
    virtual void getSize(int*, int*);
};
struct Rva0058E390Data
{
    unsigned int at00;
    UnicodeString at04, at08;
    unsigned int at0C;
    unsigned short at10;
};
class Rva00592640Owner
{
public:
    void rva0058E390(const Rva0058E390Point*, const Rva0058E390Point*, unsigned int, unsigned int);
    bool m_at00;
    unsigned char m_at01;
    bool m_at02;
    int m_unreconstructed_04;
    void *m_member8;
    Rva0058E390Data *m_memberC;
    unsigned int m_at10;
    Rva0058E390DisplayString *m_drop1, *m_drop2, *m_drop3, *m_drop4, *m_drop5;
    BfmeCellEV *m_at28, *m_at2C;
};

// ?rva0058E390@Rva00592640Owner@@QAEXPBURva0058E390Point@@0II@Z present-unmatched
void Rva00592640Owner::rva0058E390(const Rva0058E390Point *pos, const Rva0058E390Point *size, unsigned int, unsigned int)
{
    if (m_at02 && m_unreconstructed_04 < 0)
    {
        m_unreconstructed_04 = (int)(size->x + 0.5f);
        m_drop1->setWordWrap(m_unreconstructed_04);
        m_drop5->setWordWrap(m_unreconstructed_04);
        return;
    }
    if (!m_at00 || !m_memberC)
    {
        m_at00 = false;
        return;
    }
    BfmeVec2EV first, second, largest;
    ((BfmeHostEV*)this)->bfmeExtentsEV(&first, &second, &largest);
    UnicodeString text1(m_memberC->at04);
    int image1 = (int)m_at28;
    BfmeVec2EV imageSize1 = first;
    UnicodeString text2(m_memberC->at08);
    int image2 = (int)m_at2C;
    first = second;
    if (text1.isEmpty() && !text2.isEmpty())
    {
        ((StringBase<unsigned short>*)&text1)->swap(*(StringBase<unsigned short>*)&text2);
        image1 = image2;
        imageSize1 = first;
    }
    float y = pos->y;
    int width, height;
    m_drop1->getSize(&width, &height);
    float x = (size->x - width) * 0.5f + pos->x;
    {
        int iy = fast_float2long_round((float)floor(y + 0.5f));
        int ix = fast_float2long_round((float)floor(x + 0.5f));
        m_drop1->draw(ix, iy);
    }
    y += height;
    float rowHeight = 0.0f;
    bool center = false;
    typedef void (__cdecl *DrawImage)(int, Rva0058E390Point, const BfmeVec2EV*, const BfmeVec2EV*);
    if (m_memberC->at10 != 0)
    {
        if (!text1.isEmpty())
        {
            m_drop2->getSize(&width, &height);
            float h1 = (float)height;
            m_drop4->getSize(&width, &height);
            float w4 = (float)width;
            float h4 = (float)height;
            rowHeight = h1 > h4 ? h1 : h4;
            if (largest.m_bfmeYEV > rowHeight) rowHeight = largest.m_bfmeYEV;
            ((DrawImage)Rva00589040Draw)(image1, Rva0058E390Point(pos->x, (rowHeight-largest.m_bfmeYEV)*0.5f+y), &largest, &imageSize1);
            {
                int ix = fast_float2long_round((float)floor(largest.m_bfmeXEV+pos->x+0.5f));
                int iy = fast_float2long_round((float)floor((rowHeight-h1+1.0f)*0.5f+y));
                m_drop2->draw(ix, iy);
            }
            {
                int ix = fast_float2long_round((float)floor(pos->x+size->x-w4+0.5f));
                int iy = fast_float2long_round((float)floor((rowHeight-h4+1.0f)*0.5f+y));
                m_drop4->draw(ix, iy);
            }
        }
        else
        {
            m_drop4->getSize(&width, &height);
            rowHeight = (float)height;
            x = (size->x-width)*0.5f+pos->x;
            {
                int iy = fast_float2long_round((float)floor(y+0.5f));
                int ix = fast_float2long_round((float)floor(x+0.5f));
                m_drop4->draw(ix, iy);
            }
        }
    }
    else
    {
        center = true;
        if (!text1.isEmpty())
        {
            m_drop2->getSize(&width, &height);
            float w2 = (float)width;
            float h2 = (float)height;
            rowHeight = largest.m_bfmeYEV > h2 ? largest.m_bfmeYEV : h2;
            float rowX = (size->x-(w2+largest.m_bfmeXEV))*0.5f+pos->x;
            ((DrawImage)Rva00589040Draw)(image1, Rva0058E390Point(rowX, (rowHeight-largest.m_bfmeYEV)*0.5f+y), &largest, &imageSize1);
            {
                int ix = fast_float2long_round((float)floor(largest.m_bfmeXEV+rowX+0.5f));
                int iy = fast_float2long_round((float)floor((rowHeight-h2+1.0f)*0.5f+y));
                m_drop2->draw(ix, iy);
            }
        }
    }
    y += rowHeight;
    if (!text2.isEmpty())
    {
        m_drop3->getSize(&width, &height);
        float w3 = (float)width;
        float h3 = (float)height;
        rowHeight = largest.m_bfmeYEV > h3 ? largest.m_bfmeYEV : h3;
        float rowX = pos->x;
        if (center) { float totalWidth = w3+largest.m_bfmeXEV; rowX += (size->x-totalWidth)*0.5f; }
        ((DrawImage)Rva00589040Draw)(image2, Rva0058E390Point(rowX, (rowHeight-largest.m_bfmeYEV)*0.5f+y), &largest, &first);
        {
            int ix = fast_float2long_round((float)floor(largest.m_bfmeXEV+rowX+0.5f));
            int iy = fast_float2long_round((float)floor((rowHeight-h3+1.0f)*0.5f+y));
            m_drop3->draw(ix, iy);
        }
        y += rowHeight;
    }
    m_drop5->getSize(&width, &height);
    x = (size->x-width)*0.5f+pos->x;
    {
        int iy = fast_float2long_round((float)floor(y+0.5f));
        int ix = fast_float2long_round((float)floor(x+0.5f));
        m_drop5->draw(ix, iy);
    }
}
