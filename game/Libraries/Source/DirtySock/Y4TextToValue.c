// cl: /Od /GZ /GS /MD /DNDEBUG
/* EA DirtySock -- text-to-value scanners, /Od with /GZ.  Both take a default
 * to return when the input is unusable, so neither can fail visibly; a caller
 * that needs to tell "absent" from "parsed" has to pick a default it can
 * recognise.  Placement is by address neighbourhood.
 */

/* DECLARED HERE RATHER THAN INCLUDED, and that is forced by the bytes.  Under
 * /MD the CRT headers mark these __declspec(dllimport), which turns each call
 * into an indirect ff 15 straight through the IAT.  Retail calls the import
 * STUB with a direct e8, so the translation unit it was built from did not see
 * <string.h> -- these prototypes reproduce that. */
void * __cdecl memcpy( void *dest, const void *src, unsigned int count );
void * __cdecl memmove( void *dest, const void *src, unsigned int count );
int __cdecl memcmp( const void *a, const void *b, unsigned int count );

/* 0x007EE8B0 PACKS UP TO FOUR PRINTABLE CHARACTERS INTO AN INT -- the same
 * four-character tags the socket layer dispatches on, 'xmap' and the rest,
 * built from text instead of written as a literal.
 *
 * THE LENGTH LIMIT IS ENFORCED BY THE ACCUMULATOR, not by a counter.  It
 * starts at 0x20202020 -- four spaces -- and the loop runs while it stays
 * below 0x20FFFFFF.  Each character shifts a space out of the top, so after
 * the fourth the leading byte is a printable character, the value exceeds the
 * bound, and the loop stops.  A shorter string leaves the unused leading bytes
 * as SPACES rather than zeros, which is what makes a two-character tag compare
 * equal to the same tag written as a padded literal.
 *
 * The bound is a SIGNED comparison, which is safe only because the accepted
 * range stops at 0x7E: a character with the high bit set would make the
 * accumulator negative and the loop would never stop on its own.  The range
 * check is what protects the bound, not the other way round.
 */
int Rva007EE8B0( const char *text, int defaultValue )
{
	int iValue;

	if ( text == 0 || *text <= ' ' || *text >= 0x7F )
		return defaultValue;

	iValue = 0x20202020;

	while ( iValue < 0x20FFFFFF && *text > ' ' && *text < 0x7F )
	{
		iValue = ( iValue << 8 ) | *text;
		text++;
	}

	return iValue;
}

/* 0x007EE820 PARSES A DOTTED QUAD into a packed address, and it is the same
 * algorithm as the socket unit's parser at 0x007FFDD0 written differently:
 * there the running value's low byte is isolated by subtracting it out and
 * adding it back scaled, here by masking with 0xFFFFFF00 and OR-ing the new
 * byte in.  Same effect, and the two spellings sitting in one image is a
 * useful reminder that a shape match across bodies is not an identity.
 *
 * IT STOPS AT THE FIRST CHARACTER THAT IS NEITHER A DIGIT NOR A DOT and
 * returns what it has, so trailing text is ignored rather than rejected and
 * an empty string yields zero -- not the default, which is reached only by a
 * null pointer.
 *
 * There is no range check on an octet: digits accumulate into a single byte,
 * so "999" wraps rather than failing, exactly as the other parser does.
 */
int Rva007EE820( const char *text, int defaultValue )
{
	int iValue;

	iValue = 0;

	if ( text == 0 )
		return defaultValue;

	for ( iValue = 0; ; text++ )
	{
		if ( *text >= '0' && *text <= '9' )
		{
			iValue = ( iValue & 0xFFFFFF00 )
				| ( ( iValue & 0xFF ) * 10 + ( *text & 0x0F ) );
		}
		else if ( *text == '.' )
		{
			iValue = iValue << 8;
		}
		else
		{
			break;
		}
	}

	return iValue;
}

/* 0x007EE720 PARSES A SIGNED DECIMAL INTEGER, and the two things it does NOT
 * do are the ones worth knowing.
 *
 * IT DOES NOT SKIP LEADING WHITESPACE.  A space before the sign or the digits
 * ends the parse immediately and yields zero -- not the default, which only a
 * null pointer reaches.  Anything handing it text straight out of a
 * configuration line has to trim first.
 *
 * AND IT DOES NOT DETECT OVERFLOW: digits accumulate into an int by multiply
 * and add with no bound, so a long enough run wraps silently.
 *
 * A leading '+' is accepted and skipped, which strtol does but atoi is not
 * required to.  The sign is kept as a multiplier applied at the end rather
 * than by negating the accumulator, so the most negative value is not
 * representable through this path -- it would have to overflow positive first.
 */
int Rva007EE720( const char *text, int defaultValue )
{
	int iSign;
	int iValue;

	if ( text == 0 )
		return defaultValue;

	iSign = 1;

	if ( *text == '+' )
	{
		text++;
	}
	else if ( *text == '-' )
	{
		text++;
		iSign = -1;
	}

	for ( iValue = 0; *text >= '0' && *text <= '9'; text++ )
		iValue = iValue * 10 + ( *text & 0x0F );

	return iSign * iValue;
}

/* A 256-entry translation table, indexed by a SIGNED char -- so a byte with
 * the high bit set reads BEFORE the table's start.  That is what the bytes do;
 * whether anything upstream keeps such bytes out is not visible here. */
extern char g_Rva0112A210Fold[];

/* 0x007EFD00 COMPARES TWO STRINGS THROUGH THAT TABLE, and it is doing three
 * jobs at once rather than one.
 *
 * QUOTES SET A PER-SIDE TERMINATOR.  A leading double quote is consumed and
 * remembered, and thereafter a matching quote ends that side; without one the
 * side instead ends at any character below space.  The two sides are decided
 * INDEPENDENTLY, so a quoted string compares cleanly against an unquoted one
 * -- which is the point, since it lets a configuration value be written either
 * way.
 *
 * The end-of-string test is therefore not a NUL test: a control character ends
 * an unquoted side, and a NUL ends a quoted one only because it is below
 * space... which it is not, in the quoted case.  A quoted string missing its
 * closing quote runs past the terminator.
 *
 * The loop is a DO-WHILE, so both sides always advance at least once; the
 * caller's null and empty-string checks at the top are what make that safe.
 *
 * The result is the difference of the two folded characters, so it orders by
 * the TABLE's ordering rather than by the raw bytes.
 */
