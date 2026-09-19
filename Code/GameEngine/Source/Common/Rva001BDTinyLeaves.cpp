// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD
// Address-derived leaf recoveries from the 0x001BD330 carved run.

#define BFME_RVA_BYTE_GETTER(NAME, DISP) \
class NAME \
{ \
public: \
	unsigned char get() const; \
	char m_lead[DISP]; \
	unsigned char m_value; \
}; \
unsigned char NAME::get() const \
{ \
	return m_value; \
}

#define BFME_RVA_DWORD_GETTER(NAME, DISP) \
class NAME \
{ \
public: \
	int get() const; \
	char m_lead[DISP]; \
	int m_value; \
}; \
int NAME::get() const \
{ \
	return m_value; \
}

#define BFME_RVA_FLOAT_GETTER(NAME, DISP) \
class NAME \
{ \
public: \
	float get() const; \
	char m_lead[DISP]; \
	float m_value; \
}; \
float NAME::get() const \
{ \
	return m_value; \
}

#define BFME_RVA_MEMBER_INCREMENT(NAME, DISP) \
class NAME \
{ \
public: \
	void increment(); \
	char m_lead[DISP]; \
	int m_value; \
}; \
void NAME::increment() \
{ \
	++m_value; \
}

BFME_RVA_BYTE_GETTER( Rva001BD330Byte, 0x69 )
BFME_RVA_DWORD_GETTER( Rva001BD610Dword, 0x6C )
BFME_RVA_BYTE_GETTER( Rva001BD6B0Byte, 0x141 )
BFME_RVA_MEMBER_INCREMENT( Rva001BD720Counter, 0x24 )
BFME_RVA_MEMBER_INCREMENT( Rva001BD730Counter, 0x2C )
BFME_RVA_MEMBER_INCREMENT( Rva001BD740Counter, 0x28 )

class Rva001BD750Byte
{
public:
	unsigned char get() const;
	unsigned char m_value;
};

unsigned char Rva001BD750Byte::get() const
{
	return m_value;
}

class Rva001BD460List;

class Rva001BD460Node
{
public:
	void link( Rva001BD460List *list );

private:
	char m_prefix[0x25C];
	Rva001BD460Node *m_previous;
	Rva001BD460Node *m_next;
};

class Rva001BD460List
{
public:
	Rva001BD460Node *m_head;
};

void Rva001BD460Node::link( Rva001BD460List *list )
{
	m_next = list->m_head;
	if (list->m_head != 0) list->m_head->m_previous = this;
	list->m_head = this;
}

BFME_RVA_BYTE_GETTER( Rva001BD7B0Byte, 0x24 )
BFME_RVA_DWORD_GETTER( Rva001BD7C0Dword, 0x24 )
BFME_RVA_DWORD_GETTER( Rva001BD800Dword, 0x14 )
BFME_RVA_FLOAT_GETTER( Rva001BD930Float, 0x0C )
BFME_RVA_BYTE_GETTER( Rva001BD940Byte, 0x20 )
BFME_RVA_DWORD_GETTER( Rva001BD950Dword, 0x04 )
BFME_RVA_BYTE_GETTER( Rva001BD970Byte, 0x2D )
BFME_RVA_DWORD_GETTER( Rva001BD9D0Dword, 0x18 )
class Rva001BDAE0Address
{
public:
	void *address();
	char m_prefix[0x2C];
	unsigned char m_value;
};

void *Rva001BDAE0Address::address()
{
	return &m_value;
}
BFME_RVA_FLOAT_GETTER( Rva001BDBC0Float, 0x410 )
BFME_RVA_DWORD_GETTER( Rva001BDCC0Dword, 0x04 )
BFME_RVA_DWORD_GETTER( Rva001BDCF0Dword, 0x20 )
BFME_RVA_DWORD_GETTER( Rva001BDD00Dword, 0x28 )
class Rva001BDD10Dword
{
public:
	int get() const;
	int m_value;
};

int Rva001BDD10Dword::get() const
{
	return m_value;
}
BFME_RVA_DWORD_GETTER( Rva001BDD60Dword, 0x1C )
BFME_RVA_DWORD_GETTER( Rva001BDD70Dword, 0x24 )
