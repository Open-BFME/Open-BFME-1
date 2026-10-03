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

// The twelve-byte tail is assigned through ILT 0x000083E1, the 5-byte thunk in
// front of the 28-byte body at 0x00424AC0.  That thunk symbol is the only name
// defined at the call target, so this TU references it directly; the
// member-pointer view in EvaMessageWalkInfo::operator= types the call as the
// thiscall retail used (ecx = destination tail, source pushed, popped by the
// callee) without defining EvaMessageTail's assignment.
extern "C" void __identifier("?j_000083e1@@YAXXZ")();

class EvaMessageTail
{
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
		union {
			void (*thunk)();
			void (EvaMessageTail::*assign)(const EvaMessageTail &);
		} tail;
		tail.thunk = &__identifier("?j_000083e1@@YAXXZ");
		(&m_tail->*tail.assign)(that.m_tail);
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

