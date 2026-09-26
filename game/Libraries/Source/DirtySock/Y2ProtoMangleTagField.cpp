// cl: /DNDEBUG /MD /GX /Od /GZ /GS
// EA's DirtySock ProtoMangle -- the tag-field reader its response parsing runs
// on.  See Y2ProtoMangleHelpers.cpp for why this directory and this compiler
// line; every body here carries the same /Od /GZ signature.
//
// WHY THIS IS A SEPARATE TRANSLATION UNIT, and it is not a preference.  These
// bodies call strstr and strchr with a DIRECT rel32 to the import stubs at
// 0x009F709C and 0x009F6DFA.  MSVC 7.1's <string.h> declares exactly those two
// _CRTIMP -- unlike memcpy, memset, strcpy and strlen, which it declares plain
// on x86 -- so a TU that includes that header calls them through
// __imp__strstr instead and cannot reproduce these bytes.  Y2ProtoMangleHelpers
// does include <string.h>, so these bodies cannot live there.  Declaring them
// here is what reproduces retail, and it is the same move that file already
// makes for sprintf.
extern "C" char *strstr( const char *text, const char *find );
extern "C" char *strchr( const char *text, int c );

// 0x00805710 READS ONE NAMED FIELD out of a text blob, and the two characters
// it searches for are what say so: it finds the tag, then finds the '=' after
// it, then copies until '\r' or '\n'.  That is a line-oriented "tag=value"
// response, which is the shape the callers' tag strings -- "status", "peerIP",
// "peerPort" -- already implied.
//
// THE SIZE IS DECREMENTED IN THE PARAMETER SLOT, not into a local, so the
// terminator always fits: the copy loop stops at destSize - 1 and the store
// after it lands on the last byte.  Retail reuses the caller's slot for that,
// which is visible and is not a saving I chose.
//
// THE FLAG SELECTS A SECOND RETURN VALUE.  With flags == 1 the body looks for a
// '-' after the tag and returns the single digit following it, rejecting
// anything outside 0..9; otherwise it returns a plain 1.  Both are overwritten
// by -1 when the tag is missing entirely, and -1 is also what a malformed digit
// gives -- so the caller cannot tell "absent" from "malformed", only from
// "present".
//
// The value is still copied when the digit is malformed: the '=' search and the
// copy sit AFTER the digit block rather than inside its success arm.  The
// trailing i++ after the terminator is retail's, dead, and reproduced -- it is
// what makes the store a `dest[ i++ ] = 0`.
//
// THE TWO TERMINATORS ARE LOOP CONDITIONS, NOT BREAKS.  Retail's tests jump
// straight out with one `je` each; a break inside the body compiles to `jne`
// over a `jmp` -- two instructions where retail has one, at both sites, which
// then shifts every displacement after them.  The three-part && condition is
// the only spelling that reproduces it.
int Rva00805710TagFieldGet( char *dest, int destSize, const char *text,
		const char *tag, int flags )
{
	const char *value;
	int i;
	int result;
	const char *digit;

	result = -1;
	destSize -= 1;

	value = strstr( text, tag );
	if( value != 0 )
	{
		if( flags == 1 )
		{
			digit = strchr( value, '-' );
			if( digit != 0 )
			{
				result = digit[ 1 ] - '0';
				if( result < 0 || result > 9 )
					result = -1;
			}
		}
		else
		{
			result = 1;
		}

		value = strchr( value, '=' );
		if( value != 0 )
		{
			i = 0;
			++value;
			for( ; i < destSize && value[ i ] != '\r'
					&& value[ i ] != '\n'; ++i )
			{
				dest[ i ] = value[ i ];
			}
			dest[ i++ ] = 0;
		}
	}

	return result;
}

// 0x00805830: find a marker and step past the newlines that follow it.  The
// null check sits OUTSIDE the loop -- retail tests once and jumps clear -- so
// this is an `if` wrapping a `while`, not a single condition; a combined test
// re-checks the pointer on every iteration and is longer.  The character is
// read with movsx, so the text is plain signed char.
const char *Rva00805830SkipNewlines( const char *text, const char *find )
{
	text = strstr( text, find );
	if( text != 0 )
	{
		while( *text == '\n' )
			++text;
	}
	return text;
}

// strncmp is _CRTIMP in <string.h> too; strlen is not, but declaring both here
// keeps this TU free of that header for the same reason the two above are.
extern "C" int strncmp( const char *left, const char *right, unsigned int count );
extern "C" unsigned int strlen( const char *text );

// The three status words, read out of retail's .rdata at 0x012C3D28,
// 0x012C3D30 and 0x012C3D38 with the pointer table indexing them at
// 0x012C3D40.  Their ORDER is what the status code means: 0 success, 1 probe,
// 2 failure -- the body returns the index, so the table is the enumeration.
static const char *s_status[ 3 ] = { "success", "probe", "failure" };

// 0x00805620 READS THE STATUS LINE and hands back the body after it.  It pulls
// the "status" tag, matches it against the three words above by index, and
// leaves the answer through the caller's int pointer -- preset to -1, so an
// unrecognised word is reported as no status at all rather than as a fourth
// one.  What it RETURNS is the text after the first newline following "\n",
// i.e. the payload, so one call splits a response into status and body.
//
// THE MATCH IS PREFIX-ONLY AND THAT IS RETAIL'S CHOICE, not a simplification:
// the length handed to strncmp is the length of the TABLE entry, not of the
// parsed word, so a status of "successful" matches "success".  The lengths are
// computed inside the loop, once per candidate, because MSVC evaluates
// arguments right to left and the count is the rightmost.
//
// THE GUARD IS `!= 0`, WHICH IS ALWAYS TRUE HERE.  0x00805710 returns 1 when
// the tag is present and -1 when it is not, never 0, so retail's `test eax,eax`
// admits the missing-tag case as well; the loop then simply matches nothing and
// the -1 preset stands.  A `> 0` test would be the obvious intent and is not
// what the bytes do.
const char *Rva00805620ParseStatus( const char *text, int *status )
{
	char strCmd[ 0x20 ];
	int i;

	*status = -1;

	if( Rva00805710TagFieldGet( strCmd, 0x20, text, "status", 0 ) != 0 )
	{
		for( i = 0; i < 3; ++i )
		{
			if( strncmp( strCmd, s_status[ i ], strlen( s_status[ i ] ) ) == 0 )
			{
				*status = i;
				break;
			}
		}
	}

	return Rva00805830SkipNewlines( text, "\n" );
}
