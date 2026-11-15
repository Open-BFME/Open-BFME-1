// cl: /O2 /EHsc /MD


// Retail inlines this wrapper into StringBase<unsigned short> directly; declare just the
// StringBase<unsigned short> members it reaches (see build/whatif/wrapfix.py).
#include "../../../Libraries/Source/WWVegas/WWLib/string_base.h"
class UnicodeString
{
public:
	UnicodeString() : m_data(0) {}
	~UnicodeString() { ((StringBase<unsigned short> *)this)->releaseBuffer(); }

private:
	void *m_data;
};

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
