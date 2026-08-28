// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	void set(const AsciiString &other);

private:
	void *m_data;
};

struct Rva0036D9E0Entry
{
	AsciiString m_first;
	AsciiString m_second;
	int m_value;
};

extern "C" Rva0036D9E0Entry *__cdecl Rva0036D9E0CopyRange(
	const Rva0036D9E0Entry *first,
	const Rva0036D9E0Entry *last,
	Rva0036D9E0Entry *result)
{
	int count = last - first;
	while( count > 0 )
	{
		result->m_first.set(first->m_first);
		result->m_second.set(first->m_second);
		result->m_value = first->m_value;
		++first;
		++result;
		--count;
	}
	return result;
}

// @_Rva0036D9E0CopyRange 0x0036D9E0