int Rva007EFD00( const char *a, const char *b )
{
	unsigned char cTermA;
	unsigned char cTermB;
	unsigned char cA;
	unsigned char cB;

	if ( a == 0 || *a == 0 )
		return -1;

	cTermA = ( *a == '"' ) ? *a++ : 0;
	cTermB = ( *b == '"' ) ? *b++ : 0;

	do
	{
		cA = g_Rva0112A210Fold[ *a ];
		a++;
		if ( cA == cTermA || ( cA < ' ' && cTermA == 0 ) )
			cA = 0;

		cB = g_Rva0112A210Fold[ *b ];
		b++;
		if ( cB == cTermB || ( cB < ' ' && cTermB == 0 ) )
			cB = 0;
	}
	while ( cA == cB && cA != 0 && cB != 0 );

	return cA - cB;
}

/* A separator character and a suffix string, both in writable data rather than
 * among the literals, so both are configurable at run time.  The separator is
 * a plain char -- read with movsx where the buffer's own bytes are read with
 * movzx, which is what types the two differently. */
extern char g_Rva012C391CSeparator;
extern char g_Rva012C392CSuffix[];

/* 0x007EC4D0 APPENDS THE SUFFIX TO A BUFFER, inserting the separator first if
 * the buffer needs one, and returns 0 or -1 for "did not fit".
 *
 * THE SEPARATOR IS ONLY ADDED WHEN IT IS ACTUALLY MISSING.  Three conditions
 * all have to hold: the buffer is non-empty, its last character is not a
 * control character, and it is not already the separator.  So calling this
 * twice does not double the separator, and appending to text that already ends
 * in one leaves it alone -- which is what makes the operation repeatable.
 *
 * THE TWO LENGTH CHECKS ARE DIFFERENT AND BOTH MATTER.  The separator needs
 * one free byte and is checked against size - 1; the suffix is checked with a
 * FIXED MARGIN OF FOUR rather than against its own length, so a suffix longer
 * than three characters plus its terminator would overrun.  Nothing here reads
 * the suffix's length, so that margin is an assumption about the data rather
 * than a bound derived from it.
 *
 * A buffer too small for the suffix is left with the separator already
 * appended -- the failure is not atomic, and -1 does not mean "unchanged".
 */
int Rva007EC4D0( unsigned char *buffer, int size )
{
	int i;
	int iResult;
	char *pSuffix;
	unsigned char *pBuffer;

	iResult = -1;
	pSuffix = g_Rva012C392CSuffix;
	pBuffer = buffer;

	for ( i = 0; pBuffer[ i ] != 0; i++ )
	{
	}

	if ( i > 0 && pBuffer[ i - 1 ] >= ' '
		&& pBuffer[ i - 1 ] != g_Rva012C391CSeparator
		&& i < size - 1 )
	{
		pBuffer[ i ] = g_Rva012C391CSeparator;
		i++;
		pBuffer[ i ] = 0;
	}

	if ( i + 4 < size )
	{
		while ( *pSuffix != 0 )
		{
			pBuffer[ i ] = *pSuffix;
			i++;
			pSuffix++;
		}

		pBuffer[ i ] = 0;
		iResult = 0;
	}

	return iResult;
}

/* 0x007EC3F0 REPLACES THE VALUE OF A ONE-FIELD RECORD IN PLACE, rewriting the
 * buffer as "key=\nvalue" and returning 0, or -1 if there is not enough room.
 *
 * THE SCAN AT THE TOP DEFINES THE RECORD FORMAT more precisely than any of the
 * parsers in this file do.  A delimiter is '=' OR ':' FOLLOWED BY A CONTROL
 * CHARACTER -- neither punctuation mark alone ends the key, so a key may
 * contain either as long as ordinary text follows it.  What is written back is
 * always '=' and 0x0A, so ':' is accepted on input and never produced.
 * Finding no delimiter is not an error: the scan then stops at the terminator
 * and the whole existing string is taken as the key.
 *
 * A NULL VALUE MEANS "TRUNCATE", NOT "NO CHANGE", and it returns success.  The
 * key's terminator is written BEFORE the value is examined, so by the time the
 * null test runs the old value is already gone -- and the same is true of the
 * -1 path below, which leaves a truncated buffer behind.  NEITHER FAILURE NOR
 * THE NULL CASE IS A NO-OP.
 *
 * THE MARGIN OF FIVE IS NOT A FIT CHECK.  The copy stops at the last byte of
 * the buffer and the terminator always lands there, so two bytes past the key
 * would be enough to write an empty value.  Requiring five means the caller
 * gets -1 rather than a record whose value was cut to almost nothing: the
 * check is about the result being worth writing, not about it fitting.
 */
int Rva007EC3F0( unsigned char *buffer, int size, const char *value )
{
	unsigned char *p;
	unsigned char *pEnd;

	for ( p = buffer; *p != 0; p++ )
	{
		if ( ( *p == '=' || *p == ':' ) && p[ 1 ] < ' ' )
		{
			break;
		}
	}

	*p = 0;

	if ( value == 0 )
	{
		return 0;
	}

	pEnd = buffer + size - 1;

	if ( pEnd - p < 5 )
	{
		return -1;
	}

	*p = '=';
	p++;
	*p = '\n';
	p++;

	while ( *value != 0 && p != pEnd )
	{
		*p = *value;
		p++;
		value++;
	}

	*p = 0;
	return 0;
}

/* 0x007EFAB0 SCANS A RUN OF DIGITS INTO *value AND RETURNS WHERE IT STOPPED,
 * consuming at most maxLength characters.
 *
 * A NON-POSITIVE maxLength MEANS 256, not "unbounded" and not "nothing".  So
 * there is no way to ask this for an unlimited scan, and passing 0 -- the
 * value a caller would most naturally use for "no limit" -- silently gets the
 * default rather than an empty result.
 *
 * THE LIMIT IS TESTED LAST, after both digit tests, which is what makes the
 * returned pointer meaningful: stopping because the budget ran out leaves it
 * on a digit, while stopping at a non-digit leaves it on the separator.  The
 * caller can tell the two apart only by looking at what it points to.
 *
 * NO OVERFLOW CHECK, and no sign or whitespace handling -- consistent with the
 * decimal parser above, which shares this shape.  Digits are folded with & 0xF
 * rather than by subtracting '0'; the two agree for '0'..'9' and this one is a
 * byte shorter.
 */
