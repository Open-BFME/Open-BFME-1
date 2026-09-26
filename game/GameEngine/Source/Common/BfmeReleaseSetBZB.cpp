void bfmeTwoBZB(void *what);

struct BfmeHolderBZB6
{
	char m_lead[0x24];
	void *m_at24;
	void *m_at28;
	void *m_at2C;
	char m_pad30[0x34 - 0x30];
	void *m_at34;
	char m_pad38[0x3C - 0x38];
	void *m_at3C;
	char m_pad40[0xA0 - 0x40];
	void *m_atA0;
	void *m_atA4;
	void *m_atA8;
	void *m_atAC;
	void *m_atB0;
	char m_padB4[0xB8 - 0xB4];
	void *m_atB8;
	void *m_atBC;
};

void bfmeOneBZB(void *what)
{
	BfmeHolderBZB6 *self = (BfmeHolderBZB6 *)what;

	if (self->m_atB8)
		bfmeTwoBZB(self->m_atB8);
	self->m_atB8 = 0;
	self->m_atBC = 0;

	if (self->m_atA0)
		bfmeTwoBZB(self->m_atA0);
	self->m_atA0 = 0;
	self->m_at34 = 0;

	if (self->m_atA4)
		bfmeTwoBZB(self->m_atA4);
	self->m_atA4 = 0;
	self->m_at3C = 0;

	if (self->m_atA8)
		bfmeTwoBZB(self->m_atA8);
	self->m_atA8 = 0;
	self->m_at24 = 0;

	if (self->m_atAC)
		bfmeTwoBZB(self->m_atAC);
	self->m_atAC = 0;
	self->m_at28 = 0;

	if (self->m_atB0)
		bfmeTwoBZB(self->m_atB0);
	self->m_atB0 = 0;
	self->m_at2C = 0;
}
