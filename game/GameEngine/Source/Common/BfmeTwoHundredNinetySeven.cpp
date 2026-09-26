// cl: /Oy-
// A text written to the standard output, its length measured in place. Nothing
// is written for one particular kind, nor when there is no text. The count
// written lands back in the first argument's own slot.

extern "C" unsigned int __cdecl strlen(const char *at);
#pragma intrinsic(strlen)

extern "C" __declspec(dllimport) void *__stdcall GetStdHandle(unsigned long which);
extern "C" __declspec(dllimport) int __stdcall WriteFile(void *file, const void *at,
	unsigned long many, unsigned long *wrote, void *over);

void __stdcall bfmeWriteQN(int kind, void *spare, char *text)
{
	if (kind == 5)
		return;

	if (text == 0)
		return;

	WriteFile(GetStdHandle((unsigned long)-11), text, strlen(text), (unsigned long *)&kind, 0);
}
