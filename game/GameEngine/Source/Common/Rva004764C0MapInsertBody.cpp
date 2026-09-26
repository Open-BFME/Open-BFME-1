// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
//
// STLport map::operator[] body at retail 0x004764C0.  The insert callee at
// 0x004745F0 allocates a 0x18-byte node, proving that the mapped value is one
// dword.  FontDefaultSettings' parser caller identifies that dword as its
// reference-counted settings slot.

#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include <stl/_config.h>
#undef _STLP_DEFAULT_CONSTRUCTOR_BUG
#include <map>

class FontDefaultSettings
{
public:
	void Release_Ref();
};

class FontDefaultSettingsRef
{
public:
	FontDefaultSettingsRef() { m_value = 0; }
	FontDefaultSettingsRef(const FontDefaultSettingsRef &other)
		: m_value(other.m_value)
	{
	}
	~FontDefaultSettingsRef()
	{
		if (m_value != 0)
			m_value->Release_Ref();
	}
	FontDefaultSettings *m_value;
};

typedef _STL::map<int, FontDefaultSettingsRef> FontDefaultSettingsMap;

// ??A?$map@HVFontDefaultSettingsRef@@U?$less@H@_STL@@V?$allocator@U?$pair@$$CBHVFontDefaultSettingsRef@@@_STL@@@3@@_STL@@QAEAAVFontDefaultSettingsRef@@ABH@Z
template FontDefaultSettingsRef &FontDefaultSettingsMap::operator[](
	const int &key);