const char *Rva007EFAB0( const char *text, int *value, int maxLength )
{
	if ( maxLength <= 0 )
	{
		maxLength = 0x100;
	}

	*value = 0;

	for ( ; *text >= '0' && *text <= '9' && maxLength > 0; text++, maxLength-- )
	{
		*value = *value * 10 + ( *text & 0xF );
	}

	return text;
}

/* A 256-entry character-class table.  Class 1 ends a field, class 0 is
 * whitespace or a terminator, and anything >= 2 is a name character -- the
 * comparison below only ever asks whether two classes are equal AND at least
 * two, so the distinctions above 1 are the caller's business, not ours.  It is
 * indexed by the buffer's bytes UNSIGNED and by the field text's bytes SIGNED,
 * so a high-bit byte in the field reads BEFORE the table start. */
extern unsigned char g_Rva0112A310Class[];

/* 0x007EC780 REPLACES ONE NAMED FIELD IN A RECORD, or appends it, and returns
 * the length written less one -- so the value is a count of everything before
 * the separator it just placed.  This is the engine the small writers above
 * are thin wrappers over.
 *
 * A LEADING '~' MEANS "APPEND, DO NOT SEARCH".  It skips the scan entirely, so
 * a record can carry the SAME NAME TWICE, deliberately; nothing here rejects a
 * duplicate, and a later search will only ever find the first.
 *
 * THE SCAN COMPARES CHARACTER CLASSES, NOT CHARACTERS, and stops at the first
 * position where the two classes disagree or drop below 2.  A NAME MATCHES
 * WHEN THE CLASSES AT THAT POSITION SUM TO EXACTLY 2 -- that is, both sides
 * ended together on class-1 delimiters.  One side ending early gives 0 + 1 or
 * 1 + 2 and fails, which is what stops a name being a prefix of another.
 *
 * THE THREE-WAY memmove IS A RESIZE IN PLACE.  iDelta is new length minus old:
 * positive opens a gap and is the only case that can overflow the buffer,
 * negative closes one, and ZERO SHORT-CIRCUITS ON memcmp -- rewriting a field
 * with the text it already holds returns 0 without touching a byte.  That is
 * the only path that reports success without writing.
 *
 * THE OVERFLOW CHECK GUARDS ONLY GROWTH, which is correct but worth stating:
 * when iDelta <= 0 the result cannot be longer than what is already there, so
 * no check is needed and none is made.
 *
 * THE LAST BYTE IS DECIDED BY THE SEPARATOR'S IDENTITY.  Writing the field's
 * own terminator would end the record, so it is overwritten with the separator
 * -- EXCEPT where the field landed at the very end AND the separator is not a
 * newline, where a real terminator goes in instead.  The '\n' case is special
 * because a trailing newline is harmless at the end of a record and a trailing
 * anything-else would leave a separator with nothing after it.
 */
int Rva007EC780( unsigned char *buffer, int size, const char *field )
{
	int i;
	int iDelta;
	unsigned char *p;
	unsigned char *pValue;
	unsigned char *pTail;
	unsigned char cClassBuffer;
	unsigned char cClassField;
	unsigned char *pBuffer;

	pBuffer = buffer;

	if ( pBuffer == 0 )
	{
		return -1;
	}

	if ( field == 0 || (unsigned int)*field <= ' ' )
	{
		return -1;
	}

	if ( *field == '~' )
	{
		for ( p = pBuffer; *p != 0; p++ )
		{
		}

		if ( p != pBuffer && p[ -1 ] >= ' '
			&& p[ -1 ] != g_Rva012C391CSeparator
			&& p < pBuffer + size - 1 )
		{
			*p = g_Rva012C391CSeparator;
			p++;
			*p = 0;
		}

		pTail = p;
		pValue = pTail;
	}
	else
	{
		p = pBuffer;

		for ( ;; )
		{
			if ( *p == 0 )
			{
				if ( p != pBuffer && p[ -1 ] >= ' '
					&& p[ -1 ] != g_Rva012C391CSeparator
					&& p < pBuffer + size - 1 )
				{
					*p = g_Rva012C391CSeparator;
					p++;
					*p = 0;
				}

				pTail = p;
				pValue = pTail;
				break;
			}

			if ( *p <= ' ' )
			{
				p++;
				continue;
			}

			if ( g_Rva0112A310Class[ *p ] == 1 )
			{
				pTail = p;
				pValue = pTail;
				break;
			}

			for ( i = 0; ; i++ )
			{
				cClassBuffer = g_Rva0112A310Class[ p[ i ] ];
				cClassField = g_Rva0112A310Class[ field[ i ] ];

				if ( cClassBuffer != cClassField || cClassBuffer < 2 )
				{
					break;
				}
			}

			if ( cClassBuffer + cClassField == 2 )
			{
				pTail = p;
				pValue = pTail;

				for ( ; *pTail >= ' '; pTail++ )
				{
				}

				if ( *pTail > 0 )
				{
					pTail++;
				}

				break;
			}

			do
			{
				p++;
			}
			while ( *p >= ' ' );
		}
	}

	for ( i = 0; (unsigned int)field[ i ] >= ' '; i++ )
	{
	}

	i++;

	iDelta = i - ( pTail - pValue );

	for ( p = pTail; *p != 0; p++ )
	{
	}

	p++;

	if ( iDelta > 0 && pBuffer + size - p < iDelta )
	{
		return -1;
	}

	if ( iDelta == 0 && memcmp( pValue, field, i ) == 0 )
	{
		return 0;
	}

	if ( iDelta > 0 )
	{
		memmove( pTail + iDelta, pTail, p - pTail );
	}

	if ( iDelta < 0 )
	{
		memmove( pValue, pValue - iDelta, p - ( pValue - iDelta ) );
	}

	memcpy( pValue, field, i );

	if ( pValue[ i ] == 0 && g_Rva012C391CSeparator != '\n' )
	{
		pValue[ i - 1 ] = 0;
	}
	else
	{
		pValue[ i - 1 ] = g_Rva012C391CSeparator;
	}

	return i - 1;
}

