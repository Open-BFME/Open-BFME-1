// ?xfer@View@@MAEXPAVXfer@@@Z
// partial score=0.99 date=2026-09-19
// Retail 0x0045C4A0 transfers the BFME View state and its linked records.
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
	int m_width;
	int m_height;
	int m_originX;
	int m_originY;
	float m_angle;
	float m_pitch;
	float m_maxZoom;
	float m_minZoom;
	float m_maxHeight;
	float m_minHeight;
	float m_zoom;
	bool m_zoomLimited;
	unsigned char m_padding45[3];
	float m_defaultAngle;
	float m_defaultPitch;
	float m_heightAboveGround;
	float m_currentHeightAboveGround;
	float m_terrainHeight;
	int m_cameraLock;
	void *m_cameraLockDrawable;
	float m_lockType;
	float m_lockDistance;
	float m_fieldOfView;
	float m_mouseLocked;
	bool m_guardBandBiasX;
	bool m_okToAdjustHeight;
	bool m_snapImmediate;
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
		xfer->xferInt(&m_width);
		xfer->xferInt(&m_height);
		xfer->xferInt(&m_originX);
		xfer->xferInt(&m_originY);
	}

	if (version.currentVersion >= 2)
	{
		xfer->xferReal(&m_angle);
	}

	xfer->xferReal(&m_pitch);
	xfer->xferReal(&m_maxZoom);
	xfer->xferReal(&m_minZoom);
	xfer->xferReal(&m_maxHeight);
	xfer->xferReal(&m_zoom);
	xfer->xferBool(&m_zoomLimited);
	xfer->xferReal(&m_defaultAngle);
	xfer->xferReal(&m_defaultPitch);
	xfer->xferReal(&m_heightAboveGround);
	xfer->xferReal(&m_currentHeightAboveGround);

	Rva0010C3C0((MidVirtualSlot90Receiver *)xfer, &m_terrainHeight);
	BfmeParticleSystemXferHandle(*xfer, &m_cameraLock);
	xfer->xferUser(&m_cameraLockDrawable, 4);
	xfer->xferReal(&m_lockType);
	xfer->xferReal(&m_lockDistance);

	if (version.currentVersion < 3)
	{
		xfer->xferReal(&m_fieldOfView);
	}
	xfer->xferReal(&m_mouseLocked);
	xfer->xferBool(&m_guardBandBiasX);
	xfer->xferBool(&m_okToAdjustHeight);
	xfer->xferBool(&m_snapImmediate);
	xfer->xferString(&m_guardBandBias[0]);

	int count = 0;
	Rva0045B700 *node = m_bfme80;
	while (node != 0)
	{
		++count;
		node = node->m_next;
	}
	xfer->xferInt(&count);

	if (xfer->isLoading())
	{
		if (count > 0)
		{
			int index = 0;
			do
			{
				Rva0045B700 *newNode = new Rva0045B700;
				node = 0;
				if (newNode != 0)
				{
					newNode->m_next = 0;
					newNode->m_first = 0;
					node = newNode;
				}
				node->visit((Open245B700Visitor *)xfer);
				node->m_next = m_bfme80;
				m_bfme80 = node;
				++index;
			} while (index < count);
		}
	}
	else
	{
		node = m_bfme80;
		while (node != 0)
		{
			node->visit((Open245B700Visitor *)xfer);
			node = node->m_next;
		}
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
