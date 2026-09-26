// cl: /Od /GZ /RTCu /MD /DNDEBUG
/* EA DirtySock -- the comm layer's message digest, /Od with /GZ.  Placement is
 * by address neighbourhood within the 0x00810000 group.
 */

/* The digest state.  THE SHAPE IS THE ONLY EVIDENCE FOR WHAT IT IS: a running
 * BYTE count at the front, sixteen bytes of chaining state, and a 64-byte
 * block that is flushed whenever it fills.  Four state words with a 64-byte
 * block is MD5's shape, but nothing here proves the algorithm -- that is in
 * the transform at 0x00810120, which is not converted yet -- so the fields are
 * named for what this function does with them and not for what they probably
 * are.  Note the count is in BYTES, where MD5 conventionally keeps bits. */
struct Rva00810060Context
{
	unsigned int m_count;			/* +0x00 */
	unsigned int m_state[ 4 ];		/* +0x04 */
	unsigned char m_block[ 0x40 ];		/* +0x14 */
};

void Rva00810020( struct Rva00810060Context *context )
{
	context->m_count = 0;
	context->m_state[ 0 ] = 0x67452301;
	context->m_state[ 1 ] = 0xEFCDAB89;
	context->m_state[ 2 ] = 0x98BADCFE;
	context->m_state[ 3 ] = 0x10325476;
}

void Rva00810120( struct Rva00810060Context *context );

/* 0x00810060 FEEDS BYTES INTO THE DIGEST, flushing whenever the block fills.
 *
 * A NEGATIVE LENGTH MEANS "NUL-TERMINATED", and the measuring loop runs before
 * anything else -- so the same entry point takes a counted buffer or a C
 * string, chosen by the sign of an argument rather than by a separate
 * function.  A length of zero is not the same as a negative one: zero feeds
 * nothing, negative measures.
 *
 * THE FILL POSITION IS RECOVERED FROM THE COUNT rather than stored, by masking
 * the running total with 0x3F.  So the context carries no separate cursor and
 * the two can never disagree -- but it also means the count and the block
 * position are the same field, and anything that adjusts one moves the other.
 *
 * THE FLUSH TEST IS AN EQUALITY, not a bound.  It fires only on exactly 0x40,
 * which is safe because the position is masked on entry and advanced one byte
 * at a time -- an invariant of this loop rather than anything checked here.
 */
void Rva00810060( struct Rva00810060Context *context, const unsigned char *data,
	int length )
{
	int iFill;
	const unsigned char *p;

	p = data;

	if ( length < 0 )
	{
		for ( length = 0; p[ length ] != 0; length++ )
		{
		}
	}

	iFill = context->m_count & 0x3F;

	for ( ; length > 0; length-- )
	{
		context->m_block[ iFill ] = *p;
		iFill++;
		p++;
		context->m_count++;

		if ( iFill == 0x40 )
		{
			Rva00810120( context );
			iFill = 0;
		}
	}
}

/* 0x00810120 IS THE MD5 BLOCK TRANSFORM, sixty-four rounds written out in
 * full.  Retail's own name for the message schedule, from the /GZ frame
 * descriptor, is uData.
 *
 * THIS IS WHAT SETTLES THE ALGORITHM the update at 0x00810060 could only
 * suggest.  The four round functions, the shift table, the message-index
 * schedule and all sixty-four sine constants are RFC 1321's exactly -- eight
 * of them were checked against the bytes before the rest were generated from
 * the standard tables, so the match is verified at both ends and not assumed
 * from the first constant alone.
 *
 * THE THIRD ROUND FUNCTION IS SPELLED THE SHORT WAY.  RFC 1321 defines the
 * first two as (x&y)|(~x&z) and (x&z)|(y&~z); retail computes them as
 * ((y^z)&x)^z and ((x^y)&z)^y -- the well-known equivalent that saves an
 * operation.  A reader checking against the RFC will not find these forms
 * there, and they are not an approximation: they agree on every input.
 *
 * THE SCHEDULE IS BUILT BACKWARDS, from the end of the block towards the
 * start, filling uData from index fifteen down.  Each word is assembled
 * little-endian out of four descending byte reads, so the cursor walks the
 * block exactly once in reverse rather than indexing forwards.
 *
 * THE LOADING LOOP REUSES THE STATE VARIABLES.  Its counter is the same local
 * that later holds a, and its accumulator the same one that later holds b --
 * so the two phases share storage and the state is only fetched from the
 * context after the schedule is complete.  That is why the /GZ
 * uninitialised-use check fires here at all: uData is written in a loop the
 * compiler cannot prove runs.
 */
