// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// The carved four-byte body returns the address of the receiver field at +0x34.

class Rva003BC530Owner
{
public:
	void *fieldAt34();

private:
	char m_beforeField[0x34];
};

void *Rva003BC530Owner::fieldAt34()
{
	return (char *)this + 0x34;
}

class Rva003BC5A0Owner
{
public:
	void *fieldAt54();

private:
	char m_beforeField[0x54];
};

void *Rva003BC5A0Owner::fieldAt54()
{
	return (char *)this + 0x54;
}
