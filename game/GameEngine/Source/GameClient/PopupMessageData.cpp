// cl: /O2 /EHsc /MD


// Retail inlines this wrapper into StringBase<unsigned short> directly; declare just the
// StringBase<unsigned short> members it reaches (see build/whatif/wrapfix.py).
#include "../../../Libraries/Source/WWVegas/WWLib/string_base.h"
#include "../../../Libraries/Source/WWVegas/WWLib/unicode_string.h"
inline UnicodeString::UnicodeString() { m_text = 0; }
inline UnicodeString::~UnicodeString() { ((StringBase<unsigned short> *)this)->releaseBuffer(); }


class PopupMessageData
{
public:
	PopupMessageData();
	virtual ~PopupMessageData();

private:
	UnicodeString m_message;
};

PopupMessageData::PopupMessageData()
{
}

PopupMessageData::~PopupMessageData()
{
}
