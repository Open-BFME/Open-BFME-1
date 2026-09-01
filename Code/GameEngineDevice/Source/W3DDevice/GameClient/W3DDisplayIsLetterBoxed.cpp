// cl: /DNDEBUG /MD /EHsc

class W3DDisplay
{
public:
	virtual bool isLetterBoxed();

private:
	unsigned char m_retailPad[0xd0];
	bool m_letterBoxEnabled;
};

bool W3DDisplay::isLetterBoxed()
{
	return m_letterBoxEnabled;
}
