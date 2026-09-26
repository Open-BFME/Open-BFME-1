// cl: /DNDEBUG /MD /EHs-c-
// BFME W3DView::reset, retail 0x0073AC90 (152 bytes).
//
// BFME identity is established by the constructor at 0x00745B10: it installs
// primary vftable 0x011217A0, whose slot +0x14 is ILT 0x00014A38 to this body,
// slot +0xC4 is the matched resetCamera body, and slot +0x12C is the matched
// setZoom body.  That constructor also initializes +0x23F8, +0x240C, +0x2448,
// and +0x24B8.  The shipped Generals/GeneralsMD source supplies the operation
// sequence; the BFME constructor/vftable and matched methods prove its owner.

typedef float Real;
typedef int Int;
typedef bool Bool;

struct Coord2D
{
	Real x;
	Real y;
};

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

// Retail 0x00459F00 clears the height-state object embedded at W3DView+0x2448.
// Its complete vector/count/scale/flag shape is retained here so the call is
// made on a real data-bearing ABI view.
class Gen_00459F00
{
public:
	void bfmeReset();

private:
	int *m_start;
	int *m_finish;
	int *m_end;
	int m_count;
	int m_index;
	Real m_scale;
	int m_state;
	Bool m_ready;
};

// W3DView's +0x24B8 object is the same camera-limit/auxiliary object reached
// by the matched setZoom/resetCamera bodies.  Its direct initializer is the
// already-landed Rva006DF250::initialize body.  The constructor writes the
// object's vptr before reset, and initialize proves the complete data layout:
// vptr, four bytes at +4, words at +8/+C/+10/+14, a byte at +18, three bytes
// at +19, then words at +1C/+20/+24/+28 (sizeof 0x2C).  The intervening
// virtual slots remain ABI positions.
class Rva006DF250
{
public:
	virtual Real minimum();
	virtual Real maximum();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void resetState();
	void initialize();

private:
	unsigned char m_unmodelled_004[4];
	unsigned m_word08;
	unsigned m_word0C;
	unsigned m_word10;
	unsigned m_word14;
	unsigned char m_byte18;
	unsigned char m_unmodelled_019[3];
	unsigned m_word1C;
	unsigned m_word20;
	unsigned m_word24;
	unsigned m_word28;
};

#define BFME_W3D_SLOT(n) virtual void slot##n() = 0;

