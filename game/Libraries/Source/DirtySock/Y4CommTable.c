// cl: /Od /GZ /GS /MD /DNDEBUG
/* EA DirtySock -- the comm layer's entry table and its lookup, /Od with /GZ.
 * Placement is by address neighbourhood within the 0x00810000 group.
 */

/* One table entry, 0x1A4 bytes.  Only the fields the lookup touches are named;
 * the rest is gap, because nothing here reads it and guessing would be worse
 * than admitting the gap. */
struct Rva00812220Entry
{
	char m_gap0[ 0x08 ];
	char m_nameA[ 0x20 ];			/* +0x08 */
	char m_nameB[ 0x20 ];			/* +0x28, empty means a free slot */
	char m_detail[ 0xC0 ];			/* +0x48 */
	char m_templates[ 0x7C ];		/* +0x108, tab-separated */
	char m_substitution[ 0x10 ];		/* +0x184, what ~1 expands to */
	int m_value;				/* +0x194, zero means not ready */
	int m_extra;				/* +0x198 */
	int m_pending;				/* +0x19C, non-zero means skip */
	char m_gap1A0[ 4 ];
};

struct Rva007FD4E0Socket;

/* The owning object, 0x50 bytes.  THE TABLE AND THE MODULE ARE ONE
 * ALLOCATION: the lookup below reads only +0x28 and +0x2C, the constructor at
 * 0x00812320 fills the same two and six more, and the announce sender reads
 * two others -- all from the same pointer.  Three functions had three partial
 * views of it while they were converted separately; this is the union of
 * them, and only the first 0x28 remain gap because nothing here reads them. */
struct Rva00812320Module
{
	char m_gap0[ 0x28 ];
	struct Rva00812220Entry *m_first;	/* +0x28 */
	struct Rva00812220Entry *m_end;		/* +0x2C */
	int m_ready;				/* +0x30 */
	char m_gap34[ 4 ];
	struct Rva007FD4E0Socket *m_socket;	/* +0x38 */
	char m_peer[ 0x10 ];			/* +0x3C */
	int m_active;				/* +0x4C */
};

/* 0x00811CE0 COMPARES TWO STRINGS IGNORING ASCII CASE, folding with XOR 0x20
 * on the range 'A'..'Z' only -- so it is ASCII case-insensitive and nothing
 * more; no table, no locale, and bytes above 0x7F are compared exactly.
 *
 * IT IS A DO-WHILE, so it always reads and folds ONE CHARACTER FROM EACH SIDE
 * before testing anything.  Two empty strings therefore still cost a full
 * iteration, and -- more to the point -- BOTH pointers are advanced past their
 * terminators before the loop can end.  The caller never sees that, since the
 * pointers are its own copies, but it means neither string may be at the very
 * end of a mapped page.
 */
int Rva00811CE0( const char *a, const char *b )
{
	int iDiff;
	char cA;
	char cB;

	do
	{
		cA = *a;
		a++;

		if ( cA >= 'A' && cA <= 'Z' )
		{
			cA ^= 0x20;
		}

		cB = *b;
		b++;

		if ( cB >= 'A' && cB <= 'Z' )
		{
			cB ^= 0x20;
		}

		iDiff = cA - cB;
	}
	while ( cA != 0 && iDiff == 0 );

	return iDiff;
}

/* 0x00812220 FINDS AN ENTRY MATCHING UP TO TWO NAMES and returns its value,
 * or the caller's default if nothing matches.
 *
 * EITHER NAME MAY BE OMITTED, and omitted means "matches anything" rather than
 * "matches empty": a null or empty argument skips that comparison entirely.
 * With both omitted this returns the first ready entry, which makes the same
 * function a lookup and a "give me any" query depending only on its arguments.
 *
 * THE TWO COMPARISONS PASS THEIR ARGUMENTS IN OPPOSITE ORDERS -- the first as
 * (key, entry) and the second as (entry, key).  It cannot matter to the result
 * because the comparator is symmetric about zero and only the zero case is
 * tested, but the asymmetry is real and is in the bytes.
 *
 * FOUR SEPARATE CONDITIONS SKIP AN ENTRY and they are not interchangeable: an
 * empty second name means the slot is free, a non-zero pending flag means it
 * is in flight, a zero value means it is not ready, and a name mismatch means
 * it is someone else's.  All four continue silently, so a caller that gets the
 * default back cannot tell which of the four applied -- or that the table was
 * null, which returns the default too.
 */
