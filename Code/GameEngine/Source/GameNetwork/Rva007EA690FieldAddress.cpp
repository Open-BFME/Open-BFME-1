// cl: /O2 /GS
// The FESL runner calls this address-derived field accessor for owner offset 0x50.

class Rva007EA690FieldAddress
{
public:
	char *get();
};

char *Rva007EA690FieldAddress::get()
{
	return ((char *)this) + 0x50;
}
