// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Igame/Libraries/Source/WWVegas/WWLib
// Rva00099A40Owner::dup_00099A40 (0x00099A40): a RecorderClass member (m_file at +0x0C) that copies
// the open replay to a named or first free numbered file under a new title. Sole caller: 0x0056D070.
#include "ascii_string.h"
#include "unicode_string.h"

template <> inline bool StringBase<char>::isEmpty() const { return m_data == 0 || m_data->length == 0; }
inline UnicodeString::~UnicodeString() { ((StringBase<unsigned short> *)this)->releaseBuffer(); }

struct _iobuf;
typedef _iobuf FILE;
extern "C" __declspec(dllimport) int __cdecl _access(const char *path, int mode);
extern "C" __declspec(dllimport) FILE *__cdecl fopen(const char *name, const char *mode);
extern "C" __declspec(dllimport) unsigned int __cdecl fread(void *buffer, unsigned int size, unsigned int count, FILE *stream);
extern "C" __declspec(dllimport) unsigned int __cdecl fwrite(const void *buffer, unsigned int size, unsigned int count, FILE *stream);
extern "C" __declspec(dllimport) int __cdecl fseek(FILE *stream, long offset, int origin);
extern "C" __declspec(dllimport) long __cdecl ftell(FILE *stream);
extern "C" __declspec(dllimport) int __cdecl fclose(FILE *stream);
extern "C" __declspec(dllimport) int __cdecl fwprintf(FILE *stream, const wchar_t *format, ...);
extern "C" __declspec(dllimport) wint_t __cdecl fputwc(wchar_t ch, FILE *stream);

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;

static const Int MAX_REPLAY_FILE_NUMBER = 99999999;

class RecorderClass
{
public:
	static AsciiString getReplayDir();
	static AsciiString getReplayExtention();
protected:
	UnicodeString readUnicodeString();
	// Retail stores no EH state for the title local across this call.
	void logGameEnd() throw();
};

class Rva00099A40Owner : public RecorderClass
{
public:
	Bool dup_00099A40(AsciiString *a, UnicodeString *b);
private:
	char m_head[0xc];
	FILE *m_file;
};

Bool Rva00099A40Owner::dup_00099A40(AsciiString *a, UnicodeString *b)
{
	if (m_file == 0)
		return false;
	UnsignedInt fileSize = ftell(m_file);
	if (fileSize < 0x25)
		return false;
	AsciiString path;
	if (!a->StringBase<char>::isEmpty()) {
		path = RecorderClass::getReplayDir();
		path.StringBase<char>::concat(*a);
	} else {
		Int i = 1;
		while (true) {
			path.format("%s%08d%s", RecorderClass::getReplayDir().str(), i, RecorderClass::getReplayExtention().str());
			if (_access(path.str(), 0) == -1)
				break;
			++i;
			if (i < MAX_REPLAY_FILE_NUMBER)
				continue;
			break;
		}
		if (i == MAX_REPLAY_FILE_NUMBER)
			return false;
	}
	FILE *out = fopen(path.str(), "wb");
	if (out == 0)
		return false;
	Int seekRes = fseek(m_file, 0, 0);
	char buf[0x10000];
	UnsignedInt got = fread(buf, 1, 0x25, m_file);
	UnsignedInt put = fwrite(buf, 1, 0x25, out);
	if (seekRes != 0 || got < 0x25 || put < 0x25)
		return false;
	// Skips the source title so the new one in b replaces it.
	UnicodeString title = readUnicodeString();
	fwprintf(out, L"%ws", ((const StringBase<unsigned short> *)b)->str());
	fputwc(0, out);
	while (true) {
		UnsignedInt n = fread(buf, 1, 0x10000, m_file);
		UnsignedInt w = fwrite(buf, 1, n, out);
		if (n == 0x10000) {
			if (w == n)
				continue;
			break;
		}
		if (n != w)
			break;
		FILE *saved = m_file;
		m_file = out;
		logGameEnd();
		m_file = saved;
		fclose(out);
		fseek(m_file, fileSize, 0);
		return true;
	}
	return false;
}