void Rva00810120( struct Rva00810060Context *context )
{
	unsigned int uData[ 0x10 ];
	unsigned int a;
	unsigned int b;
	unsigned int c;
	unsigned int d;
	unsigned char *p;

	p = ( unsigned char * )context + 0x54;
	a = 0x10;

	while ( a > 0 )
	{
		/* THE DECREMENT IS INSIDE THE DEREFERENCE.  Written as a separate
		 * statement the byte load moves after the shift; written on the
		 * right of the sum the addition changes direction.  Only the
		 * pre-decrement form puts the pointer step first, the byte load
		 * second and the shifted accumulator as the addition's
		 * destination -- three spellings that differ by no instructions at
		 * all, only by which register ends up holding the result. */
		b = *--p;
		b = ( b << 8 ) + *--p;
		b = ( b << 8 ) + *--p;
		b = ( b << 8 ) + *--p;
		a--;
		uData[ a ] = b;
	}

	a = context->m_state[ 0 ];
	b = context->m_state[ 1 ];
	c = context->m_state[ 2 ];
	d = context->m_state[ 3 ];

	a += ( ( ( c ^ d ) & b ) ^ d ) + uData[ 0 ] + 0xD76AA478;
	a = ( a << 7 ) | ( a >> 25 );
	a += b;

	d += ( ( ( b ^ c ) & a ) ^ c ) + uData[ 1 ] + 0xE8C7B756;
	d = ( d << 12 ) | ( d >> 20 );
	d += a;

	c += ( ( ( a ^ b ) & d ) ^ b ) + uData[ 2 ] + 0x242070DB;
	c = ( c << 17 ) | ( c >> 15 );
	c += d;

	b += ( ( ( d ^ a ) & c ) ^ a ) + uData[ 3 ] + 0xC1BDCEEE;
	b = ( b << 22 ) | ( b >> 10 );
	b += c;

	a += ( ( ( c ^ d ) & b ) ^ d ) + uData[ 4 ] + 0xF57C0FAF;
	a = ( a << 7 ) | ( a >> 25 );
	a += b;

	d += ( ( ( b ^ c ) & a ) ^ c ) + uData[ 5 ] + 0x4787C62A;
	d = ( d << 12 ) | ( d >> 20 );
	d += a;

	c += ( ( ( a ^ b ) & d ) ^ b ) + uData[ 6 ] + 0xA8304613;
	c = ( c << 17 ) | ( c >> 15 );
	c += d;

	b += ( ( ( d ^ a ) & c ) ^ a ) + uData[ 7 ] + 0xFD469501;
	b = ( b << 22 ) | ( b >> 10 );
	b += c;

	a += ( ( ( c ^ d ) & b ) ^ d ) + uData[ 8 ] + 0x698098D8;
	a = ( a << 7 ) | ( a >> 25 );
	a += b;

	d += ( ( ( b ^ c ) & a ) ^ c ) + uData[ 9 ] + 0x8B44F7AF;
	d = ( d << 12 ) | ( d >> 20 );
	d += a;

	c += ( ( ( a ^ b ) & d ) ^ b ) + uData[ 10 ] + 0xFFFF5BB1;
	c = ( c << 17 ) | ( c >> 15 );
	c += d;

	b += ( ( ( d ^ a ) & c ) ^ a ) + uData[ 11 ] + 0x895CD7BE;
	b = ( b << 22 ) | ( b >> 10 );
	b += c;

	a += ( ( ( c ^ d ) & b ) ^ d ) + uData[ 12 ] + 0x6B901122;
	a = ( a << 7 ) | ( a >> 25 );
	a += b;

	d += ( ( ( b ^ c ) & a ) ^ c ) + uData[ 13 ] + 0xFD987193;
	d = ( d << 12 ) | ( d >> 20 );
	d += a;

	c += ( ( ( a ^ b ) & d ) ^ b ) + uData[ 14 ] + 0xA679438E;
	c = ( c << 17 ) | ( c >> 15 );
	c += d;

	b += ( ( ( d ^ a ) & c ) ^ a ) + uData[ 15 ] + 0x49B40821;
	b = ( b << 22 ) | ( b >> 10 );
	b += c;

	a += ( ( ( b ^ c ) & d ) ^ c ) + uData[ 1 ] + 0xF61E2562;
	a = ( a << 5 ) | ( a >> 27 );
	a += b;

	d += ( ( ( a ^ b ) & c ) ^ b ) + uData[ 6 ] + 0xC040B340;
	d = ( d << 9 ) | ( d >> 23 );
	d += a;

	c += ( ( ( d ^ a ) & b ) ^ a ) + uData[ 11 ] + 0x265E5A51;
	c = ( c << 14 ) | ( c >> 18 );
	c += d;

	b += ( ( ( c ^ d ) & a ) ^ d ) + uData[ 0 ] + 0xE9B6C7AA;
	b = ( b << 20 ) | ( b >> 12 );
	b += c;

	a += ( ( ( b ^ c ) & d ) ^ c ) + uData[ 5 ] + 0xD62F105D;
	a = ( a << 5 ) | ( a >> 27 );
	a += b;

	d += ( ( ( a ^ b ) & c ) ^ b ) + uData[ 10 ] + 0x02441453;
	d = ( d << 9 ) | ( d >> 23 );
	d += a;

	c += ( ( ( d ^ a ) & b ) ^ a ) + uData[ 15 ] + 0xD8A1E681;
	c = ( c << 14 ) | ( c >> 18 );
	c += d;

	b += ( ( ( c ^ d ) & a ) ^ d ) + uData[ 4 ] + 0xE7D3FBC8;
	b = ( b << 20 ) | ( b >> 12 );
	b += c;

	a += ( ( ( b ^ c ) & d ) ^ c ) + uData[ 9 ] + 0x21E1CDE6;
	a = ( a << 5 ) | ( a >> 27 );
	a += b;

	d += ( ( ( a ^ b ) & c ) ^ b ) + uData[ 14 ] + 0xC33707D6;
	d = ( d << 9 ) | ( d >> 23 );
	d += a;

	c += ( ( ( d ^ a ) & b ) ^ a ) + uData[ 3 ] + 0xF4D50D87;
	c = ( c << 14 ) | ( c >> 18 );
	c += d;

	b += ( ( ( c ^ d ) & a ) ^ d ) + uData[ 8 ] + 0x455A14ED;
	b = ( b << 20 ) | ( b >> 12 );
	b += c;

	a += ( ( ( b ^ c ) & d ) ^ c ) + uData[ 13 ] + 0xA9E3E905;
	a = ( a << 5 ) | ( a >> 27 );
	a += b;

	d += ( ( ( a ^ b ) & c ) ^ b ) + uData[ 2 ] + 0xFCEFA3F8;
	d = ( d << 9 ) | ( d >> 23 );
	d += a;

	c += ( ( ( d ^ a ) & b ) ^ a ) + uData[ 7 ] + 0x676F02D9;
	c = ( c << 14 ) | ( c >> 18 );
	c += d;

	b += ( ( ( c ^ d ) & a ) ^ d ) + uData[ 12 ] + 0x8D2A4C8A;
	b = ( b << 20 ) | ( b >> 12 );
	b += c;

	a += ( b ^ c ^ d ) + uData[ 5 ] + 0xFFFA3942;
	a = ( a << 4 ) | ( a >> 28 );
	a += b;

	d += ( a ^ b ^ c ) + uData[ 8 ] + 0x8771F681;
	d = ( d << 11 ) | ( d >> 21 );
	d += a;

	c += ( d ^ a ^ b ) + uData[ 11 ] + 0x6D9D6122;
	c = ( c << 16 ) | ( c >> 16 );
	c += d;

	b += ( c ^ d ^ a ) + uData[ 14 ] + 0xFDE5380C;
	b = ( b << 23 ) | ( b >> 9 );
	b += c;

	a += ( b ^ c ^ d ) + uData[ 1 ] + 0xA4BEEA44;
	a = ( a << 4 ) | ( a >> 28 );
	a += b;

	d += ( a ^ b ^ c ) + uData[ 4 ] + 0x4BDECFA9;
	d = ( d << 11 ) | ( d >> 21 );
	d += a;

	c += ( d ^ a ^ b ) + uData[ 7 ] + 0xF6BB4B60;
	c = ( c << 16 ) | ( c >> 16 );
	c += d;

	b += ( c ^ d ^ a ) + uData[ 10 ] + 0xBEBFBC70;
	b = ( b << 23 ) | ( b >> 9 );
	b += c;

	a += ( b ^ c ^ d ) + uData[ 13 ] + 0x289B7EC6;
	a = ( a << 4 ) | ( a >> 28 );
	a += b;

	d += ( a ^ b ^ c ) + uData[ 0 ] + 0xEAA127FA;
	d = ( d << 11 ) | ( d >> 21 );
	d += a;

	c += ( d ^ a ^ b ) + uData[ 3 ] + 0xD4EF3085;
	c = ( c << 16 ) | ( c >> 16 );
	c += d;

	b += ( c ^ d ^ a ) + uData[ 6 ] + 0x04881D05;
	b = ( b << 23 ) | ( b >> 9 );
	b += c;

	a += ( b ^ c ^ d ) + uData[ 9 ] + 0xD9D4D039;
	a = ( a << 4 ) | ( a >> 28 );
	a += b;

	d += ( a ^ b ^ c ) + uData[ 12 ] + 0xE6DB99E5;
	d = ( d << 11 ) | ( d >> 21 );
	d += a;

	c += ( d ^ a ^ b ) + uData[ 15 ] + 0x1FA27CF8;
	c = ( c << 16 ) | ( c >> 16 );
	c += d;

	b += ( c ^ d ^ a ) + uData[ 2 ] + 0xC4AC5665;
	b = ( b << 23 ) | ( b >> 9 );
	b += c;

	a += ( ( ~d | b ) ^ c ) + uData[ 0 ] + 0xF4292244;
	a = ( a << 6 ) | ( a >> 26 );
	a += b;

	d += ( ( ~c | a ) ^ b ) + uData[ 7 ] + 0x432AFF97;
	d = ( d << 10 ) | ( d >> 22 );
	d += a;

	c += ( ( ~b | d ) ^ a ) + uData[ 14 ] + 0xAB9423A7;
	c = ( c << 15 ) | ( c >> 17 );
	c += d;

	b += ( ( ~a | c ) ^ d ) + uData[ 5 ] + 0xFC93A039;
	b = ( b << 21 ) | ( b >> 11 );
	b += c;

	a += ( ( ~d | b ) ^ c ) + uData[ 12 ] + 0x655B59C3;
	a = ( a << 6 ) | ( a >> 26 );
	a += b;

	d += ( ( ~c | a ) ^ b ) + uData[ 3 ] + 0x8F0CCC92;
	d = ( d << 10 ) | ( d >> 22 );
	d += a;

	c += ( ( ~b | d ) ^ a ) + uData[ 10 ] + 0xFFEFF47D;
	c = ( c << 15 ) | ( c >> 17 );
	c += d;

	b += ( ( ~a | c ) ^ d ) + uData[ 1 ] + 0x85845DD1;
	b = ( b << 21 ) | ( b >> 11 );
	b += c;

	a += ( ( ~d | b ) ^ c ) + uData[ 8 ] + 0x6FA87E4F;
	a = ( a << 6 ) | ( a >> 26 );
	a += b;

	d += ( ( ~c | a ) ^ b ) + uData[ 15 ] + 0xFE2CE6E0;
	d = ( d << 10 ) | ( d >> 22 );
	d += a;

	c += ( ( ~b | d ) ^ a ) + uData[ 6 ] + 0xA3014314;
	c = ( c << 15 ) | ( c >> 17 );
	c += d;

	b += ( ( ~a | c ) ^ d ) + uData[ 13 ] + 0x4E0811A1;
	b = ( b << 21 ) | ( b >> 11 );
	b += c;

	a += ( ( ~d | b ) ^ c ) + uData[ 4 ] + 0xF7537E82;
	a = ( a << 6 ) | ( a >> 26 );
	a += b;

	d += ( ( ~c | a ) ^ b ) + uData[ 11 ] + 0xBD3AF235;
	d = ( d << 10 ) | ( d >> 22 );
	d += a;

	c += ( ( ~b | d ) ^ a ) + uData[ 2 ] + 0x2AD7D2BB;
	c = ( c << 15 ) | ( c >> 17 );
	c += d;

	b += ( ( ~a | c ) ^ d ) + uData[ 9 ] + 0xEB86D391;
	b = ( b << 21 ) | ( b >> 11 );
	b += c;
	context->m_state[ 0 ] += a;
	context->m_state[ 1 ] += b;
	context->m_state[ 2 ] += c;
	context->m_state[ 3 ] += d;
}

