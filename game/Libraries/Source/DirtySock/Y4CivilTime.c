// cl: /Od /GZ /RTCu /MD /DNDEBUG
/* EA DirtySock -- civil time from a seconds-since-epoch count, written out by
 * hand rather than called out to the CRT.  Placement is by address
 * neighbourhood; the packer at 0x007EFC20 is its only caller so far found.
 */

/* Retail's own name for this on the caller's frame is `tm2`, recovered from
 * the /GZ frame descriptor, and the layout is struct tm exactly -- 36 bytes,
 * fields in the standard order.  It is spelled out here rather than included
 * so the one field this function NEVER WRITES is visible: m_weekday.  A caller
 * that reads it gets whatever was on the stack, and with /GZ that is
 * 0xCCCCCCCC.
 */
struct Rva007EDB10Time
{
	int m_second;			/* +0x00 */
	int m_minute;			/* +0x04 */
	int m_hour;			/* +0x08 */
	int m_day;			/* +0x0C, 1-based */
	int m_month;			/* +0x10, 0-based */
	int m_year;			/* +0x14, less 1900 */
	int m_weekday;			/* +0x18, NEVER WRITTEN */
	int m_yearDay;			/* +0x1C, 0-based */
	int m_isDst;			/* +0x20, always zero */
};

/* Twenty-four month lengths: the twelve leap-year ones first, then the twelve
 * common ones.  Which half is used is selected by the PARITY of the year's
 * length -- 366 is even and picks index 0, 365 is odd and picks index 12 --
 * rather than by testing the leap flag again. */
extern int g_Rva0112A530MonthDays[];

/* 0x007EDB10 CONVERTS SECONDS SINCE 1970 INTO BROKEN-DOWN TIME, filling the
 * caller's structure and returning it.
 *
 * THE YEAR LOOP IS AN ESTIMATE-AND-CORRECT, not a count.  Rather than stepping
 * one year at a time it guesses with a divide by 366 -- always an
 * UNDERESTIMATE, since no year is longer -- forces the guess forward by one
 * when it lands on the year it started from, then subtracts 365 days per year
 * crossed and fixes up the leap days with the standard /4 - /100 + /400
 * accumulation across the span.  It then re-tests, so a guess that overshoots
 * is not possible but a guess that falls short simply iterates again.
 *
 * THE DIVISION OF SECONDS IS UNSIGNED AND EVERYTHING AFTER IT IS SIGNED.  Only
 * the initial split into days and seconds treats the timestamp as unsigned, so
 * the function keeps working past 2038 for the DAY count while the arithmetic
 * downstream is ordinary signed int.
 *
 * TWO FIELDS ARE NOT COMPUTED.  m_isDst is set to zero unconditionally -- this
 * is UTC and there is no zone rule anywhere in it -- but m_weekday is not
 * written at all, which is a different thing entirely: the caller sees
 * uninitialised stack.  Nothing in the packer at 0x007EFC20 reads it, which is
 * presumably why it was never noticed.
 */
