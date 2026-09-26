// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// BFME View::xfer, retail RVA 0x0045C4A0 (777 bytes).
// Zero Hour View.cpp writes version 1 (angle and position); BFME extends it to
// version 3 with the camera state through View+0xB0 and a linked record list
// whose nodes serialize through Rva0045B700::visit.
typedef unsigned char UnsignedByte;

struct XferVersionInfo
{
	UnsignedByte version;
	UnsignedByte currentVersion;
};

struct BfmeVec1261
{
	float x;
	float y;
	float z;
};

class Xfer
{
public:
	virtual void slot00();
	virtual bool isLoading();
	virtual void slot08();
	virtual bool isLightCRC();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1C();
	virtual void slot20();
	virtual void xferUser(void *, int);
	virtual void xferVersion(XferVersionInfo *);
	virtual void slot2C();
	virtual void slot30();
	virtual void slot34();
	virtual void slot38();
	virtual void slot3C();
	virtual void slot40();
	virtual void slot44();
	virtual void slot48();
	virtual void slot4C();
	virtual void xferString(void *);
	virtual void slot54();
	virtual void slot58();
	virtual void xferOpaque(void *);
	virtual void slot60();
	virtual void xferCoord3D(void *);
	virtual void slot68();
	virtual void xferReal(float *);
	virtual void slot70();
	virtual void slot74();
	virtual void xferInt(int *);
	virtual void slot7C();
	virtual void slot80();
	virtual void slot84();
	virtual void slot88();
	virtual void xferBool(bool *);
	virtual void slot90();
};

class Open245B700Visitor;

class Rva0045B700
{
public:
	Rva0045B700() : m_next(0), m_first(0) {}
	void visit(Open245B700Visitor *visitor);

	Rva0045B700 *m_next;
	int m_first;
	int m_second;
	unsigned char m_padding0[8];
	int m_third;
	int m_fourth;
	int m_fifth;
	int m_sixth;
	int m_seventh;
	int m_eighth;
	unsigned char m_ninth;
	unsigned char m_tenth;
};

class View
{
protected:
	virtual void xfer(Xfer *xfer);

public:
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1C();
	virtual void slot20();
	virtual void slot24();
	virtual void slot28();
	virtual void slot2C();
	virtual void slot30();
	virtual void slot34();
	virtual void slot38();
	virtual void slot3C();
	virtual void slot40();
	virtual void slot44();
	virtual void slot48();
	virtual void slot4C();
	virtual void slot50();
	virtual void transform(const BfmeVec1261 *value);
	virtual void slot58();
	virtual void slot5C();
	virtual void slot60();
	virtual void slot64();
	virtual void slot68();
	virtual void slot6C();
	virtual void slot70();
	virtual void slot74();
	virtual void slot78();
	virtual void slot7C();
	virtual void slot80();
	virtual void slot84();
	virtual void slot88();
	virtual void slot8C();
	virtual void slot90();
	virtual void slot94();
	virtual void slot98();
	virtual void slot9C();
	virtual void slotA0();
	virtual void slotA4();
	virtual void slotA8();
	virtual void slotAC();
	virtual void slotB0();
	virtual void slotB4();
	virtual void slotB8();
	virtual void slotBC();
	virtual void slotC0();
	virtual void slotC4();
	virtual void slotC8();
	virtual void slotCC();
	virtual void slotD0();
	virtual void slotD4();
	virtual void slotD8();
	virtual void slotDC();
	virtual void slotE0();
	virtual void slotE4();
	virtual void slotE8();
	virtual void slotEC();
	virtual void slotF0();
	virtual void slotF4();
	virtual void setAngle(float value);
	virtual float getAngle();
	virtual void slot100();
	virtual void slot104();
	virtual void slot108();
	virtual void slot10C();
	virtual void slot110();
	virtual void getPosition(BfmeVec1261 *value);

