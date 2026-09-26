// cl: /DNDEBUG /MD /EHsc /Iinputs/toolchains/vs2003/PROG~FBU/MICR~2RR.NET/Vc7/atlmfc/include /Iinputs/toolchains/vs2003/PROG~FBU/MICR~2RR.NET/Vc7/PlatformSDK/Include
// Open-BFME5: the VS2003 ATL CImage::Load(LPCTSTR) inline body at retail
// 0x00060010.  The header's ANSI CT2W temporary, GDI+ Bitmap lifetime, and
// private CreateFromGdiplusBitmap call are the witnessed retail sequence.

#include <atlimage.h>

typedef HRESULT (ATL::CImage::*Rva00060010CImageLoadAnsi)(LPCSTR);

Rva00060010CImageLoadAnsi rva00060010CImageLoadAnsi = &ATL::CImage::Load;
