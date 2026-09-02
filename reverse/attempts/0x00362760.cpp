// ?handle@Gen00362760@@QAEXHPAX@Z
// partial score=0.95 date=2026-09-02
// cl: /DNDEBUG /MD /EHsc

class Gen00362760Elem
{
public:
	void handle(void *arg);

private:
	unsigned char m_data[0x58];
};

class Gen00362760
{
public:
	void handle(int index, void *arg);

private:
	unsigned char m_pad[0x18];
	Gen00362760Elem *m_begin;
	Gen00362760Elem *m_end;
};

// @?handle@Gen00362760@@QAEXHPAX@Z 0x00362760
void Gen00362760::handle(int index, void *arg)
{
	unsigned char *self = (unsigned char *)this;
	if (index < 0)
		return;
	Gen00362760Elem *begin = *(Gen00362760Elem **)(self + 0x18);
	Gen00362760Elem *end = *(Gen00362760Elem **)(self + 0x1c);
	if ((unsigned int)index >= (unsigned int)(end - begin))
		return;
	(*(Gen00362760Elem **)(self + 0x18))[index].handle(arg);
}
