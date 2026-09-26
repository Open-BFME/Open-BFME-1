// cl: /DNDEBUG /MD /EHsc
// Retail reports whether the pointed-to record has a nonzero field at +0x204.

class Rva001DCD50
{
public:
	bool check( void *record );
};

bool Rva001DCD50::check( void *record )
{
	return *reinterpret_cast<unsigned int *>(static_cast<unsigned char *>(record) + 0x204) != 0;
}