int Rva00812220( struct Rva00812320Module *table, const char *keyA,
	const char *keyB, int *pExtra, int iDefault )
{
	struct Rva00812220Entry *p;

	if ( table == 0 )
	{
		return iDefault;
	}

	for ( p = table->m_first; p != table->m_end; p++ )
	{
		if ( p->m_nameB[ 0 ] == 0 )
		{
			continue;
		}

		if ( p->m_pending != 0 )
		{
			continue;
		}

		if ( keyA != 0 && *keyA != 0 && Rva00811CE0( keyA, p->m_nameA ) != 0 )
		{
			continue;
		}

		if ( keyB != 0 && *keyB != 0 && Rva00811CE0( p->m_nameB, keyB ) != 0 )
		{
			continue;
		}

		if ( p->m_value == 0 )
		{
			continue;
		}

		if ( pExtra != 0 )
		{
			*pExtra = p->m_extra;
		}

		iDefault = p->m_value;
		break;
	}

	return iDefault;
}

struct Rva007FD4E0Socket;

/* The module's owning object, 0x50 bytes.  Only the fields this file touches
 * are named; the first 0x28 stay gap because nothing here reads them.  THE
 * TABLE THE LOOKUP WALKS IS THIS OBJECT -- 0x00812220 takes the same pointer
 * and reads the same two fields, so the "table" and the "module" are one
 * allocation and the split is only in how each function names it. */
int Rva007FD920( struct Rva007FD4E0Socket *socket, const char *buffer,
	int length, int flags, void *to, int toLength );
void * __cdecl memset( void *dest, int c, unsigned int count );
void * __cdecl memcpy( void *dest, const void *src, unsigned int count );

/* "gEA\0" repeated.  THE TAG IS READ ONE CHARACTER AT A TIME FROM THREE
 * DIFFERENT OFFSETS -- 0, 5 and 10 -- which land on the 'g' of the first copy,
 * the 'E' of the second and the 'A' of the third.  The assembled result spells
 * the same three characters the run already contains contiguously, so this
 * buys nothing against a strings dump; it only makes the literal invisible to
 * a reader of the code. */
extern char g_Rva012C499CTag[];

/* 0x008125C0 SENDS THE MODULE'S ANNOUNCE PACKET.  Retail's own name for the
 * buffer, from the /GZ frame descriptor, is Packet.
 *
 * THE PACKET IS 0x180 BYTES AND ALL BUT FOUR OF THEM ARE ZERO -- three tag
 * characters at the front and one byte at offset 8.  The whole 0x180 is sent
 * regardless, so the wire cost is fixed and does not depend on content; a
 * reader looking for a length field will not find one.
 *
 * THE DESTINATION IS THE CONTEXT'S OWN STORED ADDRESS, passed by pointer with
 * a fixed length of 0x10, so this always goes to the same place and takes no
 * argument saying where.
 */
int Rva008125C0( struct Rva00812320Module *context )
{
	char Packet[ 0x180 ];

	memset( Packet, 0, sizeof( Packet ) );

	Packet[ 0 ] = g_Rva012C499CTag[ 0 ];
	Packet[ 1 ] = g_Rva012C499CTag[ 5 ];
	Packet[ 2 ] = g_Rva012C499CTag[ 10 ];
	Packet[ 8 ] = 0x3F;

	return Rva007FD920( context->m_socket, Packet, sizeof( Packet ), 0,
		context->m_peer, 0x10 );
}

