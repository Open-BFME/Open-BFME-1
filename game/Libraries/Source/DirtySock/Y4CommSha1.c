// cl: /Od /GZ /MD /DNDEBUG
/* EA DirtySock -- a SHA-1 implementation, /Od with /GZ.  Separate from the MD5
 * in Y4CommDigest.c: different context layout, different transform, and the
 * two are not related by anything but sitting in the same address range.
 */

/* THE ALGORITHM IS EVIDENCED, not inferred from the shape.  The transform at
 * 0x00811310 contains all four SHA-1 round constants, its state is five words
 * rather than four, and retail's own name for its message schedule -- from the
 * /GZ frame descriptor -- is W, 0x140 bytes, which is eighty words: SHA-1's
 * notation and its expanded schedule exactly. */
struct Rva008111D0Context
{
	unsigned int m_count;			/* +0x00, bytes already hashed */
	unsigned int m_fill;			/* +0x04, bytes waiting in the block */
	unsigned int m_state[ 5 ];		/* +0x08 */
	unsigned char m_block[ 0x40 ];		/* +0x1C */
};

void Rva00811180( struct Rva008111D0Context *context )
{
	context->m_count = 0;
	context->m_fill = 0;
	context->m_state[ 0 ] = 0x67452301;
	context->m_state[ 1 ] = 0xEFCDAB89;
	context->m_state[ 2 ] = 0x98BADCFE;
	context->m_state[ 3 ] = 0x10325476;
	context->m_state[ 4 ] = 0xC3D2E1F0;
}

void Rva00811310( struct Rva008111D0Context *context,
	const unsigned char *block );

void * __cdecl memcpy( void *dest, const void *src, unsigned int count );

/* 0x008111D0 FEEDS BYTES INTO THE SHA-1 STATE.  Where the MD5 update in
 * Y4CommDigest.c copies ONE BYTE AT A TIME through a masked cursor, this one
 * is written the other way round: top up the partial block with memcpy,
 * transform whole blocks straight out of the caller's buffer, then stash the
 * remainder.  Two digests in one library, two entirely different update
 * strategies.
 *
 * THE MIDDLE LOOP NEVER COPIES.  Full blocks are hashed in place from the
 * caller's memory, so a large call touches the context's own block buffer only
 * at the two ends.  That is the reason the transform takes a block POINTER
 * here while MD5's took only the context.
 *
 * THE FILL FIELD IS STORED, NOT DERIVED.  MD5 recovers its position by masking
 * the running count; this keeps a separate counter, so the two fields can in
 * principle disagree -- and the count is advanced only in units of 0x40, never
 * by the partial remainder, which is what makes that safe.
 *
 * THE TOP-UP BRANCH DOES NOT FALL THROUGH TO THE FLUSH.  If the partial block
 * is completed exactly it transforms and resets; otherwise it just advances
 * the fill and the whole call ends with the block still partial.  Both paths
 * then reach the same middle loop, which does nothing when the input was
 * short.
 */
void Rva008111D0( struct Rva008111D0Context *context, const char *data,
	unsigned int length )
{
	unsigned int uRoom;
	unsigned int uCopied;

	if ( context->m_fill != 0 )
	{
		uRoom = 0x40 - context->m_fill;
		uCopied = ( uRoom > length ) ? length : uRoom;

		memcpy( context->m_block + context->m_fill, data, uCopied );

		data += uCopied;
		length -= uCopied;

		if ( uCopied == uRoom )
		{
			Rva00811310( context, context->m_block );
			context->m_count += 0x40;
			context->m_fill = 0;
		}
		else
		{
			context->m_fill += uCopied;
		}
	}

	while ( length >= 0x40 )
	{
		Rva00811310( context, ( const unsigned char * )data );
		context->m_count += 0x40;
		length -= 0x40;
		data += 0x40;
	}

	if ( length != 0 )
	{
		memcpy( context->m_block + context->m_fill, data, length );
		context->m_fill += length;
	}
}

