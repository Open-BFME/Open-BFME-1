class Rva0036B140Item;

class Rva0036B140PointerRange
{
public:
	unsigned int size() const { return m_last - m_first; }
	Rva0036B140Item *operator[](int index) const { return m_first[index]; }

private:
	Rva0036B140Item **m_first;
	Rva0036B140Item **m_last;
};

class Rva0036B140Collection
{
public:
	char m_unreconstructed[ 8 ];
	Rva0036B140PointerRange m_items;

	Rva0036B140Item *itemAt(int index) const;
};

Rva0036B140Item *Rva0036B140Collection::itemAt(int index) const
{
	if( index >= 0 && (unsigned int)index < m_items.size() )
		return m_items[ index ];
	return 0;
}

// @?itemAt@Rva0036B140Collection@@QBEPAVRva0036B140Item@@H@Z 0x0036B140
