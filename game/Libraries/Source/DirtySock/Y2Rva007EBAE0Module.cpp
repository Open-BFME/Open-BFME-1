// cl: /DNDEBUG /MD /GX /Od /GZ /GS
// Three small /Od /GZ bodies from the 0x007EBAE0..0x007EC780 span, sharing this
// file because they share a compiler line and a subject: bounded string work
// against a caller's buffer.  Nothing in them names a module -- no string and no
// selector is reachable -- so the file name and every function name here are
// derived from addresses.

// 0x007EBAE0 is a GET-AND-SET on a single byte of global state: it saves the old
// value, stores the new one, and returns what was there.  A caller can therefore
// restore it, which is what makes this a scoped override rather than a setter.
// The old value goes through a one-byte local rather than staying in a register,
// which is why the frame exists at all.
extern char g_Rva012C391CFlag;

// 0x007EBCA0, the tag lookup both bodies at the end of this file feed; pinned
// by address and still a dump.
// A 256-byte case-folding table at 0x0112A210; the lookup below indexes it
// with a byte read through movzx, so it is unsigned.
extern const unsigned char g_Rva0112A210Lower[];

// Defined at the end of this file; the three wrappers above it all call it.
char *Rva007EBCA0( const char *text, const char *tag );   // 0x007EBCA0

// Reached by a direct rel32 to the import stub, so this TU never saw <stdio.h>.
extern "C" int sprintf( char *buffer, const char *format, ... );
extern "C" char *strcpy( char *dest, const char *src );
extern "C" char *strcat( char *dest, const char *src );

char Rva007EBAE0( char value )
{
	char old;

	old = g_Rva012C391CFlag;
	g_Rva012C391CFlag = value;
	return old;
}

// 0x007EC280 IS A BOUNDED COPY THAT REPORTS WHAT IT WROTE.  The counter starts
// at the caller's size and is spent per byte, so the return -- size minus what
// is left -- is the number of bytes copied, terminator included.
//
// THE SOURCE TEST IS PART OF THE LOOP CONDITION, not a break: retail leaves the
// loop with a single `je` at that test, which is what a second `&&` operand
// compiles to; a break inside the body is `jne` over a `jmp` and moves every
// displacement after it.
//
// The bound is `> 1`, so one byte is always held back, and the terminator is
// then written only when the counter is still positive -- which it always is
// after that loop.  A size of zero skips the loop and the terminator both, and
// returns zero.
int Rva007EC280( char *dest, int size, const char *src )
{
	int left;

	for( left = size; left > 1 && *src != 0; left-- )
	{
		*dest = *src;
		dest++;
		src++;
	}

	if( left > 0 )
		*dest = 0;

	return size - left;
}

// 0x007EC730 WRITES A TAG AND ITS SEPARATOR.  It copies the source up to its
// terminator and appends '=', returning the position after it, so a caller
// chains this to build "name=value" without measuring anything.
//
// IT IS UNBOUNDED.  There is no count and no limit: the only thing that stops
// the copy is the source's own terminator, and the caller's buffer is not
// consulted.  That is what the separate first argument is for -- given a null
// source, this writes a terminator through THAT pointer and returns the
// destination untouched, which is the only way it reports anything at all.
char *Rva007EC730( char *empty, char *dest, const char *src )
{
	if( src == 0 )
	{
		*empty = 0;
	}
	else
	{
		while( *src != 0 )
		{
			*dest = *src;
			dest++;
			src++;
		}

		*dest = '=';
		dest++;
	}

	return dest;
}

// 0x007EBF20 LOOKS UP A NUMBERED TAG.  It builds the name with "%s%d" -- a
// base and an index -- into a 0x100-byte buffer /GZ names `strTag`, and hands
// that to the lookup.  So the record's tags are things like "addr0",
// "addr1"; the numbering is in the name and not in the lookup.
//
// The buffer is 0x100 and the format is unbounded: a base name long enough
// overruns it, and nothing here checks.
char *Rva007EBF20( const char *text, const char *name, int index )
{
	char strTag[ 0x100 ];

	sprintf( strTag, "%s%d", name, index );
	return Rva007EBCA0( text, strTag );
}

// 0x007EBFC0 LOOKS UP THE TAG NAMED "~~" and then trims what it finds: it
// steps over every byte at or below 0x20 -- space and everything below it,
// which is leading whitespace and control characters together -- and reports a
// value that turns out to be empty as ABSENT, by returning null rather than a
// pointer to the terminator.
//
// So a caller cannot tell "no such tag" from "tag present but blank", and the
// trim is what collapses the two.  The comparison is `<= 0x20` on a value read
// with movzx, so it is UNSIGNED: a high byte is not whitespace here.
char *Rva007EBFC0( const char *text )
{
	char *value;

	value = Rva007EBCA0( text, "~~" );

	if( value != 0 )
	{
		while( *(unsigned char *)value != 0
				&& *(unsigned char *)value <= 0x20 )
			value++;

		if( *(unsigned char *)value == 0 )
			value = 0;
	}

	return value;
}

// 0x007EBE20 LOOKS UP A TAG BUILT FROM TWO PIECES, and its three arms are the
// whole content: a null first piece looks up the second alone, a null second
// looks up the first alone, and two present pieces are CONCATENATED into a
// 0x100-byte buffer /GZ names `name` and looked up together.  Two nulls fall
// into the first arm and look up nothing.
//
// The join is strcpy then strcat with no separator, so "addr" and "0" make
// "addr0" -- the same names 0x007EBF20 builds with "%s%d", reached the other
// way round.  It is unbounded for the same reason that one is.
//
// The result is initialised to null before the arms and every arm assigns it,
// so that store is dead; it is retail's and removing it removes an instruction.
char *Rva007EBE20( const char *text, const char *prefix, const char *suffix )
{
	char name[ 0x100 ];
	char *result;

	result = 0;

	if( prefix == 0 )
	{
		result = Rva007EBCA0( text, suffix );
	}
	else if( suffix == 0 )
	{
		result = Rva007EBCA0( text, prefix );
	}
	else
	{
		strcpy( name, prefix );
		strcat( name, suffix );
		result = Rva007EBCA0( text, name );
	}

	return result;
}

