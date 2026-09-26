// cl: /O2 /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib
// ??$__find@U?$_List_iterator@VUnicodeString@@U?$_Nonconst_traits@VUnicodeString@@@_STL@@@_STL@@VUnicodeString@@@_STL@@YA?AU?$_List_iterator@VUnicodeString@@U?$_Nonconst_traits@VUnicodeString@@@_STL@@@0@U10@0ABVUnicodeString@@ABUinput_iterator_tag@0@@Z
// stlport
#include <list>
#include <algorithm>
#include "string_base.h"
#include "unicode_string.h"
extern const char g_bfmeEmptyUnicode[];

inline int compareWideRuns(const unsigned short *s1, int len1,
	const unsigned short *s2, int len2)
{
	int minLen = len1;
	if (minLen >= len2)
		minLen = len2;
	// p before q: MSVC 7.1 then loads *q into EDX first at the mismatch, as retail does
	const unsigned short *p = s1;
	const unsigned short *q = s2;
	if (minLen > 0) {
		do {
			if (*p != *q) {
				int diff = (int)(unsigned int)*p - (int)(unsigned int)*q;
				if (diff != 0)
					return diff;
				break;
			}
			++p;
			++q;
			--minLen;
		} while (minLen > 0);
	}
	return len1 - len2;
}
template<> inline int StringBase<unsigned short>::compare(
	const unsigned short *text, int len) const
{
	const int myLen = m_data ? m_data->length : 0;
	const unsigned short *data = m_data ? m_data->data :
		(const unsigned short *)g_bfmeEmptyUnicode;
	return compareWideRuns(data, myLen, text, len);
}
template<> inline int StringBase<unsigned short>::compare(
	const StringBase<unsigned short> &text) const
{
	int len = text.m_data ? text.m_data->length : 0;
	const unsigned short *data = text.m_data ? text.m_data->data :
		(const unsigned short *)g_bfmeEmptyUnicode;
	return compare(data, len);
}
inline bool operator==(const UnicodeString &left, const UnicodeString &right)
{
	return left.compare(right) == 0;
}
typedef _STL::list<UnicodeString>::iterator BriefingIterator;
typedef BriefingIterator (*FindFunction)(BriefingIterator, BriefingIterator,
	const UnicodeString &, const _STL::input_iterator_tag &);
FindFunction briefingFind = &_STL::__find<BriefingIterator, UnicodeString>;
