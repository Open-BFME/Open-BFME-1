// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

struct FiveDwordElem
{
	unsigned int m_value;
	unsigned int m_unreconstructed_04;
	unsigned int m_unreconstructed_08;
	unsigned int m_unreconstructed_0c;
	unsigned int m_unreconstructed_10;
};

class Rva003543C0Arr
{
public:
	unsigned int at(int index);

	char m_pad[0x0C];
	FiveDwordElem *m_items;
};

unsigned int Rva003543C0Arr::at(int index)
{
	return m_items[index].m_value;
}

struct ByteAtOffset0CElem
{
	char m_pad[0x0C];
	unsigned char m_byte;
	char m_tail[7];
};

class Rva003543E0Arr
{
public:
	unsigned char get(int index);

	char m_pad[0x0C];
	ByteAtOffset0CElem *m_items;
};

unsigned char Rva003543E0Arr::get(int index)
{
	return m_items[index].m_byte;
}

struct ShortAtOffset0EElem
{
	char m_pad[0x0E];
	short m_short;
	char m_tail[4];
};

class Rva00354400Arr
{
public:
	int get(int index);

	char m_pad[0x0C];
	ShortAtOffset0EElem *m_items;
};

int Rva00354400Arr::get(int index)
{
	return m_items[index].m_short;
}

struct IntAtOffset08Elem
{
	char m_pad[8];
	int m_int;
	char m_tail[8];
};

class Rva00354460Arr
{
public:
	int *addr(int index);

	char m_pad[0x0C];
	IntAtOffset08Elem *m_items;
};

int *Rva00354460Arr::addr(int index)
{
	return &m_items[index].m_int;
}

class Rva00354480Arr
{
public:
	unsigned char get(int index);

	char m_pad[0x0C];
	ByteAtOffset0CElem *m_items;
};

unsigned char Rva00354480Arr::get(int index)
{
	return m_items[index].m_byte;
}

class Rva003544A0Arr
{
public:
	int get(int index);

	char m_pad[0x0C];
	ShortAtOffset0EElem *m_items;
};

int Rva003544A0Arr::get(int index)
{
	return m_items[index].m_short;
}

class Rva00355660Arr
{
public:
	unsigned char get(int index);

	char m_pad[0x18];
	ByteAtOffset0CElem *m_items;
};

unsigned char Rva00355660Arr::get(int index)
{
	return m_items[index].m_byte;
}

class Rva00355680Arr
{
public:
	unsigned char get(int index);

	char m_pad[0x38];
	ByteAtOffset0CElem *m_items;
};

unsigned char Rva00355680Arr::get(int index)
{
	return m_items[index].m_byte;
}

struct Rva00355640Key
{
	int m_pad;
	int m_index;
};

class Rva00355640Arr
{
public:
	int *addr(const Rva00355640Key *key);

	char m_pad[0x18];
	IntAtOffset08Elem *m_items;
};

int *Rva00355640Arr::addr(const Rva00355640Key *key)
{
	return &m_items[key->m_index].m_int;
}

struct IntAtOffset10Elem
{
	char m_pad[0x10];
	int m_int;
};

class Rva003558A0Arr
{
public:
	int get(const Rva00355640Key *key);

	char m_pad[0x18];
	IntAtOffset10Elem *m_items;
};

int Rva003558A0Arr::get(const Rva00355640Key *key)
{
	return m_items[key->m_index].m_int + 4;
}

class Rva00355930Arr
{
public:
	int get(const Rva00355640Key *key);

	char m_pad[0x38];
	IntAtOffset10Elem *m_items;
};

int Rva00355930Arr::get(const Rva00355640Key *key)
{
	return m_items[key->m_index].m_int + 4;
}

struct Rva003558C0Key
{
	int m_pad;
	int m_index;
	int m_value;
};

class Rva003558C0Arr
{
public:
	bool matches(const Rva003558C0Key *key);

	char m_pad[0x18];
	ShortAtOffset0EElem *m_items;
};

bool Rva003558C0Arr::matches(const Rva003558C0Key *key)
{
	return m_items[key->m_index].m_short == key->m_value;
}

class Rva00355950Arr
{
public:
	bool matches(const Rva003558C0Key *key);

	char m_pad[0x38];
	ShortAtOffset0EElem *m_items;
};

bool Rva00355950Arr::matches(const Rva003558C0Key *key)
{
	return m_items[key->m_index].m_short == key->m_value;
}

struct ByteAndShortElem
{
	char m_pad[0x0C];
	unsigned char m_byte;
	char m_pad0d;
	short m_short;
	char m_tail[4];
};

class Rva00355980Arr
{
public:
	bool matches(const Rva003558C0Key *key);

	char m_pad[0x38];
	ByteAndShortElem *m_items;
};

bool Rva00355980Arr::matches(const Rva003558C0Key *key)
{
	return m_items[key->m_index].m_short != key->m_value ||
		m_items[key->m_index].m_byte != 0;
}

class Rva003558F0Arr
{
public:
	bool matches(const Rva003558C0Key *key);

	char m_pad[0x18];
	ByteAndShortElem *m_items;
};

bool Rva003558F0Arr::matches(const Rva003558C0Key *key)
{
	return m_items[key->m_index].m_short != key->m_value ||
		m_items[key->m_index].m_byte != 0;
}
