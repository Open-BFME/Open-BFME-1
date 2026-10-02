// 0x008937E0 (57 bytes), the third body after rva008937A0GetField18 and
// rva008937C0GetChainField8: look the key up through Rva008930C0AptLookup and,
// for a valid kind-0x12 value (six-bit kind at +4, bit 15 tested through a
// byte-wide not as in Rva008A0F20KindPredicates.cpp), return bit 25 of the
// dword at +0x1C of the object at +0x50; otherwise -1.  It sat in an
// unclaimed gap: 16-byte-aligned start after an int3 pad run, ret followed by
// int3 padding, and no call, ILT stub, table slot, code immediate, pin or
// dir32 name at the address.
//
// IDENTITY IS NOT RECOVERED.  The name is derived from the address.

class BfmeNestedBE;
extern BfmeNestedBE *Rva008930C0AptLookup( int value );

struct Rva008937E0Inner
{
	char m_lead[ 0x1C ];
	unsigned int m_flags;
};

struct Rva008937E0Value
{
	int m_0;
	unsigned int m_bits;
	char m_lead[ 0x48 ];
	Rva008937E0Inner *m_inner;
};

int rva008937E0GetFlag25( int key )
{
	Rva008937E0Value *value = (Rva008937E0Value *)Rva008930C0AptLookup( key );
	if ( value && ( value->m_bits & 0x3f ) == 0x12
			&& !( (unsigned char)~( value->m_bits >> 15 ) & 1 ) )
		return ( value->m_inner->m_flags >> 25 ) & 1;
	return -1;
}
