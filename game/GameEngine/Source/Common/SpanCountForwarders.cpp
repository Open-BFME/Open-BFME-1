// Thirty-two 25-byte __thiscall bodies that hand one direct call the caller's
// own argument together with the element count of a span held in the object.
//
//     mov edx,[ecx+4] / mov eax,[ecx+8] / sub eax,edx / mov edx,[esp+4]
//     sar eax,2 / push eax / push edx / call <REL32> / ret 4
//
// THE FAMILY IS INVISIBLE TO BYTE-IDENTITY GROUPING.  The one call is a REL32,
// so a call to a fixed callee encodes a different four-byte displacement from
// each of the thirty-two addresses; masking that displacement before hashing is
// what found the family at all.
//
// WHAT THE BYTES SHOW.  `ret 4` with `this` arriving in ecx and never reloaded
// is __thiscall with one stack argument.  Two dwords at +4 and +8 are
// subtracted and arithmetic-shifted right by two: a pointer difference over a
// four-byte element, i.e. the begin/end pair of a span, yielding a SIGNED
// count.  Nothing after the call adjusts esp and the callee is entered with ecx
// unchanged, so the callee pops the two dwords itself -- __thiscall on the same
// `this` with two stack arguments, which is a non-virtual member of this class
// or of a base of it.  The argument is passed through first, the count second.
//
// THE ONLY AXIS IS THE REL32 TARGET.  Thirty-two members over sixteen distinct
// callees; every other byte of all thirty-two bodies is identical.  Distinct
// call targets cannot be one COMDAT, so these are separate functions that
// compile identically, not aliases.
//
// IDENTITY IS NOT RECOVERED.  Nothing in the image names the callers, the
// callees, the span or the element type.  Every name here is derived from an
// address and asserts no identity; the callee pins are likewise address-derived
// and additive.

#define BFME_SPAN_COUNT_CALLEE( ADDR )                                       \
	class Gen##ADDR                                                          \
	{                                                                        \
	public:                                                                  \
		void handle( void *argument, int count );                            \
	};

#define BFME_SPAN_COUNT_FORWARDER( NAME, CALLEE )                            \
	class NAME : public CALLEE                                               \
	{                                                                        \
	public:                                                                  \
		void invoke( void *argument );                                       \
		int m_head;                                                          \
		void **m_begin;                                                      \
		void **m_end;                                                        \
	};                                                                       \
	void NAME::invoke( void *argument )                                      \
	{                                                                        \
		handle( argument, m_end - m_begin );                                 \
	}

BFME_SPAN_COUNT_CALLEE( 000EFCF0 )
BFME_SPAN_COUNT_CALLEE( 00134B70 )
BFME_SPAN_COUNT_CALLEE( 0045F510 )
BFME_SPAN_COUNT_CALLEE( 0045F5C0 )
BFME_SPAN_COUNT_CALLEE( 0045F600 )
BFME_SPAN_COUNT_CALLEE( 00467A00 )
BFME_SPAN_COUNT_CALLEE( 00467A40 )
BFME_SPAN_COUNT_CALLEE( 00467A80 )
BFME_SPAN_COUNT_CALLEE( 00467AC0 )
BFME_SPAN_COUNT_CALLEE( 00467B00 )
BFME_SPAN_COUNT_CALLEE( 00467B40 )
BFME_SPAN_COUNT_CALLEE( 00467B80 )
BFME_SPAN_COUNT_CALLEE( 00582840 )
BFME_SPAN_COUNT_CALLEE( 00611CA0 )
BFME_SPAN_COUNT_CALLEE( 00692440 )
BFME_SPAN_COUNT_CALLEE( 006A10A0 )

BFME_SPAN_COUNT_FORWARDER( Rva000F1DE0SpanForwarder, Gen000EFCF0 )
BFME_SPAN_COUNT_FORWARDER( Rva000F3C00SpanForwarder, Gen000EFCF0 )
BFME_SPAN_COUNT_FORWARDER( Rva00135780SpanForwarder, Gen00134B70 )
BFME_SPAN_COUNT_FORWARDER( Rva001357A0SpanForwarder, Gen00134B70 )
BFME_SPAN_COUNT_FORWARDER( Rva0045FCC0SpanForwarder, Gen0045F510 )
BFME_SPAN_COUNT_FORWARDER( Rva0045FCE0SpanForwarder, Gen0045F510 )
BFME_SPAN_COUNT_FORWARDER( Rva0045FD80SpanForwarder, Gen0045F5C0 )
BFME_SPAN_COUNT_FORWARDER( Rva0045FDA0SpanForwarder, Gen0045F600 )
BFME_SPAN_COUNT_FORWARDER( Rva00460910SpanForwarder, Gen0045F5C0 )
BFME_SPAN_COUNT_FORWARDER( Rva00460990SpanForwarder, Gen0045F600 )
BFME_SPAN_COUNT_FORWARDER( Rva00468700SpanForwarder, Gen00467A00 )
BFME_SPAN_COUNT_FORWARDER( Rva00468720SpanForwarder, Gen00467A00 )
BFME_SPAN_COUNT_FORWARDER( Rva00468740SpanForwarder, Gen00467A40 )
BFME_SPAN_COUNT_FORWARDER( Rva00468760SpanForwarder, Gen00467A40 )
BFME_SPAN_COUNT_FORWARDER( Rva00468780SpanForwarder, Gen00467A80 )
BFME_SPAN_COUNT_FORWARDER( Rva004687A0SpanForwarder, Gen00467A80 )
BFME_SPAN_COUNT_FORWARDER( Rva004687C0SpanForwarder, Gen00467AC0 )
BFME_SPAN_COUNT_FORWARDER( Rva004687E0SpanForwarder, Gen00467AC0 )
BFME_SPAN_COUNT_FORWARDER( Rva00468860SpanForwarder, Gen00467B00 )
BFME_SPAN_COUNT_FORWARDER( Rva00468880SpanForwarder, Gen00467B00 )
BFME_SPAN_COUNT_FORWARDER( Rva00468900SpanForwarder, Gen00467B40 )
BFME_SPAN_COUNT_FORWARDER( Rva00468920SpanForwarder, Gen00467B40 )
BFME_SPAN_COUNT_FORWARDER( Rva00468940SpanForwarder, Gen00467B80 )
BFME_SPAN_COUNT_FORWARDER( Rva0046A050SpanForwarder, Gen00467B80 )
BFME_SPAN_COUNT_FORWARDER( Rva00582F30SpanForwarder, Gen00582840 )
BFME_SPAN_COUNT_FORWARDER( Rva00583560SpanForwarder, Gen00582840 )
BFME_SPAN_COUNT_FORWARDER( Rva00613680SpanForwarder, Gen00611CA0 )
BFME_SPAN_COUNT_FORWARDER( Rva00614530SpanForwarder, Gen00611CA0 )
BFME_SPAN_COUNT_FORWARDER( Rva006928C0SpanForwarder, Gen00692440 )
BFME_SPAN_COUNT_FORWARDER( Rva006928E0SpanForwarder, Gen00692440 )
BFME_SPAN_COUNT_FORWARDER( Rva006A4E50SpanForwarder, Gen006A10A0 )
BFME_SPAN_COUNT_FORWARDER( Rva006A7F60SpanForwarder, Gen006A10A0 )
