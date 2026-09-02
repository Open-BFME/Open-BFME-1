// cl: /DNDEBUG /MD /EHs-c-

class Rva00885980Class
{
public:
	int d_00885980(void);
};

class Rva00884E50Class
{
public:
	virtual ~Rva00884E50Class();
	unsigned char m_flag4;
	char m_pad5[0xFF];
	unsigned char m_flag104;
	char m_pad105[0x3F];
	unsigned char m_flag144;
	char m_pad145[0x3F];
	unsigned char m_flag184;
	char m_pad185[0xFF];
	unsigned char m_flag284;
	char m_pad285[0x1FF];
	unsigned char m_flag484;
	char m_pad485[0xFF];
	void *m_584;
	void *m_588;
	void *m_58C;
	void *m_590;
	void *m_594;
	char m_pad598[0x5C0 - 0x598];
	Rva00885980Class *m_sock;

	int d_00884e50(void);
};

int Rva00884E50Class::d_00884e50(void)
{
	if (m_584)
	{
		m_sock->d_00885980();
		m_584 = 0;
	}
	m_588 = 0;
	m_58C = 0;
	m_590 = 0;
	m_594 = 0;
	m_flag4 = 0;
	m_flag104 = 0;
	m_flag144 = 0;
	m_flag184 = 0;
	m_flag284 = 0;
	m_flag484 = 0;
	return 0;
}