struct Rva007EDB10Time *Rva007EDB10( struct Rva007EDB10Time *pTime,
	unsigned int uSeconds )
{
	int iYear;
	int iYearDays;
	int iNextYear;
	int iDays;
	int iSeconds;
	int *pMonthDays;
	unsigned int uTime;

	uTime = uSeconds;
	iDays = uTime / 86400;
	iSeconds = uTime % 86400;

	pTime->m_second = iSeconds % 60;
	iSeconds = iSeconds / 60;
	pTime->m_minute = iSeconds % 60;
	iSeconds = iSeconds / 60;
	pTime->m_hour = iSeconds;

	for ( iYear = 1970; ; iYear = iNextYear )
	{
		iYearDays = ( ( iYear & 3 ) == 0
			&& ( iYear % 100 != 0 || iYear % 400 == 0 ) ) ? 366 : 365;

		if ( iDays < iYearDays )
		{
			break;
		}

		iNextYear = iDays / 366 + iYear;

		if ( iNextYear == iYear )
		{
			iNextYear++;
		}

		iDays -= ( iNextYear - iYear ) * 365;

		iDays += ( iYear - 1 ) / 4 - ( iYear - 1 ) / 100 + ( iYear - 1 ) / 400;
		iDays -= ( iNextYear - 1 ) / 4 - ( iNextYear - 1 ) / 100
			+ ( iNextYear - 1 ) / 400;
	}

	pTime->m_year = iYear - 1900;
	pTime->m_yearDay = iDays;

	pMonthDays = &g_Rva0112A530MonthDays[ ( iYearDays & 1 ) * 12 ];

	for ( pTime->m_month = 0; iDays >= *pMonthDays; pTime->m_month++ )
	{
		iDays -= *pMonthDays;
		pMonthDays++;
	}

	pTime->m_day = iDays + 1;
	pTime->m_isDst = 0;

	return pTime;
}

/* 0x007EDE00 IS THE INVERSE, AND IT IS A BINARY SEARCH RATHER THAN A FORMULA.
 * Instead of accumulating days per year the way an ordinary mktime would, it
 * searches the whole 32-bit timestamp space for the value whose decomposition
 * matches the caller's, calling 0x007EDB10 about thirty-two times.  That is a
 * deliberate trade: the forward direction is the only calendar code that has
 * to be right, and this direction cannot disagree with it.
 *
 * The local names below -- cmp, res, mid -- are RETAIL'S OWN, recovered from
 * the /GZ frame descriptor and from the strings the uninitialised-use checks
 * pass to __RTC_UninitUse.  Those checks are the compiler's, not the author's:
 * res and mid are assigned only inside the loop, so MSVC cannot prove they are
 * set by the time the return expression reads them.
 *
 * THE MIDPOINT IS COMPUTED OVERFLOW-SAFE -- half of each end plus the carry
 * they share -- which is necessary here and not merely careful, because hi
 * starts at 0xFFFFFFFF and the naive sum would wrap on the first iteration.
 *
 * THE SEARCH DOES NOT TERMINATE ON A MISS, and that is the sharp edge.  There
 * is no "not found" exit: the loop ends only on an exact match.  A target
 * before 1970 leaves res positive at mid == 0, so hi = mid - 1 wraps back to
 * 0xFFFFFFFF and the search returns to its starting interval forever.  THE
 * RANGE VALIDATION IN THE CALLER AT 0x007EF780 IS LOAD-BEARING FOR
 * TERMINATION, not just for correctness -- it is what guarantees the target
 * lies inside the searched space.
 *
 * THE RETURN IS A TERNARY THAT MSVC MADE BRANCHLESS.  `( res ? 0 : -1 ) & mid`
 * compiles at /Od to setne + dec + and, with no jump anywhere: this compiler
 * contracts the shape `x ? 0 : -1` into a mask even with optimisation off,
 * where the same value written as `( res != 0 ) - 1` gives a three-byte
 * `sub eax, 1` instead of the one-byte `dec`.  The bytes distinguish the two
 * spellings; nothing else does.  Since the loop only exits normally with res
 * zero, the mask is unreachable-false on every real path -- it matters only
 * for an empty interval, which the unsigned bounds make impossible.
 */