/* 0x007EE1D0 APPLIES A WHOLE LIST OF FIELDS TO A RECORD and returns how many
 * of them actually changed it.
 *
 * THE COUNT IS OF CHANGES, NOT OF FIELDS APPLIED.  The engine returns 0 when a
 * field already holds the text being written, and only a strictly positive
 * result is counted here -- so a caller can use the return value to decide
 * whether the record needs saving, which is the only reason to distinguish
 * those two cases at all.  Errors return -1 and are counted the same as
 * no-change: NOTHING HERE REPORTS A FAILED FIELD.  A list that overflows the
 * buffer halfway through returns a plausible non-zero count.
 *
 * A DELIMITER WHERE A NAME SHOULD BE ENDS THE LIST.  Leading whitespace is
 * skipped, but a field starting with '=' or ':' would name nothing, so the
 * whole remainder is abandoned rather than skipped -- silently, and with the
 * fields already applied left in place.
 *
 * Fields are separated by anything below a space, and a run of them counts as
 * one separator, so the list is equally happy as newline- or NUL-delimited
 * text.
 */
int Rva007EE1D0( unsigned char *buffer, int size, const unsigned char *fields )
{
	int iChanged;
	const unsigned char *p;

	iChanged = 0;
	p = fields;

	while ( *p != 0 )
	{
		if ( *p <= ' ' )
		{
			p++;
			continue;
		}

		if ( *p == '=' || *p == ':' )
		{
			break;
		}

		if ( Rva007EC780( buffer, size, (const char *)p ) > 0 )
		{
			iChanged++;
		}

		while ( *p >= ' ' )
		{
			p++;
		}
	}

	return iChanged;
}

/* 0x007EFE30 EXTRACTS THE NAME IN FRONT OF THE FIRST '=' and returns a pointer
 * just past that '=' -- so the caller gets the key copied out and the value's
 * starting position in one call.
 *
 * THE NAME IS FOUND BY WALKING BACKWARDS from the delimiter, not forwards from
 * the start, which is what lets it pick the LAST word before the '=' out of a
 * line that has other text on it.  Everything from the previous whitespace up
 * to the delimiter is the name.
 *
 * TWO EDGES FALL OUT OF THAT WALK AND NEITHER IS GUARDED.
 *
 * The backward walk stops on a character that is whitespace or lower, and then
 * steps forward off it -- BUT ONLY IF IT DID NOT REACH THE BUFFER START.  So a
 * string that BEGINS with a space puts the walk at the buffer start with the
 * space still under it, the step-forward is skipped, and THE LEADING SPACE
 * BECOMES PART OF THE COPIED NAME.  A name at the very start of the buffer is
 * handled correctly; a name preceded only by whitespace is not.
 *
 * The size argument bounds the COPY BUT NOT THE TERMINATOR, which is written
 * unconditionally afterwards.  A caller passing its full capacity gets one
 * byte written past the end, so the argument means "capacity less one" and
 * nothing here says so.
 *
 * A missing '=' returns null and leaves the destination UNTOUCHED -- not
 * emptied -- so a caller that ignores the return reads whatever was there.
 */
unsigned char *Rva007EFE30( unsigned char *text, unsigned char *dest, int size )
{
	unsigned char *p;
	unsigned char *pDelimiter;

	p = text;

	if ( p == 0 || *p == 0 )
	{
		return 0;
	}

	while ( *p != 0 && *p != '=' )
	{
		p++;
	}

	if ( *p == 0 )
	{
		return 0;
	}

	pDelimiter = p;

	while ( p != text && *p > ' ' )
	{
		p--;
	}

	if ( p != text )
	{
		p++;
	}

	while ( p < pDelimiter && size > 0 )
	{
		*dest = *p;
		dest++;
		p++;
		size--;
	}

	*dest = 0;

	return pDelimiter + 1;
}

/* 0x007EEF30 UNPACKS SEVEN-BIT-PER-BYTE DATA back into bytes, and returns how
 * many bytes it produced.  Each input byte contributes its low seven bits to a
 * little-endian bit accumulator; whenever eight bits are available they are
 * emitted and shifted out.  This is the read side of a transport that keeps
 * the high bit clear on every byte it sends -- text-safe binary.
 *
 * THE HIGH BIT IS A CONTINUATION MARK, NOT A DATA BIT, and it is required on
 * EVERY packed byte rather than only on the last.  So the run ends at the
 * first byte without it, and THAT BYTE IS NEITHER CONSUMED NOR DECODED -- the
 * caller's source pointer is a local copy, so the terminator's position is not
 * reported either.  Only the output count comes back.
 *
 * THE BUDGET IS CHECKED BEFORE THE READ BUT SPENT ONLY ON A WRITE.  A byte
 * that contributes bits without completing one costs nothing, so the count
 * bounds OUTPUT bytes exactly -- but the input is read one byte past what the
 * budget can pay for, since the guard runs before the byte is examined.
 *
 * LEFTOVER BITS ARE DISCARDED.  Seven does not divide eight, so a run ends
 * with up to seven bits still in the accumulator and they are simply dropped.
 * That is only correct if the sender padded to a byte boundary, which nothing
 * here checks and nothing here can detect.
 */
int Rva007EEF30( unsigned char *dest, int count, const unsigned char *src )
{
	unsigned char *pOut;
	const unsigned char *pIn;
	int iCount;
	unsigned int uAccumulator;
	int iBits;

	pOut = dest;
	pIn = src;
	iCount = count;
	uAccumulator = 0;
	iBits = 0;

	while ( *pIn >= 0x80 && iCount > 0 )
	{
		uAccumulator |= ( *pIn & 0x7F ) << iBits;
		pIn++;
		iBits += 7;

		if ( iBits >= 8 )
		{
			*pOut = uAccumulator & 0xFF;
			pOut++;
			uAccumulator >>= 8;
			iBits -= 8;
			iCount--;
		}
	}

	return pOut - dest;
}

