// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

class Rva00411C30Audio
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0c();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1c();
	virtual void slot20();
	virtual void slot24();
	virtual void slot28();
	virtual void slot2c();
	virtual void slot30();
	virtual void slot34();
	virtual void slot38();
	virtual void slot3c();
	virtual void slot40();
	virtual void slot44();
	virtual void slot48();
	virtual void slot4c(void *handle);
};

extern Rva00411C30Audio *g_audio012ED668;

struct Rva00411C30Event
{
	char m_pad[0x10];
	void *m_handle;
};

class Rva00411C30
{
	char m_pad[0x14C];
	Rva00411C30Event *m_event;

public:
	void remove();
};

void Rva00411C30::remove()
{
	Rva00411C30Event *event = m_event;
	if (event)
		g_audio012ED668->slot4c(event->m_handle);
}
