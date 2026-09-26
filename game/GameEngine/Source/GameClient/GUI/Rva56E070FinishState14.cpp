// cl: /DNDEBUG /MD /EHsc

template <typename T> class StringBase
{
	friend class AsciiString;

private:
	StringBase(const StringBase<T> &other);
	~StringBase();

	void *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString(const AsciiString &other)
		: StringBase<char>(other) {}
	~AsciiString() {}
};

class RecorderClass
{
public:
	RecorderClass();
	~RecorderClass();
	bool testVersionPlayback(AsciiString filename);

private:
	char m_pad[0x2B4];
};

class Rva56E070StateOwner
{
public:
	char m_pad0[0x258];
	int m_state;
	AsciiString *m_text;

	void finishState14();
};

void Rva56E070StateOwner::finishState14()
{
	if (m_text != 0)
	{
		RecorderClass rec;
		if (rec.testVersionPlayback(*m_text))
			m_state = 13;
		else
			m_state = m_text != 0 ? 3 : 1;
	}
	else
		m_state = 1;
}
