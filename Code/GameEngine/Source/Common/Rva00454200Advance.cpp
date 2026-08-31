// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c-

struct Rva00454200Element
{
	void refresh();

private:
	char m_storage[20];
};

class Rva00454200Cursor
{
public:
	void advance();

private:
	char m_padding[0x0C];
	Rva00454200Element *m_elements;
	unsigned int m_index;
};

void Rva00454200Cursor::advance()
{
	Rva00454200Element *element = m_elements + m_index++;
	element->refresh();
}