/* The FESL allocator pair at 0x007F0000 and 0x007F0030 -- vtable slots 2 and 3
 * of the same lazily-fetched global.  Optimised code, so both are pinned
 * rather than converted. */
void *Rva007F0000( unsigned int size );
void Rva007F0030( void *block );

struct Rva0130AB68List;

struct Rva007FD4E0Socket *Rva007FD2D0( int family, int type, int protocol );
int Rva007FD510( struct Rva007FD4E0Socket *socket, const void *address,
	int addressLength );
int Rva007FDE80( struct Rva007FD4E0Socket *socket, void *callback,
	unsigned int rate, void *data,
	void ( __cdecl *proc )( struct Rva007FD4E0Socket *, int, void * ) );
void Rva007FEA20( struct Rva0130AB68List *list );
void Rva007FEBD0( void *list );
void Rva007FECB0( void *list );
void Rva007FEAA0( void *list );
void Rva007FD3F0( void *socket );
void bfmeGo1019C( int value );
void __cdecl Rva00812690( struct Rva007FD4E0Socket *socket, int reason,
	void *data );

extern struct Rva00812320Module *g_Rva0130AD00Module;
extern int g_Rva0130ACFCRefCount;

struct Rva00811D70Entry
{
	char m_gap0[ 0x08 ];
	char m_nameA[ 0x20 ];
	char m_nameB[ 0x20 ];
	char m_gap48[ 0x138 ];
	int m_value;
	char m_gap184[ 0x1C ];
	struct Rva00811D70Entry *m_next;
};

struct Rva00811D70List
{
	char m_gap0[ 0x24 ];
	struct Rva00811D70Entry *m_first;
};

int Rva00811D70( struct Rva00811D70List *list, const char *keyA,
	const char *keyB )
{
	struct Rva00811D70Entry *entry;

	Rva007FEBD0( list );
	for ( entry = list->m_first; entry != 0; entry = entry->m_next )
	{
		if ( ( keyA == 0 || Rva00811CE0( keyA, entry->m_nameA ) == 0 )
			&& ( keyB == 0 || Rva00811CE0( keyB, entry->m_nameB ) == 0 ) )
		{
			entry->m_value = 0;
			break;
		}
	}
	Rva007FECB0( list );
	return entry != 0 ? 0 : -1;
}

/* 0x00812320 CREATES THE MODULE, OR SHARES THE ONE THAT EXISTS.  Retail's own
 * names for the two address buffers, from the /GZ frame descriptor, are
 * bindaddr and peeraddr.
 *
 * IT IS A REFCOUNTED SINGLETON WITH NO LOCK.  The existing-instance test, the
 * count increment and the global store are three separate unsynchronised
 * accesses, so two threads arriving together can both allocate and one result
 * is leaked with a count of one.  Nothing here is guarded.
 *
 * THE ENTRY COUNT IS RAISED TO FOUR AND NEVER CAPPED, so a caller asking for
 * one gets four and a caller asking for a million gets a million times 0x1A4
 * handed straight to the allocator.
 *
 * THE TWO ALLOCATION FAILURES ARE HANDLED DIFFERENTLY AND BOTH ARE DEAD.  The
 * first returns null without freeing anything; the second frees the module
 * first.  Neither can run, because the allocator prints and then faults rather
 * than returning null -- so this is failure handling written against a
 * contract the allocator does not keep.
 *
 * THE SOCKET FAILURE PATH LEAKS THE ENTRY TABLE.  It frees the module but not
 * the block hung off +0x28, which was allocated separately.  That path IS
 * reachable, unlike the two above.
 *
 * BOTH ADDRESSES ARE BUILT BYTE BY BYTE, port 0x270F and, for the peer, an
 * all-ones address shifted out one byte at a time from low to high into
 * descending offsets -- a big-endian store of the broadcast address written as
 * a loop that was unrolled by hand.
 */
