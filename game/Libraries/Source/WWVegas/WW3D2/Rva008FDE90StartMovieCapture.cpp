// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Igame/Libraries/Source/WWVegas/WW3D2
// stlport
#include "always.h"
#include "vector3.h"
#include "layer.h"
#include "w3derr.h"
#include "robjlist.h"
// Grant the address-derived free body access to the canonical WW3D globals.
// Preload dependencies so the friend declaration applies only to ww3d.h.
#define private private: friend void Rva008FDE90StartMovieCapture(const char *, float, int, bool); private
#include "ww3d.h"
#undef private

// Retail 0x008FDE90 has a four-argument capture-start ABI.

struct Rva008FDE90Rect
{
    long left;
    long top;
    long right;
    long bottom;
};
extern "C" __declspec(dllimport) int __stdcall GetWindowRect(void *, Rva008FDE90Rect *);
extern const float Rva00C75350Zero;

class BfmeThingTXA
{
public:
    virtual ~BfmeThingTXA();
    BfmeThingTXA(const char *filename, int width, int height, int bitcount,
        float framerate, int count, bool compressed);
    int m_bfmeImageSize;
    int m_bfmeCount;
    void *m_bfmeBuf;
    int m_bfmeReserved0;
    int m_bfmeReserved1;
    void *m_bfmeB;
    void *m_bfmeA;
};

extern void *g_WW3D_Hwnd;

// ?Rva008FDE90StartMovieCapture@@YAXPBDMH_N@Z
void Rva008FDE90StartMovieCapture(const char *filename_base, float frame_rate,
    int buffer_count, bool compressed)
{
    if (WW3D::IsCapturing)
    {
        WW3D::IsCapturing = false;
        delete (BfmeThingTXA *)WW3D::Movie;
        WW3D::Movie = 0;
    }
    WW3D::IsCapturing = true;
    Rva008FDE90Rect bounds;
    GetWindowRect(g_WW3D_Hwnd, &bounds);
    int height = bounds.bottom - bounds.top;
    int width = bounds.right - bounds.left;
    int depth = 24;
    if (frame_rate == Rva00C75350Zero)
    {
        frame_rate = 1.0f;
        WW3D::PauseRecord = true;
    }
    else
    {
        WW3D::PauseRecord = false;
    }
    WW3D::Movie = (FrameGrabClass *)new BfmeThingTXA(filename_base, width, height, depth,
        frame_rate, buffer_count, compressed);
}