// 0x007EBCA0 IS THE TAG LOOKUP the three wrappers above all feed, and it works
// BACKWARDS.  It scans forward for a separator -- '=' or ':' -- and then walks
// back from there comparing the tag's last character first, so a tag is found
// by where its separator is rather than by where its name starts.  That is why
// the tag's end is measured up front.
//
// THE SEPARATOR TEST IS A NEGATED GUARD WITH A `continue`, not a positive `if`
// around the body.  Retail enters the body with a forward `je` from BOTH
// comparisons and falls into a short jump back to the loop; a positive `||`
// inverts the second test into a far `jne` instead, one byte longer and enough
// to move every displacement in the body.
//
// THE BACKWARD WALK'S THREE TESTS ARE ALL LOOP CONDITIONS, and the terminator
// check is a `break` rather than a `return 0`: retail leaves each of the three
// with ONE conditional jump to the same place, and the terminator's exit jumps
// to the function's own trailing `return 0` rather than making a second one.
// Writing any of them as an `if ... break` inside the body costs a byte each
// and a duplicated `xor eax,eax`.
//
// THE MATCH IS CASE-INSENSITIVE THROUGH A TABLE, not through tolower: both
// bytes are indexed into the 256-entry map at 0x0112A210.
//
// A MATCH ALSO HAS TO START ON A WORD BOUNDARY.  Running out of tag is not
// enough: the character before the name must be absent or at or below 0x20, so
// "peerIP=" does not match a request for "IP".  The scan continues from the
// same separator when that fails.
//
// THE END OF THE RECORD IS A SEPARATOR WITH NOTHING EITHER SIDE OF IT: a byte
// below 0x20 after it and whitespace before it stops the whole search and
// returns null.  That is the "~~=" terminator the wrapper above looks up by
// name, recognised here structurally rather than by text.
//
// The value returned skips one space after the separator if there is exactly
// one -- p + 2 rather than p + 1 -- and no more, so leading whitespace beyond
// that is the caller's problem.  It is 0x007EBFC0 that trims the rest.
char *Rva007EBCA0( const char *text, const char *tag )
{
	const char *p;
	const char *q;
	const char *r;
	const char *tagEnd;
	const char *tagPtr;
	const char *textPtr;
	const char *result;

	tagPtr = tag;
	textPtr = text;

	if( textPtr == 0 || *(unsigned char *)textPtr == 0 )
		return 0;

	if( tagPtr == 0 || *(unsigned char *)tagPtr == 0 )
		return 0;

	for( tagEnd = tagPtr; *(unsigned char *)tagEnd != 0; tagEnd++ )
		;
	tagEnd--;

	for( p = textPtr; *(unsigned char *)p != 0; p++ )
	{
		if( *(unsigned char *)p != '=' && *(unsigned char *)p != ':' )
			continue;

		{
			if( *(unsigned char *)( p + 1 ) < 0x20
					&& *(unsigned char *)( p - 1 ) <= 0x20 )
				break;

			for( q = p - 1, r = tagEnd;
					q >= textPtr && r >= tagPtr
						&& g_Rva0112A210Lower[ *(unsigned char *)q ]
							== g_Rva0112A210Lower[ *(unsigned char *)r ];
					q--, r-- )
			{
				if( r == tagPtr )
				{
					if( q == textPtr
							|| *(unsigned char *)( q - 1 ) <= 0x20 )
					{
						if( *(unsigned char *)( p + 1 ) == 0x20 )
							result = p + 2;
						else
							result = p + 1;

						return (char *)result;
					}
				}
			}
		}
	}

	return 0;
}

// 0x007EBB10 NORMALISES A RECORD IN PLACE, rewriting it over itself: the read
// and write pointers start together and the writer never overtakes the reader,
// because every run of control bytes collapses to one byte.
//
// IT RUNS IN TWO PASSES OVER THE SAME BUFFER.  The first replaces each run of
// bytes below 0x20 with the caller's separator and stops at the record
// terminator -- a '=' or ':' followed by a control byte, the same structural
// end 0x007EBCA0 recognises.  The second pass then rewrites what is LEFT AFTER
// that terminator with newline separators, and remembers each run's first
// character so the run ends where that character repeats.
//
// BETWEEN THE PASSES IT FIXES THE JOIN.  A trailing separator is replaced by a
// newline when there is more to come, and by a terminator when there is not, so
// the caller never sees a record ending in its own separator.  That is the only
// thing the two passes say to each other.
//
// The separator parameter is reused as a variable in the second pass, which is
// why it is not const: it holds the character each run began with.
//
// IT RETURNS NOTHING.  eax happens to hold the write pointer at the end,
// because the terminator is stored through it, but nothing sets a return value
// -- so a caller reading one is reading a side effect.  Declaring this to
// return that pointer adds an instruction retail does not have.
void Rva007EBB10( char *record, char separator )
{
	char *p;
	char *out;
	char *start;
	int extra;

	start = record;
	out = start;
	p = out;

	while( *(unsigned char *)p != 0 )
	{
		if( *(unsigned char *)p < 0x20 )
		{
			*out = separator;
			out++;

			while( *(unsigned char *)p > 0
					&& *(unsigned char *)p < 0x20 )
				p++;

			if( ( *(unsigned char *)p == '=' || *(unsigned char *)p == ':' )
					&& *(unsigned char *)( p + 1 ) < 0x20 )
				break;
		}
		else
		{
			*out = *p;
			out++;
			p++;
		}
	}

	if( out != start && *(unsigned char *)( out - 1 )
			== *(unsigned char *)&separator )
	{
		if( *(unsigned char *)&separator != 0x0A
				&& *(unsigned char *)p == 0 )
			extra = 0;
		else
			extra = 0x0A;

		out[ -1 ] = (char)extra;
	}

	while( *(unsigned char *)p != 0 )
	{
		if( *(unsigned char *)p < 0x20 )
		{
			*out = 0x0A;
			out++;

			separator = *p;
			p++;

			while( *(unsigned char *)p > 0
					&& *(unsigned char *)p < 0x20
					&& *(unsigned char *)p != *(unsigned char *)&separator )
				p++;
		}
		else
		{
			*out = *p;
			out++;
			p++;
		}
	}

	*out = 0;
}

// 0x007EC030 DELETES A TAG FROM A RECORD, in place, and the four walks are the
// whole body.  The lookup gives it the value; from there it walks BACK to the
// start of the name -- stopping at the record's start or at the first byte at
// or below 0x20 -- then FORWARD past the value and past the control run that
// ends it, then copies everything that is left down over the hole, then trims
// trailing whitespace off what it produced.
//
// SO THE SEPARATOR IS NEVER SEARCHED FOR AGAIN.  The name's extent is found by
// scanning outward from the value the lookup already returned, which is why
// this needs no second parse and why deleting a tag whose name contains a space
// would leave part of it behind.
//
// A tag that is not there is -1 and nothing is touched; anything else is 0.
// There is no way to tell how much was removed.
int Rva007EC030( char *text, const char *tag )
{
	char *value;
	char *out;
	char *p;
	char *start;

	start = text;

	value = Rva007EBCA0( start, tag );
	if( value == 0 )
		return -1;

	for( out = value; out != start
			&& *(unsigned char *)( out - 1 ) > 0x20; out-- )
		;

	for( p = value; *(unsigned char *)p >= 0x20; p++ )
		;

	while( *(unsigned char *)p > 0 && *(unsigned char *)p < 0x20 )
		p++;

	while( *(unsigned char *)p != 0 )
	{
		*out = *p;
		out++;
		p++;
	}

	while( out != start && *(unsigned char *)( out - 1 ) <= 0x20 )
		out--;

	*out = 0;
	return 0;
}