/* 0x007ED360 IS THE WRITE SIDE OF 0x007EEF30 -- it packs bytes into seven-bit
 * groups so the result survives a channel that cannot carry the high bit as
 * data, and returns how many bytes it wrote, or -1 if they would not fit.
 *
 * EVERY OUTPUT BYTE HAS THE HIGH BIT SET, THE LAST ONE INCLUDED.  That is the
 * detail that ties the pair together and it is easy to misread from either
 * side alone: the decoder stops at the first byte WITHOUT the high bit, and
 * this encoder never produces one.  SO THE TERMINATOR IS NOT PART OF THE
 * ENCODING -- it has to come from whatever the run is embedded in, and a
 * caller that packs two runs back to back with nothing between them produces
 * something the decoder will read as a single longer run.
 *
 * THE SIZE CHECK IS EXACT RATHER THAN CONSERVATIVE.  Eight bits per input byte
 * over seven bits per output byte, rounded up, is precisely what the loop
 * emits including the final partial group, so a buffer of exactly that size
 * always succeeds and one byte less always fails.
 *
 * THE FINAL FLUSH DOES NOT MASK, where the loop does.  It is safe only because
 * fewer than seven bits remain by then, so the accumulator cannot reach the
 * high bit on its own -- an invariant of the loop above rather than anything
 * this line checks.
 */
int Rva007ED360( unsigned char *dest, int destSize, const unsigned char *src,
	int count )
{
	unsigned char *pOut;
	const unsigned char *pIn;
	int iLeft;
	unsigned int uAccumulator;
	int iBits;

	pOut = dest;
	pIn = src;
	iLeft = count;
	uAccumulator = 0;
	iBits = 0;

	if ( destSize < ( count * 8 + 6 ) / 7 )
	{
		return -1;
	}

	/* THE EXPLICIT != 0 IS LOAD-BEARING, not decoration.  Written as a bare
	 * relational the comparison branches directly; compared against zero it is
	 * first materialised into a 1 or a 0 in a stack temporary which is then
	 * tested, costing five instructions and a frame slot.  Retail has the
	 * temporary, so retail has the comparison. */
	while ( ( iLeft-- > 0 ) != 0 )
	{
		uAccumulator |= *pIn << iBits;
		pIn++;
		iBits += 8;

		while ( iBits >= 7 )
		{
			*pOut = ( uAccumulator & 0x7F ) | 0x80;
			pOut++;
			uAccumulator >>= 7;
			iBits -= 7;
		}
	}

	if ( iBits > 0 )
	{
		*pOut = uAccumulator | 0x80;
		pOut++;
	}

	return pOut - dest;
}

/* 0x007EE600 COPIES OUT THE VALUE PART OF A FIELD, or the caller's default if
 * there is no value to be had, and returns where the value started or null.
 *
 * ITS SECOND PARAMETER IS NEVER READ.  Nothing in the body touches it, and a
 * scan of the whole of .text finds NO DIRECT CALLER of this function at all --
 * it is reached through a pointer or retained by the linker unreferenced.  So
 * the argument's meaning is not recoverable from anywhere: not from the body,
 * which ignores it, and not from a call site, because there is none.  It is
 * declared here as an int purely because something has to occupy the slot.
 *
 * THE DEFAULT IS ONLY USED WHEN NO DELIMITER IS FOUND AT ALL.  A field that
 * ends immediately after its delimiter -- the terminator case -- BREAKS OUT to
 * the same tail, so an explicitly empty value also yields the default rather
 * than an empty string.  There is no way to store a value that reads back as
 * empty through this accessor.
 *
 * THE RETURN AND THE COPY REPORT DIFFERENT THINGS.  The pointer says where the
 * value began in the source; the buffer holds a truncated copy.  A caller that
 * wants the whole value when it did not fit has to use the pointer, and
 * nothing indicates truncation happened.
 *
 * BOTH COPIES RESERVE ROOM FOR THE TERMINATOR, unlike the extractor at
 * 0x007EFE30 in this same file, which does not.  Two functions a few hundred
 * bytes apart disagree about what their size argument means.
 */
char *Rva007EE600( char *field, int iUnused, char *dest, int destSize,
	const char *defaultText )
{
	int i;
	char *p;

	for ( p = field; *p != 0; p++ )
	{
		if ( *p == '=' || *p == ':' )
		{
			if ( p[ 1 ] < ' ' )
			{
				if ( p[ 1 ] == 0 )
				{
					break;
				}

				p += 2;

				if ( dest != 0 )
				{
					for ( i = 0; i < destSize - 1 && p[ i ] != 0; i++ )
					{
						dest[ i ] = p[ i ];
					}

					dest[ i ] = 0;
				}

				return p;
			}
		}
	}

	if ( dest != 0 && defaultText != 0 )
	{
		for ( i = 0; i < destSize - 1 && defaultText[ i ] != 0; i++ )
		{
			dest[ i ] = defaultText[ i ];
		}

		dest[ i ] = 0;
	}

	return 0;
}

/* The high-nibble half of the hex decode.  Its low-nibble partner is the table
 * the dollar-prefixed parser already uses, so a byte is decoded by OR-ing one
 * lookup from each -- no shift and no multiply anywhere. */
extern unsigned char g_Rva0112A010HexHigh[];
extern unsigned char g_Rva0112A110Hex[];

unsigned int __cdecl strlen( const char *text );

/* 0x007EE930 EXTRACTS ONE VALUE FROM A SEPARATED LIST, undoing the escaping
 * the writers apply, and substitutes a caller default when the value is not
 * there.  It is the read side of 0x007ECE60.
 *
 * IT HAS THREE MODES AND THE ARGUMENTS SELECT THEM RATHER THAN A FLAG.  With a
 * destination it copies and unescapes; WITH A NULL DESTINATION IT MEASURES,
 * returning the decoded length without writing anything; and if the value is
 * missing entirely it falls back to the default, measuring THAT instead when
 * the destination is also null.  One function, three behaviours, none of them
 * named.
 *
 * THE MEASURING PASS AND THE COPYING PASS DISAGREE ABOUT ESCAPES, which is the
 * kind of thing only a byte-level reading catches.  The copy handles a doubled
 * percent as a literal percent and a percent-hex pair as one byte; THE MEASURE
 * PASS HAS NO DOUBLED-PERCENT CASE AT ALL and treats "%%" as a percent escape
 * followed by a stray character, so it can return a length one larger than the
 * copy would produce.  A caller that measures to size a buffer is safe; a
 * caller that measures to predict the exact result is not.
 *
 * A LEADING QUOTE SETS THE TERMINATOR and is consumed.  Everything downstream
 * then compares against that terminator instead of against the quote, so an
 * unquoted value ends at a control character or the separator and a quoted one
 * runs to its closing quote -- the same one-variable trick the quote-aware
 * compare in this file uses, arrived at independently.
 *
 * THE INDEX IS CONSUMED BY SKIPPING, and a list too short does not report an
 * error: the walk sets the text pointer to null and the default path takes
 * over, so "no such element" and "no value" are the same outcome.
 */