class W3DView
{
public:
	// BFME owner slots used by the retail reset body.
	BFME_W3D_SLOT(0)  BFME_W3D_SLOT(1)  BFME_W3D_SLOT(2)
	BFME_W3D_SLOT(3)  BFME_W3D_SLOT(4)  virtual void reset();
	BFME_W3D_SLOT(6)  BFME_W3D_SLOT(7)  BFME_W3D_SLOT(8)
	BFME_W3D_SLOT(9)  BFME_W3D_SLOT(10) BFME_W3D_SLOT(11)
	BFME_W3D_SLOT(12) BFME_W3D_SLOT(13) BFME_W3D_SLOT(14)
	BFME_W3D_SLOT(15) BFME_W3D_SLOT(16) BFME_W3D_SLOT(17)
	BFME_W3D_SLOT(18) BFME_W3D_SLOT(19) BFME_W3D_SLOT(20)
	BFME_W3D_SLOT(21) BFME_W3D_SLOT(22) BFME_W3D_SLOT(23)
	BFME_W3D_SLOT(24) BFME_W3D_SLOT(25) BFME_W3D_SLOT(26)
	BFME_W3D_SLOT(27) BFME_W3D_SLOT(28) BFME_W3D_SLOT(29)
	BFME_W3D_SLOT(30) BFME_W3D_SLOT(31) BFME_W3D_SLOT(32)
	BFME_W3D_SLOT(33) BFME_W3D_SLOT(34) BFME_W3D_SLOT(35)
	BFME_W3D_SLOT(36) BFME_W3D_SLOT(37) BFME_W3D_SLOT(38)
	BFME_W3D_SLOT(39) BFME_W3D_SLOT(40) BFME_W3D_SLOT(41)
	BFME_W3D_SLOT(42) BFME_W3D_SLOT(43) BFME_W3D_SLOT(44)
	BFME_W3D_SLOT(45)
	virtual void setViewFilter(Int filter) = 0; // slot 46, +0xB8
	BFME_W3D_SLOT(47) BFME_W3D_SLOT(48)
	virtual void resetCamera(const Coord3D *location, Int milliseconds,
		Real easeIn, Real easeOut) = 0; // slot 49, +0xC4
	BFME_W3D_SLOT(50) BFME_W3D_SLOT(51) BFME_W3D_SLOT(52)
	BFME_W3D_SLOT(53) BFME_W3D_SLOT(54)
	virtual void setTimeMultiplier(Int multiple) = 0; // slot 55, +0xDC
	BFME_W3D_SLOT(56) BFME_W3D_SLOT(57) BFME_W3D_SLOT(58)
	BFME_W3D_SLOT(59) BFME_W3D_SLOT(60) BFME_W3D_SLOT(61)
	BFME_W3D_SLOT(62) BFME_W3D_SLOT(63) BFME_W3D_SLOT(64)
	BFME_W3D_SLOT(65) BFME_W3D_SLOT(66) BFME_W3D_SLOT(67)
	BFME_W3D_SLOT(68) BFME_W3D_SLOT(69) BFME_W3D_SLOT(70)
	BFME_W3D_SLOT(71) BFME_W3D_SLOT(72) BFME_W3D_SLOT(73)
	BFME_W3D_SLOT(74) BFME_W3D_SLOT(75) BFME_W3D_SLOT(76)
	BFME_W3D_SLOT(77) BFME_W3D_SLOT(78) BFME_W3D_SLOT(79)
	BFME_W3D_SLOT(80) BFME_W3D_SLOT(81) BFME_W3D_SLOT(82)
	BFME_W3D_SLOT(83) BFME_W3D_SLOT(84) BFME_W3D_SLOT(85)
	BFME_W3D_SLOT(86) BFME_W3D_SLOT(87) BFME_W3D_SLOT(88)
	BFME_W3D_SLOT(89) BFME_W3D_SLOT(90) BFME_W3D_SLOT(91)
	BFME_W3D_SLOT(92) BFME_W3D_SLOT(93) BFME_W3D_SLOT(94)
	BFME_W3D_SLOT(95) BFME_W3D_SLOT(96) BFME_W3D_SLOT(97)
	BFME_W3D_SLOT(98) BFME_W3D_SLOT(99) BFME_W3D_SLOT(100)
	BFME_W3D_SLOT(101) BFME_W3D_SLOT(102) BFME_W3D_SLOT(103)
	BFME_W3D_SLOT(104) BFME_W3D_SLOT(105) BFME_W3D_SLOT(106)
	BFME_W3D_SLOT(107) BFME_W3D_SLOT(108) BFME_W3D_SLOT(109)
	virtual void setGuardBandBias(const Coord2D *gb) = 0; // slot 110, +0x1B8

	// 0x0045CB70 calls two EBF helpers and clears this object's +0x74 flag.
	// The BFME constructor proves this is the W3DView owner, but it does not
	// prove that EBF is a distinct base subobject.  Keep the call as a direct
	// neutral member and pin its body, rather than inventing an inheritance cast.
	void bfmeGoEBF();

private:
	char m_body0004[0x138 - 4];
	int m_field138;
	char m_body013C[0x23F8 - 0x13C];
	Real m_groundLevel;
	char m_body23FC[0x240C - 0x23FC];
	Bool m_cameraHasMovedSinceRequest;
	char m_body240D[0x2448 - 0x240D];
	Gen_00459F00 m_heightState; // +0x2448
	char m_gap2468[0x24AC - 0x2468];
	int m_field24AC; // reset to zero before setTimeMultiplier
	char m_gap24B0[4];
	int m_field24B4;
	Rva006DF250 m_zoomLimits; // +0x24B8
};

#undef BFME_W3D_SLOT

// ?reset@W3DView@@UAEXXZ
void W3DView::reset()
{
	bfmeGoEBF();
	m_field24AC = 0;
	setTimeMultiplier(1);
	m_zoomLimits.resetState();
	resetCamera(0, 0, 0.0f, 0.0f);
	setViewFilter(9);
	Coord2D gb = { 0, 0 };
	setGuardBandBias(&gb);
	m_field24B4 = 0;
	m_field138 = 0;
	m_groundLevel = 10.0f;
	m_heightState.bfmeReset();
	m_cameraHasMovedSinceRequest = false;
	m_zoomLimits.initialize();
}
