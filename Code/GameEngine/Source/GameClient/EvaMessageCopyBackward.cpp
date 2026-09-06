// cl: /O2 /GX- /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport

// Open-BFME5: the 0x00425AE0 reverse-copy helper shifts 28-byte records
// backward.  Eva's nearby init/reset code uses the same 0x1C message-table
// stride as the matched forward copy at 0x00425A60.  Each record has four
// inline dwords and a twelve-byte tree-backed tail assigned through the
// existing ILT 0x000083E1.  The binary is stripped, so the type spelling here
// is a descriptive reconstructed record name based on that caller/stride/
// member-operation chain.

class EvaMessageTail
{
public:
	EvaMessageTail &operator=( const EvaMessageTail & );

private:
	char m_raw[ 12 ];
};

struct EvaMessageReverseInfo
{
	int m_field0;
	int m_field4;
	int m_field8;
	int m_fieldC;
	EvaMessageTail m_tail;

	EvaMessageReverseInfo &operator=( const EvaMessageReverseInfo &that )
	{
		m_field0 = that.m_field0;
		m_field4 = that.m_field4;
		m_field8 = that.m_field8;
		m_fieldC = that.m_fieldC;
		m_tail = that.m_tail;
		return *this;
	}
};

namespace _STL
{
struct random_access_iterator_tag
{
};

template <class InputIterator, class OutputIterator, class Distance>
OutputIterator __copy_backward( InputIterator first, InputIterator last,
	OutputIterator result, const random_access_iterator_tag &, Distance * )
{
	Distance count = last - first;
	for ( ; count > 0; --count )
		*--result = *--last;
	return result;
}

template EvaMessageReverseInfo *__copy_backward<EvaMessageReverseInfo *, EvaMessageReverseInfo *, int>(
	EvaMessageReverseInfo *, EvaMessageReverseInfo *, EvaMessageReverseInfo *,
	const random_access_iterator_tag &, int *);
}
