// cl: /DNDEBUG /MD /EHsc
// LANAPI::GetMyName, RVA685660,32B. The actual LANAPI vtable111AF50 slot47
// points through ILT15D4D to this body. It copies the Unicode name at+10
// through StringBase<unsigned short>888400. Former canonical4C7970 belongs
// to DownloadManager::getErrorString; its caller establishes that separate owner.
#include "../../../Libraries/Source/WWVegas/WWLib/string_base.h"
#include "../../../Libraries/Source/WWVegas/WWLib/unicode_string.h"
inline UnicodeString::UnicodeString(const UnicodeString &that) { ((StringBase<unsigned short> *)this)->StringBase<unsigned short>::StringBase(*(const StringBase<unsigned short> *)&that); }
inline UnicodeString::UnicodeString() { m_text = 0; }
inline UnicodeString::~UnicodeString() { ((StringBase<unsigned short> *)this)->releaseBuffer(); }

class LANAPI {
public:
    virtual UnicodeString GetMyName();
private:
    char preceding[0xC];
    UnicodeString m_name;
};
UnicodeString LANAPI::GetMyName() { return m_name; }
