class Rva0036B410Subobject
{
public:
	char m_unreconstructed;
};

class Rva0036B410Item
{
public:
	char m_unreconstructed[ 0x84 ];
	Rva0036B410Subobject m_subobject;
};

class Rva0036B410PointerRange
{
public:
	unsigned int size(void) const { return m_end - m_begin; }
	Rva0036B410Item *operator[](int index) const { return m_begin[index]; }

private:
	Rva0036B410Item **m_begin;
	Rva0036B410Item **m_end;
};

class Rva0036B410Collection
{
public:
	char m_unreconstructed[ 8 ];
	Rva0036B410PointerRange m_items;

	Rva0036B410Subobject *subobjectAt(int index) const;
};

Rva0036B410Subobject *Rva0036B410Collection::subobjectAt(int index) const
{
	if( index < 0 || (unsigned int)index > m_items.size() - 1 )
		return 0;

	Rva0036B410Item *item = m_items[index];
	return item ? &item->m_subobject : 0;
}

// @?subobjectAt@Rva0036B410Collection@@QBEPAVRva0036B410Subobject@@H@Z 0x0036B410
