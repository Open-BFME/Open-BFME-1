// _Rva0080FD30
// partial score=0.99 date=2026-09-09
// cl: /Od /GZ /GS /MD /DNDEBUG
/* MULTI-PRECISION INTEGER PRIMITIVES, built /Od with /GZ.
 *
 * The representation is read out of the bodies here rather than assumed: LIMBS
 * ARE 16 BITS and are stored MOST-SIGNIFICANT FIRST.  The bit test computes
 * its word index as (16 * count - index - 1) / 16, counting from the END,
 * which is only correct for a most-significant-first array; the addition at
 * 0x0080FD30 -- not yet converted, see reverse/re_attempts.log -- walks all
 * three of its arrays backwards and shifts its carry down by 16 per limb,
 * which agrees and fixes the limb width.
 *
 * Placement is by address neighbourhood -- neither body reaches a string and
 * nothing here names the module.
 */

/* 0x0080FE70 TESTS ONE BIT, numbered from the LEAST significant end.
 *
 * Bit 0 lives in the LAST limb, which is why the word index is computed by
 * subtracting from the total rather than dividing directly -- the array is
 * most-significant-first but the bit numbering is not.
 *
 * IT RETURNS THE MASKED BIT, NOT A BOOLEAN: the value is the bit still in
 * place, so it is 0x0001 for bit 0 but 0x8000 for bit 15.  A caller comparing
 * against 1 works only for bit 0.  The result is also truncated to 16 bits and
 * returned through movzx, so the caller gets 0x0000..0x8000 and never a
 * sign-extended value.
 *
 * The limb width is a LOCAL initialised to 16 rather than a constant in the
 * expressions, and it is used four times; folding it into the arithmetic
 * compiles differently.
 */
int Rva0080FE70( const unsigned short *bits, int count, int index )
{
	int iWidth;
	int iBit;
	int iWord;
	unsigned short uResult;

	iWidth = 16;

	iBit = index % iWidth;
	iWord = ( iWidth * count - index - 1 ) / iWidth;

	uResult = (unsigned short)( bits[ iWord ] & ( 1 << iBit ) );
	return uResult;
}

/* RC4 STATE.  The two indices sit at +0x00 and +0x01 and the permutation
 * follows at +0x02, so the object is 258 bytes.  The layout is read from the
 * two bodies below, both of which address the table as base plus index plus
 * two.
 */
struct Rva0080F200Rc4
{
	unsigned char m_x;              /* +0x00 */
	unsigned char m_y;              /* +0x01 */
	unsigned char m_s[ 256 ];       /* +0x02 */
};

/* 0x0080F200 IS THE RC4 KEY SCHEDULE, with one departure from the standard:
 * IT TAKES A ROUND COUNT and repeats the whole mixing pass that many times.
 * Textbook RC4 does exactly one pass.  A round count below 1 is clamped up to
 * 1, so the caller cannot skip the schedule entirely.
 *
 * The identification rests on the shape, not on any string: a 256-byte
 * identity permutation, then j accumulating S[i] plus a key byte cycled with
 * i modulo the key length, swapping S[i] and S[j].  That is RC4's KSA and
 * nothing else.
 *
 * A ZERO-LENGTH KEY SKIPS THE MIXING ENTIRELY -- the table is left as the
 * identity permutation and both indices at zero, which is a valid state that
 * enciphers nothing.  The test is signed, so a negative length behaves the
 * same way; the modulo inside the loop is UNSIGNED, which is why the length
 * has to be rejected before it is reached rather than after.
 */
void Rva0080F200( struct Rva0080F200Rc4 *state, const unsigned char *key,
	int keyLength, int rounds )
{
	unsigned int i;
	unsigned char j;
	unsigned char t1;
	unsigned char t2;

	if ( rounds < 1 )
		rounds = 1;

	state->m_x = 0;
	state->m_y = 0;

	for ( i = 0; i < 0x100; i++ )
		state->m_s[ i ] = (unsigned char)i;

	if ( keyLength > 0 )
	{
		j = 0;

		for ( ; rounds > 0; rounds-- )
		{
			for ( i = 0; i < 0x100; i++ )
			{
				/* += , not a three-term sum: retail adds the key byte to
				 * S[i] FIRST and folds the result into j last, which is the
				 * grouping a compound assignment produces and a left-to-right
				 * sum does not. */
				j += state->m_s[ i ] + key[ i % keyLength ];

				t1 = state->m_s[ i ];
				t2 = state->m_s[ j ];

				state->m_s[ i ] = t2;
				state->m_s[ j ] = t1;
			}
		}
	}
}

