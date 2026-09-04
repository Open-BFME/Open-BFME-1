// ??1Q3EhMember0089C900@@QAE@XZ
// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc-

struct EvaStringData0089C900
{
	unsigned short m_refCount;
};

class EvaTaggedValue0089C900
{
public:
	virtual void retain();
	virtual void release();
};

struct EvaSideSound0089C900
{
	EvaStringData0089C900 *m_string;
	unsigned int m_value;
};

extern void (__cdecl **Rva01337A30ReleaseTable)(void *);
extern void (*Rva008A30A0ReleasePtr)(void *);

class Q3EhMember0089C900
{
public:
	~Q3EhMember0089C900();

private:
	volatile int m_count;
	EvaSideSound0089C900 *m_elements;
	EvaTaggedValue0089C900 *m_left;
	EvaTaggedValue0089C900 *m_right;
};

Q3EhMember0089C900::~Q3EhMember0089C900()
{
	register Q3EhMember0089C900 *self = this;
	int i = 0;
	unsigned int offset;
	if (self->m_right != (EvaTaggedValue0089C900 *)i && ((unsigned int)self->m_right & 1) == 0)
	{
		self->m_right->release();
		self->m_right = (EvaTaggedValue0089C900 *)i;
	}

	if (self->m_left != (EvaTaggedValue0089C900 *)i && ((unsigned int)self->m_left & 1) == 0)
	{
		self->m_left->release();
		self->m_left = (EvaTaggedValue0089C900 *)i;
	}

	if (self->m_elements != (EvaSideSound0089C900 *)i)
	{
		for (; i < self->m_count; ++i)
			{
				offset = (unsigned int)i * 8;
				EvaStringData0089C900 *string = *(EvaStringData0089C900 **)((char *)self->m_elements + offset);
				if (string != 0)
					{
						if (string != reinterpret_cast<EvaStringData0089C900 *>(0x012D5298))
						{
							EvaTaggedValue0089C900 *sound = (EvaTaggedValue0089C900 *)((unsigned int)*(unsigned int *)((char *)self->m_elements + offset + 4) & ~1u);
							if (sound != 0 && (*(unsigned int *)((char *)self->m_elements + offset + 4) & 1) == 0)
							{
								sound = (EvaTaggedValue0089C900 *)((unsigned int)sound & ~1u);
								sound->release();
							}
					}

					EvaSideSound0089C900 *entry = (EvaSideSound0089C900 *)((char *)self->m_elements + offset);
					EvaStringData0089C900 *data = entry->m_string;
					--data->m_refCount;
					if (data->m_refCount == 0)
						Rva01337A30ReleaseTable[1](data);
					entry->m_string = 0;
					}
			}

		Rva008A30A0ReleasePtr(self->m_elements);
		self->m_elements = 0;
	}
}
