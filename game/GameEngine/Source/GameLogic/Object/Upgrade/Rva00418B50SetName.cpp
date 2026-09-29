// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// Address-derived body at 0x00418B50. The earlier ledger name
// TooltipUpgrade::~TooltipUpgrade was wrong: the body takes one stack argument
// (ret 4), builds the AsciiString 'ReferenceDisplayName', compares the argument
// with it through the out-of-line AsciiString compare (ILT 0x000220C5), then
// clears or assigns the AsciiString member at +0x2D4.
#include "ascii_string.h"

template <typename T> inline bool StringBase<T>::isNotEmpty() const
{
	return m_data != 0 && m_data->length != 0;
}

class Rva00418B50Owner
{
public:
	void setName(const AsciiString &name);

private:
	unsigned char m_pad000[0x2D4];
	AsciiString m_name;
};

void Rva00418B50Owner::setName(const AsciiString &name)
{
	AsciiString key("ReferenceDisplayName");
	if (name.StringBase<char>::compare(key) == 0)
		m_name.clear();
	else if (name.isNotEmpty())
		m_name = name;
}
