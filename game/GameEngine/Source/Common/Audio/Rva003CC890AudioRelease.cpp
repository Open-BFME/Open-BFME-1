// cl: /DNDEBUG /MD

class Rva003CC890Audio
{
public:
	virtual void slot00(); virtual void slot04(); virtual void slot08();
	virtual void slot0c(); virtual void slot10(); virtual void slot14();
	virtual void slot18(); virtual void slot1c(); virtual void slot20();
	virtual void slot24(); virtual void slot28(); virtual void slot2c();
	virtual void slot30(); virtual void slot34(); virtual void slot38();
	virtual void slot3c(); virtual void slot40(); virtual void slot44();
	virtual void slot48();
	virtual void slot4c( unsigned int handle );
};

extern Rva003CC890Audio *TheAudio;

class Rva003CC890Event
{
public:
	virtual ~Rva003CC890Event();

	char m_head[0x0c];
	unsigned int m_handle;
};

class Rva003CC890Node
{
public:
	char m_head[0x38];
	unsigned char m_refs;
};

class Rva003CC890
{
public:
	void release( void );

	char m_head[0x0c];
	Rva003CC890Event *m_event;
	Rva003CC890Node *m_nodes[8];
	char m_mid[0x04];
	int m_flag;
	unsigned char m_refs;
};

void Rva003CC890::release( void )
{
	if( m_event )
	{
		TheAudio->slot4c( m_event->m_handle );
		delete m_event;
		Rva003CC890Event **eventSlot = &m_event;
		*eventSlot = 0;

		Rva003CC890Node *n0 = m_nodes[0];
		if( n0 ) n0->m_refs--;
		Rva003CC890Node *n1 = m_nodes[1];
		if( n1 ) n1->m_refs--;
		Rva003CC890Node *n2 = m_nodes[2];
		if( n2 ) n2->m_refs--;
		Rva003CC890Node *n3 = m_nodes[3];
		if( n3 ) n3->m_refs--;
		Rva003CC890Node *n4 = m_nodes[4];
		if( n4 ) n4->m_refs--;
		Rva003CC890Node *n5 = m_nodes[5];
		if( n5 ) n5->m_refs--;
		Rva003CC890Node *n6 = m_nodes[6];
		if( n6 ) n6->m_refs--;
		Rva003CC890Node *n7 = m_nodes[7];
		if( n7 ) n7->m_refs--;
		m_refs--;
	}
	m_flag = 0;
}
