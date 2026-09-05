// cl: /O2 /Ob2 /GR- /EHsc- /MD /DNDEBUG
// RVA-derived owner; descriptive getCurrentAnimFraction. ZH twin in W3DModelDraw.cpp
// without isAnyMaintainFrameFlagSet. Class_ID vslot +0x0C, Peek_Animation_And_Info
// vslot +0x20C. Owning layout is RVA-derived; m_renderObject is at +0x34.

#define TEN_SLOTS(P) \
	virtual void *s_##P##0(); virtual void *s_##P##1(); \
	virtual void *s_##P##2(); virtual void *s_##P##3(); \
	virtual void *s_##P##4(); virtual void *s_##P##5(); \
	virtual void *s_##P##6(); virtual void *s_##P##7(); \
	virtual void *s_##P##8(); virtual void *s_##P##9()

class HAnimClass;

class Rva0075BA30OwnerRenderObj
{
public:
	virtual void *dtor();
	virtual void *clone();
	virtual void *pad2();
	virtual int Class_ID();
	TEN_SLOTS(a); TEN_SLOTS(b); TEN_SLOTS(c); TEN_SLOTS(d);
	TEN_SLOTS(e); TEN_SLOTS(f); TEN_SLOTS(g); TEN_SLOTS(h);
	TEN_SLOTS(i); TEN_SLOTS(j); TEN_SLOTS(k); TEN_SLOTS(l);
	virtual void *s_m0(); virtual void *s_m1(); virtual void *s_m2();
	virtual void *s_m3(); virtual void *s_m4(); virtual void *s_m5();
	virtual void *s_m6();
	virtual HAnimClass *Peek_Animation_And_Info(float &frame, int &numFrames, int &mode, float &mult);
};

#undef TEN_SLOTS

class Rva0075BA30Owner
{
	float getCurrentAnimFraction() const;

	int m_pad0[5];
	void *m_curState;
	int m_pad1[7];
	Rva0075BA30OwnerRenderObj *m_renderObject;
};

// ?getCurrentAnimFraction@Rva0075BA30Owner@@ABEMXZ
float Rva0075BA30Owner::getCurrentAnimFraction() const
{
	if (m_curState != 0 && m_renderObject != 0 && m_renderObject->Class_ID() == 0x19)
	{
		float framenum;
		float dummy;
		int mode;
		int numFrames;

		m_renderObject->Peek_Animation_And_Info(framenum, numFrames, mode, dummy);
		if (framenum < 0.0)
			return 0.0f;
		else if (framenum >= numFrames)
			return 1.0f;
		else
			return framenum / ((float)numFrames - 1.0f);
	}

	return -1.0f;
}
