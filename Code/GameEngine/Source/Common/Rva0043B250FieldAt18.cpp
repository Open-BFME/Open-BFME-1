// Retail RVA 0x0043B250. The caller proves a this-relative field address,
// but no evidence proves the owning class or field type.

class Rva0043B250
{
public:
	void *fieldAt18();
};

void *Rva0043B250::fieldAt18()
{
	return (char *)this + 0x18;
}
