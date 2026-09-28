// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// Ported from the Generals/GeneralsMD W3DControlBar.cpp twin (EA GPL-3.0),
// the Zero Hour file the lift's name names; retail RVA 0079C7E0, 844 bytes.
//
// IDENTITY -- proved from the binary, not inherited from the lift. The retail
// W3DFunctionLexicon callback table is a 12-byte-stride array of
// {const char *name, void *fn, pad} at 0x012BA580; its entry at 0x012BA5BC is
// {0x0111D37C, 0x00403D0A}, the string at 0x0111D37C is
// "W3DCommandBarHelpPopupDraw", and 0x00403D0A is a 5-byte ILT thunk whose
// jmp targets 0x0079C7E0. The already-landed siblings resolve through the same
// table the same way (W3DCommandBarGenExpDraw -> 0x0042121F -> 0x0079B7D0,
// W3DCommandBarBackgroundDraw -> 0x004152D5 -> 0x0079CC00,
// W3DCommandBarForegroundDraw -> 0x00425437 -> 0x0079CD60). Arity agrees: two
// stack words in, bare ret.
//
// BFME DIFFERENCE FROM THE TWIN: only the image HEIGHT of the three bar images
// is read. Retail loads [image+0x28] for endBar, beginBar and centerBar and
// never touches [image+0x24], so the twin's getImageWidth() stores are gone.
// The clipping test is recomputed from the coordinates rather than reusing
// reg.hi.y, which is the shape the register allocator then produced.
//
// SHAPE LEVER -- the one non-obvious statement, kept because it is load
// bearing. `pos` has its address escape to winGetScreenPosition before any
// member of it is read by value, and MSVC 7.1 then keeps it as ONE opaque
// 8-byte local. Retail's frame keeps the position as two independently live
// members, which is what fixes the order of the two block-entry reload pairs
// at +0x256/+0x25A and +0x2D9/+0x2DD: retail emits pos.y then pos.x, the
// opaque form emits pos.x then pos.y. Reading the members by value BEFORE the
// address escapes splits the aggregate in x-then-y order and reproduces both
// sites exactly. Measured on this body: 843/844 with the read (0 masked byte
// differences, 48 relocations) against 836/844 without it, and the 8 differing
// bytes were the two reload pairs and nothing else. The read has to be of
// pos.x and it has to precede the call -- reading pos.y first, reading the
// members after either call, reading after the null-image guard, and a
// whole-struct copy all leave the 8 bytes. No code is emitted for the two
// locals; they exist only to mark the members as read.
//
// These compact views expose only the offsets and virtual slots this body reads.
#include "ascii_string.h"
struct ICoord2D {
    int x, y;
};
struct IRegion2D {
    ICoord2D lo, hi;
};
class WinInstanceData;
class GameWindow {
  public:
    int winGetScreenPosition(int *, int *);
    int winGetSize(int *, int *);
};
class Image {
  public:
    unsigned char pad_00[0x24];
    ICoord2D m_imageSize;
    int getImageWidth() const { return m_imageSize.x; }
    int getImageHeight() const { return m_imageSize.y; }
};
class ImageCollection {
  public:
    const Image *findImageByName(const AsciiString &);
};
extern ImageCollection *TheMappedImageCollection;
class GameWindowManager {
  public:
    virtual void slot00();
    virtual void slot01();
    virtual void slot02();
    virtual void slot03();
    virtual void slot04();
    virtual void slot05();
    virtual void slot06();
    virtual void slot07();
    virtual void slot08();
    virtual void slot09();
    virtual void slot10();
    virtual void slot11();
    virtual void slot12();
    virtual void slot13();
    virtual void slot14();
    virtual void slot15();
    virtual void slot16();
    virtual void slot17();
    virtual void slot18();
    virtual void slot19();
    virtual void slot20();
    virtual void slot21();
    virtual void slot22();
    virtual void slot23();
    virtual void slot24();
    virtual void slot25();
    virtual void slot26();
    virtual void slot27();
    virtual void slot28();
    virtual void slot29();
    virtual void slot30();
    virtual void slot31();
    virtual void slot32();
    virtual void slot33();
    virtual void slot34();
    virtual void slot35();
    virtual void slot36();
    virtual void slot37();
    virtual void slot38();
    virtual void slot39();
    virtual void slot40();
    virtual void slot41();
    virtual void slot42();
    virtual void slot43();
    virtual void slot44();
    virtual void slot45();
    virtual void slot46();
    virtual void slot47();
    virtual void slot48();
    virtual void slot49();
    virtual void slot50();
    virtual void slot51();
    virtual void slot52();
    virtual void slot53();
    virtual void slot54();
    virtual void slot55();
    virtual void slot56();
    virtual void slot57();
    virtual void slot58();
    virtual void slot59();
    virtual void slot60();
    virtual void winDrawImage(const Image *, int, int, int, int, int = -1);
};
extern GameWindowManager *TheWindowManager;
class Display {
  public:
    virtual void slot00();
    virtual void slot01();
    virtual void slot02();
    virtual void slot03();
    virtual void slot04();
    virtual void slot05();
    virtual void slot06();
    virtual void slot07();
    virtual void slot08();
    virtual void slot09();
    virtual void slot10();
    virtual void slot11();
    virtual void slot12();
    virtual void slot13();
    virtual void slot14();
    virtual void slot15();
    virtual void slot16();
    virtual void slot17();
    virtual void slot18();
    virtual void slot19();
    virtual void slot20();
    virtual void slot21();
    virtual void slot22();
    virtual void slot23();
    virtual void slot24();
    virtual void slot25();
    virtual void slot26();
    virtual void slot27();
    virtual void slot28();
    virtual void slot29();
    virtual void slot30();
    virtual void slot31();
    virtual void slot32();
    virtual void slot33();
    virtual void setClipRegion(IRegion2D *);
    virtual void slot35();
    virtual void enableClipping(bool);
};
extern Display *TheDisplay;
typedef int Int;
#define FALSE false
void W3DCommandBarHelpPopupDraw(GameWindow *window, WinInstanceData *instData) {
    static const Image *endBar = TheMappedImageCollection->findImageByName("Helpbox-top");
    static const Image *beginBar = TheMappedImageCollection->findImageByName("Helpbox-bottom");
    static const Image *centerBar = TheMappedImageCollection->findImageByName("Helpbox-middle");

    ICoord2D pos, size;
    Int screenLeft = pos.x, screenTop = pos.y;  // see SHAPE LEVER: never used
    (void)screenLeft; (void)screenTop;
    window->winGetScreenPosition(&pos.x, &pos.y);
    window->winGetSize(&size.x, &size.y);

    if (!endBar || !beginBar || !centerBar)
        return;

    // get image sizes for the ends
    ICoord2D topSize, bottomSize, start, end;
    bottomSize.y = beginBar->getImageHeight();
    topSize.y = endBar->getImageHeight();

    // draw the center repeating bar
    Int centerWidth, pieces;

    // get width we have to draw our repeating center in
    centerWidth = size.y - topSize.y - bottomSize.y;

    if (centerWidth <= 0) {
        // draw left end
        start.x = pos.x;
        start.y = pos.y + size.y - bottomSize.y;
        end.y = pos.y + size.y;
        end.x = pos.x + size.x;
        TheWindowManager->winDrawImage(beginBar, start.x, start.y, end.x, end.y);

        // draw right end
        start.y = pos.y + size.y - bottomSize.y - topSize.y;
        start.x = pos.x;
        end.x = pos.x + size.x;
        end.y = start.y + topSize.y;
        TheWindowManager->winDrawImage(endBar, start.x, start.y, end.x, end.y);
    } else {
        // how many whole repeating pieces will fit in that width
        pieces = centerWidth / centerBar->getImageHeight();

        // draw the pieces
        start.x = pos.x;
        start.y = pos.y + topSize.y;
        end.x = start.x + size.x;
        for (Int i = 0; i < pieces; i++) {
            end.y = start.y + centerBar->getImageHeight();
            TheWindowManager->winDrawImage(centerBar, start.x, start.y, end.x, end.y);
            start.y += centerBar->getImageHeight();
        }  // end for i

        // we will draw the image but clip the parts we don't want to show
        IRegion2D reg;
        reg.lo.x = start.x;
        reg.lo.y = start.y;
        reg.hi.x = pos.x + size.x;
        reg.hi.y = pos.y + size.y - bottomSize.y;
        centerWidth = pos.y + size.y - bottomSize.y - start.y;
        if (centerWidth > 0) {
            TheDisplay->setClipRegion(&reg);
            end.y = start.y + centerBar->getImageHeight();
            TheWindowManager->winDrawImage(centerBar, start.x, start.y, end.x, end.y);
            TheDisplay->enableClipping(FALSE);
        }

        // draw left end
        end.x = pos.x + size.x;
        end.y = pos.y + size.y;
        start.x = pos.x;
        start.y = pos.y + size.y - bottomSize.y;
        TheWindowManager->winDrawImage(beginBar, start.x, start.y, end.x, end.y);

        // draw right end
        start.x = pos.x;
        start.y = pos.y;
        end.x = pos.x + size.x;
        end.y = pos.y + topSize.y;
        TheWindowManager->winDrawImage(endBar, start.x, start.y, end.x, end.y);
    }
}
