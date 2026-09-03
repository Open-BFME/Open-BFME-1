// ?release@Rva003CC890@@QAEXXZ
// partial score=0.92 date=2026-09-02
// cl: /DNDEBUG /MD

// Open-BFME5: retail 0x003CC890, 137 bytes. The body carried only a machine
// byte-dump row.
//
// If the pointer at +0x0C is live, vtable slot 0x4C of TheAudio (0x012ED668)
// is called with the dword at +0x10 of that object -- the same removeAudioEvent
// slot BattlePlanUpdate's destructor uses -- then the object is deleted and
// the slot cleared. Eight pointers at +0x10..+0x2C and the byte at +0x38 of
// this are then decremented when non-null. The dword at +0x34 is always
// cleared.

class Rva003CC890Audio
{
public:
	virtual void slot00();	virtual void slot04();	virtual void slot08();
	virtual void slot0c();	virtual void slot10();	virtual void slot14();
	virtual void slot18();	virtual void slot1c();	virtual void slot20();
	virtual void slot24();	virtual void slot28();	virtual void slot2c();
	virtual void slot30();	virtual void slot34();	virtual void slot38();
	virtual void slot3c();	virtual void slot40();	virtual void slot44();
	virtual void slot48();
	virtual void slot4c(unsigned int handle);
};

extern Rva003CC890Audio *TheAudio;

class Rva003CC890Event
{
public:
	virtual ~Rva003CC890Event();

	char m_bfmeHead[0x0C];
	unsigned int m_bfmeHandle;				// +0x10
};

class Rva003CC890Node
{
public:
	char m_bfmeHead[0x38];
	unsigned char m_bfmeRefs;				// +0x38
};

class Rva003CC890
{
public:
	void release(void);

	char m_bfmeHead[0x0C];
	Rva003CC890Event *m_bfmeEvent;			// +0x0C
	Rva003CC890Node *m_bfmeN0;				// +0x10
	Rva003CC890Node *m_bfmeN1;				// +0x14
	Rva003CC890Node *m_bfmeN2;				// +0x18
	Rva003CC890Node *m_bfmeN3;				// +0x1C
	Rva003CC890Node *m_bfmeN4;				// +0x20
	Rva003CC890Node *m_bfmeN5;				// +0x24
	Rva003CC890Node *m_bfmeN6;				// +0x28
	Rva003CC890Node *m_bfmeN7;				// +0x2C
	char m_bfmeMid[0x34 - 0x30];
	int m_bfmeFlag;							// +0x34
	unsigned char m_bfmeRefs;				// +0x38
};

// ?release@Rva003CC890@@QAEXXZ
void Rva003CC890::release(void)
{
	if (m_bfmeEvent)
	{
		TheAudio->slot4c(m_bfmeEvent->m_bfmeHandle);
		delete m_bfmeEvent;
		m_bfmeEvent = 0;
		Rva003CC890Node *n0 = m_bfmeN0;
		if (n0)
			n0->m_bfmeRefs--;
		Rva003CC890Node *n1 = m_bfmeN1;
		if (n1)
			n1->m_bfmeRefs--;
		Rva003CC890Node *n2 = m_bfmeN2;
		if (n2)
			n2->m_bfmeRefs--;
		Rva003CC890Node *n3 = m_bfmeN3;
		if (n3)
			n3->m_bfmeRefs--;
		Rva003CC890Node *n4 = m_bfmeN4;
		if (n4)
			n4->m_bfmeRefs--;
		Rva003CC890Node *n5 = m_bfmeN5;
		if (n5)
			n5->m_bfmeRefs--;
		Rva003CC890Node *n6 = m_bfmeN6;
		if (n6)
			n6->m_bfmeRefs--;
		Rva003CC890Node *n7 = m_bfmeN7;
		if (n7)
			n7->m_bfmeRefs--;
		m_bfmeRefs--;
	}
	m_bfmeFlag = 0;
}
