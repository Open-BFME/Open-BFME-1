// cl: /DNDEBUG /MD /EHs-c-
// Byte-identical sibling of FunctionLexicon::gameWinDrawFunc (0x00105420) and
// FunctionLexicon::winLayoutInitFunc (0x001054E0): same TABLE_ANY-fallback
// shape (findFunction on one slot, findFunction on a second slot if the first
// misses, otherwise a direct findFunction with the caller's index), but this
// one probes the two BFME-inserted table slots between TABLE_GAME_WIN_DRAW
// and TABLE_WIN_LAYOUT_INIT that FunctionLexicon.h documents as
// TABLE_BFME_UNIDENTIFIED_5/6 (offsets 0x1c/0x20 in m_tables) instead of the
// device-draw/draw or layout-init/device-init pairs those two use. No caller
// or vftable slot names this accessor, so the name is address-derived.

enum NameKeyType
{
	NAMEKEY_INVALID = 0,
	FORCE_NAMEKEYTYPE_LONG = 0x7fffffff
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/FunctionLexicon.h
// findFunction(key, CONST) is defined in the same TU as gameWinDrawFunc /
// winLayoutInitFunc in retail, so the compiler inlines it down to a single
// key-validity test plus a direct keyToFunc(key, m_tables[CONST]) call for
// each literal slot; only the runtime-index tail (findFunction(key, index))
// stays an out-of-line call. This TU reproduces that inlined shape directly
// instead of re-declaring findFunction as a call target for the two literal
// slots.
class FunctionLexicon
{
public:
	enum TableIndex
	{
		TABLE_ANY = -1,
		TABLE_BFME_UNIDENTIFIED_5 = 5,
		TABLE_BFME_UNIDENTIFIED_6 = 6
	};
	struct TableEntry;

	void *rva00105480( NameKeyType key, TableIndex index = TABLE_ANY );

protected:
	void *findFunction( NameKeyType key, TableIndex index );
	void *keyToFunc( NameKeyType key, TableEntry *table );

	// local twin of findFunction's own body -- defined in this TU so the
	// literal-index calls below can be auto-inlined the same way retail's
	// findFunction( key, CONST ) calls were, instead of forcing an
	// out-of-line call that never happened in the shipped binary.
	void *localFindFunction( NameKeyType key, TableIndex index );

	char m_pad[ 8 ];
	TableEntry *m_tables[ 12 ];
};

void *FunctionLexicon::localFindFunction( NameKeyType key, TableIndex index )
{
	void *func = 0;

	if ( key == NAMEKEY_INVALID )
		return 0;

	if ( index == TABLE_ANY )
	{
		int i;

		for ( i = 0; i < 12; i++ )
		{
			func = keyToFunc( key, m_tables[ i ] );
			if ( func )
				break;
		}
	}
	else
	{
		func = keyToFunc( key, m_tables[ index ] );
	}

	return func;
}

// ?rva00105480@FunctionLexicon@@QAEPAXW4NameKeyType@@W4TableIndex@1@@Z
void *FunctionLexicon::rva00105480( NameKeyType key, TableIndex index )
{
	if ( index == TABLE_ANY )
	{
		void *func;

		func = localFindFunction( key, TABLE_BFME_UNIDENTIFIED_5 );
		if ( func == 0 )
		{
			func = localFindFunction( key, TABLE_BFME_UNIDENTIFIED_6 );
		}
		return func;
	}
	return findFunction( key, index );
}
