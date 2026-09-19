// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME5: assign a by-value narrow string into the member at +0x3cc.

#include <string>

class Gen_00648B40
{
public:
	void bfmeSetString(_STL::string value);

private:
	unsigned char m_prefix[0x3c9];
	bool m_hasValue;
	unsigned char m_padding[2];
	_STL::string m_value;
};

void Gen_00648B40::bfmeSetString(_STL::string value)
{
	m_hasValue = true;
	m_value = value;
}
