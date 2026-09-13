// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD
// Retail 0x006ACE30. Same +0x9C scale / +0xA0 tree / +0x188 48-byte buffer
// as Rva006ABB80::reset and 0x006B0C50. insert_unique the name; if it was
// new and the scale is not 1.0f, fill the buffer with 0x02.

template <class T>
class StringBase
{
public:
	void *m_data;
};

class Rva006AEE00Tree
{
public:
	struct InsertResult
	{
		void *m_node;
		char m_ok;
		unsigned char m_pad[3];
	};

	void insert_unique(InsertResult *out, const StringBase<char> &key);
};

class Rva006ACE30
{
public:
	void insertFill(const StringBase<char> &name);

	char m_pad[0x9C];
	unsigned m_scaleBits;
	Rva006AEE00Tree m_tree;
	char m_padA8[0x188 - 0xA8];
	unsigned char m_buf[48];
};

void Rva006ACE30::insertFill(const StringBase<char> &name)
{
	Rva006AEE00Tree::InsertResult r;
	m_tree.insert_unique(&r, name);
	if (r.m_ok && m_scaleBits != 0x3F800000)
	{
		__asm
		{
			lea edi, [esi + 188h]
			mov ecx, 0Ch
			mov eax, 02020202h
			rep stosd
		}
	}
}