// 0x007EC2E0 RETURNS THE FIRST TAG'S NAME.  It scans for the first separator,
// walks BACK from it to where the name starts -- the record's start, or the
// first byte at or below 0x20 -- and then copies forward from there to the
// separator.  Same outward-from-the-separator trick 0x007EC030 uses to delete
// one, and it stops at the same structural record terminator.
//
// THE DESTINATION IS CLEARED BEFORE ANYTHING ELSE, but only when the caller
// gave a positive size -- so a size of zero leaves the buffer untouched rather
// than being treated as an error, and a null or empty record then returns 0
// with the buffer already emptied.
//
// TWO OF THE THREE EXITS DO NOT TERMINATE THE BUFFER.  Running off the end of
// the record and hitting the record terminator both return the count as it
// stands, leaving whatever the initial clear left; only the successful copy
// writes a terminator.  Since the count is 0 on both of those paths and the
// clear already wrote a zero, the result is still a valid empty string -- which
// is why the omission is invisible rather than a bug.
//
// The copy bound is `written + 1 < destSize`, so one byte is always held back.
//
// BOTH EXITS FROM THE LOOP ARE `break`, NOT `return`.  Retail jumps to a single
// shared `mov eax,written` at the end; writing either as its own return loads
// the count again before jumping, three bytes retail does not have.
int Rva007EC2E0( const char *text, char *dest, int destSize )
{
	int written;
	const char *p;
	const char *q;
	const char *start;

	written = 0;
	start = text;

	if( destSize > 0 )
		*dest = 0;

	if( start == 0 || *(unsigned char *)start == 0 )
		return 0;

	for( p = start; *(unsigned char *)p != 0; p++ )
	{
		if( *(unsigned char *)p != '=' && *(unsigned char *)p != ':' )
			continue;

		if( *(unsigned char *)( p + 1 ) < 0x20
				&& *(unsigned char *)( p - 1 ) <= 0x20 )
			break;

		for( q = p; q != start
				&& *(unsigned char *)( q - 1 ) > 0x20; q-- )
			;

		while( q != p && written + 1 < destSize )
		{
			dest[ written ] = *q;
			written++;
			q++;
		}

		dest[ written ] = 0;
		break;
	}

	return written;
}

// Twenty-four letters, one per bit, in bit order from the least significant.
// A terminator in the table is what bounds the loop below, so the table's own
// length is the number of flags this can name -- nothing else limits it.
extern char g_Rva0112A410FlagLetters[];

// Rva007EC780 lives in Y4TextToValue.c, which is C.  The two halves of this
// module ended up split across a .c and a .cpp by two different lanes; the
// declaration has to say so or the call will not link.
extern "C" int Rva007EC780( unsigned char *buffer, int size, const char *field );

// 0x007ECAF0 NAMES A BIT MASK IN LETTERS and stores it as a field.  Bit zero
// takes the first letter of the table, bit one the second, and set bits
// contribute their letter in order -- so the value reads back as the flags it
// stands for rather than as a number.
//
// THE LOOP ENDS ON EITHER EXHAUSTION, and that asymmetry matters.  It stops
// when the remaining mask is zero OR when the table runs out, so bits above
// the table's length are DISCARDED SILENTLY: the field is written, the call
// reports success, and the information is simply gone.
//
// THE SHIFT IS ARITHMETIC, so a mask with its top bit set never empties -- it
// shifts in ones forever.  The table terminator is the only thing that stops
// it, which makes the table's length load-bearing rather than incidental.
int Rva007ECAF0( char *record, int size, const char *name, int flags )
{
	char *p;
	const char *pLetter;
	char strField[ 0x120 ];

	p = Rva007EC730( record, strField, name );

	for( pLetter = g_Rva0112A410FlagLetters;
		flags != 0 && *pLetter != 0; flags >>= 1, pLetter++ )
	{
		if( ( flags & 1 ) != 0 )
		{
			*p = *pLetter;
			p++;
		}
	}

	*p = 0;

	return Rva007EC780( ( unsigned char * )record, size, strField );
}

// 0x007ECD90 IS THE INVERSE OF THE FOUR-CHARACTER TAG PACKER at 0x007EE8B0,
// and it shares that function's convention exactly: a tag is four printable
// bytes in an int, left-padded with SPACES rather than zeros.
//
// THE PADDING IS SKIPPED BY THE SAME SIGNED BOUND THE PACKER USED.  A value
// whose top byte is a space or lower compares at or below 0x20FFFFFF, so the
// byte is dropped and the value shifts on; the first byte above that bound
// begins the text.  ONE CONSEQUENCE IS THAT THE SKIPPING IS NOT ONLY LEADING:
// a space in the MIDDLE of a tag is dropped too, so a tag written with an
// interior space does not survive a round trip through the pair.
//
// THE LOOP CANNOT RUN AWAY because the shift is left and unsigned in effect --
// four shifts of eight empty any int -- so the four-byte limit is a property
// of the width rather than a counter, exactly as it is in the packer.
int Rva007ECD90( char *record, int size, const char *name, int value )
{
	char *p;
	char strField[ 0x120 ];

	p = Rva007EC730( record, strField, name );

	for( ; value != 0; value <<= 8 )
	{
		if( value > 0x20FFFFFF )
		{
			*p = ( char )( value >> 24 );
			p++;
		}
	}

	*p = 0;

	return Rva007EC780( ( unsigned char * )record, size, strField );
}

// Mirrors the definition in Y4CivilTime.c, which is C.  Duplicated rather than
// shared because the module is split across two translation units and two
// languages; the layout is struct tm and both halves agree on it.
struct Rva007EDB10Time
{
	int m_second; int m_minute; int m_hour;
	int m_day; int m_month; int m_year;
	int m_weekday; int m_yearDay; int m_isDst;
};

extern "C" struct Rva007EDB10Time *Rva007EDB10(
	struct Rva007EDB10Time *pTime, unsigned int uSeconds );
extern "C" unsigned int Rva007FEF60( void );

// "%d.%d.%d %d:%02d:%02d" -- in writable data rather than among the literals,
// so the stored format is configurable at run time.  Note the asymmetry it
// carries: the DATE fields are unpadded and the CLOCK fields after the first
// are zero-padded, so the text is not fixed width and cannot be sorted as a
// string even though it starts with the year.
extern char g_Rva012C3938Format[];

// Declared without the CRT header on purpose: under /MD that header marks
// sprintf dllimport and the call becomes an indirect through the IAT, where
// retail calls the import stub directly.
extern "C" int __cdecl sprintf( char *dest, const char *format, ... );

