// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport

// Open-BFME: STLport GeometryRecord range copies, retail 0x000FC5D0 and
// 0x000FCD80.
//
// GeometryInfo's record vector and the adjacent placement-copy helper prove
// the 0x10-byte element: three scalar words followed by StringBase at +0x0c.
// The retail loops are STLport's random-access __copy instantiations for that
// element: the const-source form at 0x000FC5D0 serves vector copying, while
// vector erase uses the mutable-source form at 0x000FCD80.  Their StringBase
// assignments call the already recovered StringBase::set body at 0x00887C90.

template <typename T>
class StringBase
{
public:
	StringBase &operator=(const StringBase &other);

	void set(const StringBase &other);

private:
	void *m_data;
};

struct GeometryRecordValues
{
	int m_first;
	int m_second;
	int m_third;
};

struct GeometryRecord
{
	GeometryRecordValues m_values;
	StringBase<char> m_name;
};

namespace _STL
{
struct random_access_iterator_tag
{
};

template <class InputIterator, class OutputIterator, class Distance>
OutputIterator __copy(InputIterator first, InputIterator last,
	OutputIterator result, const random_access_iterator_tag &, Distance *)
{
	for (Distance count = last - first; count > 0;
		--count, ++first, ++result)
	{
		const GeometryRecord *source = first;
		GeometryRecord *destination = result;
		destination->m_values = source->m_values;
		destination->m_name.set(source->m_name);
	}
	return result;
}

// ??$__copy@PBUGeometryRecord@@PAU1@H@_STL@@YAPAUGeometryRecord@@PBU1@0PAU1@ABUrandom_access_iterator_tag@0@PAH@Z
template GeometryRecord *__copy<const GeometryRecord *, GeometryRecord *, int>(
	const GeometryRecord *, const GeometryRecord *, GeometryRecord *,
	const random_access_iterator_tag &, int *);

// ??$__copy@PAUGeometryRecord@@PAU1@H@_STL@@YAPAUGeometryRecord@@PAU1@00ABUrandom_access_iterator_tag@0@PAH@Z
template GeometryRecord *__copy<GeometryRecord *, GeometryRecord *, int>(
	GeometryRecord *, GeometryRecord *, GeometryRecord *,
	const random_access_iterator_tag &, int *);
}
