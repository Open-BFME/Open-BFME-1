// cl: /DNDEBUG /MD /EHsc

class UnicodeString
{
	unsigned char m_storage[4];
};

class AsciiString
{
public:
	AsciiString() : m_data(0) {}
	~AsciiString();
	void translate(const UnicodeString &text);

private:
	char *m_data;
};

class DisplayString
{
public:
	unsigned char m_unmodelled_00[4];
	UnicodeString m_text;
	unsigned char m_unmodelled_08[4];
	DisplayString *m_next;
	DisplayString *m_previous;
};

class DisplayStringManager
{
protected:
	void unLink(DisplayString *string);

private:
	unsigned char m_unmodelled_00[8];
	DisplayString *m_head;
};

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
