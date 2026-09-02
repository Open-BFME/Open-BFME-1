// cl: /DNDEBUG /MD /EHsc

// Address-derived element identity: a matched counted loop calls this body
// through its ILT.  The element owns a record at +4; before deleting it the
// record's optional +8 interface receives its slot-0x40 shutdown callback.
class Rva0060A240Shutdown
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1C();
	virtual void slot20();
	virtual void slot24();
	virtual void slot28();
	virtual void slot2C();
	virtual void slot30();
	virtual void slot34();
	virtual void slot38();
	virtual void slot3C();
	virtual void shutdown();
};

class Gen_uwm_00009eda
{
public:
	~Gen_uwm_00009eda();

private:
	char m_pad[8];
	Rva0060A240Shutdown *m_shutdown;

	friend class Rva0060A240Element;
};

class Rva0060A240Element
{
public:
	void update();

private:
	char m_pad[4];
	Gen_uwm_00009eda *m_owned;
};

// ?update@Rva0060A240Element@@QAEXXZ
void Rva0060A240Element::update()
{
	Gen_uwm_00009eda *owned = m_owned;
	if (owned != 0)
	{
		Rva0060A240Shutdown *shutdown = owned->m_shutdown;
		if (shutdown != 0)
			shutdown->shutdown();
		delete m_owned;
		m_owned = 0;
	}
}