/* 0x0080F300 IS THE RC4 STREAM STEP: it enciphers IN PLACE, so the caller's
 * buffer is overwritten, and because the operation is an exclusive-or the same
 * body both encrypts and decrypts.
 *
 * The two indices are LOADED INTO LOCALS at the top and written back at the
 * end rather than being updated through the object each step.  That is what
 * makes a partial run resumable -- state left in the object is always
 * consistent with how many bytes have actually been processed -- and it is why
 * the body is safe to call repeatedly over a stream.
 *
 * The keystream index is the sum of the two swapped values masked to a byte;
 * the mask is explicit in the bytes rather than implied by a narrow type.
 */
void Rva0080F300( struct Rva0080F200Rc4 *state, unsigned char *data,
	int length )
{
	unsigned char t1;
	unsigned char t2;
	unsigned char x;
	unsigned char y;

	x = state->m_x;
	y = state->m_y;

	for ( ; length > 0; length-- )
	{
		/* Both compound: the increment is an 8-BIT `add dl,1` rather than a
		 * widened one, and the index update folds S[x] into y the same way
		 * the key schedule folds its sum into j. */
		x++;
		y += state->m_s[ x ];

		t1 = state->m_s[ x ];
		t2 = state->m_s[ y ];

		state->m_s[ x ] = t2;
		state->m_s[ y ] = t1;

		/* Compound again -- retail computes the keystream byte BEFORE loading
		 * the plaintext, which is what ^= produces; an explicit
		 * `*data = *data ^ ...` loads the destination first. */
		*data ^= state->m_s[ ( t1 + t2 ) & 0xFF ];
		data++;
	}

	state->m_x = x;
	state->m_y = y;
}

/* 0x0080FED0 PACKS A BYTE STRING INTO LIMBS, most-significant first, and
 * returns the number of limbs the string actually needs.
 *
 * A NEGATIVE LIMB COUNT MEANS "exactly as many as needed" -- it is replaced by
 * the required count, so the padding loop below does nothing.  Any larger
 * count is honoured by writing ZERO LIMBS FIRST, which is what makes the
 * result right-aligned in a fixed-width buffer: the number keeps its value and
 * gains leading zeros, exactly as a big-endian integer should.
 *
 * AN ODD BYTE COUNT IS HANDLED BY A SEPARATE FIRST LIMB holding a single byte
 * -- not by padding the string.  Padding at the front would have worked too
 * and is what a reader might assume; the bytes show the odd byte becoming a
 * limb of its own, which keeps the remaining pairs aligned to the input rather
 * than shifted by one.  That is visible in a 16-bit movzx, which is how a
 * single byte reaches a limb without touching the high half.
 *
 * The floor and ceiling of half the byte count are computed separately with
 * the signed shift idiom, and comparing them is how the body tests for
 * oddness -- there is no AND with 1 anywhere.
 */
int Rva0080FED0( unsigned short *result, int limbs, const unsigned char *bytes,
	int byteCount )
{
	int iFloor;
	int iNeeded;

	iFloor = byteCount / 2;
	iNeeded = ( byteCount + 1 ) / 2;

	if ( limbs < 0 )
		limbs = iNeeded;

	for ( ; limbs > iNeeded; limbs-- )
	{
		*result = 0;
		result++;
	}

	if ( iFloor != iNeeded )
	{
		*result = *bytes;
		result++;
		bytes++;
		limbs--;
	}

	for ( ; limbs > 0; limbs-- )
	{
		*result = (unsigned short)( ( bytes[ 0 ] << 8 ) | bytes[ 1 ] );
		result++;
		bytes += 2;
	}

	return iNeeded;
}

void Rva0080FFB0( const unsigned short *limbs, int limbCount,
	unsigned char *bytes, int byteCount )
{
	byteCount /= 2;
	limbs += limbCount - byteCount;

	for ( ; byteCount > 0; byteCount-- )
	{
		*bytes = (unsigned char)( *limbs >> 8 );
		bytes++;
		*bytes = *(const unsigned char *)limbs;
		bytes++;
		limbs++;
	}
}

