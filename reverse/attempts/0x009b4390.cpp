// ?Rva009B4390CodecCall@@YAHPAXHPBDZZ
// partial score=0.2 date=2026-09-24
// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD
#include <windows.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

extern "C" __declspec(dllimport) HBITMAP WINAPI CreateBitmap(
	int, int, UINT, UINT, const void *);
extern "C" __declspec(dllimport) BOOL WINAPI BitBlt(
	HDC, int, int, int, int, HDC, int, int, DWORD);
typedef DWORD COLORREF;
extern "C" __declspec(dllimport) COLORREF WINAPI GetPixel(HDC, int, int);

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

// ?Rva009B4390CodecCall@@YAHPAXHPBDZZ
int __cdecl Rva009B4390CodecCall(void *context, int offset, const char *format, ...)
{
	RECT rect;
	HFONT font;
	volatile int result;
	unsigned char *output;
	HBITMAP bitmap;
	HGDIOBJ selected;
	int stride;
	HGDIOBJ oldBitmap;

	stride = *(int *)((char *)context + 0x1b8);
	output = *(unsigned char **)((char *)context + 0x25c);
	char buffer[256];
	((volatile char *)buffer)[0] = 0;
	memset(buffer + 1, 0, 255);
	va_list args;
	output += offset;
	va_start(args, format);
	_ReadWriteBarrier();
	result = 0;
	_vsnprintf(buffer, sizeof(buffer), format, args);
	va_end(args);

	rect.left = 0;
	rect.top = 0;
	rect.right = (int)strlen(buffer + 16) * 8;
	rect.bottom = 8;

	HDC dc = CreateCompatibleDC(0);
	if (dc == 0)
		return result;

	bitmap = CreateBitmap(rect.right, rect.bottom, 1, 1, 0);
	if (bitmap == 0)
		goto delete_dc;

	oldBitmap = SelectObject(dc, bitmap);
	if (oldBitmap == 0)
		goto delete_bitmap;

	font = CreateFontA(8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x22, "");
	if (font == 0)
		goto restore_bitmap;

	selected = SelectObject(dc, bitmap);
	if (selected == 0)
		goto restore_bitmap;

	SelectObject(dc, font);
	SetTextColor(dc, 1);
	SetBkColor(dc, 0);
	SetBkMode(dc, 1);
	if (BitBlt(dc, rect.left, rect.top, rect.right, rect.bottom,
		dc, rect.left, rect.top, 0x42))
	{
		if (ExtTextOutA(dc, 0, 0, 4, &rect, buffer,
			(UINT)strlen(buffer), 0))
		{
			for (int y = rect.top; y < rect.bottom; ++y)
			{
				for (int x = rect.left; x < rect.right; ++x)
				{
					if (GetPixel(dc, x, rect.bottom - y - 1) != 0)
						output[x] = 0xff;
				}
				output += stride;
			}
			result = (int)strlen(buffer);
		}
	}

restore_bitmap:
	SelectObject(dc, oldBitmap);
	DeleteObject(bitmap);
	if (font != 0)
	{
		if (selected != 0)
			SelectObject(dc, selected);
		DeleteObject(font);
	}
	goto delete_dc;

delete_bitmap:
	DeleteObject(bitmap);
delete_dc:
	DeleteDC(dc);
	return result;
}
