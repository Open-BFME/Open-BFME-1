// cl: /DNDEBUG /MD /EHsc
// Retail 0x00099E10, 927 bytes: copies a replay from the replay directory to a named or the
// next free numbered replay file, writing the given title in place of the stored replay name.
#include <string.h>

struct _iobuf;
typedef _iobuf FILE;
extern "C" __declspec(dllimport) int __cdecl _access(const char *path, int mode);
extern "C" __declspec(dllimport) FILE *__cdecl fopen(const char *name, const char *mode);
extern "C" __declspec(dllimport) unsigned int __cdecl fread(void *buffer, unsigned int size, unsigned int count, FILE *stream);
extern "C" __declspec(dllimport) unsigned int __cdecl fwrite(const void *buffer, unsigned int size, unsigned int count, FILE *stream);
extern "C" __declspec(dllimport) int __cdecl fseek(FILE *stream, long offset, int origin);
extern "C" __declspec(dllimport) int __cdecl fclose(FILE *stream);
extern "C" __declspec(dllimport) int __cdecl fwprintf(FILE *stream, const wchar_t *format, ...);
extern "C" __declspec(dllimport) unsigned short __cdecl fputwc(unsigned short ch, FILE *stream);

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;
typedef unsigned short WideChar;

static const Int MAX_REPLAY_FILE_NUMBER = 99999999;

#include "../../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"
#include "../../../../Libraries/Source/WWVegas/WWLib/unicode_string.h"

inline UnicodeString::UnicodeString() { m_text = 0; }
inline UnicodeString::~UnicodeString() { ((StringBase<wchar_t> *)this)->releaseBuffer(); }
template<> inline bool StringBase<char>::isEmpty() const { return m_data == 0 || m_data->length == 0; }
template<> inline void StringBase<char>::concat(const StringBase<char> &str)
{
    const int len = str.m_data ? str.m_data->length : 0;
    const char *data = str.m_data ? &str.m_data->data[0] : "";
    concat(data, len);
}

class RecorderClass
{
public:
	static AsciiString getReplayDir();
	static AsciiString getReplayExtention();
};

UnicodeString readUnicodeString(FILE *file);

Bool dup_00099E10(AsciiString *src, AsciiString *dst, UnicodeString *title)
{
	AsciiString srcPath;
	srcPath = RecorderClass::getReplayDir();
	srcPath.StringBase<char>::concat(*src);
	AsciiString dstPath;
	if (!dst->StringBase<char>::isEmpty()) {
		dstPath = RecorderClass::getReplayDir();
		dstPath.StringBase<char>::concat(*dst);
	} else {
		Int i = 1;
		while (true) {
			dstPath.format("%s%08d%s", RecorderClass::getReplayDir().str(), i, RecorderClass::getReplayExtention().str());
			if (_access(dstPath.str(), 0) == -1)
				break;
			++i;
			if (i < MAX_REPLAY_FILE_NUMBER)
				continue;
			break;
		}
		if (i == MAX_REPLAY_FILE_NUMBER)
			return false;
	}
	FILE *in = fopen(srcPath.str(), "rb");
	if (in == 0)
		return false;
	FILE *out = fopen(dstPath.str(), "wb");
	if (out == 0)
		return false;
	Int seekRes = fseek(in, 0, 0);
	char buf[0x10000];
	UnsignedInt got = fread(buf, 1, 0x25, in);
	UnsignedInt put = fwrite(buf, 1, 0x25, out);
	if (seekRes != 0 || got < 0x25 || put < 0x25)
		return false;
	UnicodeString name = readUnicodeString(in);
	fwprintf(out, L"%ws", ((const StringBase<unsigned short> *)title)->str());
	fputwc(0, out);
	UnsignedInt n;
	UnsignedInt w;
	do {
		n = fread(buf, 1, 0x10000, in);
		w = fwrite(buf, 1, n, out);
	} while (n == 0x10000 && w == n);
	if (n != w)
		return false;
	fclose(in);
	fclose(out);
	return true;
}