struct Rva00812320Module *Rva00812320( int iEntries )
{
	struct Rva007FD4E0Socket *pSocket;
	char bindaddr[ 0x10 ];
	char peeraddr[ 0x10 ];
	struct Rva00812320Module *pModule;
	unsigned int uAddr;

	if ( g_Rva0130AD00Module != 0 )
	{
		g_Rva0130ACFCRefCount++;
		return g_Rva0130AD00Module;
	}

	pModule = Rva007F0000( 0x50 );

	if ( pModule == 0 )
	{
		return 0;
	}

	memset( pModule, 0, 0x50 );

	if ( iEntries < 4 )
	{
		iEntries = 4;
	}

	pModule->m_first = Rva007F0000( iEntries * 0x1A4 );

	if ( pModule->m_first == 0 )
	{
		Rva007F0030( pModule );
		return 0;
	}

	pModule->m_end = pModule->m_first + iEntries;

	memset( pModule->m_first, 0,
		( char * )pModule->m_end - ( char * )pModule->m_first );

	pModule->m_active = 1;

	pSocket = Rva007FD2D0( 2, 2, 0 );

	if ( pSocket == 0 )
	{
		Rva007F0030( pModule );
		return 0;
	}

	g_Rva0130AD00Module = pModule;
	g_Rva0130ACFCRefCount = 1;

	Rva007FEA20( ( struct Rva0130AB68List * )pModule );
	Rva007FEBD0( pModule );

	*( short * )&bindaddr[ 0 ] = 2;
	*( short * )&bindaddr[ 2 ] = 0;
	*( int * )&bindaddr[ 4 ] = 0;
	*( int * )&bindaddr[ 8 ] = 0;
	*( int * )&bindaddr[ 12 ] = 0;
	bindaddr[ 2 ] = 0x27;
	bindaddr[ 3 ] = 0x0F;

	Rva007FD510( pSocket, bindaddr, 0x10 );

	*( short * )&peeraddr[ 0 ] = 2;
	*( short * )&peeraddr[ 2 ] = 0;
	*( int * )&peeraddr[ 4 ] = 0;
	*( int * )&peeraddr[ 8 ] = 0;
	*( int * )&peeraddr[ 12 ] = 0;
	peeraddr[ 2 ] = 0x27;
	peeraddr[ 3 ] = 0x0F;

	uAddr = 0xFFFFFFFF;
	peeraddr[ 7 ] = ( char )uAddr;
	uAddr >>= 8;
	peeraddr[ 6 ] = ( char )uAddr;
	uAddr >>= 8;
	peeraddr[ 5 ] = ( char )uAddr;
	uAddr >>= 8;
	peeraddr[ 4 ] = ( char )uAddr;

	memcpy( pModule->m_peer, peeraddr, 0x10 );

	pModule->m_ready = 1;
	pModule->m_socket = pSocket;

	Rva007FDE80( pModule->m_socket, ( void * )2, 0x64, pModule,
		Rva00812690 );

	Rva007FECB0( pModule );
	Rva008125C0( pModule );

	return pModule;
}

void Rva00812CD0( void *object )
{
	void *socket;
	char *table;

	if ( object == 0 )
	{
		return;
	}

	if ( g_Rva0130ACFCRefCount > 1 )
	{
		g_Rva0130ACFCRefCount--;
		return;
	}

	g_Rva0130AD00Module = 0;
	g_Rva0130ACFCRefCount = 0;

	while ( *( void ** )( ( char * )object + 0x24 ) != 0 )
	{
		table = *( char ** )( ( char * )object + 0x24 );
		Rva00811D70( object, table + 8, table + 0x28 );
		Rva00812690( *( struct Rva007FD4E0Socket ** )( ( char * )object + 0x38 ),
			0, object );
	}

	Rva007FEBD0( object );
	socket = *( void ** )( ( char * )object + 0x38 );
	*( void ** )( ( char * )object + 0x38 ) = 0;
	Rva007FD3F0( socket );
	Rva007FECB0( object );
	Rva007FEAA0( object );
	bfmeGo1019C( *( int * )( ( char * )object + 0x28 ) );
	bfmeGo1019C( ( int )object );
}

