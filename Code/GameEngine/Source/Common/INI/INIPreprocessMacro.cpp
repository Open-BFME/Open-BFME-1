// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: INI::preprocessMacro at retail 0x008524B0 (148B).
//
// BFME-only -- Zero Hour has no such function.  It is the macro-substitution
// hook every INI scanner runs its token through; scanInt/scanReal/scanBool in
// ini_parsers.cpp already call it, and the name is the provisional one already
// pinned in reverse/symbols.csv.
//
// Behaviour, read off the binary: a token whose first character is a digit is
// returned unchanged (the '-' compare at +0x12 is reachable-but-dead, so any
// comment claiming '-' is special-cased describes nothing).  Otherwise a
// rolling shift/XOR hash is taken over the whole token, that hash indexes the
// bucket vector through the two globals at 0x0130CE5C/0x0130CE60, the chain is
// walked comparing node->hash, and the found node's text is returned offset by
// 8 -- or the pooled empty string when the node carries none.
//
// THE RECORDED BLOCKER -- "retail allocates an 8-byte stack frame and stores a
// dead default-text value into a slot never read back; a dead-store scheduling
// residual" -- IS REFUTED.  The store is not dead scheduling and not a default
// text.  The constant is 0x0130CE58, the ADDRESS OF THE HASH TABLE ITSELF, and
// the 8-byte frame is an STLport hash iterator {_M_cur, _M_ht} returned BY
// VALUE from an inlined find().  Binding that return value to a local is what
// allocates the frame and writes the _M_ht half; _M_cur stays in edx and its
// half of the store folds away.  Nothing about volatile, for-vs-while or split
// begin/end locals could have reached it, because the slot is a real object.
//
// Two further shape tells, both source-order rather than codegen:
//   * the digit test is written high-bound first ('9' before '0'), which is
//     what puts `cmp al,0x39` ahead of `cmp al,0x30`;
//   * the text/empty choice is a TERNARY inside the found branch, not two
//     return statements.  Two returns make MSVC lay the empty-string block out
//     with its own epilogue and drop the hoisted `lea eax,[edx+8]`; the
//     ternary hoists the lea above the branch and lets the found path share
//     the token path's epilogue, which is exactly retail's block order.

struct INIMacroNode
{
	INIMacroNode *m_next;
	unsigned int  m_hash;
	char         *m_text;
};

struct INIMacroHash;

struct INIMacroIterator
{
	INIMacroNode *m_cur;
	INIMacroHash *m_ht;
};

// TU-scoped replica of the bucket table at 0x0130CE58: the empty hasher,
// key-equal and extract-key sub-objects pad to four bytes, so the bucket
// vector's begin/end land at the +0x04/+0x08 the body reads absolutely.
struct INIMacroHash
{
	char           m_functors[4];
	INIMacroNode **m_bucketsBegin;
	INIMacroNode **m_bucketsEnd;

	INIMacroIterator find( unsigned int key )
	{
		unsigned int count = (unsigned int)( m_bucketsEnd - m_bucketsBegin );
		INIMacroNode *first = m_bucketsBegin[ key % count ];
		while( first != 0 && first->m_hash != key )
			first = first->m_next;

		INIMacroIterator it;
		it.m_cur = first;
		it.m_ht = this;
		return it;
	}
};

extern INIMacroHash TheINIMacroHash;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	static const char *preprocessMacro( const char *token );
};

const char *INI::preprocessMacro( const char *token )
{
	char c = token[0];
	if( c <= '9' && c >= '0' && c != '-' )
		return token;

	unsigned int hash = 0;
	unsigned int shift = 0;
	if( *token != 0 )
	{
		const char *p = token;
		do
		{
			shift = ( *p + shift ) & 0x1f;
			hash ^= ( 1u << shift );
			++p;
		} while( *p != 0 );
	}

	INIMacroIterator it = TheINIMacroHash.find( hash );
	if( it.m_cur != 0 )
	{
		const char *text = it.m_cur->m_text;
		return text != 0 ? text + 8 : "";
	}

	return token;
}
