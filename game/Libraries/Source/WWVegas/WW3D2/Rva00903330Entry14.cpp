// cl: /O2 /Ob0

class Rva00903330EntryTable
{
public:
	char *entry14(int index) const;
};
char *Rva00903330EntryTable::entry14(int index) const
{
	return reinterpret_cast<char *>(const_cast<Rva00903330EntryTable *>(this)) + index * 0x54 + 0x14;
}