int Rva007EE930( const char *text, char *dest, int destSize,
	const char *defaultText, int index, int cSeparator )
{
	int iLen;
	unsigned char cTerm;
	const unsigned char *p;
	unsigned char c;

	cTerm = 0;

	if ( text != 0 )
	{
		if ( *text == '"' )
		{
			cTerm = *text;
			text++;
		}

		for ( ; index > 0; index-- )
		{
			while ( ( ( c = *text ) != cTerm && c >= ' '
				&& c != cSeparator ) != 0 )
			{
				text++;
			}

			/* THE POSITIVE CASE COMES FIRST, as an if/else rather than a
			 * guard-and-fall-through.  Retail branches on equality into the
			 * advance and lets the failure fall past it; inverting the test
			 * so the failure is the guard reorders the two blocks and costs
			 * two bytes. */
			if ( *text == cSeparator )
			{
				text++;
			}
			else
			{
				text = 0;
				break;
			}
		}
	}

	if ( text == 0 )
	{
		if ( defaultText == 0 )
		{
			return -1;
		}

		if ( dest == 0 )
		{
			return strlen( defaultText );
		}

		for ( iLen = 1; iLen < destSize && *defaultText != 0; iLen++ )
		{
			*dest = *defaultText;
			dest++;
			defaultText++;
		}

		*dest = 0;
		return iLen - 1;
	}

	if ( dest == 0 )
	{
		iLen = 0;

		for ( p = ( const unsigned char * )text;
			*p != cTerm && *p >= ' ' && *p != cSeparator; p++ )
		{
			if ( *p == '%' && p[ 1 ] >= ' ' && p[ 2 ] >= ' ' )
			{
				p += 2;
			}

			iLen++;
		}

		return iLen;
	}

	if ( destSize < 1 )
	{
		return -1;
	}

	iLen = 1;
	p = ( const unsigned char * )text;

	while ( iLen < destSize && *p != cTerm && *p >= ' ' && *p != cSeparator )
	{
		if ( *p == '%' && p[ 1 ] == '%' )
		{
			*dest = '%';
			dest++;
			p += 2;
			iLen++;
		}
		else if ( *p == '%' && p[ 1 ] >= ' ' && p[ 2 ] >= ' ' )
		{
			*dest = g_Rva0112A010HexHigh[ p[ 1 ] ] | g_Rva0112A110Hex[ p[ 2 ] ];
			dest++;
			p += 3;
			iLen++;
		}
		else
		{
			*dest = *p;
			dest++;
			p++;
			iLen++;
		}
	}

	*dest = 0;
	return iLen - 1;
}

/* 0x007EEC30 READS A VALUE AND DECODES WHICHEVER ENCODING IT IS IN, choosing
 * between them by the FIRST CHARACTER alone: a caret means seven-bit packed
 * binary, a quote means a quoted run, anything else is escaped text.  The
 * writers that produce those three forms are in three different places and
 * none of them agrees with the others about anything except this one byte.
 *
 * IT IS THE SAME THREE-MODE SHAPE as the list extractor at 0x007EE930 -- copy,
 * measure with a null destination, or fall back to the default -- but WITHOUT
 * the separator and index arguments.  The two share no code and the escaped
 * text path is duplicated between them almost instruction for instruction,
 * which is what makes the small differences worth naming rather than assuming.
 *
 * THE PACKED MEASUREMENT IS AN ESTIMATE, NOT A COUNT.  It finds the run's end
 * by scanning for the first byte without the high bit and then computes seven
 * eighths of the length, so it agrees with the unpacker only when the sender
 * padded to a byte boundary.  It also does not consult the destination size,
 * because in measuring mode there is no destination.
 *
 * THE PACKED DECODE RESERVES ITS OWN TERMINATOR by handing the unpacker one
 * less than the buffer size and then writing the terminator at whatever length
 * came back -- so unlike the text paths, the count returned here is the number
 * of bytes produced rather than that number less one.  TWO PATHS OUT OF THIS
 * FUNCTION USE DIFFERENT CONVENTIONS FOR THEIR RETURN VALUE.
 *
 * THE QUOTE VARIABLE IS SET IN AN ELSE, not initialised up front the way the
 * list extractor does it -- the same idea reached twice with different
 * spellings, which is a hint the two were written at different times.
 */