// 0x007ED9F0 STORES A TIMESTAMP AS A HUMAN-READABLE DATE FIELD.
//
// A ZERO TIMESTAMP MEANS NOW.  There is no separate entry point for "stamp
// this with the current time" -- passing zero is the way to ask, which also
// means the epoch second cannot be stored through this function.  That is the
// same convention the parser at 0x007EF780 arrived at from the other side, and
// neither of them says so in its signature.
//
// THE OUTPUT IS UNBOUNDED IN PRINCIPLE AND SAFE IN PRACTICE ONLY BY ARITHMETIC.
// sprintf writes into the tail of a 288-byte local after the name and its
// separator, with no size passed; nothing here checks that the name left room.
// A name approaching the buffer's length would overflow it, and the /GS cookie
// this function carries is the only thing that would notice.
//
// The two human-facing adjustments -- year plus 1900, month plus one -- appear
// here for the third time in this module rather than being shared, which keeps
// every outward-facing function independent of the others.
int Rva007ED9F0( char *record, int size, const char *name, unsigned int uWhen )
{
	struct Rva007EDB10Time *ptm;
	struct Rva007EDB10Time tm2;
	char *pDest;
	unsigned int uTime;
	char item[ 0x120 ];

	uTime = uWhen;

	if( uTime == 0 )
	{
		uTime = Rva007FEF60();
	}

	ptm = Rva007EDB10( &tm2, uTime );

	if( ptm == 0 )
	{
		return -1;
	}

	pDest = Rva007EC730( record, item, name );

	sprintf( pDest, g_Rva012C3938Format,
		ptm->m_year + 1900, ptm->m_month + 1, ptm->m_day,
		ptm->m_hour, ptm->m_minute, ptm->m_second );

	return Rva007EC780( ( unsigned char * )record, size, item );
}

extern "C" unsigned int Rva007EDE00( const struct Rva007EDB10Time *pTime );
extern "C" void * __cdecl memset( void *dest, int c, unsigned int count );

// 0x007EE050 STORES A PACKED DATE AND TIME AS A DATE FIELD.  It is the mirror
// of the reader at 0x007EFC20: that one parses text and hands back two packed
// integers, this one takes two packed integers and writes the text.
//
// THE ROUND TRIP IS NOT SYMMETRIC, though, and the packing is where it shows.
// The date field is unpacked with a SIXTEEN-BIT year but an EIGHT-BIT month
// and day, and the clock with three eight-bit fields -- so this accepts values
// the reader can never have produced, and truncates rather than rejecting
// them.  A day of 300 becomes 44 with no complaint anywhere.
//
// THE ADJUSTMENTS RUN THE OTHER WAY HERE, year less 1900 and month less one,
// converting the human numbering back to the C one.  That is the fourth
// appearance of the pair in this module and the second in this direction.
//
// THE OFFSET IS SUBTRACTED, NOT ADDED, matching the reader that adds it -- and
// only when the conversion succeeded, so a zero result stays zero and is then
// read one level down as "use the current time".  A DATE THAT CONVERTS TO THE
// EPOCH THEREFORE STORES AS NOW rather than as 1970, which is the same blind
// spot the rest of this chain has, arrived at from a third direction.
int Rva007EE050( char *record, int size, const char *name,
	int iDate, int iTime, int iOffset )
{
	struct Rva007EDB10Time tm;
	unsigned int uTime;

	memset( &tm, 0, sizeof( tm ) );
	tm.m_isDst = -1;

	tm.m_year = ( ( iDate >> 16 ) & 0xFFFF ) - 1900;
	tm.m_month = ( ( iDate >> 8 ) & 0xFF ) - 1;
	tm.m_day = iDate & 0xFF;
	tm.m_hour = ( iTime >> 16 ) & 0xFF;
	tm.m_minute = ( iTime >> 8 ) & 0xFF;
	tm.m_second = iTime & 0xFF;

	uTime = Rva007EDE00( &tm );

	if( uTime != 0 )
	{
		uTime -= iOffset;
	}

	return Rva007ED9F0( record, size, name, uTime );
}

// 0x007EDD30 IS THE FIELD-WISE WRITER, taking six separate components where
// 0x007EE050 takes two packed integers.  With it the module's date interface
// closes into a FOUR-WAY SYMMETRY: read packed (0x007EFC20), read field-wise
// (0x007EFB20), write packed (0x007EE050), write field-wise (this).  All four
// are independent -- none is written in terms of another -- which is why the
// year and month adjustments appear in every one of them.
//
// THIS IS THE ONLY ONE OF THE FOUR THAT CANNOT TRUNCATE.  Its components
// arrive as full ints rather than through eight-bit fields, so it is the only
// path by which a caller can supply a value that the packed forms could not
// represent, and equally the only one that will not silently mangle one.  What
// it does instead is hand the value to a search that has no not-found exit, so
// an out-of-range component does not truncate here -- it fails further down.
int Rva007EDD30( char *record, int size, const char *name,
	int iYear, int iMonth, int iDay, int iHour, int iMinute, int iSecond,
	int iOffset )
{
	struct Rva007EDB10Time tm;
	unsigned int uTime;

	memset( &tm, 0, sizeof( tm ) );
	tm.m_isDst = -1;

	tm.m_year = iYear - 1900;
	tm.m_month = iMonth - 1;
	tm.m_day = iDay;
	tm.m_hour = iHour;
	tm.m_minute = iMinute;
	tm.m_second = iSecond;

	uTime = Rva007EDE00( &tm );

	if( uTime != 0 )
	{
		uTime -= iOffset;
	}

	return Rva007ED9F0( record, size, name, uTime );
}

// Two 256-entry tables, adjacent in data, giving the FIRST and SECOND
// character of each byte's hex pair.  Two tables rather than one nibble table
// indexed twice, so neither the shift nor the mask appears anywhere.
extern char g_Rva01129E10HexFirst[];
extern char g_Rva01129F10HexSecond[];

// 0x007ED0E0 STORES A BLOCK OF BYTES AS A HEXADECIMAL FIELD, prefixed with the
// dollar sign that the value parser at 0x007EF780 reads as "this is hex".  The
// two ends of that convention are in different translation units and neither
// names the other; the marker is all they share.
//
// THE BUFFER IS EIGHT KILOBYTES ON THE STACK, large enough that MSVC emits a
// stack probe before the frame is even established.  That caps a field at
// something under 4096 input bytes, and the limit is enforced -- but by
// ARITHMETIC ON THE BUFFER RATHER THAN ON THE ARGUMENT: it measures how much
// of the buffer the name already consumed and compares the remainder against
// two characters per byte plus a terminator.  So the maximum count depends on
// the length of the name, and no constant anywhere states it.
//
// THE CHECK IS UNSIGNED, which matters more than it looks.  A negative count
// makes the left side wrap to an enormous value, so it fails the test and
// returns -1 rather than running the loop backwards.  That is a real guard
// rather than an accident of the loop bound, which would also have stopped it.
int Rva007ED0E0( char *record, int size, const char *name,
	const unsigned char *src, int count )
{
	char *p;
	char item[ 0x2100 ];
	const unsigned char *pSrc;

	pSrc = src;

	p = Rva007EC730( record, item, name );

	*p = '$';
	p++;

	if( count * 2 + 1 > sizeof( item ) - ( p - item ) )
	{
		return -1;
	}

	while( count > 0 )
	{
		*p = g_Rva01129E10HexFirst[ *pSrc ];
		p++;
		*p = g_Rva01129F10HexSecond[ *pSrc ];
		p++;
		pSrc++;
		count--;
	}

	*p = 0;

	return Rva007EC780( ( unsigned char * )record, size, item );
}

