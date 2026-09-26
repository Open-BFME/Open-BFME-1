// cl: /O2
// Retail 0x0006B080 returns the address at this + 0x30.

class Rva0006B080FieldAddress
{
public:
	char *get();
};

char *Rva0006B080FieldAddress::get()
{
	return reinterpret_cast<char *>(this) + 0x30;
}
