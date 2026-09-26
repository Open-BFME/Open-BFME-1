// 0x003D50B0, 83 bytes, ret 0: the rounded-up average of eight unsigned bytes
// living at +0x390..+0x397 of the object.
//
//     int sum = 0;
//     for ( int i = 0; i < 8; ++i )
//         sum += m_value[ i ];
//     return ( sum + 7 ) / 8;
//
// WHAT THE BYTES SHOW.  Eight `movzx` loads -- so the elements are UNSIGNED
// char, not signed -- at eight consecutive offsets, summed into eax.  The tail
// is `add eax,7 / cdq / and edx,7 / add eax,edx / sar eax,3`: MSVC 7.1's SIGNED
// division by 8, applied to sum+7.  A shift would have been emitted for an
// unsigned or a `>> 3`, so the accumulator is a signed int and the operator is
// `/`.  The `+7` before the division is the round-up.
//
// THE LOOP IS THE SOURCE, NOT THE EIGHT ADDS.  Written out as one eight-term
// expression the compiler folds `+7` into the last `lea eax,[eax+ecx+7]`, 82
// bytes with no separate `add eax,7`.  Retail keeps the `add eax,7` standing on
// its own, which is what the fully unrolled `for` produces: the loop's sum is
// complete before the rounding term is applied.  The unrolled load order --
// +0x396, +0x397, then +0x395 down to +0x390 -- is the unroller's, and is
// reproduced exactly by the loop.
//
// IDENTITY IS NOT RECOVERED.  Nothing names the object or the eight bytes; the
// name is address-derived and the member is spelled for what the byte does.
// The 0x390 bytes ahead of the array place it and assert nothing else.

class Rva003D50B0
{
public:
	char m_lead[ 0x390 ];
	unsigned char m_value[ 8 ];

	int average() const;
};

int Rva003D50B0::average() const
{
	int sum = 0;

	for ( int i = 0; i < 8; ++i )
		sum += m_value[ i ];

	return ( sum + 7 ) / 8;
}
