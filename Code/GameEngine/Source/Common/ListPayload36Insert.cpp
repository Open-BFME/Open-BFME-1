// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME: STLport list range insertion for a 36-byte payload with
// non-trivial copy construction, retail 0x0076B430, 75 bytes.
#define _STLP_NO_EXCEPTIONS 1
#include <list>

struct Rva0076B430Payload
{
	int value[9];
	Rva0076B430Payload();
	Rva0076B430Payload(const Rva0076B430Payload &);
	~Rva0076B430Payload();
	Rva0076B430Payload &operator=(const Rva0076B430Payload &);
};

bool operator==(const Rva0076B430Payload &, const Rva0076B430Payload &);
bool operator<(const Rva0076B430Payload &, const Rva0076B430Payload &);

template class _STL::list<Rva0076B430Payload>;
