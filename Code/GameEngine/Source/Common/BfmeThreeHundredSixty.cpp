extern "C" unsigned char bfmeVftVC[];

void bfmeFreeVC(void *what);

class BfmeThingVC
{
public:
	void *bfmeKillVC(int flags);
	void *m_bfmeVft;
	void *m_bfmeWhat;
	void **m_bfmeSlot;
};

void *BfmeThingVC::bfmeKillVC(int flags)
{
	void **slot = m_bfmeSlot;
	void *what = m_bfmeWhat;
	m_bfmeVft = bfmeVftVC;
	*slot = what;
	if ((flags & 1) != 0)
		bfmeFreeVC(this);
	return this;
}
