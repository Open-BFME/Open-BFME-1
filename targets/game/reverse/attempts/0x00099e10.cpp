// ?dup_00099E10@@YA_NPAVAsciiString@@0PAVUnicodeString@@@Z
// partial score=0.862 date=2026-09-27
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Igame/Libraries/Source/WWVegas/WWLib
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

template <typename T> class StringBase
{
	friend class AsciiString;
	friend class UnicodeString;

private:
	struct Header
	{
		int m_refCount;
		unsigned short m_length;
		unsigned short m_capacity;
		T m_text[1];
	};

	StringBase() : m_data(0) {}
	StringBase(const T *text);
	StringBase(const StringBase<T> &other);
	~StringBase() { releaseBuffer(); }

public:
	void set(const StringBase<T> &other);
	void concat(const T *text, Int length);

private:
	void releaseBuffer();

private:
	Header *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString(const char *text) : StringBase<char>(text) {}
	AsciiString(const AsciiString &other) : StringBase<char>(other) {}
	~AsciiString() {}

	AsciiString &operator=(const AsciiString &other)
	{
		StringBase<char>::set(other);
		return *this;
	}

	void concat(const char *text, Int length) { StringBase<char>::concat(text, length); }

	void concat(const AsciiString &other)
	{
		const Int length = other.m_data ? other.m_data->m_length : 0;
		const char *text = other.m_data ? other.m_data->m_text : (const char *)0x0107388B;
		StringBase<char>::concat(text, length);
	}

	void __cdecl format(AsciiString fmt, ...);

	const char *str() const { return m_data ? m_data->m_text : (const char *)0x0107388B; }
	Int getLength() const { return m_data ? m_data->m_length : 0; }
	Bool isEmpty() const { return m_data == 0 || m_data->m_length == 0; }
};

class UnicodeString : private StringBase<WideChar>
{
public:
	UnicodeString() : StringBase<WideChar>() {}
	UnicodeString(const UnicodeString &other) : StringBase<WideChar>(other) {}
	~UnicodeString() {}

	const WideChar *str() const { return m_data ? m_data->m_text : (const WideChar *)0x0107388C; }
};

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
	srcPath.concat(*src);
	AsciiString dstPath;
	if (!dst->isEmpty()) {
		dstPath = RecorderClass::getReplayDir();
		dstPath.concat(*dst);
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
	if (out == 0) {
		fclose(in);
		return false;
	}
	Int seekRes = fseek(in, 0, 0);
	char buf[0x10000];
	UnsignedInt got = fread(buf, 1, 0x25, in);
	UnsignedInt put = fwrite(buf, 1, 0x25, out);
	if (seekRes != 0 || got < 0x25 || put < 0x25)
		return false;
	{
		(void)readUnicodeString(in);
		fwprintf(out, L"%ws", title->str());
		fputwc(0, out);
		while (true) {
			UnsignedInt n = fread(buf, 1, 0x10000, in);
			UnsignedInt w = fwrite(buf, 1, n, out);
			if (n != 0x10000) {
				if (w == n) {
					fclose(in);
					fclose(out);
					return true;
				}
				break;
			}
			if (w != n)
				break;
		}
	}
	return false;
}
