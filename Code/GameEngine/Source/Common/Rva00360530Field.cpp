// cl: /O2 /Ob0

// The carved body only proves an address sixteen bytes into the receiver.
// No caller or table provides a semantic name for that field.
class Rva00360530
{
public:
	void *field();
};

void *Rva00360530::field()
{
	return reinterpret_cast<char *>(this) + 0x10;
}