/* 0x00811310 IS THE SHA-1 BLOCK TRANSFORM.  Retail's own name for the message
 * schedule, from the /GZ frame descriptor, is W -- 0x140 bytes, eighty words,
 * SHA-1's own notation.
 *
 * IT IS ROLLED, NOT UNROLLED, which is the visible difference from the MD5
 * transform beside it: four loops of twenty rounds each rather than sixty-four
 * written-out rounds, and 891 bytes against 3765.  The MD5 in this library
 * spells every round; this one does not.  Two primitives, two styles, in one
 * codebase.
 *
 * THE SCHEDULE IS BUILT BIG-ENDIAN and forwards, from index zero up -- the
 * opposite of the MD5 loader beside it, which assembles little-endian words
 * walking the block backwards.  That is not a stylistic choice: SHA-1 is
 * defined big-endian and MD5 little-endian, so the two loaders disagree
 * because the standards do.
 *
 * EACH ROUND'S TEMPORARY IS SCOPED TO ITS LOOP.  Retail gives the four loops
 * four DISTINCT stack slots rather than sharing one, which is what a
 * block-scoped local -- or a macro that declares one -- produces at /Od.  A
 * single temporary hoisted to function scope would use one slot and would not
 * match.
 *
 * THE EXPANSION RECOMPUTES ITS XOR CHAIN TWICE, once for each half of the
 * rotate, so the four-way exclusive-or of W[t-3], W[t-8], W[t-14] and W[t-16]
 * appears twice per iteration.  Written with a temporary it would appear once
 * and the bytes would not match; the duplication is in the original.
 */
void Rva00811310( struct Rva008111D0Context *context,
	const unsigned char *block )
{
	int i;
	int t;
	unsigned int a;
	unsigned int b;
	unsigned int c;
	unsigned int d;
	unsigned int e;
	unsigned int W[ 0x50 ];

	for ( i = 0; i != 0x10; i++ )
	{
		W[ i ] = ( block[ i * 4 ] << 24 ) | ( block[ i * 4 + 1 ] << 16 )
			| ( block[ i * 4 + 2 ] << 8 ) | block[ i * 4 + 3 ];
	}

	for ( t = 0x10; t != 0x50; t++ )
	{
		W[ t ] = ( ( W[ t - 3 ] ^ W[ t - 8 ] ^ W[ t - 14 ] ^ W[ t - 16 ] ) << 1 )
			| ( ( W[ t - 3 ] ^ W[ t - 8 ] ^ W[ t - 14 ] ^ W[ t - 16 ] ) >> 31 );
	}

	a = context->m_state[ 0 ];
	b = context->m_state[ 1 ];
	c = context->m_state[ 2 ];
	d = context->m_state[ 3 ];
	e = context->m_state[ 4 ];

	for ( t = 0x00; t != 0x14; t++ )
	{
		unsigned int uTemp = ( ( a << 5 ) | ( a >> 27 ) ) + ( ( b & c ) | ( ~b & d ) ) + e
			+ W[ t ] + 0x5A827999;

		e = d;
		d = c;
		c = ( b << 30 ) | ( b >> 2 );
		b = a;
		a = uTemp;
	}

	for ( t = 0x14; t != 0x28; t++ )
	{
		unsigned int uTemp = ( ( a << 5 ) | ( a >> 27 ) ) + ( b ^ c ^ d ) + e
			+ W[ t ] + 0x6ED9EBA1;

		e = d;
		d = c;
		c = ( b << 30 ) | ( b >> 2 );
		b = a;
		a = uTemp;
	}

	for ( t = 0x28; t != 0x3C; t++ )
	{
		unsigned int uTemp = ( ( a << 5 ) | ( a >> 27 ) ) + ( ( b & c ) | ( b & d ) | ( c & d ) ) + e
			+ W[ t ] + 0x8F1BBCDC;

		e = d;
		d = c;
		c = ( b << 30 ) | ( b >> 2 );
		b = a;
		a = uTemp;
	}

	for ( t = 0x3C; t != 0x50; t++ )
	{
		unsigned int uTemp = ( ( a << 5 ) | ( a >> 27 ) ) + ( b ^ c ^ d ) + e
			+ W[ t ] + 0xCA62C1D6;

		e = d;
		d = c;
		c = ( b << 30 ) | ( b >> 2 );
		b = a;
		a = uTemp;
	}

	context->m_state[ 0 ] += a;
	context->m_state[ 1 ] += b;
	context->m_state[ 2 ] += c;
	context->m_state[ 3 ] += d;
	context->m_state[ 4 ] += e;
}