extern "C" int Rva007ED360( unsigned char *dest, int destSize,
	const unsigned char *src, int count );

// 0x007ED220 IS THE OTHER BINARY FIELD FORMAT, and putting it beside the hex
// one at 0x007ED0E0 shows the module carries TWO encodings for the same job,
// distinguished by a single marker character: a dollar sign for hex, a caret
// for seven-bit packing.  Hex costs two characters per byte and is readable;
// the packed form costs eight sevenths and is not.  Nothing chooses between
// them here -- the caller does, by picking a function.
//
// THE GUARD HAS TWO PARTS AND NEITHER SUBSUMES THE OTHER.  The size test is
// unsigned, so it catches a count large enough to overflow the buffer; the
// separate negative test is needed because a small negative count produces a
// SMALL positive size estimate rather than a wrapped one, and would sail
// through.  The hex writer needs only one test because its estimate is a
// plain doubling, which does wrap.
//
// THE ENCODER IS ALSO GIVEN THE REMAINING SPACE, so the length is checked
// twice by two different calculations -- once here from the ceiling formula
// and once inside from the same formula.  They agree, which makes the second
// check dead, but the encoder cannot know that and neither can this.
int Rva007ED220( char *record, int size, const char *name,
	const unsigned char *src, int count )
{
	char *p;
	char item[ 0x2100 ];
	const unsigned char *pSrc;
	int iWritten;

	pSrc = src;

	p = Rva007EC730( record, item, name );

	*p = '^';
	p++;

	if( ( count * 8 + 6 ) / 7 + 1 > sizeof( item ) - ( p - item ) || count < 0 )
	{
		return -1;
	}

	iWritten = Rva007ED360( ( unsigned char * )p,
		sizeof( item ) - ( p - item ), pSrc, count );

	if( iWritten < 0 )
	{
		return -1;
	}

	p += iWritten;
	*p = 0;

	return Rva007EC780( ( unsigned char * )record, size, item );
}

// 0x007EC5C0 STORES A SIGNED DECIMAL AS A FIELD, without sprintf and without
// a separate scratch buffer.
//
// THE DIGITS ARE BUILT BACKWARDS INTO THE SAME BUFFER, THIRTY-TWO BYTES AHEAD
// of where they will end up, and then copied forward over themselves.  That
// works because the copy advances one byte for every digit while the source
// starts at least twenty-one bytes ahead of it, so the write cursor can never
// overtake the read cursor -- an invariant of the arithmetic, not something
// any line here checks.  NOTHING CHECKS THE FAR END EITHER: a name landing
// within thirty-two bytes of the buffer's end puts the scratch past it.
//
// THE ACCUMULATOR IS UNSIGNED AND THAT IS WHAT MAKES INT_MIN WORK.  Negating
// the most negative int overflows as a signed value but lands exactly on
// 0x80000000 when the result is unsigned, so the loop produces the right ten
// digits.  A signed accumulator would have looped forever or printed nothing.
//
// ZERO IS HANDLED AFTER THE FACT rather than as a special case up front: the
// loop writes no digits at all, and the check that follows notices the
// terminator is still where it started and backs up one byte to write a '0'.
int Rva007EC5C0( char *record, int size, const char *name, int value )
{
	char *p;
	unsigned char *pDigit;
	char item[ 0x120 ];
	unsigned int uValue;

	p = Rva007EC730( record, item, name );

	if( value < 0 )
	{
		*p = '-';
		p++;
		uValue = -value;
	}
	else
	{
		uValue = value;
	}

	pDigit = ( unsigned char * )p + 32;

	pDigit--;
	*pDigit = 0;

	while( uValue > 0 )
	{
		pDigit--;
		*pDigit = uValue % 10 + '0';
		uValue = uValue / 10;
	}

	if( *pDigit == 0 )
	{
		pDigit--;
		*pDigit = '0';
	}

	while( *pDigit != 0 )
	{
		*p = *pDigit;
		p++;
		pDigit++;
	}

	*p = 0;

	return Rva007EC780( ( unsigned char * )record, size, item );
}

extern "C" unsigned int __cdecl strlen( const char *text );

// 0x007EC130 RENAMES A FIELD IN PLACE, keeping its value and resizing the
// record around the new name.  It finds the field with the backwards matcher
// at 0x007EBCA0, walks back over the old name, shifts the rest of the record
// by the difference in name lengths, and writes the new name over the old.
//
// TWO OF ITS THREE PATHS DO NOT WORK, and both are visible only in the bytes.
// This is written as retail has it, not as it was meant.
//
// THE SHRINK LOOP NEVER ADVANCES ITS CURSOR.  Where the grow path steps its
// pointer each iteration, this one reads and writes through the SAME
// unchanging pointer, so it copies one byte to one place forever unless the
// value was already empty.  A rename to a SHORTER name hangs.  The line after
// it compounds the slip by terminating at the old position rather than the
// shifted one, which would have left the record a byte long even if the loop
// had ended.
//
// THE GROW GUARD IS INVERTED with respect to the fit test every other writer
// in this module uses.  It proceeds when the record length is at least the
// capacity less the growth -- that is, when the result will NOT fit -- and
// returns -1 when it will.  So growing a name succeeds only in the cases that
// overflow, and fails in the cases that are safe.
//
// The rename itself, the walk and the matcher are all sound; it is only the
// two resize paths.  A caller renaming to a name of the SAME length skips both
// and works correctly, which is presumably why this survived.
int Rva007EC130( unsigned char *record, int size, const char *oldName,
	const char *newName )
{
	int iDelta;
	unsigned char *pValue;
	unsigned char *pName;
	unsigned char *pEnd;
	unsigned char *pRecord;

	pRecord = record;

	pValue = ( unsigned char * )Rva007EBCA0( ( const char * )pRecord, oldName );

	if( pValue == 0 )
	{
		return -1;
	}

	if( pValue[ -1 ] == ' ' )
	{
		pValue--;
	}

	pValue--;

	// An empty-bodied for, not a while: retail steps the cursor in the
	// increment clause, which puts the decrement BEFORE the test in the
	// listing.  A while with the decrement in its body reverses those two
	// blocks and costs two bytes.
	for( pName = pValue; pName != pRecord && pName[ -1 ] > ' '; pName-- )
	{
	}

	iDelta = strlen( newName ) - ( pValue - pName );

	if( iDelta < 0 )
	{
		while( *pValue != 0 )
		{
			pValue[ iDelta ] = *pValue;
		}

		*pValue = 0;
	}

	if( iDelta > 0 )
	{
		for( pEnd = pValue; *pEnd != 0; pEnd++ )
		{
		}

		if( pEnd - pRecord < size - iDelta )
		{
			return -1;
		}

		for( ; pEnd != pValue; pEnd-- )
		{
			pEnd[ iDelta ] = *pEnd;
		}
	}

	while( *newName != 0 )
	{
		*pName = *newName;
		pName++;
		newName++;
	}

	return 0;
}