unsigned int Rva007EDE00( const struct Rva007EDB10Time *pTime )
{
	int res;
	struct Rva007EDB10Time cmp;
	unsigned int lo;
	unsigned int hi;
	unsigned int mid;

	lo = 0;
	hi = 0xFFFFFFFF;

	while ( lo <= hi )
	{
		mid = ( lo >> 1 ) + ( hi >> 1 ) + ( lo & hi & 1 );

		Rva007EDB10( &cmp, mid );

		res = cmp.m_year - pTime->m_year;

		if ( res == 0 )
		{
			res = cmp.m_month - pTime->m_month;

			if ( res == 0 )
			{
				res = cmp.m_day - pTime->m_day;

				if ( res == 0 )
				{
					res = cmp.m_hour - pTime->m_hour;

					if ( res == 0 )
					{
						res = cmp.m_minute - pTime->m_minute;

						if ( res == 0 )
						{
							res = cmp.m_second - pTime->m_second;

							if ( res == 0 )
							{
								break;
							}
						}
					}
				}
			}
		}

		if ( res > 0 )
		{
			hi = mid - 1;
		}
		else
		{
			lo = mid + 1;
		}
	}

	return ( res ? 0 : -1 ) & mid;
}

/* A 256-entry hex digit table.  Indexed by a SIGNED char, so a high-bit byte
 * reads before the table start, the same quirk the fold and class tables in
 * Y4TextToValue.c have. */
extern unsigned char g_Rva0112A110Hex[];

/* Declared rather than included: under /MD the CRT header marks memset
 * dllimport and the call becomes an indirect through the IAT, where retail
 * calls the import stub directly. */
void * __cdecl memset( void *dest, int c, unsigned int count );

/* The bounded digit scanner, and the current-time helper.
 *
 * NOTE ON THE SECOND ONE: it was landed in Y4DirtySockSocket.c declared void,
 * which is byte-neutral there -- time() leaves the result in eax and that body
 * disturbs nothing -- so the gate never contradicted it.  THIS CALLER USES THE
 * VALUE, which is what settled the question; the declaration there now reads
 * unsigned int and its translation unit still matches 40 of 40. */
const char *Rva007EFAB0( const char *text, int *value, int maxLength );
unsigned int Rva007FEF60( void );

/* 0x007EF780 PARSES A TIMESTAMP IN ANY OF THREE NOTATIONS and falls back to a
 * caller-supplied default, or to the current time, when it cannot.
 *
 * THE THREE NOTATIONS ARE TRIED IN ORDER AND ONLY THE FIRST CHARACTER PICKS
 * BETWEEN THEM.  A leading '$' means hexadecimal; a bare run of digits that
 * ENDS AT WHITESPACE means the value is already a timestamp and is taken
 * verbatim; anything else starting with a digit is parsed as a calendar date.
 * That middle test is the interesting one -- it parses the decimal number
 * first and then looks at where the scan STOPPED to decide whether it was a
 * timestamp at all, so "1234" is a timestamp and "1234-05-06" is a date, and
 * the two are told apart only after the fact.
 *
 * THE HEX PATH ACCEPTS FAR MORE THAN HEX.  It runs while the character is at
 * least '0', so every letter and most punctuation above '0' keeps it going,
 * folded through the table.  It stops at a space or a control character and
 * nowhere else, and it never checks for overflow.
 *
 * THE DATE FIELDS ARE SEPARATED BY ANY SINGLE NON-DIGIT.  One character is
 * skipped between fields, whatever it is, so hyphens, colons, slashes and
 * spaces all work and are never distinguished -- and exactly one is skipped,
 * so a date with two separators between fields loses the following field to
 * the scanner returning zero.
 *
 * VALIDATION IS ALL-OR-NOTHING AND SIGNALS THROUGH THE YEAR.  Any field out of
 * range zeroes m_year, which is then read as "invalid" -- so a bad SECOND
 * discards a perfectly good date rather than being clamped.  The ranges are
 * ordinary except the last: seconds are allowed up to 61, which is the C
 * standard's leap-second allowance rather than anything this code can use.
 *
 * THE YEAR RANGE IS LOAD-BEARING FOR TERMINATION, not just correctness.
 * 0x007EDE00 searches for a match and has no not-found exit, so a year below
 * 1970 would leave it looping forever; the 1970..2107 test here is what keeps
 * the target inside the space it searches.
 *
 * A RESULT OF ZERO IS INDISTINGUISHABLE FROM FAILURE.  The epoch itself parses
 * to 0 and is then replaced by the default, so this function cannot return the
 * first second of 1970 no matter what it is given.
 */
