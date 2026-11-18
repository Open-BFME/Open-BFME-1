// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Push-button overlay helper with the decoded private register ABI.

#include "../../../../../../GameEngine/Include/Common/ScalarTypes.h"

typedef int Color;

class Image;

#include "../../../../../../Libraries/Include/Lib/ICoord2D.h"

// ?imageWidth@@YAHPBVImage@@@Z absent-from-retail
inline Int imageWidth(const Image *image)
{
    return *(const Int *)((const unsigned char *)image + 0x24);
}

class Display;

// BFME float-coordinate call view; the shared Display interface retains integer coordinates.
class DisplayImageView00794040
{
public:
    virtual void unused00();
    virtual void unused01();
    virtual void unused02();
    virtual void unused03();
    virtual void unused04();
    virtual void unused05();
    virtual void unused06();
    virtual void unused07();
    virtual void unused08();
    virtual void unused09();
    virtual void unused10();
    virtual void unused11();
    virtual void unused12();
    virtual void unused13();
    virtual void unused14();
    virtual void unused15();
    virtual void unused16();
    virtual void unused17();
    virtual void unused18();
    virtual void unused19();
    virtual void unused20();
    virtual void unused21();
    virtual void unused22();
    virtual void unused23();
    virtual void unused24();
    virtual void unused25();
    virtual void unused26();
    virtual void unused27();
    virtual void unused28();
    virtual void unused29();
    virtual void unused30();
    virtual void unused31();
    virtual void unused32();
    virtual void unused33();
    virtual void unused34();
    virtual void unused35();
    virtual void unused36();
    virtual void unused37();
    virtual void unused38();
    virtual void unused39();
    virtual void unused40();
    virtual void unused41();
    virtual void unused42();
    virtual void unused43();
    virtual void beginImageDraw();
    virtual void unused45();
    virtual void unused46();
    virtual void unused47();
    virtual void unused48();
    virtual void unused49();
    virtual void unused50();
    virtual void unused51();
    virtual void unused52();
    virtual void drawImageCore(const Image *image, Real startX, Real startY,
        Real endX, Real endY, Color color, Int mode);
    virtual void unused54();
    virtual void endImageDraw();
};

extern Display *TheDisplay;

// ?drawGeometry00794040@@YAXPAVDisplayImageView00794040@@PBVImage@@ABM222H@Z absent-from-retail
// Restrict the center reads after beginImageDraw to retain the x87 operand order.
__forceinline void drawGeometry00794040(DisplayImageView00794040 *display, const Image *image,
    const Real &centerX, const Real &centerY, const Real &extentX, const Real &extentY, Color color)
{
    display->beginImageDraw();
    display->drawImageCore(image, centerX - extentX, centerY - extentY,
        *(const volatile Real *)&centerX + extentX, *(const volatile Real *)&centerY + extentY, color, 2);
    display->endImageDraw();
}

// ?drawCenteredScaledImage00794040@@YAXPBVImage@@PBUICoord2D@@1H@Z
static void drawCenteredScaledImage00794040(const Image *image, const ICoord2D *start,
    const ICoord2D *size, Color color)
{
    Real halfX = size->x * 0.5f;
    Real halfY = size->y * 0.5f;
    Real centerX = start->x + halfX;
    Real centerY = start->y + halfY;
    Real extentX = imageWidth(image) * halfX * (1.0f / 48.0f);
    Real extentY = *(const Int *)((const unsigned char *)image + 0x28) * halfY * (1.0f / 48.0f);
    drawGeometry00794040((DisplayImageView00794040 *)TheDisplay, image, centerX, centerY, extentX, extentY, color);
}

// ?emitCenteredScaledImage00794040@@YAXPBVImage@@PBUICoord2D@@1H@Z absent-from-retail
void emitCenteredScaledImage00794040(const Image *image, const ICoord2D *start,
    const ICoord2D *size, Color color)
{
    drawCenteredScaledImage00794040(image, start, size, color);
}
