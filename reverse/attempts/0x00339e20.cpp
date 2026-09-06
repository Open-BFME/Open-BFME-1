// ??1BfmeOwnVTZ@@UAE@XZ
// partial score=0.55 date=2026-09-05
// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: near-twin of the 0x00339DA0 BfmeOwnVTY constructor's vtable (0x010E7688) family;
// virtual destructor at retail 0x00339E20 reassigns the owned string via the pointer member
// then clears the local string member.

class BfmeStrVTZ
{
public:
	~BfmeStrVTZ() { bfmeClearVTZ(); }
	void bfmeAssignVTZ(const BfmeStrVTZ &other);
	void bfmeClearVTZ();
	unsigned short *m_bfme00;
};

class BfmeOwnVTZ
{
public:
	virtual void bfmeSlot0VTZ();
	virtual ~BfmeOwnVTZ();
	BfmeStrVTZ m_bfme04;
	BfmeStrVTZ *m_bfme08;
};

// ?d_00339e20@@YAXXZ
BfmeOwnVTZ::~BfmeOwnVTZ()
{
	BfmeOwnVTZ *self = this;
	self->m_bfme08->bfmeAssignVTZ(self->m_bfme04);
	self->m_bfme04.bfmeClearVTZ();
}
