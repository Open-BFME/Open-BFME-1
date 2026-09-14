// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: EnumeratedIP scalar-deleting destructor at retail RVA 0x00625010
// (30 bytes). The exact constructor at 0x00624BA0 and the recovered
// IPEnumeration allocation/list teardown establish the non-virtual node type.
// This wrapper calls its destructor through ILT 0x00028FB0 before delete.

class EnumeratedIP
{
public:
	~EnumeratedIP();
};

void forceEnumeratedIPDelete(EnumeratedIP *address)
{
	delete address;
}
