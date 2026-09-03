// cl: /DNDEBUG /MD /EHsc

class UnicodeString
{
public:
	UnicodeString();
	UnicodeString(const UnicodeString &that);
	~UnicodeString();

	static UnicodeString TheEmptyString;

private:
	void *m_data;
};

class Rva00416BD0Src
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual UnicodeString getName();
};

class Rva00416BD0
{
	char m_pad[0x2D0];
	Rva00416BD0Src *m_2d0;

public:
	UnicodeString getName();
};

UnicodeString Rva00416BD0::getName()
{
	if (m_2d0)
		return m_2d0->getName();
	return UnicodeString::TheEmptyString;
}
