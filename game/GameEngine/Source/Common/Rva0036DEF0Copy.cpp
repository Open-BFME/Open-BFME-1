#include <new>

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
// Retail's AsciiString derives from StringBase<char>: its own copy ctor is the
// forwarder at 0x0005EE50 and it holds nothing of its own, so a caller that
// copies a string encodes the base body at 0x00887B60 directly. The delegation
// has to be visible here for this TU to encode the same call.
template <typename T>
class StringBase
{
	friend class AsciiString;

private:
	StringBase(const StringBase<T> &src);

	struct Header
	{
		int ref_count;
		unsigned short length;
		unsigned short capacity;
		T data[1];
	};

	Header *m_data;
};

class AsciiString
{
public:
	// Retail inlines this forwarder, so the call site encodes
	// StringBase<char>'s copy ctor at 0x00887B60 directly.
	AsciiString(const AsciiString &other)
	{
		((StringBase<char> *)this)->StringBase<char>::StringBase(
			*(const StringBase<char> *)&other);
	}

private:
	void *m_data;
};

struct Rva0036DEF0Payload
{
	AsciiString m_text;
	int m_first;
	int m_second;
};

struct Rva0036DEF0Result
{
	int m_key;
	Rva0036DEF0Payload m_payload;

	Rva0036DEF0Result(int key, const Rva0036DEF0Payload &payload)
		: m_key(key), m_payload(payload) {}
};

extern "C" Rva0036DEF0Result __cdecl Rva0036DEF0Copy(
	const int &key,
	const Rva0036DEF0Payload &payload)
{
	// VC7 retains this state word around the potentially throwing string copy.
	volatile int constructionState = 0;
	return Rva0036DEF0Result(key, payload);
}

// @_Rva0036DEF0Copy 0x0036DEF0

extern "C" void __cdecl Rva0036E2D0Construct(
	Rva0036DEF0Result *result,
	const Rva0036DEF0Result &source)
{
	new (result) Rva0036DEF0Result(source);
}

// @_Rva0036E2D0Construct 0x0036E2D0