// 0x007ECBE0 STORES AN ADDRESS AS A DOTTED QUAD.  The four bytes are pulled
// off the LOW end of the value and stored HIGHEST-INDEX FIRST, so the array
// ends up in printing order and the loop that follows can simply walk it
// forwards.  The byte order is therefore fixed here and nowhere else: the
// caller hands over a host-order integer and never sees the convention.
//
// THE DIGITS ARE PEELED, NOT DIVIDED DOWN.  Each segment tests against 9 and
// 99 to decide how many digits it has, then emits them most-significant first
// -- so there is no reversal step and no scratch buffer, unlike the decimal
// writer at 0x007EC5C0 which builds backwards.  Two number formatters a few
// hundred bytes apart, two different strategies, because this one knows its
// values are at most three digits and that one does not.
//
// THERE IS NO LENGTH CHECK ANYWHERE.  A dotted quad is at most fifteen
// characters, so it fits after any reasonable name -- but "reasonable" is the
// whole argument, and nothing enforces it.  The hex and packed writers in this
// module both check; this one does not.
int Rva007ECBE0( char *record, int size, const char *name, unsigned int value )
{
	int i;
	unsigned char c;
	char *p;
	unsigned char seg[ 4 ];
	char item[ 0x120 ];

	p = Rva007EC730( record, item, name );

	seg[ 3 ] = ( unsigned char )value;
	value >>= 8;
	seg[ 2 ] = ( unsigned char )value;
	value >>= 8;
	seg[ 1 ] = ( unsigned char )value;
	value >>= 8;
	seg[ 0 ] = ( unsigned char )value;

	for( i = 0; i < 4; i++ )
	{
		c = seg[ i ];

		if( i > 0 )
		{
			*p = '.';
			p++;
		}

		if( c > 9 )
		{
			if( c > 99 )
			{
				*p = c / 100 + '0';
				p++;
				c = c % 100;
			}

			*p = c / 10 + '0';
			p++;
			c = c % 10;
		}

		*p = c + '0';
		p++;
	}

	*p = 0;

	return Rva007EC780( ( unsigned char * )record, size, item );
}

// 0x007ECE60 STORES A STRING AS A FIELD, escaping whatever would confuse the
// record format and quoting the whole thing if it contains a space.  It is the
// general-purpose writer the typed ones above are specialisations of.
//
// A NULL VALUE DELETES THE FIELD and returns SUCCESS.  There is no separate
// remove entry point -- passing null is how you ask -- so this cannot store a
// null and a caller cannot tell "removed" from "written" by the return value.
//
// SEVEN CHARACTERS ARE ESCAPED AS %XX and the set is exactly the record
// syntax: control characters and DEL, the two delimiters '=' and ':', the
// quote that this function may add itself, the '%' that introduces an escape,
// and the '^' that marks a packed binary field elsewhere in this module.  The
// '$' of a hex field is NOT escaped, which is safe only because a hex field is
// recognised by position rather than by scanning.
//
// THE QUOTE DECISION IS MADE BEFORE THE COPY AND RE-READ AFTER IT, through a
// pointer that survives the whole loop -- the opening and closing quotes are
// therefore decided by the same test rather than by a flag, which is why the
// scan pointer is a local rather than a boolean.
//
// THE BUDGET GOES NEGATIVE DELIBERATELY.  An escape that does not fit is
// skipped but STILL CHARGED three, so the counter records the overrun rather
// than saturating, and the check after the loop turns any overrun into -1.
// Truncated output is never handed back as success -- but note the field has
// already been partially written into the record buffer by then.
int Rva007ECE60( char *record, int size, const char *name, const char *value )
{
	char *p;
	const unsigned char *pScan;
	const unsigned char *pSrc;
	char item[ 0x1200 ];
	int iLeft;

	pSrc = ( const unsigned char * )value;
	iLeft = sizeof( item );

	if( pSrc == 0 )
	{
		Rva007EC030( record, name );
		return 0;
	}

	p = Rva007EC730( record, item, name );

	iLeft -= p - item;

	for( pScan = pSrc; *pScan != 0 && *pScan != ' '; pScan++ )
	{
	}

	if( *pScan == ' ' )
	{
		*p = '"';
		p++;
		iLeft--;
	}

	for( ; *pSrc != 0 && iLeft > 0; pSrc++ )
	{
		if( *pSrc < ' ' || *pSrc == 0x7F || *pSrc == '=' || *pSrc == '"'
			|| *pSrc == ':' || *pSrc == '%' || *pSrc == '^' )
		{
			if( iLeft >= 3 )
			{
				*p = '%';
				p++;
				*p = g_Rva01129E10HexFirst[ *pSrc ];
				p++;
				*p = g_Rva01129F10HexSecond[ *pSrc ];
				p++;
			}

			iLeft -= 3;
		}
		else
		{
			*p = *pSrc;
			p++;
			iLeft--;
		}
	}

	if( iLeft <= 0 )
	{
		return -1;
	}

	if( *pScan == ' ' )
	{
		if( iLeft <= 0 )
		{
			return -1;
		}

		*p = '"';
		p++;
	}

	if( iLeft <= 0 )
	{
		return -1;
	}

	*p = 0;

	return Rva007EC780( ( unsigned char * )record, size, item );
}

// The fallback key, two bytes, "GS".  It sits four bytes before the date
// format string and immediately after the "~~=\n" suffix, so the whole of this
// module's configurable data is one small run of writable bytes.
extern unsigned char g_Rva012C3934DefaultKey[];

