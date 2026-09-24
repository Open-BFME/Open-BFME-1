// cl: /Od /GZ /GS /MD /DNDEBUG
/* 0x0080FD30 ADDS TWO MULTI-PRECISION INTEGERS of `count` 16-bit limbs,
 * most-significant limb first (the representation Y4MultiPrecision.c reads out
 * of the bit test at 0x0080FE70).  All three arrays are walked backwards from
 * their ends, the 32-bit carry is shifted down by 16 per limb, and the carry
 * out is returned.  The only caller is the modular double-and-add at
 * 0x0080FB40; the subtraction at 0x0080FDD0 is its twin.
 *
 * THE CARRY IS THE LEFT OPERAND and the two limbs are grouped on the right:
 * `carry + ( *--a + *--b )`.  Every other spelling of the same sum -- limbs
 * first, carry last, or the carry beside one limb -- decrements the pointers in
 * the same order but adds the carry into EAX (the *a register) instead of ECX
 * (the *b register), one ModRM byte off retail.
 */
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
		carry = carry + ( *--a + *--b );
		*--result = (unsigned short)carry;
		carry >>= 16;
	}

	return carry;
}
