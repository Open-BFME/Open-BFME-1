// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: GameClient::loadPostProcess at 0x00430540 (93B).
// ZH twin walks getDrawableList and lifts m_nextDrawableID. Retail enters
// through the Snapshot subobject at +8, so firstDrawable/getDrawableList is
// the virtual at GameClient+0x7C (this-8) and m_nextDrawableID is this+0x20
// (= GameClient+0x28, same as registerDrawable / allocDrawableID).
// Drawable::getNextDrawable is the inline +0x104 load.
// BFME tail: if the AsciiString at Snapshot+0xB0 is non-empty, notify
// TheTacticalView through vtable+0x220.

#define BFME_VSLOT(n) virtual void slot##n();

enum DrawableID
{
};

class Drawable
{
public:
	DrawableID getID() const;
	Drawable *getNextDrawable() const { return m_nextDrawable; }

private:
	unsigned char m_pad[0x104];
	Drawable *m_nextDrawable;
};

class SubsystemInterface
{
public:
	BFME_VSLOT(0) BFME_VSLOT(1) BFME_VSLOT(2) BFME_VSLOT(3) BFME_VSLOT(4)
	BFME_VSLOT(5) BFME_VSLOT(6) BFME_VSLOT(7) BFME_VSLOT(8) BFME_VSLOT(9)
	BFME_VSLOT(10) BFME_VSLOT(11) BFME_VSLOT(12) BFME_VSLOT(13) BFME_VSLOT(14)
	BFME_VSLOT(15) BFME_VSLOT(16) BFME_VSLOT(17) BFME_VSLOT(18) BFME_VSLOT(19)
	BFME_VSLOT(20) BFME_VSLOT(21) BFME_VSLOT(22) BFME_VSLOT(23) BFME_VSLOT(24)
	BFME_VSLOT(25) BFME_VSLOT(26) BFME_VSLOT(27) BFME_VSLOT(28) BFME_VSLOT(29)
	BFME_VSLOT(30)
	virtual Drawable *getDrawableList();
	int m_siPad;
};

struct BfmeNameString
{
	struct Buf
	{
		int ref;
		unsigned short len;
	};
	Buf *m_data;
};

class GameClient
{
public:
	virtual void crc();
	virtual void xfer();

protected:
	virtual void loadPostProcess();

	unsigned char m_snapPad[0x1C];
	DrawableID m_nextDrawableID;
	unsigned char m_snapPad2[0x8C];
	BfmeNameString m_name;
};

#undef BFME_VSLOT

#define BFME_TEN_VIRTUALS(PREFIX) \
	virtual void PREFIX##0(void); virtual void PREFIX##1(void); \
	virtual void PREFIX##2(void); virtual void PREFIX##3(void); \
	virtual void PREFIX##4(void); virtual void PREFIX##5(void); \
	virtual void PREFIX##6(void); virtual void PREFIX##7(void); \
	virtual void PREFIX##8(void); virtual void PREFIX##9(void)

class View
{
public:
	BFME_TEN_VIRTUALS(v00);
	BFME_TEN_VIRTUALS(v10);
	BFME_TEN_VIRTUALS(v20);
	BFME_TEN_VIRTUALS(v30);
	BFME_TEN_VIRTUALS(v40);
	BFME_TEN_VIRTUALS(v50);
	BFME_TEN_VIRTUALS(v60);
	BFME_TEN_VIRTUALS(v70);
	BFME_TEN_VIRTUALS(v80);
	BFME_TEN_VIRTUALS(v90);
	BFME_TEN_VIRTUALS(vA0);
	BFME_TEN_VIRTUALS(vB0);
	BFME_TEN_VIRTUALS(vC0);
	virtual void vD0(void);
	virtual void vD1(void);
	virtual void vD2(void);
	virtual void vD3(void);
	virtual void vD4(void);
	virtual void vD5(void);
	virtual void bfmeApplyName(BfmeNameString *name);
};

#undef BFME_TEN_VIRTUALS

extern View *TheTacticalView;

// Entered as the Snapshot subobject (GameClient+8). getDrawableList is the
// primary-vtable slot at +0x7C, reached by this-8.
// ?loadPostProcess@GameClient@@MAEXXZ
void GameClient::loadPostProcess(void)
{
	SubsystemInterface *client = (SubsystemInterface *)((char *)this - 8);
	Drawable *draw;
	for (draw = client->getDrawableList(); draw; draw = draw->getNextDrawable())
		if (draw->getID() >= m_nextDrawableID)
			m_nextDrawableID = (DrawableID)((unsigned)draw->getID() + 1);

	if (m_name.m_data != 0 && m_name.m_data->len != 0)
		TheTacticalView->bfmeApplyName(&m_name);
}
