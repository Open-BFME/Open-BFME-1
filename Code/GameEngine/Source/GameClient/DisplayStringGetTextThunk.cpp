// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: DisplayString::getText returns UnicodeString member at +4.

class UnicodeString
{
public:
	UnicodeString();
	UnicodeString(const UnicodeString &);
	~UnicodeString();
};

class DisplayString
{
public:
	virtual UnicodeString getText();
private:
	UnicodeString m_text;
};

// ?getText@DisplayString@@UAE?AVUnicodeString@@XZ
UnicodeString DisplayString::getText()
{
	return m_text;
}
