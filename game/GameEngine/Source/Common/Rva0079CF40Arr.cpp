// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

struct Rva0079CF40Elem
{
	unsigned int a;
	unsigned int b;
};

class Rva0079CF40Arr
{
public:
	Rva0079CF40Elem *at(int index);

	char m_pad[0x4dc];
	Rva0079CF40Elem m_items[1];
};

Rva0079CF40Elem *Rva0079CF40Arr::at(int index)
{
	return m_items + index;
}
