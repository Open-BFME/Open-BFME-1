// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// Ported from GeneralsMD W3DControlBar.cpp (EA GPL-3.0); retail RVA 0079B7D0.
// Identity: W3DFunctionLexicon registers this callback by its exact name;
// retail uses GenExpBarTop1/Bottom1/1 and the same drawing/clipping flow.
// BFME differences: Player skill points are float at +25c; threshold reads
// at +268/+26c; Image size at +24; manager draw slot +f4 and Display +88/+90.
// These compact views expose only offsets and virtual slots read by this body.
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
class Player {
  public:
    bool isPlayerActive() const;
    unsigned char pad_000[0x25c];
    float m_skillPoints;
    unsigned char pad_260[4];
    int m_sciencePurchasePoints[2];
    int m_levelDown;
    float getSkillPoints() const { return m_skillPoints; }
    int getSkillPointsLevelDown() const { return m_levelDown; }
    int getSkillPointsLevelUp() const { return m_sciencePurchasePoints[1]; }
};
class PlayerList {
  public:
    unsigned char pad_00[12];
    Player *m_local;
    Player *getLocalPlayer() { return m_local; }
};
extern PlayerList *ThePlayerList;
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
void W3DCommandBarGenExpDraw(GameWindow *window, WinInstanceData *instData) {
    Player *player = ThePlayerList->getLocalPlayer();
    if (!player->isPlayerActive())
        return;
    static const Image *endBar = TheMappedImageCollection->findImageByName("GenExpBarTop1");
    static const Image *beginBar = TheMappedImageCollection->findImageByName("GenExpBarBottom1");
    static const Image *centerBar = TheMappedImageCollection->findImageByName("GenExpBar1");
    Int progress;
    progress = ((player->getSkillPoints() - player->getSkillPointsLevelDown()) * 100) /
               (player->getSkillPointsLevelUp() - player->getSkillPointsLevelDown());

    if (progress <= 0)
        return;

    // GS This should never be necessary, but scripts can change the points required or even disable
    // a level. A disabled level will be -1 for points required.  Just be totally safe and bind to
    // 100, and we will fix the scripts to bind the points gained later.
    if (progress > 100)
        progress = 100;

    ICoord2D pos, size;
    window->winGetScreenPosition(&pos.x, &pos.y);
    window->winGetSize(&size.x, &size.y);

    if (!endBar || !beginBar || !centerBar)
        return;

    Int range;
    range = size.y * progress / 100;

    // get image sizes for the ends
    ICoord2D topSize, bottomSize, start, end;
    bottomSize.x = beginBar->getImageWidth();
    bottomSize.y = beginBar->getImageHeight();
    topSize.x = endBar->getImageWidth();
    topSize.y = endBar->getImageHeight();

    // get two key points used in the end drawing
    ICoord2D bottomEnd, topStart;
    bottomEnd.x = pos.x + size.x;
    bottomEnd.y = pos.y + size.y - bottomSize.y;
    topStart.x = pos.x;
    topStart.y = pos.y + size.y - range - topSize.y;

    // draw the center repeating bar
    Int centerWidth, pieces;

    // get width we have to draw our repeating center in
    centerWidth = bottomEnd.y - topStart.y;

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
        start.y = topStart.y;
        end.x = start.x + size.x; // centerImage->getImageHeight() + yOffset;
        for (Int i = 0; i < pieces; i++) {

            end.y = start.y + centerBar->getImageHeight();
            TheWindowManager->winDrawImage(centerBar, start.x, start.y, end.x, end.y);
            start.y += centerBar->getImageHeight();

        } // end for i

        // we will draw the image but clip the parts we don't want to show
        IRegion2D reg;
        reg.lo.x = start.x;
        reg.lo.y = start.y;
        reg.hi.x = bottomEnd.x;
        reg.hi.y = bottomEnd.y;
        centerWidth = bottomEnd.y - start.y;
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
        start.y = bottomEnd.y;
        TheWindowManager->winDrawImage(beginBar, start.x, start.y, end.x, end.y);

        // draw right end
        start.x = pos.x;
        start.y = pos.y + size.y - range;
        end.x = pos.x + size.x;
        end.y = pos.y + size.y - range - topSize.y;
        TheWindowManager->winDrawImage(endBar, start.x, start.y, end.x, end.y);
    }
}
