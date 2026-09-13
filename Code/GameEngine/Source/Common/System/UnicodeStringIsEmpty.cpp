// cl: /DNDEBUG /MD /EHsc
// Open-BFME6: standalone definition for the Zero Hour UnicodeString layout.
// PopupLadderSelect.cpp uses BFME's StringBase-backed wrapper; keeping this
// body separate preserves the distinct retail UnicodeString entry at 0x5E4C0.

typedef unsigned short WideChar;

class UnicodeString
{
private:
	struct Data
	{
		unsigned short m_refCount;
		unsigned short m_numCharsAllocated;
		WideChar m_text[1];
	};

	Data *m_data;

public:
	bool isEmpty() const;
};

bool UnicodeString::isEmpty() const
{
	return m_data == 0 || m_data->m_text[0] == 0;
}
