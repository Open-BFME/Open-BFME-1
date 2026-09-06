// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
// Score buffer destructor at retail RVA 0x008C6020.

extern void (__cdecl *TheBfmeFree)(void *storage, unsigned int bytes);

class Gen008C6020Buffer
{
public:
	~Gen008C6020Buffer()
	{
		if (m_buffer != 0)
			TheBfmeFree(m_buffer, m_count << 2);
	}

private:
	int m_count;
	void *m_buffer;
	int m_pad;
};

class Gen008C6020Grid
{
public:
	~Gen008C6020Grid()
	{
		if (m_buffer != 0)
			TheBfmeFree(m_buffer, m_width * m_count << 2);
	}

private:
	int m_width;
	int m_count;
	void *m_buffer;
};

class Gen008C6020
{
public:
	~Gen008C6020();

private:
	char m_head[4];
	Gen008C6020Buffer m_buffer1;
	Gen008C6020Buffer m_buffer2;
	Gen008C6020Buffer m_buffer3;
	Gen008C6020Buffer m_buffer4;
	Gen008C6020Buffer m_buffer5;
	Gen008C6020Buffer m_buffer6;
	Gen008C6020Grid m_grid;
};

Gen008C6020::~Gen008C6020()
{
}
