// cl: /DNDEBUG /MD /EHsc /O2
// Retail 0x007D0B90 is an opaque three-byte this-returning body.
// The retail image proves the address and ABI, but it does not prove a class
// or semantic method name, so the source keeps the address-derived owner.

class Rva007D0B90
{
public:
    Rva007D0B90 *method();
};

Rva007D0B90 *Rva007D0B90::method()
{
    return this;
}
