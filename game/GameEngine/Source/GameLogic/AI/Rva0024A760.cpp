// cl: /DNDEBUG /MD /EHsc
// Open-BFME: Horde member refresh and status update at retail 0x0024A760.

class BfmeRvaA760Object
{
public:
	char m_head[0x128];
	union
	{
		unsigned char m_flagsByte;
		unsigned int m_flags;
	};
	unsigned int m_status;

	void apply(int value);
	void notify(void);
};

class BfmeRvaA760CountOwner
{
public:
	int getCount(void);
};

class BfmeRvaA760Probe
{
public:
	char m_head[0x228];
	int m_capacity;
};

class BfmeRvaA760ProbeInterface
{
public:
	bool accepts(BfmeRvaA760Object *object, int count);
};

class BfmeRvaA760Output
{
public:
	void fill(int *value);
};

class Rva0024A760
{
public:
	void update(BfmeRvaA760Object *object);
	void finish(BfmeRvaA760Object *object);

	char m_head[4];
	BfmeRvaA760Probe *m_probe;
	BfmeRvaA760CountOwner *m_countOwner;
	char m_gap[0xec - 0x0c];
	BfmeRvaA760Output m_output;
	int m_remaining;
};

void Rva0024A760::update(BfmeRvaA760Object *object)
{
	BfmeRvaA760Object *member = object;
	BfmeRvaA760CountOwner *countOwner = m_countOwner;
	BfmeRvaA760Probe *probe = m_probe;
	int count = countOwner->getCount();
	if (((BfmeRvaA760ProbeInterface *)((char *)probe + 0x224))
		->accepts(member, count))
	{
		if (probe->m_capacity > 0)
		{
			int output;
			((BfmeRvaA760Output *)((char *)this + 0xec))->fill(&output);
			--m_remaining;
			member->apply(0x14);
			signed char status = (signed char)member->m_status;
			if ((status >> 7) == 0)
				return;
			member->m_status &= 0xffffff7f;
			member->notify();
			return;
		}
	}

	if ((member->m_flagsByte & 0x40) != 0)
	{
		member->m_flags &= 0xffffffbf;
		member->notify();
	}
	finish(member);
}
