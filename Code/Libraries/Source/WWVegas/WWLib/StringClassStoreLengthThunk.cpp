// cl: /DNDEBUG /MD /EHsc

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib/wwstring.h
class StringClass
{
	struct HEADER
	{
		int allocated_length;
		int length;
	};

	char *m_Buffer;
	static char *m_EmptyString;

	void Store_Length(int length);

	HEADER *Get_Header(void) const
	{
		return reinterpret_cast<HEADER *>(((char *)m_Buffer) - sizeof(StringClass::HEADER));
	}
};

// ?Store_Length@StringClass@@AAEXH@Z
void StringClass::Store_Length(int length)
{
	if (m_Buffer != m_EmptyString) {
		HEADER *header = Get_Header();
		header->length = length;
	}
}
