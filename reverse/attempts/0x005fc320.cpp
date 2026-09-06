// ?d_005fc320@@YAXXZ
// partial score=0.94 date=2026-09-06
// cl: /O2 /Ob1 /DNDEBUG /MD /EHs-c-
// Retail 0x005FC320, 105 bytes.  The owner is the small FX playback state
// whose context supplies the position, start frame, and completion flag.

struct Coord3D
{
	float x;
	float y;
	float z;
};

class Matrix3D;

class FXList
{
public:
	bool bfmeIsBlocked(void) const;
};

class BridgeAreaEffectsFXShim
{
public:
	void doFXPos(const Coord3D *, const Matrix3D *, float, const Coord3D *) const;
};

class ClientRoot005FC320
{
public:
	virtual void slot00(void) = 0;
	virtual void slot01(void) = 0;
	virtual void slot02(void) = 0;
	virtual void slot03(void) = 0;
	virtual void slot04(void) = 0;
	virtual void slot05(void) = 0;
	virtual void slot06(void) = 0;
	virtual void slot07(void) = 0;
	virtual void slot08(void) = 0;
	virtual void slot09(void) = 0;
	virtual void slot10(void) = 0;
	virtual void slot11(void) = 0;
	virtual void slot12(void) = 0;
	virtual void slot13(void) = 0;
	virtual void slot14(void) = 0;
	virtual void slot15(void) = 0;
	virtual void slot16(void) = 0;
	virtual void slot17(void) = 0;
	virtual void slot18(void) = 0;
	virtual void slot19(void) = 0;
	virtual void slot20(void) = 0;
	virtual void slot21(void) = 0;
	virtual void slot22(void) = 0;
	virtual void slot23(void) = 0;
	virtual void slot24(void) = 0;
	virtual void slot25(void) = 0;
	virtual unsigned int getFrame(void) = 0;
};

#define TheGameClient (*(ClientRoot005FC320 **)0x012F1464)

class Rva005FC320
{
public:
	void update(void);

private:
	char m_pad00[4];
	const void *m_context;
	char m_pad08[4];
	bool m_complete;
	char m_pad0d[7];
	int m_threshold;
	BridgeAreaEffectsFXShim *m_fx;
	bool m_active;
};

class Rva005FC320Context
{
private:
	char m_pad00[0x1c];

public:
	Coord3D m_position;
	__forceinline const Coord3D *getPosition(void) const { return &m_position; }
};

// ?update@Rva005FC320@@QAEXXZ
void Rva005FC320::update(void)
{
	if (!m_active)
		return;

	if (!m_fx)
		return;

	const Rva005FC320Context *context = (const Rva005FC320Context *)m_context;
	unsigned int frame = TheGameClient->getFrame();
	if (frame - *(unsigned int *)((char *)context + 0x6c) < (unsigned int)m_threshold)
		return;

	volatile Coord3D *position = (volatile Coord3D *)context->getPosition();
	const BridgeAreaEffectsFXShim *fx = m_fx;
	if (fx && !((FXList *)fx)->bfmeIsBlocked())
		fx->doFXPos((const Coord3D *)position, 0, 0.0f, 0);

	bool complete = m_complete;
	m_active = false;
	if (complete)
		*(unsigned int *)((char *)m_context + 0x68) = 1;
}