unsigned int Rva007EF780( const char *text, unsigned int uDefault )
{
	struct Rva007EDB10Time tm;
	unsigned int uDecimal;
	unsigned int uResult;

	uResult = 0;

	if ( text == 0 )
	{
		goto done;
	}

	if ( *text == '$' )
	{
		text++;

		for ( ; *text >= '0'; text++ )
		{
			uResult = ( uResult << 4 ) | g_Rva0112A110Hex[ *text ];
		}

		goto done;
	}

	if ( *text >= '0' && *text <= '9' )
	{
		if ( *Rva007EFAB0( text, (int *)&uDecimal, 0 ) <= ' ' )
		{
			uResult = uDecimal;
			goto done;
		}
	}

	/* A WRAPPING GUARD, NOT AN EARLY EXIT, and the bytes are what say so.  Both
	 * bounds here compile to far conditional jumps straight to the tail, which
	 * is the shape an if whose BLOCK ends there produces.  Written as two
	 * "goto done" statements each test inverts and jumps over an unconditional
	 * jump instead -- one instruction more, twice.  The probe just above is a
	 * genuine early exit and keeps that shape. */
	if ( *text >= '0' && *text <= '9' )
	{
		memset( &tm, 0, sizeof( tm ) );
		tm.m_isDst = -1;

		text = Rva007EFAB0( text, &tm.m_year, 4 );

		if ( ( *text < '0' || *text > '9' ) && *text != 0 )
		{
			text++;
		}

		text = Rva007EFAB0( text, &tm.m_month, 2 );

		if ( ( *text < '0' || *text > '9' ) && *text != 0 )
		{
			text++;
		}

		text = Rva007EFAB0( text, &tm.m_day, 2 );

		if ( ( *text < '0' || *text > '9' ) && *text != 0 )
		{
			text++;
		}

		text = Rva007EFAB0( text, &tm.m_hour, 2 );

		if ( ( *text < '0' || *text > '9' ) && *text != 0 )
		{
			text++;
		}

		text = Rva007EFAB0( text, &tm.m_minute, 2 );

		if ( ( *text < '0' || *text > '9' ) && *text != 0 )
		{
			text++;
		}

		text = Rva007EFAB0( text, &tm.m_second, 2 );

		if ( tm.m_year < 1970 || tm.m_year > 2107
			|| tm.m_month < 1 || tm.m_month > 12
			|| tm.m_day < 1 || tm.m_day > 31 )
		{
			tm.m_year = 0;
		}

		if ( tm.m_hour < 0 || tm.m_hour > 23
			|| tm.m_minute < 0 || tm.m_minute > 59
			|| tm.m_second < 0 || tm.m_second > 61 )
		{
			tm.m_year = 0;
		}

		if ( tm.m_year != 0 )
		{
			tm.m_month--;
			tm.m_year -= 1900;
			uResult = Rva007EDE00( &tm );
		}
	}

done:

	if ( uResult == 0 )
	{
		uResult = ( uDefault == 0 ) ? Rva007FEF60() : uDefault;
	}

	return uResult;
}

