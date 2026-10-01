// Sixteen address-qualified members store BfmeParserBindingBaseVE's vftable,
// then forward the +8 field to the receiver at +4.
// The owning class identities remain unproved.

class Q1SharedTarget0107C7D0
{
public:
	int m_opaque;
};

extern "C" Q1SharedTarget0107C7D0 __identifier("??_7BfmeParserBindingBaseVE@@6B@");
#define g_q1Shared0107C7D0 __identifier("??_7BfmeParserBindingBaseVE@@6B@")

class Q1Forwardee0000871A
{
public:
	void handle( int value );
};

#define Q1_SHARED_STORE_FORWARD( NAME )                                   \
	class NAME                                                            \
	{                                                                     \
	public:                                                               \
		Q1SharedTarget0107C7D0 *m_target;                                     \
		Q1Forwardee0000871A *m_receiver;                                      \
		int m_value;                                                      \
		void invoke();                                                    \
	};                                                                    \
	void NAME::invoke()                                                   \
	{                                                                     \
		m_target = &g_q1Shared0107C7D0;                                       \
		m_receiver->handle( m_value );                                    \
	}

Q1_SHARED_STORE_FORWARD( Rva000875F0 )
Q1_SHARED_STORE_FORWARD( Rva00089040 )
Q1_SHARED_STORE_FORWARD( Rva0018F0E0 )
Q1_SHARED_STORE_FORWARD( Rva00190EF0 )
Q1_SHARED_STORE_FORWARD( Rva001915E0 )
Q1_SHARED_STORE_FORWARD( Rva00191600 )
Q1_SHARED_STORE_FORWARD( Rva00191620 )
Q1_SHARED_STORE_FORWARD( Rva0034FA20 )
Q1_SHARED_STORE_FORWARD( Rva0034FA40 )
Q1_SHARED_STORE_FORWARD( Rva0044F6D0 )
Q1_SHARED_STORE_FORWARD( Rva0044F6F0 )
Q1_SHARED_STORE_FORWARD( Rva00746EC0 )
Q1_SHARED_STORE_FORWARD( Rva00746EE0 )
Q1_SHARED_STORE_FORWARD( Rva00746F00 )
Q1_SHARED_STORE_FORWARD( Rva00746F20 )
Q1_SHARED_STORE_FORWARD( Rva00746F40 )
