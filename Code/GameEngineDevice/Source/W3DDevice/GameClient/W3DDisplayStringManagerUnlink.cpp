// cl: /DNDEBUG /MD /EHsc

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/UnicodeString.h
class UnicodeString
{
	unsigned char m_storage[4];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	AsciiString() : m_data(0) {}
	~AsciiString();
	void translate(const UnicodeString &text);

private:
	char *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/DisplayString.h
class DisplayString
{
public:
	unsigned char m_unmodelled_00[4];
	UnicodeString m_text;
	unsigned char m_unmodelled_08[4];
	DisplayString *m_next;
	DisplayString *m_previous;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/DisplayStringManager.h
class DisplayStringManager
{
protected:
	void link(DisplayString *string);
	void unLink(DisplayString *string);

private:
	unsigned char m_unmodelled_00[8];
	DisplayString *m_head;
};

void DisplayStringManager::link(DisplayString *string)
{
	AsciiString unusedText;
	unusedText.translate(string->m_text);

	if (string)
	{
		string->m_next = m_head;
		if (m_head)
			m_head->m_previous = string;
		m_head = string;
	}
}

void DisplayStringManager::unLink(DisplayString *string)
{
	AsciiString unusedText;
	unusedText.translate(string->m_text);

	if (string && m_head)
	{
		if (string->m_next)
			string->m_next->m_previous = string->m_previous;

		if (string->m_previous)
			string->m_previous->m_next = string->m_next;
		else
			m_head = string->m_next;
	}
}