unsigned int __cdecl strlen( const char *text );
char * __cdecl strcpy( char *dest, const char *src );
char * __cdecl strstr( const char *haystack, const char *needle );

/* 0x00811E20 FORMATS MATCHING ENTRIES INTO A TEXT LISTING, one line per
 * template, and returns how many lines it wrote.  Retail's own names for the
 * two buffers, from the /GZ frame descriptor, are addr and record.
 *
 * EACH ENTRY CARRIES SEVERAL TEMPLATES, tab-separated, and each becomes its
 * own line -- so the count returned is a count of LINES and not of entries,
 * and one matching entry can contribute many or none.
 *
 * A TEMPLATE IS FILTERED BY ITS FIRST THREE CHARACTERS.  It must be at least
 * five long with a colon in position four; that colon is then temporarily
 * overwritten with a terminator so the prefix can be searched for in the
 * caller's filter, and put back afterwards.  THE BUFFER IS EDITED AND
 * RESTORED IN PLACE rather than copied, which is why the same byte is written
 * twice a few instructions apart.
 *
 * TWO SUBSTITUTIONS ARE RECOGNISED AND THEY BEHAVE DIFFERENTLY.  A "~1"
 * expands to a field from the entry -- unless that field is empty, in which
 * case the whole line is ABANDONED rather than expanded to nothing.  A "~2"
 * simply ends the line early, keeping what came before it.  So one marker can
 * suppress a line and the other truncates it, and only the bytes distinguish
 * them.
 *
 * THE TRUNCATION MARKER IS THREE DOTS AND A NEWLINE, written when the next
 * line would not fit -- and note the check reserves FIVE bytes rather than the
 * four it writes, so there is always one byte spare that nothing uses.  On
 * that path it returns the count so far, so a caller cannot tell a complete
 * listing from a truncated one by the return value alone; it has to look for
 * the dots.
 *
 * FIELD OFFSETS ARE EVIDENCED, FIELD LENGTHS ARE NOT.  Only the starts of
 * m_detail, m_templates and m_substitution are visible in the code; the sizes
 * below are what makes them adjacent and total 0x1A4, not something the bytes
 * say.
 */
