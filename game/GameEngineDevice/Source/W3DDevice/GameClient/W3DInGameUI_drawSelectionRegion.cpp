// ?drawSelectionRegion@W3DInGameUI@@MAEXXZ
// Retail RVA 0x006FC3F0, 340 bytes. W3DInGameUI vtable VA 0x01120590
// slot +0x1b8 -> ILT RVA 0x0001e71d -> this body; matched draw at
// 0x006FBFF0 calls this slot in the ZH drawSelectionRegion position.
// The rectangle is the ZH twin with BFME render-state calls; BFME adds
// the point-list branch. TU-local layout preserves the banked names.
// Display slots +0xb0/+0xb4/+0xbc/+0xdc and Mouse position +0x4d10
// are read directly from retail. The inline helpers preserve the witnessed
// conversion lifetimes: rectangle floats before begin; line ints after begin.
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
    __forceinline void rectangle006FC3F0(Real x,Real y,Real w,Real h,Real width,UnsignedInt color) {
        rva006E9B70(); drawOpenRect(x,y,w,h,width,color); rva006E9B80();
    }
    __forceinline void line006FC3F0(Int x,Int y,Int w,Int h,Real width,UnsignedInt color,UnsignedInt color2) {
        rva006E9B70(); drawLine(x,y,w,h,width,color,color2); rva006E9B80();
    }

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

            reinterpret_cast<W3DDisplay *>(TheDisplay)->line006FC3F0(startPoint.x,startPoint.y,endPoint.x,endPoint.y,2.0f,0xBBFFBB33,0xBBFFBB33);
        } while (point != m_unmodelled_1304);
    }
    else
    {
        reinterpret_cast<W3DDisplay *>(TheDisplay)->rectangle006FC3F0(
            static_cast<Real>(m_unmodelled_24.first.x), static_cast<Real>(m_unmodelled_24.first.y),
            static_cast<Real>(m_unmodelled_24.second.x-m_unmodelled_24.first.x),
            static_cast<Real>(m_unmodelled_24.second.y-m_unmodelled_24.first.y),2.0f,0xBBFFBB33);
    }
}
