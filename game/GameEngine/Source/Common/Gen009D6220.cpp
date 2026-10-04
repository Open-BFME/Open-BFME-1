// cl: /DNDEBUG /MD /O2
// Clean C++ conversion of the formatted text builder at retail RVA 0x009D6220.
#include <stdarg.h>
#include <string.h>
#include <new>

// This formatter has its own scratch buffer at VA 0x0134D4B8. The INI
// exception constructor's g_bfmeFormatBuffer is the distinct VA 0x0130C650.
extern char Rva0134D4B8FormatBuffer[];
extern "C" __declspec(dllimport) int __cdecl _vsnprintf(char *, unsigned int, const char *, va_list);
// The block is allocated through the global `operator new[]`, the 17-byte
// body at retail 0x00881F70 (??_U@YAPAXI@Z, matched in WWLib/mem_ops.cpp).

struct BfmeFormattedText
{
	char *text;
	int tag;
};

extern "C" BfmeFormattedText *__cdecl bfmeFormatText(BfmeFormattedText *result, int tag, const char *format, ...)
{
	result->tag = tag;
	result->text = 0;
	if (format != 0)
	{
		va_list args;
		va_start(args, format);
		int length = _vsnprintf(Rva0134D4B8FormatBuffer, 2047, format, args);
		result->text = static_cast<char *>(::operator new[](length + 1));
		memcpy(result->text, Rva0134D4B8FormatBuffer, length);
		result->text[length] = 0;
		va_end(args);
	}
	return result;
}

// Native _vsnprintf receives capacity 0x7FF for this writable scratch view.
// Own only that used range; the original allocation extent is not claimed.
// See identity_evidence/0134d4b8-format-buffer-used-view.md.
char Rva0134D4B8FormatBuffer[2047];
