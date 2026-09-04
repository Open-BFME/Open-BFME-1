// cl: /DNDEBUG /MD /EHsc
//
// Rva003BFC20::run, retail 0x003BFC20, 92 bytes.
//
// Sibling gate on d_003b8450: if m_at3D, vcall+clear+notify on m_at20; if
// m_at70, read m_at78 then slide this back 8 for step/finish and the
// +0x78/+0xC8/+0xCC settle writes.

class Glo012F1024Type
{
public:
	void step();
};

extern Glo012F1024Type *TheLivingWorldCampaignManager;

class Gen003BFC20Owner
{
public:
	virtual void vslot0();
	virtual void vslot1();
	void clear();
	void notify();
};

class Rva003BFC20
{
public:
	void run();
	void finish();

private:
	char m_pad00[ 0x20 ];
	Gen003BFC20Owner *m_at20;
	char m_pad24[ 0x3D - 0x24 ];
	bool m_at3D;
	char m_pad3E[ 0x70 - 0x3E ];
	bool m_at70;
	char m_pad71[ 0x78 - 0x71 ];
	bool m_at78;
	char m_pad79[ 0xC8 - 0x79 ];
	bool m_atC8;
	char m_padC9[ 0xCC - 0xC9 ];
	int m_atCC;
};

// ?run@Rva003BFC20@@QAEXXZ
void Rva003BFC20::run()
{
	Rva003BFC20 *self = this;
	if( !self->m_at3D )
		return;
	self->m_at20->vslot1();
	self->m_at20->clear();
	self->m_at20->notify();
	if( !self->m_at70 )
		return;
	unsigned char flag = (unsigned char)self->m_at78;
	self = (Rva003BFC20 *)( (char *)self - 8 );
	if( flag )
	{
		TheLivingWorldCampaignManager->step();
		self->finish();
	}
	self->m_at78 = false;
	self->m_atC8 = true;
	self->m_atCC = 0x78;
}