/* A POINTER to the hex digits, not the digits themselves -- the code loads a
 * dword from this address and indexes through it, so the table can be
 * retargeted at run time.  It points into the same short run of writable data
 * that holds the module's other configurable bytes. */
extern char *g_Rva012C4998HexDigits;

/* 0x00810FF0 FINISHES THE DIGEST AND FORMATS IT, padding the block, appending
 * the length, running the final transform and writing the result out.
 *
 * THE PADDING BYTE IS A VARIABLE THAT ZEROES ITSELF.  It starts at 0x80 and is
 * set to zero immediately after the first store, so one loop writes the
 * required 0x80 followed by as many zeros as it takes -- no separate first
 * write, and no counter distinguishing the two cases.
 *
 * IT IS A DO-WHILE, so it always writes at least one byte.  That is what makes
 * a block already at the length offset pad out a WHOLE FURTHER BLOCK rather
 * than none, which is required and would be wrong with a while.
 *
 * THE LENGTH IS STORED AS FIVE BYTES AND THREE ZEROS.  The context counts
 * BYTES, so the bit count is the byte count times eight -- thirty-five bits,
 * which needs five bytes -- and the top three of the eight-byte field are
 * written as literal zeros rather than computed.  A message of 512 MB or more
 * would need the sixth byte and silently gets a wrong length.
 *
 * THE OUTPUT FORMAT IS CHOSEN BY THE BUFFER SIZE, not by a flag: 0x21 bytes or
 * more gets thirty-two hex characters and a terminator, anything smaller gets
 * RAW BYTES and no terminator, truncated to the size given.  So the same call
 * produces text or binary depending on a number, and a caller passing 33 for a
 * 16-byte buffer gets neither what it asked for nor an error.
 */
