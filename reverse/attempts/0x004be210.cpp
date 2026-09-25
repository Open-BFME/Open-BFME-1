// ?GadgetTextEntrySetCursorPosition@@YAXPAVGameWindow@@I@Z
// partial score=0.479339 date=2026-09-25
// cl: /DNDEBUG /MD /EHsc
// The DisplayString vtable offsets below are the retail slots used by this body.
typedef unsigned char Byte;
typedef unsigned int UnsignedInt;
typedef int Int;
class GameWindow
{
public:
    void *winGetUserData();
    int winGetSize(Int *width, Int *height);
};
class DisplayString
{
public:
    virtual void slot00();                 // +0x00
    virtual void setText();                // +0x04
    virtual void *getText();               // +0x08
    virtual Int getTextLength();            // +0x0c
    virtual void slot10();
    virtual void slot14();
    virtual void slot18();
    virtual void slot1c();
    virtual void slot20();
    virtual void slot24();
    virtual void slot28();
    virtual void slot2c();
    virtual void slot30();
    virtual void slot34();
    virtual void slot38();
    virtual void slot3c();
    virtual Int getWidth(Int charPos);      // +0x40
};
struct BfmeEntryDataForCursor
{
    DisplayString *text;                    // +0x00
    void *secretTextDisplay;                // +0x04
    void *constructText;                    // +0x08
    UnsignedInt flags;                      // +0x0c
    short maxTextLen;                       // +0x10
    Byte receivedUnichar;                   // +0x12
    Byte drawTextFromStart;                 // +0x13
    Byte padding14[8];
    unsigned short charPos;                 // +0x1c
    unsigned short conCharPos;              // +0x1e
    Byte padding20[4];
    UnsignedInt visibleStart;               // +0x24
};
void __cdecl GadgetTextEntrySetCursorPosition(GameWindow *window, UnsignedInt position)
{
    BfmeEntryDataForCursor *entry =
        (BfmeEntryDataForCursor *)window->winGetUserData();
    unsigned short cursor = (unsigned short)position;
    entry->charPos = cursor;

    // Retail compares the zero-extended cursor against the unsigned start.
    if ((UnsignedInt)cursor < entry->visibleStart) {
        entry->visibleStart = cursor < 5 ? 0 : (UnsignedInt)(cursor - 5);
        return;
    }

    // The consumed cursor parameter becomes the signed width scratch slot.
    Int &width = reinterpret_cast<Int &>(position);
    Int height;
    window->winGetSize(&width, &height);
    if (width > 8)
        width -= 8;

    DisplayString *text = entry->text;
    Int endWidth = text->getWidth(entry->charPos);
    Int startWidth = text->getWidth((Int)entry->visibleStart);
    if (endWidth - startWidth <= width)
        return;

    Int length = entry->text->getTextLength();
    Int cursorPlusFive = (Int)entry->charPos + 5;
    const Int &measurementEnd = cursorPlusFive < length ? cursorPlusFive : length;
    endWidth = entry->text->getWidth(measurementEnd);
    while (endWidth - entry->text->getWidth((Int)entry->visibleStart) > width) {
        ++entry->visibleStart;
    }
}