// 0x007ED850 STORES AN OBSCURED STRING AS A HEX FIELD.  It is NOT a plain XOR:
// each output byte is fed back into the next, so the stream is chained and one
// changed input byte changes everything after it.
//
// THE TRANSFORM IS ROTATE-THEN-XOR.  The plaintext byte is combined with the
// previous output, the result is rotated left by three, and the key byte is
// mixed in; that becomes both the emitted byte and the feedback for the next
// round.  The rotate is written as a shift pair with a mask that cannot
// matter -- an eight-bit value shifted right by five is already under eight --
// so the AND is belt-and-braces in the original rather than a real bound.
//
// THE KEY IS WEAK BY CONSTRUCTION AND THAT IS VISIBLE HERE.  It wraps at its
// own terminator, and the default is TWO BYTES, so the key period is two.  A
// null or empty key silently becomes the default rather than being refused,
// which means a caller that forgets to supply one still gets ciphertext-looking
// output and no indication that it is barely obscured.  This is obfuscation,
// not encryption, and nothing in the signature says so.
//
// THERE IS NO LENGTH CHECK.  Output is two characters per input byte into a
// buffer of 0x2100, after the name, and nothing compares the two.  The hex
// writer at 0x007ED0E0 takes a count and checks it; this one takes a
// NUL-terminated string and does not.
int Rva007ED850( char *record, int size, const char *name,
	const unsigned char *key, const unsigned char *src )
{
	unsigned char cCarry;
	unsigned char cMix;
	char *p;
	const unsigned char *pKey;
	char item[ 0x2100 ];
	const unsigned char *pKeyStart;
	const unsigned char *pSrc;

	pKeyStart = key;
	pSrc = src;

	if( pKeyStart == 0 || *pKeyStart == 0 )
	{
		pKeyStart = g_Rva012C3934DefaultKey;
	}

	p = Rva007EC730( record, item, name );

	*p = '$';
	p++;

	cCarry = 0;
	pKey = pKeyStart;

	for( ; *pSrc != 0; pSrc++ )
	{
		cMix = *pSrc ^ cCarry;
		cCarry = ( ( cMix << 3 ) | ( ( cMix >> 5 ) & 7 ) ) ^ *pKey;
		pKey++;

		if( *pKey == 0 )
		{
			pKey = pKeyStart;
		}

		*p = g_Rva01129E10HexFirst[ cCarry ];
		p++;
		*p = g_Rva01129F10HexSecond[ cCarry ];
		p++;
	}

	*p = 0;

	return Rva007EC780( ( unsigned char * )record, size, item );
}

extern unsigned char g_Rva0112A310Class[];

// 0x007ED470 SERIALISES A BINARY BUFFER INTO A FIELD UNDER A FORMAT STRING.
// It is the general case the typed writers in this module are shortcuts for:
// a tiny interpreter over the data, emitting comma-separated values.
//
// THE DIRECTIVES ARE 'a' 'b' 'w' 'l' 's', optionally preceded by a decimal
// count, with '#' introducing a comment run and '*' meaning REPEAT.  The
// repeat works by stepping the format pointer BACK one, so the previous
// directive runs again on the next pass -- it is bounded by the DATA, not by
// the format, and a format ending in '*' consumes the buffer to its end.
//
// A NEGATIVE LENGTH MEANS 64K, not "unbounded" and not an error, so a caller
// who does not know the size gets a fixed ceiling rather than a refusal.
//
// NUMBERS ARE RIGHT-ALIGNED IN A FIXED NIBBLE FIELD AND THEN CLOSED UP, which
// is what the terminator-at-the-top and the copy-down are for.  THE EXACT-FIT
// CASE SKIPS THE SEPARATOR: when a value uses every nibble of its width the
// digits are already in place, the pointer is simply advanced, and the comma
// that every other path appends is never written.  A full-width value is
// therefore run together with whatever follows it.
//
// THE NEGATIVE TEST IS A MAGNITUDE TEST, not a sign bit.  Only values above
// 0xFFFF0000 print with a minus, so a 32-bit value that is negative as an int
// but smaller in magnitude than 65536 prints as a large positive number.  That
// is consistent for the 'w' and 'b' widths, which cannot reach the threshold
// at all, and inconsistent for 'l'.
//
// STRINGS ARE ESCAPED THROUGH THE CHARACTER-CLASS TABLE, the same one the
// field matcher uses, so what counts as safe here is defined by the record
// syntax rather than by this function.
//
// TRAILING SEPARATORS ARE STRIPPED IN A LOOP at the end, which is the only
// thing that keeps a format whose last directive produced nothing from leaving
// a dangling comma.
int Rva007ED470( char *record, int size, const char *name,
	const unsigned char *data, int length, const char *format )
{
	int iWidth;
	int iCount;
	char *pDigit;
	char *p;
	unsigned int uValue;
	const unsigned char *pString;
	const unsigned char *pData;
	const unsigned char *pEnd;
	char item[ 0x1200 ];

	uValue = 0;
	pData = data;

	pEnd = ( length < 0 ) ? pData + 0x10000 : pData + length;

	p = Rva007EC730( record, item, name );

	while( *format != 0 )
	{
		if( pData >= pEnd )
		{
			break;
		}

		if( *format == '#' )
		{
			format++;

			while( *format != 0 && ( *format++ != '=' ) != 0 )
			{
			}
		}

		for( iCount = 0; *format >= '0' && *format <= '9'; format++ )
		{
			iCount = iCount * 10 + ( *format & 0xF );
		}

		iWidth = 0;
		pString = 0;

		if( *format == 'a' )
		{
			pData += ( iCount != 0 ) ? iCount : 1;
		}

		if( *format == 'b' )
		{
			uValue = *pData;
			iWidth = 2;
			pData += 1;
		}

		if( *format == 'w' )
		{
			uValue = *( const unsigned short * )pData;
			iWidth = 4;
			pData += 2;
		}

		if( *format == 'l' )
		{
			uValue = *( const unsigned int * )pData;
			iWidth = 8;
			pData += 4;
		}

		if( *format == 's' )
		{
			pString = pData;
			pData += iCount;
		}

		if( iWidth > 0 )
		{
			if( uValue > 0xFFFF0000 )
			{
				uValue = -uValue;
				*p = '-';
				p++;
			}

			pDigit = p + iWidth + 1;
			pDigit--;
			*pDigit = 0;

			while( uValue != 0 )
			{
				pDigit--;
				*pDigit = g_Rva01129F10HexSecond[ uValue & 0xF ];
				uValue >>= 4;
			}

			if( p == pDigit )
			{
				p += iWidth;
			}
			else
			{
				while( *pDigit != 0 )
				{
					*p = *pDigit;
					p++;
					pDigit++;
				}

				*p = ',';
				p++;
			}
		}

		if( pString != 0 )
		{
			while( *pString != 0 )
			{
				uValue = *pString;
				pString++;

				if( g_Rva0112A310Class[ uValue ] > 1 )
				{
					*p = ( char )uValue;
					p++;
				}
				else
				{
					*p = '%';
					p++;
					*p = g_Rva01129E10HexFirst[ uValue ];
					p++;
					*p = g_Rva01129F10HexSecond[ uValue ];
					p++;
				}
			}

			*p = ',';
			p++;
		}

		format++;

		if( *format == '*' )
		{
			format--;
		}
	}

	while( p[ -1 ] == ',' )
	{
		p--;
	}

	*p = 0;

	return Rva007EC780( ( unsigned char * )record, size, item );
}

#include <stdarg.h>

// A run of field names in UNINITIALISED data.  There are no bytes for it in
// the image -- the address lands past the raw .data, so the names are written
// at run time and CANNOT BE RECOVERED STATICALLY.  Every reference to them is
// a DIR32 whose operand comes from retail, so the bytes match regardless of
// what this symbol is called or what it eventually holds; the offsets below
// are the only thing that is real.
extern char g_Rva0130A5A4Names[];

// The configurable separator, also used by the record engine in Y4TextToValue.c
// -- one byte of writable data shared across the seam between the two halves of
// this module.
extern char g_Rva012C391CSeparator;

