// cl: /DNDEBUG /MD /EHsc
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/render2dsentence.cpp
#include <windows.h>

class FontCharsClassGdiState
{
public:
	FontCharsClassGdiState();

	int m_refs;
	HBITMAP m_oldBitmap;
	HBITMAP m_bitmap;
	void *m_bits;
	HDC m_dc;
};

// ??0FontCharsClassGdiState@@QAE@XZ
FontCharsClassGdiState::FontCharsClassGdiState() :
	m_refs(0),
	m_oldBitmap(0),
	m_bitmap(0),
	m_bits(0),
	m_dc(0)
{
	HDC screen_dc = ::GetDC(0);
	m_dc = ::CreateCompatibleDC(screen_dc);
	::ReleaseDC(0, screen_dc);

	::SetBkColor(m_dc, RGB(0, 0, 0));
	::SetTextColor(m_dc, RGB(255, 255, 255));

	BITMAPINFOHEADER bitmap_info;
	bitmap_info.biSize = 40;
	bitmap_info.biWidth = 64;
	bitmap_info.biHeight = -64;
	bitmap_info.biPlanes = 1;
	bitmap_info.biBitCount = 24;
	bitmap_info.biCompression = BI_RGB;
	bitmap_info.biSizeImage = 0;
	bitmap_info.biXPelsPerMeter = 0;
	bitmap_info.biYPelsPerMeter = 0;
	bitmap_info.biClrUsed = 0;
	bitmap_info.biClrImportant = 0;

	m_bitmap = ::CreateDIBSection(m_dc, (const BITMAPINFO *)&bitmap_info,
		DIB_RGB_COLORS, &m_bits, 0, 0);
	m_oldBitmap = (HBITMAP)::SelectObject(m_dc, m_bitmap);
}
