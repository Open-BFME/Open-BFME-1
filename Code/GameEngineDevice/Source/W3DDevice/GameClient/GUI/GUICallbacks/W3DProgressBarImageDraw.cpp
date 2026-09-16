// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c-
// W3DGadgetProgressBarImageDraw, retail 0x00793A60 (1 byte).
//
// The FunctionLexicon draw table at 0x012BA454 stores the string
// W3DGadgetProgressBarImageDraw in its row at 0x012BA52C next to the ILT thunk
// 0x004208CE, and that thunk jumps to 0x00793A60.  Retail parks a single ret
// there, so BFME emptied the callback that Zero Hour fills with the five-image
// bar draw.  The sibling W3DNoDraw at 0x0079A320 is the same one-byte shape and
// proves the linker gives each empty callback its own address instead of
// folding them together.
//
// Zero Hour's full body stays in W3DProgressBar.cpp, which is where the drawn
// variant W3DGadgetProgressBarImageDrawA still lives.
//
// Local ABI-slice replica so no shared header moves.

class GameWindow;
class WinInstanceData;

void W3DGadgetProgressBarImageDraw( GameWindow *window, WinInstanceData *instData )
{
}
