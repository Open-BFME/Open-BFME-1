// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

struct Rva007B80D0Triple
{
	unsigned int a;
	unsigned int b;
	unsigned int c;
};

class Rva007B80D0Arr
{
public:
	Rva007B80D0Triple *at(int index);

	char m_pad[0x10];
	Rva007B80D0Triple *m_items;
};

Rva007B80D0Triple *Rva007B80D0Arr::at(int index)
{
	return m_items + index;
}

struct Rva007B9EC0Six
{
	unsigned short a;
	unsigned short b;
	unsigned short c;
};

class Rva007B9EC0Arr
{
public:
	Rva007B9EC0Six *at(int index);

	char m_pad[0x0c];
	Rva007B9EC0Six *m_items;
};

Rva007B9EC0Six *Rva007B9EC0Arr::at(int index)
{
	return m_items + index;
}

class Rva0079E3D0Arr
{
public:
	Rva007B80D0Triple *at(int index);

	char m_pad[0x54];
	Rva007B80D0Triple *m_items;
};

Rva007B80D0Triple *Rva0079E3D0Arr::at(int index)
{
	return m_items + index;
}
