// Nine bodies in two shapes, both pushing one pointer twice into a cdecl maker
// and storing what comes back at +0x04.
//
// The five 24-byte setters take the pointer directly. The four 28-byte ones
// dereference their argument first and then return this, which makes them
// constructors taking the pointer BY REFERENCE -- one load before the pushes
// and a mov eax,esi at the end are the whole difference.
//
// Four of the five makers are reached by both shapes, which is what pairs a
// setter with its constructor; the fifth has only a setter. All five are known
// by address alone. Use the defining wrapper names and their integer ABI;
// the pointer casts preserve the same 32-bit arguments and result.

int Rva003897C0(int first, int second);			// ILT 0x0004B28B

int Rva003C9220(int first, int second);			// ILT 0x00002B8F

int Rva0054E860(int first, int second);			// ILT 0x00025225

int Rva0054E8E0(int first, int second);			// ILT 0x0000403E

int Rva00593060(int first, int second);			// ILT 0x000283D5

class Gen_0038eb90
{
public:
	void bfmeSet(void *value);

	char m_bfmeHead[0x04];
	void *m_bfmeMade;						// +0x04
};

class Gen_003ca460
{
public:
	void bfmeSet(void *value);

	char m_bfmeHead[0x04];
	void *m_bfmeMade;						// +0x04
};

class Gen_0054f350
{
public:
	void bfmeSet(void *value);

	char m_bfmeHead[0x04];
	void *m_bfmeMade;						// +0x04
};

class Gen_0054f370
{
public:
	void bfmeSet(void *value);

	char m_bfmeHead[0x04];
	void *m_bfmeMade;						// +0x04
};

class Gen_005958f0
{
public:
	void bfmeSet(void *value);

	char m_bfmeHead[0x04];
	void *m_bfmeMade;						// +0x04
};

class Gen_003ca670
{
public:
	Gen_003ca670(void *const &value);

	char m_bfmeHead[0x04];
	void *m_bfmeMade;						// +0x04
};

class Gen_0054f950
{
public:
	Gen_0054f950(void *const &value);

	char m_bfmeHead[0x04];
	void *m_bfmeMade;						// +0x04
};

class Gen_0054f9d0
{
public:
	Gen_0054f9d0(void *const &value);

	char m_bfmeHead[0x04];
	void *m_bfmeMade;						// +0x04
};

class Gen_00597700
{
public:
	Gen_00597700(void *const &value);

	char m_bfmeHead[0x04];
	void *m_bfmeMade;						// +0x04
};

// ?bfmeSet@Gen_0038eb90@@QAEXPAX@Z
void Gen_0038eb90::bfmeSet(void *value)
{
	m_bfmeMade = reinterpret_cast<void *>(Rva003897C0(
		reinterpret_cast<int>(value), reinterpret_cast<int>(value)));
}

// ?bfmeSet@Gen_003ca460@@QAEXPAX@Z
void Gen_003ca460::bfmeSet(void *value)
{
	m_bfmeMade = reinterpret_cast<void *>(Rva003C9220(
		reinterpret_cast<int>(value), reinterpret_cast<int>(value)));
}

// ?bfmeSet@Gen_0054f350@@QAEXPAX@Z
void Gen_0054f350::bfmeSet(void *value)
{
	m_bfmeMade = reinterpret_cast<void *>(Rva0054E860(
		reinterpret_cast<int>(value), reinterpret_cast<int>(value)));
}

// ?bfmeSet@Gen_0054f370@@QAEXPAX@Z
void Gen_0054f370::bfmeSet(void *value)
{
	m_bfmeMade = reinterpret_cast<void *>(Rva0054E8E0(
		reinterpret_cast<int>(value), reinterpret_cast<int>(value)));
}

// ?bfmeSet@Gen_005958f0@@QAEXPAX@Z
void Gen_005958f0::bfmeSet(void *value)
{
	m_bfmeMade = reinterpret_cast<void *>(Rva00593060(
		reinterpret_cast<int>(value), reinterpret_cast<int>(value)));
}

// ??0Gen_003ca670@@QAE@ABQAX@Z
Gen_003ca670::Gen_003ca670(void *const &value)
{
	m_bfmeMade = reinterpret_cast<void *>(Rva003C9220(
		reinterpret_cast<int>(value), reinterpret_cast<int>(value)));
}

// ??0Gen_0054f950@@QAE@ABQAX@Z
Gen_0054f950::Gen_0054f950(void *const &value)
{
	m_bfmeMade = reinterpret_cast<void *>(Rva0054E860(
		reinterpret_cast<int>(value), reinterpret_cast<int>(value)));
}

// ??0Gen_0054f9d0@@QAE@ABQAX@Z
Gen_0054f9d0::Gen_0054f9d0(void *const &value)
{
	m_bfmeMade = reinterpret_cast<void *>(Rva0054E8E0(
		reinterpret_cast<int>(value), reinterpret_cast<int>(value)));
}

// ??0Gen_00597700@@QAE@ABQAX@Z
Gen_00597700::Gen_00597700(void *const &value)
{
	m_bfmeMade = reinterpret_cast<void *>(Rva00593060(
		reinterpret_cast<int>(value), reinterpret_cast<int>(value)));
}
