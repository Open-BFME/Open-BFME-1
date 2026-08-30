// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport

// Open-BFME: STLport GeometryShape copy-backward helper, retail 0x000FCF70.
// The vector insertion path at retail 0x004FF8F0 passes its 0x24-byte shape
// range through the ILT at 0x004381E0.  The range arithmetic and the inline
// assignment below identify this as the out-of-line __copy_backward body for
// vector<GeometryShape>.

template <typename T>
class StringBase
{
public:
	StringBase &operator=(const StringBase &other)
	{
		set(other);
		return *this;
	}

	void set(const StringBase &other); // retail 0x00887C90

private:
	void *m_data;
};

typedef bool Bool;

struct GeometryShapeMiddle
{
	int m_first;
	int m_second;
	int m_third;
};

struct GeometryShape
{
	int m_type;
	float m_height;
	float m_majorRadius;
	int m_unmodelled00c;
	GeometryShapeMiddle m_unmodelled10;
	StringBase<char> m_name;
	Bool m_enabled;
	char m_unmodelled21[0x03];

	GeometryShape &operator=(const GeometryShape &other)
	{
		m_type = other.m_type;
		m_height = other.m_height;
		m_majorRadius = other.m_majorRadius;
		m_unmodelled00c = other.m_unmodelled00c;
		m_unmodelled10 = other.m_unmodelled10;
		m_name = other.m_name;
		m_enabled = other.m_enabled;
		return *this;
	}
};

namespace _STL
{
struct random_access_iterator_tag
{
};

template <class InputIterator, class OutputIterator, class Distance>
OutputIterator __copy_backward(InputIterator first, InputIterator last,
	OutputIterator result, const random_access_iterator_tag &, Distance *)
{
	for (Distance count = last - first; count > 0; --count, ++first, ++result)
		*result = *first;
	return result;
}

// ??$__copy_backward@PAUGeometryShape@@PAU1@H@_STL@@YAPAUGeometryShape@@PAU1@00ABUrandom_access_iterator_tag@0@PAH@Z
template GeometryShape *__copy_backward<GeometryShape *, GeometryShape *, int>(
	GeometryShape *, GeometryShape *, GeometryShape *,
	const random_access_iterator_tag &, int *);
}
