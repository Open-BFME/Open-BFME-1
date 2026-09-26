// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME7: STLport list<T>::_M_fill_insert for two more payload widths,
// byte twins of the 36-byte one in ListPayload36Insert.cpp (found by the
// near-miss object scan: the only differing byte is the node size pushed to
// the allocator).  0x0009F290 (65 bytes) links 0x0C-byte nodes, so the payload
// is 4 bytes; 0x003C0000 (65 bytes) links 0x14-byte nodes, a 12-byte payload.
// Both payloads still copy through an out-of-line constructor, as the
// 36-byte model does.
#define _STLP_NO_EXCEPTIONS 1
#include <list>

struct Rva0009F290Payload
{
	int value[1];
	Rva0009F290Payload();
	Rva0009F290Payload(const Rva0009F290Payload &);
	~Rva0009F290Payload();
	Rva0009F290Payload &operator=(const Rva0009F290Payload &);
};

bool operator==(const Rva0009F290Payload &, const Rva0009F290Payload &);
bool operator<(const Rva0009F290Payload &, const Rva0009F290Payload &);


struct Rva003C0000Payload
{
	int value[3];
	Rva003C0000Payload();
	Rva003C0000Payload(const Rva003C0000Payload &);
	~Rva003C0000Payload();
	Rva003C0000Payload &operator=(const Rva003C0000Payload &);
};

bool operator==(const Rva003C0000Payload &, const Rva003C0000Payload &);
bool operator<(const Rva003C0000Payload &, const Rva003C0000Payload &);


template class _STL::list<Rva0009F290Payload>;
template class _STL::list<Rva003C0000Payload>;
