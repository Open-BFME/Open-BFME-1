// ?rva009D86E0@Rva009D8630BlockWriter@@QAEXPBD@Z
// partial score=0.62 date=2026-09-11
// Retail RVA 0x009D86E0, 518 bytes: Rva009D8630BlockWriter::rva009D86E0,
// called from beginBlock (XferBlockWriter.cpp) when m_flag is set.
// A null/empty name writes a single zero marker byte instead of returning
// silently; a name already in the map writes 0xFF + its stored index; a new
// name writes its length (capped at 0xFE) and bytes, then inserts it.
// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

#define _STLP_NO_EXCEPTIONS 1
#include <hash_map>
#include <string>

struct BfmeFormattedText
{
	char *text;
	int tag;
};

extern "C" BfmeFormattedText *__cdecl bfmeFormatText(
	BfmeFormattedText *result, int tag, const char *format, ...);
__declspec(noreturn) void __stdcall _CxxThrowException(void *object, void *throwInfo);
extern "C" unsigned char g_rva005c5100ThrowInfo[];

class BfmeByteStream
{
public:
	virtual void slot0();
	virtual void slot1();
	virtual void slot2();
	virtual void slot3();
	virtual int write(const void *buffer, int size);
};

typedef _STL::basic_string<char, _STL::char_traits<char>, _STL::allocator<char> >
	Rva009D86E0String;
typedef _STL::pair<const Rva009D86E0String, int> Rva009D86E0Pair;
typedef _STL::hash_map<Rva009D86E0String, int,
	_STL::hash<Rva009D86E0String>, _STL::equal_to<Rva009D86E0String>,
	_STL::allocator<Rva009D86E0Pair> > Rva009D86E0NameMap;
struct Rva009D86E0AuxMap
{
	unsigned char storage[0x14];
	int size(void) const
	{
		return *reinterpret_cast<const int *>(storage + 0x10);
	}
};

// TU-local shim: only the members and single virtual needed to reproduce this
// method's own offsets. The real class (six virtuals, m_positions) lives in
// XferBlockWriter.cpp, which forward-declares this same method.
class Rva009D8630BlockWriter
{
public:
	virtual void slot0();
	void rva009D86E0(const char *name);

private:
	BfmeByteStream *m_stream;
	bool m_flag;
	unsigned char m_pad09[3];
	unsigned char m_positions[0x0c];
	Rva009D86E0NameMap m_names;
	Rva009D86E0AuxMap m_aux;
};

void Rva009D8630BlockWriter::rva009D86E0(const char *name)
{
	unsigned char marker;
	BfmeFormattedText error;

	if (name == 0 || *name == 0)
	{
		marker = 0;
		if (m_stream->write(&marker, 1) != 1)
		{
			bfmeFormatText(&error, 1, 0);
			_CxxThrowException(&error, g_rva005c5100ThrowInfo);
		}
		return;
	}

	Rva009D86E0NameMap::const_iterator found;
	{
		Rva009D86E0String key(name);
		found = m_names.find(key);
	}
	if (found != m_names.end())
	{
		marker = 0xff;
		if (m_stream->write(&marker, 1) != 1)
		{
			bfmeFormatText(&error, 1, 0);
			_CxxThrowException(&error, g_rva005c5100ThrowInfo);
		}

		if (m_stream->write(&found->second, 4) != 4)
		{
			bfmeFormatText(&error, 1, 0);
			_CxxThrowException(&error, g_rva005c5100ThrowInfo);
		}
		return;
	}

	const char *cursor = name + 1;
	while (*cursor != 0)
		++cursor;
	unsigned int length = static_cast<unsigned int>(cursor - (name + 1));
	if (length > 0xfe)
		length = 0xfe;

	if (m_stream->write(&length, 1) != 1)
	{
		bfmeFormatText(&error, 1, 0);
		_CxxThrowException(&error, g_rva005c5100ThrowInfo);
	}
	if (m_stream->write(name, static_cast<int>(length)) !=
		static_cast<int>(length))
	{
		bfmeFormatText(&error, 1, 0);
		_CxxThrowException(&error, g_rva005c5100ThrowInfo);
	}

	m_names[Rva009D86E0String(name)] =
		static_cast<int>(m_aux.size() + m_names.size());
}