void Rva00810FF0( struct Rva00810060Context *context, char *out, int outSize )
{
	int i;
	unsigned int uWord;
	unsigned char cPad;
	char *pOut;

	uWord = 0;
	cPad = 0x80;
	pOut = out;

	i = context->m_count & 0x3F;

	/* AN EXPLICIT BREAK, not a do-while condition.  The two compile to the
	 * same test but retail carries the pair of trampolines a break produces
	 * -- one jump to the exit and one back to the top -- where a do-while
	 * branches straight back and saves four bytes. */
	for ( ;; )
	{
		context->m_block[ i ] = cPad;
		i++;
		cPad = 0;

		if ( i == 0x40 )
		{
			Rva00810120( context );
			i = 0;
		}

		if ( i == 0x38 )
		{
			break;
		}
	}

	context->m_block[ 0x38 ] = ( unsigned char )( context->m_count << 3 );
	context->m_block[ 0x39 ] = ( unsigned char )( context->m_count >> 5 );
	context->m_block[ 0x3A ] = ( unsigned char )( context->m_count >> 13 );
	context->m_block[ 0x3B ] = ( unsigned char )( context->m_count >> 21 );
	context->m_block[ 0x3C ] = ( unsigned char )( context->m_count >> 29 );
	context->m_block[ 0x3D ] = 0;
	context->m_block[ 0x3E ] = 0;
	context->m_block[ 0x3F ] = 0;

	Rva00810120( context );

	for ( i = 0; i < 0x10; i++ )
	{
		if ( ( i & 3 ) == 0 )
		{
			uWord = context->m_state[ i >> 2 ];
		}

		if ( outSize >= 0x21 )
		{
			*pOut = g_Rva012C4998HexDigits[ ( uWord >> 4 ) & 0xF ];
			pOut++;
			*pOut = g_Rva012C4998HexDigits[ uWord & 0xF ];
			pOut++;
		}
		else if ( i < outSize )
		{
			*pOut = ( char )uWord;
			pOut++;
		}

		uWord >>= 8;
	}

	if ( outSize >= 0x21 )
	{
		*pOut = 0;
	}
}
