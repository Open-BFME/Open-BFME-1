// cl: /O2 /GX- /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport

// Retail 0x00425980 fills a 28-byte message-table destination range.  The
// first two pointers delimit that range and the third points at one source
// record which is reused on every iteration; the body copies four inline
// dwords and assigns the opaque twelve-byte tree-backed tail through the
// existing ILT 0x000083E1.  This descriptive reconstructed record type is
// supported by the matching 0x1C stride and the neighboring Eva init/reset
// vector operations.  Eva's 0x004269E0 insertion path reaches this helper via
// ILT 0x0000163B.

class EvaMessageTail
{
public:
	EvaMessageTail &operator=( const EvaMessageTail & );

private:
	char m_raw[ 12 ];
};

struct EvaMessageWalkInfo
{
	int m_field0;
	int m_field4;
	int m_field8;
	int m_fieldC;
	EvaMessageTail m_tail;

	EvaMessageWalkInfo &operator=( const EvaMessageWalkInfo &that )
	{
		m_field0 = that.m_field0;
		m_field4 = that.m_field4;
		m_field8 = that.m_field8;
		m_fieldC = that.m_fieldC;
		m_tail = that.m_tail;
		return *this;
	}
};

void Rva00425980Fill( EvaMessageWalkInfo *first,
	EvaMessageWalkInfo *last, EvaMessageWalkInfo *source )
{
	while ( first != last )
	{
		*first = *source;
		++first;
	}
}

