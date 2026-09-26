// cl: /O2
// BFME W3DView::pitchCamera, retail 0x0073FCF0.
// BFME stores the pitch movement state at the offsets below.  The setter at
// 0x0002A1B2 receives the two ease values and the duration as float words.

typedef float Real;
typedef int Int;
typedef bool Bool;

#define TheAnimationMsPerStep (*(Int *)0x012BB1CC)
#define BfmeKTHE (*(Real *)0x0109ECC0)

class BfmeThingBRD
{
public:
	void bfmeDoBRD(void *, void *, void *);

private:
	char m_body[8];
};

class W3DView;

class Gen0073C890Owner
{
	friend class W3DView;

	void updateOneFrame();
};

class W3DView
{
public:
	#define BFME_SLOT(n) virtual Real bfmeSlot##n(Real) = 0;
	BFME_SLOT(0)
	BFME_SLOT(1)
	BFME_SLOT(2)
	BFME_SLOT(3)
	BFME_SLOT(4)
	BFME_SLOT(5)
	BFME_SLOT(6)
	BFME_SLOT(7)
	BFME_SLOT(8)
	BFME_SLOT(9)
	BFME_SLOT(10)
	BFME_SLOT(11)
	BFME_SLOT(12)
	BFME_SLOT(13)
	BFME_SLOT(14)
	BFME_SLOT(15)
	BFME_SLOT(16)
	BFME_SLOT(17)
	BFME_SLOT(18)
	BFME_SLOT(19)
	BFME_SLOT(20)
	BFME_SLOT(21)
	BFME_SLOT(22)
	BFME_SLOT(23)
	BFME_SLOT(24)
	BFME_SLOT(25)
	BFME_SLOT(26)
	BFME_SLOT(27)
	BFME_SLOT(28)
	BFME_SLOT(29)
	BFME_SLOT(30)
	BFME_SLOT(31)
	BFME_SLOT(32)
	BFME_SLOT(33)
	BFME_SLOT(34)
	BFME_SLOT(35)
	BFME_SLOT(36)
	BFME_SLOT(37)
	BFME_SLOT(38)
	BFME_SLOT(39)
	BFME_SLOT(40)
	BFME_SLOT(41)
	BFME_SLOT(42)
	BFME_SLOT(43)
	BFME_SLOT(44)
	BFME_SLOT(45)
	BFME_SLOT(46)
	BFME_SLOT(47)
	BFME_SLOT(48)
	BFME_SLOT(49)
	BFME_SLOT(50)
	BFME_SLOT(51)
	BFME_SLOT(52)
	BFME_SLOT(53)
	BFME_SLOT(54)
	BFME_SLOT(55)
	BFME_SLOT(56)
	BFME_SLOT(57)
	BFME_SLOT(58)
	BFME_SLOT(59)
	BFME_SLOT(60)
	BFME_SLOT(61)
	BFME_SLOT(62)
	BFME_SLOT(63)
	BFME_SLOT(64)
	BFME_SLOT(65)
	BFME_SLOT(66)
	BFME_SLOT(67)
	BFME_SLOT(68)
	BFME_SLOT(69)
	BFME_SLOT(70)
	BFME_SLOT(71)
	BFME_SLOT(72)
	BFME_SLOT(73)
	BFME_SLOT(74)
	BFME_SLOT(75)
	BFME_SLOT(76)
	BFME_SLOT(77)
	BFME_SLOT(78)
	BFME_SLOT(79)
	BFME_SLOT(80)
	BFME_SLOT(81)
	BFME_SLOT(82)
	BFME_SLOT(83)
	BFME_SLOT(84)
	BFME_SLOT(85)
	BFME_SLOT(86)
	BFME_SLOT(87)
	BFME_SLOT(88)
	BFME_SLOT(89)
	BFME_SLOT(90)
	BFME_SLOT(91)
	BFME_SLOT(92)
	BFME_SLOT(93)
	BFME_SLOT(94)
	BFME_SLOT(95)
	BFME_SLOT(96)
	BFME_SLOT(97)
	BFME_SLOT(98)
	BFME_SLOT(99)
	BFME_SLOT(100)
	BFME_SLOT(101)
	BFME_SLOT(102)
	BFME_SLOT(103)
	BFME_SLOT(104)
	BFME_SLOT(105)
	BFME_SLOT(106)
	BFME_SLOT(107)
	BFME_SLOT(108)
	BFME_SLOT(109)
	BFME_SLOT(110)
	BFME_SLOT(111)
	BFME_SLOT(112)
	BFME_SLOT(113)
	BFME_SLOT(114)
	BFME_SLOT(115)
	BFME_SLOT(116)
	BFME_SLOT(117)
	BFME_SLOT(118)
	BFME_SLOT(119)
	BFME_SLOT(120)
	BFME_SLOT(121)
	BFME_SLOT(122)
	BFME_SLOT(123)
	BFME_SLOT(124)
	BFME_SLOT(125)
	BFME_SLOT(126)
	BFME_SLOT(127)
	BFME_SLOT(128)
	BFME_SLOT(129)
	BFME_SLOT(130)
	BFME_SLOT(131)
	BFME_SLOT(132)
	BFME_SLOT(133)
	BFME_SLOT(134)
	virtual void pitchCamera(Real finalPitch, Int milliseconds, Real easeIn, Real easeOut);

private:
	char m_padding0000[0x68];
	Real m_cameraPitch;
	char m_padding0070[0x22C - 0x70];
	Int m_pcNumFrames;
	Int m_pcCurFrame;
	Real m_pcAngle;
	Real m_pcFinalPitch;
	Real m_pcStartPitch;
	Real m_pcEndPitch;
	char m_padding0244[0x24C - 0x244];
	BfmeThingBRD m_pcEase;
	Bool m_doingPitchCamera;
};

void W3DView::pitchCamera(Real finalPitch, Int milliseconds, Real easeIn, Real easeOut)
{
	Int &duration = milliseconds;
	register W3DView *view = this;
	view->m_doingPitchCamera = true;
	if (duration < 1) {
		duration = 1;
	}
	Int frames = duration / TheAnimationMsPerStep;
	if (frames < 1) {
		frames = 1;
	}
	view->m_pcStartPitch = *reinterpret_cast<volatile Real *>(&view->m_cameraPitch) * BfmeKTHE;
	view->m_pcNumFrames = frames;
	view->m_pcCurFrame = 0;
	view->m_pcEndPitch = view->bfmeSlot134(finalPitch);
	view->m_pcAngle = view->bfmeSlot133(view->m_cameraPitch);
	view->m_pcFinalPitch = finalPitch;
	typedef void (BfmeThingBRD::*SetEase)(Real, Real, Real);
	SetEase setEase = reinterpret_cast<SetEase>(&BfmeThingBRD::bfmeDoBRD);
	(view->m_pcEase.*setEase)(easeIn, easeOut, (Real)duration);
	if (duration == 1) {
		((Gen0073C890Owner *)view)->updateOneFrame();
	}
}

#undef BFME_SLOT
#undef BfmeKTHE