	unsigned char m_padding04[0x14];
	int m_bfme18;
	int m_height;
	int m_bfme20;
	int m_originY;
	float m_angle;
	float m_pitchAngle;
	float m_bfme30;
	float m_bfme34;
	float m_bfme38;
	float m_zoom;
	float m_bfme40;
	bool m_heightAboveGround;
	unsigned char m_padding45[3];
	float m_zoomLimited;
	float m_bfme4c;
	float m_bfme50;
	float m_currentHeightAboveGround;
	float m_terrainHeightUnderCamera;
	int m_bfme5c;
	void *m_bfme60;
	float m_bfme64;
	float m_bfme68;
	float m_FOV;
	float m_bfme70;
	bool m_bfme74;
	bool m_bfme75;
	bool m_bfme76;
	unsigned char m_padding77;
	int m_guardBandBias[2];
	Rva0045B700 *m_bfme80;
	bool m_bfme84;
	unsigned char m_padding85[3];
	int m_bfme88;
	int m_bfme8c;
	int m_bfme90;
	int m_bfme94;
	float m_bfme98;
	float m_bfme9c;
	float m_bfmea0;
	float m_bfmea4;
	float m_bfmea8;
	float m_bfmeac;
	float m_bfmeb0;
};

class MidVirtualSlot90Receiver;
void Rva0010C3C0(MidVirtualSlot90Receiver *receiver, void *value);
void BfmeParticleSystemXferHandle(Xfer &xfer, void *value);

void View::xfer(Xfer *xfer)
{
	if (xfer->isLightCRC())
		return;

	XferVersionInfo version = { 1, 3 };
	xfer->xferVersion(&version);

	float angle = getAngle();
	xfer->xferReal(&angle);
	setAngle(angle);

	BfmeVec1261 position;
	getPosition(&position);
	xfer->xferReal(&position.x);
	xfer->xferReal(&position.y);
	xfer->xferReal(&position.z);
	transform(&position);

	if (version.currentVersion < 3)
	{
		xfer->xferInt(&m_bfme18);
		xfer->xferInt(&m_height);
		xfer->xferInt(&m_bfme20);
		xfer->xferInt(&m_originY);
	}

	if (version.currentVersion >= 2)
	{
		xfer->xferReal(&m_angle);
	}

	xfer->xferReal(&m_pitchAngle);
	xfer->xferReal(&m_bfme30);
	xfer->xferReal(&m_bfme34);
	xfer->xferReal(&m_bfme38);
	xfer->xferReal(&m_bfme40);
	xfer->xferBool(&m_heightAboveGround);
	xfer->xferReal(&m_zoomLimited);
	xfer->xferReal(&m_bfme4c);
	xfer->xferReal(&m_bfme50);
	xfer->xferReal(&m_currentHeightAboveGround);

	Rva0010C3C0((MidVirtualSlot90Receiver *)xfer, &m_terrainHeightUnderCamera);
	BfmeParticleSystemXferHandle(*xfer, &m_bfme5c);
	xfer->xferUser(&m_bfme60, 4);
	xfer->xferReal(&m_bfme64);
	xfer->xferReal(&m_bfme68);

	if (version.currentVersion < 3)
	{
		xfer->xferReal(&m_FOV);
	}
	xfer->xferReal(&m_bfme70);
	xfer->xferBool(&m_bfme74);
	xfer->xferBool(&m_bfme75);
	xfer->xferBool(&m_bfme76);
	xfer->xferString(&m_guardBandBias[0]);

	int count = 0;
	Rva0045B700 *node;
	for (node = m_bfme80; node != 0; node = node->m_next)
		++count;
	xfer->xferInt(&count);
	if (xfer->isLoading())
	{
		for (int index = 0; index < count; ++index)
		{
			node = new Rva0045B700;
			node->visit((Open245B700Visitor *)xfer);
			node->m_next = m_bfme80;
			m_bfme80 = node;
		}
	}
	else
	{
		for (node = m_bfme80; node != 0; node = node->m_next)
			node->visit((Open245B700Visitor *)xfer);
	}
	xfer->xferBool(&m_bfme84);
	Rva0010C3C0((MidVirtualSlot90Receiver *)xfer, &m_bfme88);
	xfer->xferOpaque(&m_bfme8c);
	xfer->xferReal(&m_bfme98);
	xfer->xferReal(&m_bfme9c);
	xfer->xferReal(&m_bfmea0);
	xfer->xferReal(&m_bfmea4);
	xfer->xferReal(&m_bfmea8);
	xfer->xferReal(&m_bfmeac);
	xfer->xferReal(&m_bfmeb0);

}
