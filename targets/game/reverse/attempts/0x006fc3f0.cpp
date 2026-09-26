// ?drawSelectionRegion@W3DInGameUI@@MAEXXZ
// partial score=0.69 date=2026-09-23
// cl: /DNDEBUG /MD /EHsc

class Display;
class Mouse;
extern Display *TheDisplay;
extern Mouse *TheMouse;

typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;

struct Rva006FC3F0Point
{
    Int x;
    Int y;
};

struct Rva006FC3F0Region
{
    Rva006FC3F0Point first;
    Rva006FC3F0Point second;
};

struct Rva006FC3F0PointNode
{
    Rva006FC3F0PointNode *next;
    Rva006FC3F0PointNode *unmodelled_04;
    Rva006FC3F0Point point;
};

struct Rva006FC3F0MouseView
{
    unsigned char unmodelled_00[0x4D10];
    struct
    {
        Rva006FC3F0Point pos;
    } m_currMouse;
};

#define DECLARE_TEN(prefix) \
    virtual void prefix##0() = 0; virtual void prefix##1() = 0; \
    virtual void prefix##2() = 0; virtual void prefix##3() = 0; \
    virtual void prefix##4() = 0; virtual void prefix##5() = 0; \
    virtual void prefix##6() = 0; virtual void prefix##7() = 0; \
    virtual void prefix##8() = 0; virtual void prefix##9() = 0;

class W3DDisplay
{
public:
    DECLARE_TEN(display0)
    DECLARE_TEN(display10)
    DECLARE_TEN(display20)
    DECLARE_TEN(display30)
    virtual void display40() = 0;
    virtual void display41() = 0;
    virtual void display42() = 0;
    virtual void display43() = 0;
    virtual void rva006E9B70() = 0;
    virtual void drawLine(Real startX, Real startY, Real endX, Real endY,
        Real lineWidth, UnsignedInt lineColor1, UnsignedInt lineColor2) = 0;
    virtual void display46() = 0;
    virtual void drawOpenRect(Real startX, Real startY, Real width, Real height,
        Real lineWidth, UnsignedInt lineColor) = 0;
    virtual void display48() = 0;
    virtual void display49() = 0;
    virtual void display50() = 0;
    virtual void display51() = 0;
    virtual void display52() = 0;
    virtual void display53() = 0;
    virtual void display54() = 0;
    virtual void rva006E9B80() = 0;
};

class W3DInGameUISlots
{
public:
    DECLARE_TEN(ui0)
    DECLARE_TEN(ui10)
    DECLARE_TEN(ui20)
    DECLARE_TEN(ui30)
    DECLARE_TEN(ui40)
    DECLARE_TEN(ui50)
    DECLARE_TEN(ui60)
    DECLARE_TEN(ui70)
    DECLARE_TEN(ui80)
    DECLARE_TEN(ui90)
    DECLARE_TEN(ui100)
};

class W3DInGameUI : public W3DInGameUISlots
{
private:
    unsigned char unmodelled_04[0x1C];
    unsigned char m_isDragSelecting;
    unsigned char unmodelled_21[3];
    Rva006FC3F0Region m_unmodelled_24;
    unsigned char unmodelled_34[0x1304 - 0x34];
    Rva006FC3F0PointNode *m_unmodelled_1304;
    unsigned char unmodelled_1308[0x10];
    unsigned char m_unmodelled_1318;

protected:
    virtual void drawSelectionRegion();
};

#undef DECLARE_TEN

// ?drawSelectionRegion@W3DInGameUI@@MAEXXZ
void W3DInGameUI::drawSelectionRegion()
{
    if (m_unmodelled_1318)
    {
        Rva006FC3F0PointNode *point = m_unmodelled_1304->next;
        if (point == m_unmodelled_1304)
            return;

        do
        {
            Rva006FC3F0Point startPoint = point->point;
            point = point->next;
            Rva006FC3F0Point endPoint;
            if (point != m_unmodelled_1304)
            {
                endPoint = point->point;
            }
            else
            {
                Rva006FC3F0MouseView *mouse = reinterpret_cast<Rva006FC3F0MouseView *>(TheMouse);
                endPoint.x = mouse->m_currMouse.pos.x;
                endPoint.y = mouse->m_currMouse.pos.y;
            }

            W3DDisplay *display = reinterpret_cast<W3DDisplay *>(TheDisplay);
            display->rva006E9B70();
            display->drawLine(static_cast<Real>(startPoint.x), static_cast<Real>(startPoint.y),
                static_cast<Real>(endPoint.x), static_cast<Real>(endPoint.y), 2.0f,
                0xBBFFBB33, 0xBBFFBB33);
            display->rva006E9B80();
        } while (point != m_unmodelled_1304);
    }
    else
    {
        Int y = m_unmodelled_24.first.y;
        Int height = m_unmodelled_24.second.y - y;
        Real floatHeight = static_cast<Real>(height);
        W3DDisplay *display = reinterpret_cast<W3DDisplay *>(TheDisplay);
        Int x = m_unmodelled_24.first.x;
        Int width = m_unmodelled_24.second.x - x;
        Real floatY = static_cast<Real>(y);
        Real floatWidth = static_cast<Real>(width);
        Real floatX = static_cast<Real>(x);
        display->rva006E9B70();
        display->drawOpenRect(floatX, floatY, floatWidth, floatHeight, 2.0f,
            0xBBFFBB33);
        display->rva006E9B80();
    }
}
