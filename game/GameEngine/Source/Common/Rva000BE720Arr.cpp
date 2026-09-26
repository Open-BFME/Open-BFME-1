// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

struct Rva000BE720Elem
{
	char m_bytes[20];
};

class Rva000BE720Arr
{
public:
	Rva000BE720Elem *at(int index);
};

Rva000BE720Elem *Rva000BE720Arr::at(int index)
{
	return ((Rva000BE720Elem *)this) + index;
}

class Rva00382950Arr
{
public:
	Rva000BE720Elem *at(int index);
};

Rva000BE720Elem *Rva00382950Arr::at(int index)
{
	return ((Rva000BE720Elem *)this) + index;
}
