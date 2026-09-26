// cl: /O2 /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Iinputs/reference/shims/stringinline
// stlport
// Open-BFME: vector<GeometryRecord> copy constructor, retail 0x000FDF90.
// GeometryInfo's copy constructor calls this member through ILT 0x000149DE.

#include <vector>
#include "StringInline.h"

struct GeometryRecord
{
	GeometryRecord();
	GeometryRecord(const GeometryRecord &other)
		: m_first(other.m_first),
		  m_second(other.m_second),
		  m_third(other.m_third),
		  m_name(other.m_name)
	{
	}
	int m_first;
	int m_second;
	int m_third;
	AsciiString m_name;
};

template class _STL::vector<GeometryRecord>;
