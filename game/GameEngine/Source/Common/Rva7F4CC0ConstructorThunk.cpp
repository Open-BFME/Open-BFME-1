struct Rva7F4CC0Child
{
	Rva7F4CC0Child();
	__forceinline void normalize()
	{
		second = 0;
		third = 0;
		first = 0;
		table = 0x011296B0;
	}

	volatile unsigned int table;
	volatile unsigned int first;
	volatile unsigned int second;
	volatile unsigned int third;
};

struct Rva7F4CC0Primary
{
	Rva7F4CC0Primary() : first(0), second(0), third(0), fourth(0), enabled(false) {}

	unsigned int first;
	unsigned int second;
	unsigned int third;
	unsigned int fourth;
	bool enabled;
};

struct Rva7F4CC0ConstructorThunk : Rva7F4CC0Primary, Rva7F4CC0Child
{
	Rva7F4CC0ConstructorThunk();
};

// ?d_007f4cc0@@YAXXZ
Rva7F4CC0ConstructorThunk::Rva7F4CC0ConstructorThunk()
{
	Rva7F4CC0Child::normalize();
}
