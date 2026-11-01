// cl: /DNDEBUG /MD /EHsc
// Eight unreferenced eight-byte __thiscall bodies of one shape:
//
//     add ecx,8 / jmp <table method>
//
// Each forwards its own stack arguments unchanged to a member at +8 of its
// receiver, tail-jumping to one of two Apt table helpers whose pins already
// name them: 0x0089D890 (?bfmeAdd1024@BfmeTab1024@@QAEXHH@Z, two stack words)
// and 0x0089CEF0 (?bfmeFind1024@BfmeTab1024@@QAEHH@Z, one stack word, value
// in EAX). Each sits alone in an int3-padded .text gap no ledger row covered,
// and no call, ILT stub, table slot or dir32 name reaches it.
//
// IDENTITY IS NOT RECOVERED: every owner is address-derived, and only the
// table member's offset (+8) is read from the bytes.

class BfmeTab1024
{
public:
	void bfmeAdd1024(int key, int value);
	int bfmeFind1024(int key);
};

class Rva00891A90Owner
{
public:
	void add(int key, int value);
private:
	char m_pad[8];
	BfmeTab1024 m_table;
};

void Rva00891A90Owner::add(int key, int value)
{
	m_table.bfmeAdd1024(key, value);
}

class Rva00898290Owner
{
public:
	void add(int key, int value);
private:
	char m_pad[8];
	BfmeTab1024 m_table;
};

void Rva00898290Owner::add(int key, int value)
{
	m_table.bfmeAdd1024(key, value);
}

class Rva008982A0Owner
{
public:
	int find(int key);
private:
	char m_pad[8];
	BfmeTab1024 m_table;
};

int Rva008982A0Owner::find(int key)
{
	return m_table.bfmeFind1024(key);
}

class Rva008982B0Owner
{
public:
	int find(int key);
private:
	char m_pad[8];
	BfmeTab1024 m_table;
};

int Rva008982B0Owner::find(int key)
{
	return m_table.bfmeFind1024(key);
}

class Rva008A3120Owner
{
public:
	void add(int key, int value);
private:
	char m_pad[8];
	BfmeTab1024 m_table;
};

void Rva008A3120Owner::add(int key, int value)
{
	m_table.bfmeAdd1024(key, value);
}

class Rva008B4240Owner
{
public:
	int find(int key);
private:
	char m_pad[8];
	BfmeTab1024 m_table;
};

int Rva008B4240Owner::find(int key)
{
	return m_table.bfmeFind1024(key);
}

class Rva008C48F0Owner
{
public:
	void add(int key, int value);
private:
	char m_pad[8];
	BfmeTab1024 m_table;
};

void Rva008C48F0Owner::add(int key, int value)
{
	m_table.bfmeAdd1024(key, value);
}

class Rva008C4900Owner
{
public:
	int find(int key);
private:
	char m_pad[8];
	BfmeTab1024 m_table;
};

int Rva008C4900Owner::find(int key)
{
	return m_table.bfmeFind1024(key);
}