/* 0x007EFC20 PARSES A TIMESTAMP AND HANDS BACK THE DATE AND THE TIME AS TWO
 * PACKED INTEGERS, each field in its own byte-aligned slot.
 *
 * THE PACKING IS DECIMAL-READABLE IN HEX, which is the whole point of the
 * layout: the date comes out as 0xYYYYMMDD-in-hex-digit-positions -- year in
 * the top sixteen bits, month plus one in the next eight, day in the low eight
 * -- and the time as hour, minute, second in three bytes.  Printed as hex it
 * reads back as the date, which is what makes these values usable in a log or
 * a record field without a formatter.
 *
 * THE MONTH IS RESTORED TO ONE-BASED HERE and the year to its full value, both
 * undoing what the parser did on the way in.  So the packed form is the human
 * convention and the structure in between is the C one; neither side of this
 * function sees the other's numbering.
 *
 * THE OFFSET IS APPLIED AFTER PARSING, not before, so it shifts the RESULT
 * rather than the interpretation of the text.  It is added to an unsigned
 * timestamp, so a negative offset that takes the value below the epoch wraps
 * to a far-future date instead of failing.
 *
 * A PARSED VALUE OF 0 OR 1 IS REJECTED.  Zero is the parser's own failure
 * signal, but one is rejected too -- it is the default this passes in, so a
 * timestamp that comes back as exactly the default is treated as "the parse
 * did not produce anything".  That makes 1 January 1970, 00:00:01 unusable in
 * the same way the epoch second itself already was.
 *
 * BOTH OUTPUTS ARE OPTIONAL AND INDEPENDENT; passing null for both parses the
 * text and reports only whether it was valid.
 */
int Rva007EFC20( const char *text, int *pDate, int *pTime, int iOffset )
{
	struct Rva007EDB10Time *ptm;
	struct Rva007EDB10Time tm2;
	unsigned int uTime;

	uTime = Rva007EF780( text, 1 );

	if ( uTime <= 1 )
	{
		return -1;
	}

	ptm = Rva007EDB10( &tm2, uTime + iOffset );

	if ( ptm == 0 )
	{
		return -1;
	}

	if ( pDate != 0 )
	{
		*pDate = ( ( ptm->m_year + 1900 ) << 16 )
			| ( ( ptm->m_month + 1 ) << 8 ) | ptm->m_day;
	}

	if ( pTime != 0 )
	{
		*pTime = ( ptm->m_hour << 16 ) | ( ptm->m_minute << 8 ) | ptm->m_second;
	}

	return 0;
}

/* 0x007EFB20 IS THE SAME PARSE AS 0x007EFC20 DELIVERED FIELD BY FIELD, six
 * optional out-pointers instead of two packed integers.  The two are siblings
 * rather than one wrapping the other: both call the parser and the decomposer
 * themselves, and neither is written in terms of the other, so the packing
 * convention lives in exactly one of them and the field convention in the
 * other.
 *
 * THE SAME TWO ADJUSTMENTS ARE REPEATED HERE -- year plus 1900, month plus one
 * -- rather than shared with the packer.  So the human numbering is applied
 * twice in this translation unit, at the two places that face outward, and the
 * structure in between is C-numbered throughout.  A caller of either sees only
 * the convention it asks for.
 *
 * EVERY OUTPUT IS INDEPENDENTLY OPTIONAL and each is tested separately, so a
 * caller wanting only the hour pays for the whole parse and the whole
 * decomposition regardless -- there is no early exit once the work is done,
 * and no way to ask for less of it.
 */
int Rva007EFB20( const char *text, int *pYear, int *pMonth, int *pDay,
	int *pHour, int *pMinute, int *pSecond, int iOffset )
{
	struct Rva007EDB10Time *ptm;
	struct Rva007EDB10Time tm2;
	unsigned int uTime;

	uTime = Rva007EF780( text, 1 );

	if ( uTime <= 1 )
	{
		return -1;
	}

	ptm = Rva007EDB10( &tm2, uTime + iOffset );

	if ( ptm == 0 )
	{
		return -1;
	}

	if ( pYear != 0 )
	{
		*pYear = ptm->m_year + 1900;
	}

	if ( pMonth != 0 )
	{
		*pMonth = ptm->m_month + 1;
	}

	if ( pDay != 0 )
	{
		*pDay = ptm->m_day;
	}

	if ( pHour != 0 )
	{
		*pHour = ptm->m_hour;
	}

	if ( pMinute != 0 )
	{
		*pMinute = ptm->m_minute;
	}

	if ( pSecond != 0 )
	{
		*pSecond = ptm->m_second;
	}

	return 0;
}
