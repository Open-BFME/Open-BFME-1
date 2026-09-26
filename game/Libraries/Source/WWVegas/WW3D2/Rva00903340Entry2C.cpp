// cl: /O2 /Ob0

class Rva00903340EntryTable
{
public:
	char *entry2C(int index) const;
};
char *Rva00903340EntryTable::entry2C(int index) const
{
	return reinterpret_cast<char *>(const_cast<Rva00903340EntryTable *>(this)) + index * 0x54 + 0x2C;
}
