// ?getAt@AsciiStringVectorHolder@@QBE?AVAsciiString@@I@Z
// partial score=0.92 date=2026-09-02
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Bounds-checked copy of vector<AsciiString>[index] into an out-parameter.
// OOB copies the process-wide empty string at 0x1336e50.

#include <vector>

class AsciiString
{
public:
	AsciiString();
	AsciiString(const AsciiString &);
	~AsciiString();
	AsciiString &operator=(const AsciiString &);

private:
	void *m_data;
};

extern AsciiString TheEmptyAsciiString;

class AsciiStringVectorHolder
{
public:
	AsciiString getAt(unsigned int index) const;

private:
	char m_pad[8];
	_STL::vector<AsciiString> m_names;			// begin +8, finish +0xc
};

AsciiString AsciiStringVectorHolder::getAt(unsigned int index) const
{
	if (index < m_names.size())
		return m_names[index];
	return TheEmptyAsciiString;
}
