// cl: /O2 /GX- /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport

// Open-BFME5: STLport __copy helper used by Eva's 28-byte message-table vector.
// EvaInit's message entries carry four plain dwords followed by a twelve-byte
// tree-backed member whose retail assignment operator is reached through ILT
// 0x000083E1, whose
// thunk resolves to the matched _Rb_tree assignment body at 0x00424AC0.

class EvaMessageTail
{
public:
	EvaMessageTail &operator=( const EvaMessageTail & );

private:
	char m_raw[ 12 ];
};

// The 28-byte record is spelled EvaMessageInfo because matched Eva::init/reset
// callers use the 0x004263D0 message-table assignment, whose copy ILT
// 0x00003F6C enters this body.  The binary is stripped; this is a reconstructed
// source identity from that caller chain, not an independent retail name.
struct EvaMessageInfo
{
	int m_field0;
	int m_field4;
	int m_field8;
	int m_fieldC;
	EvaMessageTail m_tail;

	EvaMessageInfo &operator=( const EvaMessageInfo &that )
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
OutputIterator __copy( InputIterator first, InputIterator last,
	OutputIterator result, const random_access_iterator_tag &, Distance * )
{
	for ( Distance count = last - first; count > 0; --count, ++first, ++result )
		*result = *first;
	return result;
}

template EvaMessageInfo *__copy<const EvaMessageInfo *, EvaMessageInfo *, int>(
	const EvaMessageInfo *, const EvaMessageInfo *, EvaMessageInfo *,
	const random_access_iterator_tag &, int *);
}
