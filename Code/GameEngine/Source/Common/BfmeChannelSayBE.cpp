// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
//
// Open-BFME5: the queued-text send at retail 0x0054D320, 49 bytes.  Nothing
// happens without a target; with one, the caller's text is copied into the
// by-value argument the sender takes.

class StringBaseWideBE
{
protected:
	StringBaseWideBE(const StringBaseWideBE &other) throw();

	~StringBaseWideBE(void) throw();

	unsigned short *m_bfmeWideBE;
};

class UnicodeStringBE : public StringBaseWideBE
{
public:
	UnicodeStringBE(const UnicodeStringBE &other) throw() : StringBaseWideBE(other)
	{
	}

	~UnicodeStringBE(void) throw()
	{
	}
};

void bfmeSendBE(int target, UnicodeStringBE text) throw();

class BfmeChannelBE
{
public:
	char bfmeSayBE(const UnicodeStringBE &text);

	char m_bfmePadBE[0x74];
	int m_bfmeTargetBE;
};

char BfmeChannelBE::bfmeSayBE(const UnicodeStringBE &text)
{
	char sent = 0;

	if (m_bfmeTargetBE != 0)
	{
		bfmeSendBE(m_bfmeTargetBE, text);

		sent = 1;
	}

	return sent;
}
