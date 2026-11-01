// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
struct HWND__;
HWND__ *g_bfmeObjECFFlag27C = 0;

// DX8WebBrowser's browser-engine COM pointer cell (VA 0x0134B280, beside
// hWnd): Initialize creates it, CreateBrowser/Update/Render call through it
// and Shutdown releases it. Only its four zero bytes are defined here.
class Rva00958D30;
struct Rva00959410Ptr { Rva00958D30 *m_p; };
Rva00959410Ptr Rva00959410Dispatch = { 0 };