int Rva007EEC30( const char *text, unsigned char *dest, int destSize,
	const char *defaultText )
{
	int iLen;
	unsigned char cTerm;
	const unsigned char *p;

	if ( text == 0 )
	{
		if ( defaultText == 0 )
		{
			return -1;
		}

		if ( dest == 0 )
		{
			return strlen( defaultText );
		}

		for ( iLen = 1; iLen < destSize && *defaultText != 0; iLen++ )
		{
			*dest = *defaultText;
			dest++;
			defaultText++;
		}

		*dest = 0;
		return iLen - 1;
	}

	if ( *text == '^' )
	{
		if ( dest == 0 )
		{
			for ( p = ( const unsigned char * )text + 1; *p >= 0x80; p++ )
			{
			}

			iLen = ( ( p - ( const unsigned char * )text ) - 1 ) * 7 / 8;
			return iLen;
		}

		if ( destSize < 1 )
		{
			return -1;
		}

		iLen = Rva007EEF30( dest, destSize - 1,
			( const unsigned char * )text + 1 );
		dest[ iLen ] = 0;
		return iLen;
	}

	if ( *text == '"' )
	{
		cTerm = *text;
		text++;
	}
	else
	{
		cTerm = 0;
	}

	if ( dest == 0 )
	{
		iLen = 0;

		for ( p = ( const unsigned char * )text; *p != cTerm && *p >= ' '; p++ )
		{
			if ( *p == '%' && p[ 1 ] >= ' ' && p[ 2 ] >= ' ' )
			{
				p += 2;
			}

			iLen++;
		}

		return iLen;
	}

	if ( destSize < 1 )
	{
		return -1;
	}

	iLen = 1;
	p = ( const unsigned char * )text;

	while ( iLen < destSize && *p != cTerm && *p >= ' ' )
	{
		if ( *p == '%' && p[ 1 ] == '%' )
		{
			*dest = '%';
			dest++;
			p += 2;
			iLen++;
		}
		else if ( *p == '%' && p[ 1 ] >= ' ' && p[ 2 ] >= ' ' )
		{
			*dest = g_Rva0112A010HexHigh[ p[ 1 ] ] | g_Rva0112A110Hex[ p[ 2 ] ];
			dest++;
			p += 3;
			iLen++;
		}
		else
		{
			*dest = *p;
			dest++;
			p++;
			iLen++;
		}
	}

	*dest = 0;
	return iLen - 1;
}

/* 0x007EEFF0 READS A VALUE AS BINARY AND NOTHING ELSE.  Where 0x007EEC30
 * accepts three encodings and falls back to text, this one accepts only the
 * two BINARY forms -- dollar-prefixed hex and caret-prefixed packed -- and
 * REFUSES anything else outright.  Two readers over the same data, one
 * permissive and one strict, and the strictness is the whole difference.
 *
 * IT WRITES NO TERMINATOR, which is what makes it a binary reader rather than
 * a string one.  The decode loop is bounded by the destination size and may
 * fill it completely; the caller gets a length back and nothing else.  The
 * packed path likewise hands the unpacker the FULL size where 0x007EEC30 held
 * one byte back for a terminator it then wrote.
 *
 * THE HEX PAIR TEST IS NOT A HEX TEST.  It accepts any two characters at or
 * above '0', so letters past 'f' and most punctuation pass and are folded
 * through the tables to whatever those tables say.  It stops on the first
 * character below '0' -- which is how the value ends, since the separator and
 * every control character are below it.  A malformed pair is decoded rather
 * than rejected.
 *
 * The measuring and decoding paths use DIFFERENT LOOP SHAPES for the same
 * walk: the measure is a for with the step in its increment clause, the decode
 * a while with the step at the end of its body.  Same arithmetic, and the
 * bytes keep them distinct.
 */
int Rva007EEFF0( const char *text, unsigned char *dest, int destSize )
{
	int iLen;
	const unsigned char *p;
	unsigned char *pDest;

	pDest = dest;

	if ( text == 0 || ( *text != '$' && *text != '^' ) )
	{
		return -1;
	}

	if ( pDest == 0 )
	{
		iLen = 0;

		if ( *text == '$' )
		{
			for ( p = ( const unsigned char * )text + 1;
				*p >= '0' && p[ 1 ] >= '0'; p += 2 )
			{
				iLen++;
			}
		}
		else
		{
			for ( p = ( const unsigned char * )text + 1; *p >= 0x80; p++ )
			{
			}

			iLen = ( ( p - ( const unsigned char * )text ) - 1 ) * 7 / 8;
		}

		return iLen;
	}

	if ( destSize < 1 )
	{
		return -1;
	}

	iLen = 0;

	if ( *text == '$' )
	{
		p = ( const unsigned char * )text + 1;

		while ( iLen < destSize && *p >= '0' && p[ 1 ] >= '0' )
		{
			*pDest = g_Rva0112A010HexHigh[ *p ] | g_Rva0112A110Hex[ p[ 1 ] ];
			pDest++;
			iLen++;
			p += 2;
		}
	}
	else
	{
		iLen = Rva007EEF30( pDest, destSize,
			( const unsigned char * )text + 1 );
	}

	return iLen;
}

/* The decoder's fallback key.  IT IS A SECOND COPY: the encoder at 0x007ED850
 * reads its default from 0x012C3934 and this reads from 0x012C3950, and both
 * hold the same two bytes.  They round-trip today because the contents agree,
 * not because anything ties them together -- these are writable data, so a
 * caller that changes one at run time silently breaks the pair. */
extern unsigned char g_Rva012C3950DefaultKey[];

/* 0x007EF5B0 IS THE INVERSE OF THE OBSCURING WRITER at 0x007ED850: it reads a
 * dollar-prefixed hex field and undoes the chained rotate-and-xor.
 *
 * IT IS ALSO A PASS-THROUGH.  A value that does NOT begin with a dollar sign
 * is handed straight to the plain reader at 0x007EEC30 -- so this is safe to
 * call on any field, and a caller cannot tell from the return value whether
 * the value was obscured or was ordinary text.  Obscuring is advisory, not
 * enforced.
 *
 * THE ROTATE RUNS THE OTHER WAY -- right by three where the writer rotates
 * left by three -- and the feedback byte is the RAW CIPHERTEXT, taken before
 * the key is mixed out, which is exactly what the writer emitted.  That is
 * what makes the chain reversible; feeding back the plaintext instead would
 * decode the first byte and nothing after it.
 *
 * THE MEASURING PASS IGNORES THE KEY ENTIRELY, as it must -- the output length
 * is one byte per hex pair whatever the key is -- so it is the one path here
 * that cannot be broken by a key mismatch, and correspondingly the one that
 * tells a caller nothing about whether the decode will be meaningful.
 */
