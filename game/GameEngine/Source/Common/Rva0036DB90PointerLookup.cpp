class Rva0036DB90Item;

class Rva0036DB90PointerRange
{
public:
	unsigned int size(void) const { return m_end - m_begin; }
	Rva0036DB90Item *operator[](unsigned int index) const { return m_begin[index]; }

private:
	Rva0036DB90Item **m_begin;
	Rva0036DB90Item **m_end;
};

class Rva0036DB90Collection
{
public:
	char m_unreconstructed[ 0xE8 ];
	Rva0036DB90PointerRange m_items;

	Rva0036DB90Item *itemAt(unsigned int index) const;
};

Rva0036DB90Item *Rva0036DB90Collection::itemAt(unsigned int index) const
{
	if( index >= m_items.size() )
		return 0;
	return m_items[index];
}

// @?itemAt@Rva0036DB90Collection@@QBEPAVRva0036DB90Item@@I@Z 0x0036DB90