/* 0x00811840 COPIES THE STATE OUT AS BYTES, big-endian within each word, and
 * clamps the request to the digest's twenty bytes.
 *
 * IT COMPUTES ITS SHIFT WITH A DIVISION.  The byte position within a word is
 * i modulo four, and MSVC emits an actual unsigned divide by four rather than
 * a mask -- so this loop pays a div per byte where an AND would do.  The index
 * beside it uses a shift, so the two halves of the same decomposition are
 * written differently in the original.
 *
 * OVER-ASKING IS CLAMPED, UNDER-ASKING IS NOT PADDED, and neither is reported:
 * a caller passing more than twenty gets twenty and a caller passing less gets
 * a prefix, with no return value to distinguish them.
 */
void Rva00811840( struct Rva008111D0Context *context, unsigned char *out,
	unsigned int size )
{
	unsigned char *p;
	unsigned int i;

	p = out;

	if ( size > 0x14 )
	{
		size = 0x14;
	}

	for ( i = 0; i != size; i++ )
	{
		p[ i ] = context->m_state[ i >> 2 ] >> ( ( 3 - i % 4 ) * 8 );
	}
}

/* 0x008116B0 FINISHES THE SHA-1 AND WRITES THE RESULT.
 *
 * THE LENGTH GOES IN BIG-ENDIAN HERE, high byte first at the low offset --
 * the mirror image of the MD5 finalise in Y4CommDigest.c, which writes its
 * length little-endian.  Both are correct for their own standard, and the two
 * routines sit a few hundred bytes apart doing the opposite thing.
 *
 * IT ALSO STOPS SHORT OF A FULL SIXTY-FOUR-BIT LENGTH in the same way MD5
 * does: five computed bytes and three literal zeros, because the count is in
 * BYTES and the field wants BITS.  A message of 512 MB or more overflows the
 * five bytes and is hashed with a wrong length -- the same bound, reached
 * independently in both implementations.
 *
 * THE PADDING BYTE IS A VARIABLE THAT CLEARS ITSELF, exactly as in the MD5:
 * 0x80 the first time, zero afterwards.  Here it matters more, because the
 * two-block case really can run the store twice -- when fewer than nine bytes
 * remain there is no room for the length, so the block is filled, transformed,
 * and the whole thing repeated with the marker already spent.
 */
void Rva008116B0( struct Rva008111D0Context *context, unsigned char *out,
	unsigned int size )
{
	unsigned int i;
	unsigned char cPad;
	unsigned int uRoom;

	cPad = 0x80;
	uRoom = 0x40 - context->m_fill;
	context->m_count += context->m_fill;

	if ( uRoom < 9 )
	{
		context->m_block[ context->m_fill ] = cPad;

		for ( i = context->m_fill + 1; i < 0x40; i++ )
		{
			context->m_block[ i ] = 0;
		}

		Rva00811310( context, context->m_block );
		cPad = 0;
		context->m_fill = 0;
	}

	context->m_block[ context->m_fill ] = cPad;

	for ( i = context->m_fill + 1; i < 0x38; i++ )
	{
		context->m_block[ i ] = 0;
	}

	context->m_block[ 0x38 ] = 0;
	context->m_block[ 0x39 ] = 0;
	context->m_block[ 0x3A ] = 0;
	context->m_block[ 0x3B ] = ( context->m_count >> 29 ) & 0xFF;
	context->m_block[ 0x3C ] = ( context->m_count >> 21 ) & 0xFF;
	context->m_block[ 0x3D ] = ( context->m_count >> 13 ) & 0xFF;
	context->m_block[ 0x3E ] = ( context->m_count >> 5 ) & 0xFF;
	context->m_block[ 0x3F ] = ( context->m_count << 3 ) & 0xFF;

	Rva00811310( context, context->m_block );

	Rva00811840( context, out, size );
}