int Rva0080FD30( unsigned short *result, int count,
	const unsigned short *a, const unsigned short *b )
{
	unsigned int carry;

	a += count;
	b += count;
	result += count;
	carry = 0;

	for ( ; count > 0; count-- )
	{
		carry = *--a + *--b + carry;
		*--result = (unsigned short)carry;
		carry >>= 16;
	}

	return carry;
}
int Rva0080FDD0( unsigned short *result, int count,
	const unsigned short *a, const unsigned short *b )
{
	unsigned int carry;

	a += count;
	b += count;
	result += count;
	carry = 0;

	for ( ; count > 0; count-- )
	{
		carry = *--a - *--b - carry;
		*--result = (unsigned short)carry;
		carry = ( carry >> 16 ) & 1;
	}

	return carry;
}
void *memset( void *dest, int value, unsigned int count );
void *memcpy( void *dest, const void *src, unsigned int count );

void Rva0080FB40( unsigned short *result, int count,
	const unsigned short *bits, const unsigned short *addend,
	const unsigned short *modulus )
{
	int i;
	int carry;
	unsigned short first[ 0x100 ];
	unsigned short second[ 0x100 ];
	unsigned short *current;
	unsigned short *other;

	current = first;
	other = second;
	memset( current, 0, count * 2 );
	for ( i = count * 2 * 8 - 1; i >= 0; i-- )
	{
		carry = Rva0080FD30( current, count, current, current );
		if ( Rva0080FDD0( other, count, current, modulus ) == 0
			|| carry != 0 )
		{
			unsigned short *swap = current;
			current = other;
			other = swap;
		}

		if ( Rva0080FE70( bits, count, i ) != 0 )
		{
			carry = Rva0080FD30( current, count, current, addend );
			if ( Rva0080FDD0( other, count, current, modulus ) == 0
				|| carry != 0 )
			{
				unsigned short *swap = current;
				current = other;
				other = swap;
			}
		}
	}
	memcpy( result, current, count * 2 );
}

unsigned int Rva007FEA00( void );

/* The padded block: a fixed 0x400-byte buffer with its used length beside it. */
struct Rva0080F430Block
{
	unsigned char m_data[ 0x400 ];
	int m_size;                     /* +0x400 */
};

/* 0x0080F430 BUILDS A PKCS#1 v1.5 TYPE-2 ENCRYPTION BLOCK: a leading 0x00, a
 * 0x02, non-zero random padding, a 0x00 separator, then the payload
 * right-aligned at the end.  Every one of those five pieces is in the bytes,
 * and together they are the padding scheme rather than a resemblance to it.
 *
 * THE RANDOMNESS IS A TICK COUNT RUN THROUGH AN LCG, and the multiplier is
 * 0x10DCD -- 69069, the Knuth/VAX constant.  The seed is the millisecond
 * clock, so the padding is PREDICTABLE to anyone who can guess when the block
 * was built; PKCS#1 assumes a cryptographic source here and this is not one.
 * That is retail's, and it is worth writing down rather than passing over,
 * because the code looks correct in every other respect.
 *
 * The first pass spreads the seed's 32 bits over the whole buffer as 0/1
 * bytes, cycling every 32 positions; the second overwrites each byte by
 * xoring successive LCG outputs into it, REPEATING UNTIL THE BYTE IS NON-ZERO.
 * That retry is what PKCS#1 requires of padding bytes -- a zero would be
 * mistaken for the separator -- and it is a do-while, so a byte is always
 * xored at least once regardless of what the first pass left.
 *
 * The separator is written at one BEFORE the payload's start, so a payload
 * exactly filling the buffer would write outside it; nothing here checks the
 * length against the size.
 */
void Rva0080F430( struct Rva0080F430Block *block, const void *data,
	int length )
{
	int i;
	unsigned int uSeed;

	uSeed = Rva007FEA00();

	for ( i = 0; i < block->m_size; i++ )
		block->m_data[ i ] = ( uSeed & ( 1 << ( i & 0x1F ) ) ) != 0;

	for ( i = 0; i < block->m_size; i++ )
	{
		do
		{
			uSeed = uSeed * 0x10DCD + 0x10DCD;
			block->m_data[ i ] ^= (char)uSeed;
		}
		while ( block->m_data[ i ] == 0 );
	}

	block->m_data[ 0 ] = 0;
	block->m_data[ 1 ] = 2;

	i = block->m_size - length;
	block->m_data[ i - 1 ] = 0;

	memcpy( &block->m_data[ i ], data, length );
}