int Rva00811E20( struct Rva00812320Module *module, const char *keyA,
	const char *keyB, char *out, int outSize, int bIncludePending )
{
	char *p;
	char *pOut;
	char *pTemplate;
	char addr[ 0x100 ];
	char record[ 0x200 ];
	int iCount;
	struct Rva00812220Entry *pEntry;

	iCount = 0;

	if ( outSize < 5 )
	{
		return -1;
	}

	*out = 0;

	for ( pEntry = module->m_first; pEntry != module->m_end; pEntry++ )
	{
		if ( pEntry->m_nameB[ 0 ] == 0 )
		{
			continue;
		}

		if ( Rva00811CE0( keyA, pEntry->m_nameA ) != 0 )
		{
			continue;
		}

		if ( bIncludePending == 0 && pEntry->m_pending != 0 )
		{
			continue;
		}

		p = pEntry->m_templates;

		while ( *p != 0 )
		{
			pOut = addr;

			while ( *p != 0 && *p != 9 )
			{
				*pOut = *p;
				pOut++;
				p++;
			}

			*pOut = 0;
			pOut++;

			if ( *p == 9 )
			{
				p++;
			}

			if ( strlen( addr ) < 5 || addr[ 3 ] != ':' )
			{
				continue;
			}

			addr[ 3 ] = 0;

			if ( *keyB != 0 && strstr( keyB, addr ) == 0 )
			{
				continue;
			}

			addr[ 3 ] = ':';

			strcpy( record, pEntry->m_nameB );

			/* AN EMPTY-BODIED FOR, unlike the two advances below it.  This
			 * one carries an initialiser and retail steps the cursor in the
			 * increment clause; the other two have nothing to initialise and
			 * are plain whiles with the step in the body.  Same walk, three
			 * times, two shapes -- and only the bytes separate them. */
			for ( pOut = record; *pOut != 0; pOut++ )
			{
			}

			*pOut = 9;
			pOut++;

			strcpy( pOut, pEntry->m_detail );

			while ( *pOut != 0 )
			{
				pOut++;
			}

			*pOut = 9;
			pOut++;

			for ( pTemplate = addr; *pTemplate != 0; pTemplate++ )
			{
				if ( pTemplate[ 0 ] == '~' && pTemplate[ 1 ] == '1' )
				{
					if ( pEntry->m_substitution[ 0 ] == 0 )
					{
						break;
					}

					strcpy( pOut, pEntry->m_substitution );

					while ( *pOut != 0 )
					{
						pOut++;
					}

					pTemplate++;
					continue;
				}

				if ( pTemplate[ 0 ] == '~' && pTemplate[ 1 ] == '2' )
				{
					break;
				}

				*pOut = *pTemplate;
				pOut++;
			}

			if ( *pTemplate != 0 )
			{
				continue;
			}

			*pOut = '\n';
			pOut++;
			*pOut = 0;

			if ( strlen( record ) + 5 > outSize )
			{
				*out = '.';
				out++;
				*out = '.';
				out++;
				*out = '.';
				out++;
				*out = '\n';
				out++;
				*out = 0;
				return iCount;
			}

			strcpy( out, record );
			out += strlen( record );
			outSize -= strlen( record );
			iCount++;
		}
	}

	return iCount;
}

/* 0x00811900 COPIES THE WHOLE ENTRY TABLE OUT, but only when it has changed
 * since the caller last asked.
 *
 * THE CHANGE TEST IS A STAMP THE CALLER HOLDS.  It compares the caller's saved
 * value against the module's own counter and returns zero when they agree, so
 * the caller carries the "have I seen this" state and the module carries none.
 * Several callers can poll independently without interfering.
 *
 * THE STAMP IS WRITTEN UNCONDITIONALLY EVEN THOUGH IT WAS TESTED FOR NULL.
 * The guard above tolerates a null pointer -- it short-circuits and skips the
 * comparison -- and then the very next statement dereferences it anyway.  A
 * caller passing null to mean "always copy" gets a null write instead.
 *
 * BOTH SIZES ARE ROUNDED DOWN TO WHOLE ENTRIES, and the two roundings are not
 * spelled the same way: the table's own extent divides SIGNED and the caller's
 * buffer size divides UNSIGNED.  The first can never be negative in practice,
 * so the difference has no effect -- but it is there, and it is the kind of
 * thing that says the two expressions were written at different moments.
 *
 * A NULL DESTINATION SUPPRESSES THE COPY BUT NOT THE STAMP UPDATE, so probing
 * for the size consumes the change notification: ask twice and the second call
 * returns zero.
 */
int Rva00811900( struct Rva00812320Module *module, int *pStamp, void *dest,
	int destSize )
{
	int iSize;

	if ( pStamp != 0 && *pStamp == module->m_active )
	{
		return 0;
	}

	*pStamp = module->m_active;

	iSize = ( ( char * )module->m_end - ( char * )module->m_first ) / 0x1A4
		* 0x1A4;

	if ( iSize > destSize )
	{
		iSize = ( unsigned int )destSize / 0x1A4 * 0x1A4;
	}

	if ( dest != 0 )
	{
		memcpy( dest, module->m_first, iSize );
	}

	return iSize;
}