int Rva007EF5B0( const char *text, unsigned char *dest, int destSize,
	const unsigned char *key, const char *defaultText )
{
	int iLen;
	unsigned char cPrev;
	unsigned char cMix;
	const unsigned char *p;
	const unsigned char *pKey;
	const unsigned char *pKeyStart;

	pKeyStart = key;

	if ( text == 0 )
	{
		return -1;
	}

	if ( *text != '$' )
	{
		return Rva007EEC30( text, dest, destSize, defaultText );
	}

	if ( pKeyStart == 0 || *pKeyStart == 0 )
	{
		pKeyStart = g_Rva012C3950DefaultKey;
	}

	if ( dest == 0 )
	{
		iLen = 0;

		for ( p = ( const unsigned char * )text + 1;
			*p >= '0' && p[ 1 ] >= '0'; p += 2 )
		{
			iLen++;
		}

		return iLen;
	}

	if ( destSize < 1 )
	{
		return -1;
	}

	iLen = 1;
	p = ( const unsigned char * )text + 1;
	pKey = pKeyStart;
	cPrev = 0;

	while ( iLen < destSize && *p >= '0' && p[ 1 ] >= '0' )
	{
		cMix = ( g_Rva0112A010HexHigh[ *p ] | g_Rva0112A110Hex[ p[ 1 ] ] )
			^ *pKey;
		pKey++;

		if ( *pKey == 0 )
		{
			pKey = pKeyStart;
		}

		cMix = ( cMix << 5 ) | ( ( cMix >> 3 ) & 0x1F );
		*dest = cMix ^ cPrev;
		dest++;

		cPrev = g_Rva0112A010HexHigh[ *p ] | g_Rva0112A110Hex[ p[ 1 ] ];

		iLen++;
		p += 2;
	}

	*dest = 0;
	return iLen - 1;
}

/* Uninitialised data again -- the text substituted when the caller passes
 * none.  No bytes for it exist in the image, so what it holds is set at run
 * time and is not recoverable here. */
extern char g_Rva0130A5ACEmpty[];

/* 0x007EF190 IS THE INVERSE OF THE FORMAT-DRIVEN SERIALISER at 0x007ED470: it
 * reads comma-separated values back into a binary buffer under the same
 * directive letters.  Retail's own name for its scratch buffer is tmp.
 *
 * A NULL DESTINATION IS NOT AN ERROR -- IT IS A SCRATCH BUFFER.  When the
 * caller passes none, a 1 KB local stands in and the whole parse runs into it
 * and is discarded, with only the LENGTH returned.  So this doubles as a
 * measuring pass without a separate code path, and a caller measuring a format
 * that would produce more than 1 KB overruns that local silently.
 *
 * THREE THINGS DIFFER FROM THE WRITER, all of them small and none visible from
 * the letters alone.
 *
 * The unbounded length is 0xFFFF here where the writer uses 0x10000 -- one
 * byte apart, so a buffer the writer would exactly fill is one short of what
 * the reader will accept.
 *
 * The end check runs at the END of the loop body where the writer checks at
 * the TOP, so THIS ALWAYS PROCESSES AT LEAST ONE DIRECTIVE even when the
 * destination is already full.
 *
 * And the sign is taken from the FIRST CHARACTER before any digits are read,
 * then re-tested afterwards to negate -- where the writer decides sign by
 * magnitude.  A value the writer emitted as a large positive number is read
 * back as exactly that; the two disagree about anything above 0xFFFF0000.
 *
 * A STRING FIELD IS ZERO-FILLED TO ITS DECLARED WIDTH, so 's' is fixed-width
 * on the way in even though the writer emits it variable-length and relies on
 * the comma.  The count is what makes the round trip work, and a format that
 * omits it silently reads nothing.
 */
int Rva007EF190( const char *text, unsigned char *data, int length,
	const char *format )
{
	char cSign;
	int iWidth;
	int iCount;
	unsigned char tmp[ 0x400 ];
	int uValue;
	unsigned char *pOut;
	unsigned char *pEnd;

	pOut = data;

	pEnd = ( length < 0 ) ? pOut + 0xFFFF : pOut + length;

	if ( text == 0 )
	{
		text = g_Rva0130A5ACEmpty;
	}

	if ( pOut == 0 )
	{
		data = tmp;
		pOut = data;
	}

	while ( *format != 0 )
	{
		if ( *format == '#' )
		{
			format++;

			while ( *format != 0 && ( *format++ != '=' ) != 0 )
			{
			}
		}

		for ( iCount = 0; *format >= '0' && *format <= '9'; format++ )
		{
			iCount = iCount * 10 + ( *format & 0xF );
		}

		iWidth = 0;

		if ( *format == 'a' )
		{
			pOut += ( iCount != 0 ) ? iCount : 1;
		}

		if ( *format == 'b' )
		{
			iWidth = 2;
		}

		if ( *format == 'w' )
		{
			iWidth = 4;
		}

		if ( *format == 'l' )
		{
			iWidth = 8;
		}

		if ( iWidth > 0 )
		{
			cSign = *text;

			if ( cSign == '-' )
			{
				text++;
			}

			uValue = 0;

			for ( ; iWidth > 0 && *text >= '0'; iWidth-- )
			{
				uValue = ( uValue << 4 ) | g_Rva0112A110Hex[ *text ];
				text++;
			}

			if ( iWidth > 0 && *text == ',' )
			{
				text++;
			}

			if ( cSign == '-' )
			{
				uValue = -uValue;
			}

			if ( *format == 'b' )
			{
				*pOut = ( unsigned char )uValue;
				pOut += 1;
			}

			if ( *format == 'w' )
			{
				*( unsigned short * )pOut = ( unsigned short )uValue;
				pOut += 2;
			}

			if ( *format == 'l' )
			{
				*( int * )pOut = uValue;
				pOut += 4;
			}
		}

		if ( *format == 's' && iCount > 0 )
		{
			for ( iWidth = 0; ( *text >= '0' || *text == '%' )
				&& iWidth + 1 < iCount; iWidth++ )
			{
				if ( *text == '%' )
				{
					pOut[ iWidth ] = g_Rva0112A010HexHigh[ text[ 1 ] ]
						| g_Rva0112A110Hex[ text[ 2 ] ];
					text += 3;
				}
				else
				{
					pOut[ iWidth ] = *text;
					text++;
				}
			}

			while ( iWidth < iCount )
			{
				pOut[ iWidth ] = 0;
				iWidth++;
			}

			pOut += iWidth;

			if ( *text == ',' )
			{
				text++;
			}
		}

		if ( pOut >= pEnd )
		{
			break;
		}

		format++;

		if ( *format == '*' )
		{
			format--;
		}
	}

	return pOut - data;
}
