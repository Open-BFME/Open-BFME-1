#include <new>

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	AsciiString(const AsciiString &other);

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
