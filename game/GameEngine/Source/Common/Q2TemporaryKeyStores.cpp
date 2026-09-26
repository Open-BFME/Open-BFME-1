// Seven 33-byte __thiscall members that build a string temporary from a
// literal and hand it, by value, to one member of their own object:
//
//   push ecx                       ; reserve the by-value argument slot
//   push esi
//   push <FLAG> / push ecx         ; second argument, then the slot again
//   mov esi,ecx
//   mov [esp+0xc],esp              ; cleanup pointer for the in-place temporary
//   mov ecx,esp                    ; construct AT the argument slot
//   push <LITERAL> / call ?StringBase<char>::StringBase(char const *)
//   mov ecx,esi / call <STORE>
//   pop esi / pop ecx / ret
//
// WHAT THE BYTES SHOW.  The temporary is never built somewhere else and
// copied: `mov ecx,esp` right after the argument slot is pushed constructs it
// IN PLACE at the outgoing argument, which is what MSVC does for a by-value
// class argument.  The callee pops both dwords (esp is back at the saved esi
// when `pop esi` runs), so it is __thiscall with two stack arguments, and the
// class is four bytes wide because one push reserves it.  Both calls take ecx
// from the object, so the store is a member of the same class this function
// belongs to.  `mov [esp+0xc],esp` records the temporary's address for
// cleanup.
//
// THE SHAPE OF THE STRING CLASS IS FORCED, and this is the part that took the
// most work.  A flat four-byte class with a `const char *` constructor, with
// or without a copy constructor and destructor, produces a DIFFERENT 33 bytes:
// MSVC emits `mov ecx,esp` BEFORE `mov [esp+0xc],esp`, the opposite order from
// retail, and a version without both the copy constructor and the destructor
// does not construct in place at all (27 or 35 bytes, or 42-92 with an unwind
// frame).  Retail's order appears only when the constructed class is DERIVED
// and its own constructor is an inline delegation to a base constructor --
// which is exactly what the REL32 says, since it lands on
// ?StringBase<char>::StringBase(char const *), a BASE constructor the ledger
// already matches at 0x00888BC0.  Twenty-one spellings were tried; that is the
// one that reproduces the bytes, and no compiler flag reorders the other ones
// (Ob1 Ob2 Ox G5 G6 G7 Og Oi Ot Oy- GF Gy O1 Os Oa Ow GB Gd Gr Gz all swept).
//
// THE LITERALS ARE READ OUT OF RETAIL and re-checked by the build's
// string-reference gate: OverallWinStreak, OverallBestWinStreak,
// OverallLossStreak, OverallWorstLossStreak, PreferredSide, Highest1vs1Rank
// and Highest2vs2Rank.  All seven rows call the same store body, which is what
// makes them seven members of one class.
//
// TWO AXES: the literal and the second argument, which is 0 in six rows and 4
// in one.  21 of the 33 bytes are concrete.
//
// WHAT THE BYTES DO NOT DECIDE.  The second argument is int-width and could be
// an enumerator or a bool.  Nothing shows a data member of the owner.  The
// string class carries exactly one dword and nothing here says what is in it;
// the copy constructor and destructor are declared and left undefined because
// the bytes only require that they EXIST, not what they do.
//
// IDENTITY IS NOT RECOVERED except for StringBase and the literals; the owner,
// its store member and the derived string class are named for addresses or for
// their role.

template < class TChar >
class StringBase
{
private:
	StringBase( const TChar *text );

	void *m_unreconstructed_00;

	friend class Q2AsciiString;
};

class Q2AsciiString : public StringBase< char >
{
public:
	Q2AsciiString( const char *text ) : StringBase< char >( text ) {}
	Q2AsciiString( const Q2AsciiString &other );
	~Q2AsciiString();
};

class Gen000A9490Owner
{
public:
	void store( Q2AsciiString key, int flag );		///< body 0x000A9490

	void Rva0009CEA0();
	void Rva0009CF00();
	void Rva0009CF60();
	void Rva0009CFC0();
	void Rva0009D020();
	void Rva000A9880();
	void Rva000A98E0();
};

#define Q2_TEMPORARY_KEY_STORE( NAME, LITERAL, FLAG )                     \
	void Gen000A9490Owner::NAME()                                         \
	{                                                                     \
		store( Q2AsciiString( LITERAL ), FLAG );                          \
	}

Q2_TEMPORARY_KEY_STORE( Rva0009CEA0, "OverallWinStreak", 0 )
Q2_TEMPORARY_KEY_STORE( Rva0009CF00, "OverallBestWinStreak", 0 )
Q2_TEMPORARY_KEY_STORE( Rva0009CF60, "OverallLossStreak", 0 )
Q2_TEMPORARY_KEY_STORE( Rva0009CFC0, "OverallWorstLossStreak", 0 )
Q2_TEMPORARY_KEY_STORE( Rva0009D020, "PreferredSide", 4 )
Q2_TEMPORARY_KEY_STORE( Rva000A9880, "Highest1vs1Rank", 0 )
Q2_TEMPORARY_KEY_STORE( Rva000A98E0, "Highest2vs2Rank", 0 )
