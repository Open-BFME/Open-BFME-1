// cl: /DNDEBUG /MD /EHsc
// BFME's RingRenderObjClass visibility wrapper. The retail class has two more
// virtual slots than the later public header; this TU models the exact ABI
// slice without changing that shared vendored declaration.

#define BFME_VIRTUAL_EIGHT(a, b, c, d, e, f, g, h) \
	virtual void Dummy##a(); virtual void Dummy##b(); \
	virtual void Dummy##c(); virtual void Dummy##d(); \
	virtual void Dummy##e(); virtual void Dummy##f(); \
	virtual void Dummy##g(); virtual void Dummy##h();

class RenderObjClass
{
public:
	BFME_VIRTUAL_EIGHT(0, 1, 2, 3, 4, 5, 6, 7)
	BFME_VIRTUAL_EIGHT(8, 9, 10, 11, 12, 13, 14, 15)
	BFME_VIRTUAL_EIGHT(16, 17, 18, 19, 20, 21, 22, 23)
	BFME_VIRTUAL_EIGHT(24, 25, 26, 27, 28, 29, 30, 31)
	BFME_VIRTUAL_EIGHT(32, 33, 34, 35, 36, 37, 38, 39)
	BFME_VIRTUAL_EIGHT(40, 41, 42, 43, 44, 45, 46, 47)
	BFME_VIRTUAL_EIGHT(48, 49, 50, 51, 52, 53, 54, 55)
	BFME_VIRTUAL_EIGHT(56, 57, 58, 59, 60, 61, 62, 63)
	BFME_VIRTUAL_EIGHT(64, 65, 66, 67, 68, 69, 70, 71)
	BFME_VIRTUAL_EIGHT(72, 73, 74, 75, 76, 77, 78, 79)
	BFME_VIRTUAL_EIGHT(80, 81, 82, 83, 84, 85, 86, 87)
	BFME_VIRTUAL_EIGHT(88, 89, 90, 91, 92, 93, 94, 95)
	virtual void Dummy96();
	virtual void Dummy97();
	virtual void Dummy98();
	virtual void Dummy99();
	virtual void Set_Hidden(int onoff)
	{
		if (onoff) {
			Bits &= ~0x2000UL;
		} else {
			Bits |= 0x2000UL;
		}
	}
	virtual void Set_Visible(int onoff, int sceneToken);
	virtual void Set_Animation_Hidden(int onoff)
	{
		if (onoff) {
			Bits &= ~0x4000UL;
		} else {
			Bits |= 0x4000UL;
		}
	}
	virtual void Set_Force_Visible(int onoff);
	BFME_VIRTUAL_EIGHT(104, 105, 106, 107, 108, 109, 110, 111)
	BFME_VIRTUAL_EIGHT(112, 113, 114, 115, 116, 117, 118, 119)
	BFME_VIRTUAL_EIGHT(120, 121, 122, 123, 124, 125, 126, 127)
	virtual void Dummy128();
	virtual void Dummy129();
	virtual void Dummy130();
	virtual void Dummy131();
	virtual void Dummy132();

protected:
	unsigned char PaddingToBits[12];
	unsigned long Bits;
};

class RingRenderObjClass : public RenderObjClass
{
public:
	virtual void Set_Hidden(int onoff);
	virtual void Set_Visible(int onoff, int sceneToken = 0);
	virtual void Set_Animation_Hidden(int onoff);
	virtual void Set_Force_Visible(int onoff);
	virtual void Update_On_Visibilty();
};

// ?Set_Hidden@RingRenderObjClass@@UAEXH@Z
void RingRenderObjClass::Set_Hidden(int onoff)
{
	RenderObjClass::Set_Hidden(onoff);
	Update_On_Visibilty();
}

// ?Set_Visible@RingRenderObjClass@@UAEXHH@Z
void RingRenderObjClass::Set_Visible(int onoff, int sceneToken)
{
	RenderObjClass::Set_Visible(onoff, sceneToken);
	Update_On_Visibilty();
}

#undef BFME_VIRTUAL_EIGHT
