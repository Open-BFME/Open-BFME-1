// Both entry points read the same base at +0x244 and distinct dword offsets.
struct Rva009A5880Offsets
{
	char m_reserved[0x220];
	int m_offset220;
	int m_offset224;
	char m_reserved228[0x1c];
	int m_base244;
};

int __cdecl rva009A5880FirstOffset(const Rva009A5880Offsets *value)
{
	return value->m_base244 + value->m_offset220;
}

int __cdecl rva009A58A0SecondOffset(const Rva009A5880Offsets *value)
{
	return value->m_base244 + value->m_offset224;
}
