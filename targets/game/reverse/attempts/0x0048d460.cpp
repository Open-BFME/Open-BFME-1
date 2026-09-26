// ?rva0048D460AnsiToWide@@YGXPBDPAVUnicodeString@@@Z
// partial score=0.89 date=2026-09-24
// cl: /O2 /DNDEBUG /MD /EHsc
#include <string.h>

class UnicodeString;
void __stdcall rva0048D460AnsiToWide(const char *source, UnicodeString *target);

template<class CharT>
class StringBase
{
	friend void __stdcall rva0048D460AnsiToWide(const char *, UnicodeString *);
private:
	void releaseBuffer();
};

class UnicodeString : public StringBase<unsigned short>
{
public:
	UnicodeString &operator=(const unsigned short *text);
};

extern "C" __declspec(dllimport) int __stdcall MultiByteToWideChar(
	unsigned int codePage, unsigned int flags, const char *source,
	int sourceLength, unsigned short *target, int targetLength);

void __stdcall rva0048D460AnsiToWide(const char *source, UnicodeString *target)
{
	int length = MultiByteToWideChar(0, 0, source, strlen(source), 0, 0);
	target->releaseBuffer();
	if (length <= 0)
		return;

	unsigned short *buffer = new unsigned short[length + 1];
	if (buffer == 0)
		return;

	int written = MultiByteToWideChar(0, 0, source, strlen(source), buffer, length);
	if (written <= 0) {
		target->releaseBuffer();
		delete[] buffer;
		return;
	}

	buffer[written] = 0;
	*target = buffer;
	delete[] buffer;
}