// 0x007EE280 BUILDS A RECORD FROM A FORMAT STRING AND VARARGS, dispatching
// each directive to the typed writer for it.  It is the top of this module:
// everything else converted here is something this can call.
//
// THE DIRECTIVE LETTERS MAP ONE TO ONE ONTO THE WRITERS -- 's' to the escaped
// string writer, 'd' to the decimal one, 'a' to the dotted quad, 'f' to the
// flag letters, 'e' to the timestamp.  The FIELD NAME does not come from the
// format; each writer is handed a fixed name out of the table above, so the
// format decides only the TYPE and the caller cannot name a field through it.
//
// TWO DIRECTIVES ARE NOT WRITERS AT ALL.  'i' takes a pointer and stores it as
// the SOURCE RECORD for later use, writing nothing; 'x' then looks a field up
// in that source and copies it across verbatim, falling back to a placeholder
// pair from the same table when the lookup fails.  So a format can splice
// fields out of one record into another, and the 'i' that arms it may appear
// anywhere before the 'x' that uses it.
//
// WHITESPACE IN THE FORMAT MEANS "SEPARATOR", not a space: any character at or
// below a space emits the configured separator byte and then swallows the
// whole run that follows, so the format is free-form and its own layout does
// not reach the output.
//
// AN '=' ALREADY WRITTEN IS BACKED OVER before each directive, which is what
// lets the writers append their own name and delimiter without the caller
// having to know whether one is already there.
//
// THE RETURN IS BYTES WRITTEN, computed as the difference between the size on
// entry and the size left -- so it counts what the writers consumed as well as
// what this function emitted directly.
int Rva007EE280( char *record, int size, const char *format, ... )
{
	int iResult;
	va_list args;
	unsigned char c;
	int iSize;
	const char *pSource;
	const char *pString;
	int iValue;
	unsigned int uAddress;
	int iFlags;
	unsigned int uWhen;
	const char *pName;
	const char *pFound;
	const char *pRaw;

	iSize = size;
	pSource = g_Rva0130A5A4Names;

	va_start( args, format );

	// THE INNER != 0 IS LOAD-BEARING.  Retail materialises the fetch-and-test
	// into a 1 or a 0 in a stack temporary and then tests THAT, which is the
	// shape a comparison-of-a-comparison produces; the single-comparison form
	// branches directly and loses five instructions and a frame slot.
	while( ( ( c = *format++ ) != 0 ) != 0 && size > 1 )
	{
		if( c <= ' ' )
		{
			*record = g_Rva012C391CSeparator;
			record++;
			size--;

			while( *format != 0 && *format <= ' ' )
			{
				format++;
			}
		}
		// AN ELSE-IF CHAIN, NOT THREE GUARDS WITH CONTINUES.  All three arms
		// converge on the end of the loop body and the back edge is there, so
		// each arm ends in a FORWARD jump.  Written as separate ifs with
		// continues, each arm jumps BACKWARD to the top instead -- same
		// behaviour, different displacement, and the only thing that tells
		// the two apart is the sign of that jump.
		else if( c != '%' )
		{
			*record = c;
			record++;
			size--;
		}
		else if( *format != 0 )
		{

			iResult = 0;
			c = *format;
			format++;

			if( record[ -1 ] == '=' )
			{
				record--;
				size++;
			}

			*record = 0;

			if( c == 's' )
			{
				pString = va_arg( args, const char * );
				iResult = Rva007ECE60( record, size, &g_Rva0130A5A4Names[ 1 ],
					pString );
			}
			else if( c == 'd' )
			{
				iValue = va_arg( args, int );
				iResult = Rva007EC5C0( record, size, &g_Rva0130A5A4Names[ 2 ],
					iValue );
			}
			else if( c == 'a' )
			{
				uAddress = va_arg( args, unsigned int );
				iResult = Rva007ECBE0( record, size, &g_Rva0130A5A4Names[ 3 ],
					uAddress );
			}
			else if( c == 'f' )
			{
				iFlags = va_arg( args, int );
				iResult = Rva007ECAF0( record, size, &g_Rva0130A5A4Names[ 4 ],
					iFlags );
			}
			else if( c == 'e' )
			{
				uWhen = va_arg( args, unsigned int );
				iResult = Rva007ED9F0( record, size, &g_Rva0130A5A4Names[ 5 ],
					uWhen );
			}
			else if( c == 'i' )
			{
				pSource = va_arg( args, const char * );
			}
			else if( c == 'x' )
			{
				pName = va_arg( args, const char * );
				pFound = Rva007EBCA0( pSource, pName );

				if( pFound != 0 )
				{
					iResult = Rva007EC780( ( unsigned char * )record, size,
						pFound - 1 );
				}
				else
				{
					iResult = Rva007ECE60( record, size,
						&g_Rva0130A5A4Names[ 7 ], &g_Rva0130A5A4Names[ 6 ] );
				}
			}
			else if( c == 'r' )
			{
				pRaw = va_arg( args, const char * );

				while( *pRaw != 0 && size > 0 )
				{
					*record = *pRaw;
					record++;
					pRaw++;
					size--;
				}
			}

			if( iResult > 0 )
			{
				record += iResult;
				size -= iResult;
			}
		}
	}

	va_end( args );

	if( size > 0 )
	{
		*record = 0;
	}

	return iSize - size;
}

// 0x007EE150 COPIES ONE FIELD FROM ANOTHER RECORD, name and all.  It finds the
// value with the backwards matcher, walks back over the name to the start of
// the whole "name=value" run, and hands that to the replace-or-append engine.
//
// IT LANDS HERE RATHER THAN BESIDE THE ENGINE because it calls the matcher,
// which is C++-mangled in this file and cannot be named from the C half of the
// module.  That is the same seam that put the two field formatters here, and
// it is a fact about how two lanes reconstructed one translation unit rather
// than anything retail did.
//
// THE RECORD BUILDER'S 'x' DIRECTIVE DOES THE SAME JOB DIFFERENTLY, and the
// difference is worth stating because both are now converted: that one backs
// the pointer up by exactly ONE byte and lets the engine rescan for a
// delimiter, where this walks the whole name.  Two callers of one matcher,
// two conventions for what to hand on, and neither is documented anywhere but
// in the bytes.
//
// A MISSING FIELD RETURNS 0, NOT -1 -- the same value a successful no-op
// returns from the engine -- so a caller cannot distinguish "no such field in
// the source" from "the destination already held this".
int Rva007EE150( char *record, int size, const char *name, const char *source )
{
	const unsigned char *p;
	const char *pSource;

	pSource = source;

	p = ( const unsigned char * )Rva007EBCA0( pSource, name );

	if( p == 0 )
	{
		return 0;
	}

	while( p != ( const unsigned char * )pSource && p[ -1 ] > ' ' )
	{
		p--;
	}

	return Rva007EC780( ( unsigned char * )record, size, ( const char * )p );
}
