// cl: /DNDEBUG /MD /O2
// Clean C++ conversion of the channel close helper at retail RVA 0x009D6DD0.

class BfmeChannel
{
public:
	virtual void slot0();
	virtual void slot1();
	virtual void slot2();
	virtual void slot3();
	virtual void bfmeWrite(const void *data, unsigned int size);
};

class Gen009D6DD0
{
public:
	void bfmeClose();

private:
	unsigned char m_pad[4];
	BfmeChannel *m_channel;
	bool m_emitEnd;
};

void Gen009D6DD0::bfmeClose()
{
	if (m_channel != 0)
	{
		if (m_emitEnd)
		{
			unsigned int endTag = 0x00454E44;
			m_channel->bfmeWrite(&endTag, sizeof(endTag));
		}
		m_channel = 0;
	}
}
