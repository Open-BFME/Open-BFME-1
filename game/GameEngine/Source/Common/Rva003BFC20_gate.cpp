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

// Retail's global at 0x012F1024 is EA's LivingWorldCampaignManager singleton,
// defined once in GameEngine/Source/GameLogic/LivingWorld/
// LivingWorldCampaignManager.cpp, so this reference carries that canonical type
// (class, not struct); the local view above is cast in at the one use.
class LivingWorldCampaignManager;

extern LivingWorldCampaignManager *TheLivingWorldCampaignManager;

// ILTs 0x00040016 and 0x0002DE89 reach the matched Glo012F1028Sub
// bodies at 0x003CAD90 and 0x003CAD20.
class Glo012F1028Sub
{
public:
	virtual void vslot0();
	virtual void vslot1();
	void refresh003CAD90();
	void bfmeNotify();
};

// ILT 0x0000A754 reaches the matched niladic member at 0x003BEC30.
class Rva003BEED0
{
public:
	void finish();
};

class Rva003BFC20
{
public:
	void run();

private:
	char m_pad00[ 0x20 ];
	Glo012F1028Sub *m_at20;
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
	self->m_at20->refresh003CAD90();
	self->m_at20->bfmeNotify();
	if( !self->m_at70 )
		return;
	unsigned char flag = (unsigned char)self->m_at78;
	self = (Rva003BFC20 *)( (char *)self - 8 );
	if( flag )
	{
		((Glo012F1024Type *)TheLivingWorldCampaignManager)->step();
		((Rva003BEED0 *)self)->finish();
	}
	self->m_at78 = false;
	self->m_atC8 = true;
	self->m_atCC = 0x78;
}
