// ?Rva009B4390CodecCall@@YAHPAXH0HHHHHHHHHHHH@Z
// partial score=0.152459 date=2026-09-22
// cl: /DNDEBUG /MD /O2
// Address-derived identity; callers at 0x009AABB0 and 0x009AAC80.
#include <windows.h>
#include <stdio.h>
extern "C" __declspec(dllimport) HBITMAP __stdcall CreateBitmap(int, int, UINT, UINT, const void *);
extern "C" __declspec(dllimport) BOOL __stdcall BitBlt(HDC, int, int, int, int, HDC, int, int, DWORD);
extern "C" __declspec(dllimport) DWORD __stdcall GetPixel(HDC, int, int);

int __cdecl Rva009B4390CodecCall(
    void *owner, int offset, void *format, int a0, int a1, int a2,
    int a3, int a4, int a5, int a6, int a7, int a8, int a9, int a10, int a11)
{
    int width = *(int *)((char *)owner + 0x1b8);
    unsigned char *output = (unsigned char *)(*(int *)((char *)owner + 0x25c) + offset);
    char buffer[256] = {0};
    int result = 0;
    _vsnprintf(buffer, sizeof(buffer), (const char *)format, (va_list)&a0);
    int count = 0;
    while (buffer[count]) ++count;
    RECT rect = {0, 0, count * 8, 8};
    HDC dc = CreateCompatibleDC(0);
    HBITMAP bitmap = 0;
    HFONT font = 0;
    HGDIOBJ oldBitmap = 0;
    HGDIOBJ oldFont = 0;
    if (dc && (bitmap = CreateBitmap(rect.right, rect.bottom, 1, 1, 0)) != 0) {
        oldBitmap = SelectObject(dc, bitmap);
        if (oldBitmap) {
            font = CreateFontA(8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x22, "");
            if (font && (oldFont = SelectObject(dc, bitmap)) != 0) {
                SelectObject(dc, font);
                SetTextColor(dc, 1);
                SetBkColor(dc, 0);
                SetBkMode(dc, 1);
                if (BitBlt(dc, 0, 0, rect.right, rect.bottom, dc, 0, 0, 0x42)
                    && ExtTextOutA(dc, 0, 0, 4, &rect, buffer, count, 0)) {
                    for (int y = 0; y < rect.bottom; ++y) {
                        for (int x = 0; x < rect.right; ++x)
                            if (GetPixel(dc, x, rect.bottom - y - 1) != 0)
                                output[x] = 0xff;
                        output += width;
                    }
                    result = count;
                }
            }
            SelectObject(dc, oldBitmap);
            DeleteObject(bitmap);
        } else {
            DeleteObject(bitmap);
        }
    }
    if (font) {
        if (oldFont) SelectObject(dc, oldFont);
        DeleteObject(font);
    }
    if (dc) DeleteDC(dc);
    return result;
}
