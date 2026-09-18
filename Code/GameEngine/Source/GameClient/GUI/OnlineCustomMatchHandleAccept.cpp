// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

template <typename T> class StringBase
{
protected:
	StringBase(const T *text);
	friend class UnicodeString;

private:
	void releaseBuffer();
	void *m_data;
};

class UnicodeString : private StringBase<unsigned short>
{
public:
	UnicodeString(const unsigned short *text) : StringBase<unsigned short>(text) {}
	~UnicodeString()
	{
		releaseBuffer();
	}
};

void setConnectingPlayerName(int index, const UnicodeString &text);
void setConnectingPlayerStatus(int index, const UnicodeString &text);

class GenActionSink
{
public:
	void add(void *owner, const char *name, int count, const char *first,
		int second, int third, int fourth, int fifth);
};

class BfmeMgr19E : public GenActionSink
{
};

extern BfmeMgr19E *g_mgr12F19E8;

class Rva00539110Owner
{
	public:
	char m_padding00[0x250];
	void *m_actionOwner;
};

class Gen0000C955
{
public:
	virtual void slot00();
	void handle(bool accepted);

private:
	char m_padding00[0x30];
	Rva00539110Owner *m_owner;
	char m_padding38[0x198];
	int m_acceptCount;
};

void Gen0000C955::handle(bool accepted)
{
	if (g_mgr12F19E8 == 0)
		return;

	if (accepted)
	{
		if (m_acceptCount == 0)
		{
			int index = 0;
			while (index < 8)
			{
				{
					UnicodeString emptyName((const unsigned short *)0x01084C34);
					setConnectingPlayerName(index, emptyName);
				}
				{
					UnicodeString emptyStatus((const unsigned short *)0x01084C34);
					setConnectingPlayerStatus(index, emptyStatus);
				}
				++index;
			}

			g_mgr12F19E8->add(m_owner->m_actionOwner,
				(const char *)0x011053D4, 1, (const char *)0x011074E4,
				0, 0, 0, 0);
		}
		++m_acceptCount;
	}
	else if (m_acceptCount != 0)
	{
		--m_acceptCount;
		if (m_acceptCount == 0)
			g_mgr12F19E8->add(m_owner->m_actionOwner,
				(const char *)0x011053D4, 1, (const char *)0x011074C8,
				0, 0, 0, 0);
	}
}
