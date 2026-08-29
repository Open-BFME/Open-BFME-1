// Open-BFME5 conversions: small self-contained bodies.

class Bfme5Counted
{
public:
	char m_bfmePad[0x24];
	int m_bfmeScale;
	char m_bfmePad2[0x74];
	int *m_bfmeCount;
};

class Bfme5Holder
{
public:
	int bfmeTotal(void);

	char m_bfmePad[0xc8];
	Bfme5Counted *m_bfmeCounted;
};

int Bfme5Holder::bfmeTotal(void)
{
	if (m_bfmeCounted)
		return *m_bfmeCounted->m_bfmeCount * m_bfmeCounted->m_bfmeScale;

	return 0;
}

class Bfme5Subject
{
public:
	char m_bfmePad[0x71];
	char m_bfmeBusy;
	char m_bfmePad2[0x4ab];
	char m_bfmeReady;
};

class Bfme5Watcher
{
public:
	char bfmeIsLive(void);

	char m_bfmePad[4];
	Bfme5Subject *m_bfmeSubject;
};

char Bfme5Watcher::bfmeIsLive(void)
{
	if (m_bfmeSubject->m_bfmeBusy)
		return 1;

	if (m_bfmeSubject && m_bfmeSubject->m_bfmeReady)
		return 1;

	return 0;
}
