// cl: /Ob1
/* A small CALENDAR DATE class sitting just below the DirtySock text helpers.
 * It is a separate translation unit from those because it is built with
 * OPTIMISATION ON: no /GZ local fill, no frame pointer, a switch lowered to an
 * index byte table plus a jump table, and a modulo folded into `and eax,
 * 0x80000003` with a sign fixup.  The socket and text units are /Od /GZ, so
 * this cannot share a file with them.
 *
 * THE OBJECT LAYOUT COMES FROM THE THREE BODIES AGREEING.  The constructor
 * writes +0x00 and +0x08 and passes 1 to the day setter; the setter validates
 * against a per-month length and writes +0x04; and the leap-year test is
 * handed +0x08.  So +0x00 is the month, +0x04 the day, +0x08 the year, and
 * nothing here is inferred from field order alone.
 */

/* Not a member: the setter loads the YEAR VALUE into ecx before calling, where
 * a member call would have loaded the object pointer.  One integer argument in
 * ecx and nothing on the stack is __fastcall. */
bool __fastcall Rva007FF3F0IsLeapYear( int year );

struct Rva007FF700Date
{
	int m_month;    /* +0x00 */
	int m_day;      /* +0x04 */
	int m_year;     /* +0x08 */

	Rva007FF700Date();
	int setDay( int day );
};

/* The ordinary rule, and the bytes show all three tests: divisible by four,
 * except centuries, except every fourth century.  The first test compiles to
 * `and eax, 0x80000003` with a decrement/or/increment fixup rather than a
 * divide -- that fixup is what makes it correct for NEGATIVE years, which a
 * plain mask would get wrong. */
bool __fastcall Rva007FF3F0IsLeapYear( int year )
{
	/* THE GROUPING IS READ FROM THE JUMP TARGETS, and it is not the textbook
	 * one.  When the divisible-by-four test FAILS, retail does not jump to
	 * "false" -- it jumps to the divisible-by-400 test.  That rules out the
	 * usual `y%%4==0 && (y%%100!=0 || y%%400==0)` spelling, which can only
	 * reach the 400 test after the 4 test has passed, and identifies the
	 * equivalent regrouping below.  Both compute the same answer; only one
	 * compiles to these bytes. */
	if ( ( year % 4 == 0 && year % 100 != 0 ) || year % 400 == 0 )
		return true;
	else
		return false;
}

/* Default state is 1 January 1900.  The day goes in through the setter rather
 * than by direct assignment, so it is range-checked like any other day. */
Rva007FF700Date::Rva007FF700Date()
{
	m_month = 1;
	m_year = 1900;
	setDay( 1 );
}

/* Returns 0 on success, -2 for a day outside the month, and -1 for a month
 * that is not 1..12 -- so the two failures are DISTINGUISHABLE, which matters
 * because an out-of-range day leaves a valid object while a bad month means
 * the object was already inconsistent.
 *
 * February's length is 28 plus the leap flag, computed as an arithmetic
 * conversion of the bool rather than a branch.
 */
int Rva007FF700Date::setDay( int day )
{
	int iLength;

	switch ( m_month )
	{
	case 2:
		/* The conversion is written out.  Adding the bool directly gives a
		 * `movzx eax, al`, which trusts the callee to return 0 or 1; retail
		 * normalises with neg/sbb/neg, and that is what an explicit ternary
		 * emits. */
		iLength = 28 + ( Rva007FF3F0IsLeapYear( m_year ) ? 1 : 0 );
		break;

	case 4:
	case 6:
	case 9:
	case 11:
		iLength = 30;
		break;

	case 1:
	case 3:
	case 5:
	case 7:
	case 8:
	case 10:
	case 12:
		iLength = 31;
		break;

	default:
		return -1;
	}

	if ( day <= 0 || day > iLength )
		return -2;

	m_day = day;
	return 0;
}
