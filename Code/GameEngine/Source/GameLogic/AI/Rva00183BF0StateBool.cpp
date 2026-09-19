// cl: /DNDEBUG /MD /EHsc

// Retail RVA 0x00183BF0 is slot 14 of the Rva00183C10 vtable at 0x0109B190.
// The slot routes through ILT 0x0002EF0A and returns true without using this.

typedef bool Bool;

class Rva00183C10
{
public:
	virtual Bool rva00183BF0() const;
};

// ?rva00183BF0@Rva00183C10@@UBE_NXZ
Bool Rva00183C10::rva00183BF0() const
{
	return true;
}
