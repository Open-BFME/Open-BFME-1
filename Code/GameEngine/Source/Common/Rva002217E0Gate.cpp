// cl: /DNDEBUG /MD /EHsc
// Open-BFME6: 0x002217E0. Null-check the object, compare a deep virtual at
// +0x1C4 against this-0x1C, then two interface virtuals and a flag at
// this-0x20+0x151.

class Object;

class BfmeDeepE0
{
public:
#define SLOT(n) virtual void slot##n() = 0;
	SLOT(00) SLOT(01) SLOT(02) SLOT(03) SLOT(04) SLOT(05) SLOT(06) SLOT(07)
	SLOT(08) SLOT(09) SLOT(10) SLOT(11) SLOT(12) SLOT(13) SLOT(14) SLOT(15)
	SLOT(16) SLOT(17) SLOT(18) SLOT(19) SLOT(20) SLOT(21) SLOT(22) SLOT(23)
	SLOT(24) SLOT(25) SLOT(26) SLOT(27) SLOT(28) SLOT(29) SLOT(30) SLOT(31)
	SLOT(32) SLOT(33) SLOT(34) SLOT(35) SLOT(36) SLOT(37) SLOT(38) SLOT(39)
	SLOT(40) SLOT(41) SLOT(42) SLOT(43) SLOT(44) SLOT(45) SLOT(46) SLOT(47)
	SLOT(48) SLOT(49) SLOT(50) SLOT(51) SLOT(52) SLOT(53) SLOT(54) SLOT(55)
	SLOT(56) SLOT(57) SLOT(58) SLOT(59) SLOT(60) SLOT(61) SLOT(62) SLOT(63)
	SLOT(64) SLOT(65) SLOT(66) SLOT(67) SLOT(68) SLOT(69) SLOT(70) SLOT(71)
	SLOT(72) SLOT(73) SLOT(74) SLOT(75) SLOT(76) SLOT(77) SLOT(78) SLOT(79)
	SLOT(80) SLOT(81) SLOT(82) SLOT(83) SLOT(84) SLOT(85) SLOT(86) SLOT(87)
	SLOT(88) SLOT(89) SLOT(90) SLOT(91) SLOT(92) SLOT(93) SLOT(94) SLOT(95)
	SLOT(96) SLOT(97) SLOT(98) SLOT(99) SLOT(100) SLOT(101) SLOT(102) SLOT(103)
	SLOT(104) SLOT(105) SLOT(106) SLOT(107) SLOT(108) SLOT(109) SLOT(110) SLOT(111)
	SLOT(112)
#undef SLOT
	virtual void *virt1C4() = 0;
};

class BfmeIface48
{
public:
	virtual void s00() = 0;
	virtual void s01() = 0;
	virtual void s02() = 0;
	virtual void s03() = 0;
	virtual void s04() = 0;
	virtual void s05() = 0;
	virtual void s06() = 0;
	virtual void s07() = 0;
	virtual void s08() = 0;
	virtual void s09() = 0;
	virtual void s10() = 0;
	virtual void s11() = 0;
	virtual void s12() = 0;
	virtual void s13() = 0;
	virtual void s14() = 0;
	virtual void s15() = 0;
	virtual void s16() = 0;
	virtual void s17() = 0;
	virtual bool virt48(Object *obj) = 0;
};

class BfmeIface84
{
public:
#define SLOT(n) virtual void slot##n() = 0;
	SLOT(00) SLOT(01) SLOT(02) SLOT(03) SLOT(04) SLOT(05) SLOT(06) SLOT(07)
	SLOT(08) SLOT(09) SLOT(10) SLOT(11) SLOT(12) SLOT(13) SLOT(14) SLOT(15)
	SLOT(16) SLOT(17) SLOT(18) SLOT(19) SLOT(20) SLOT(21) SLOT(22) SLOT(23)
	SLOT(24) SLOT(25) SLOT(26) SLOT(27) SLOT(28) SLOT(29) SLOT(30) SLOT(31)
	SLOT(32)
#undef SLOT
	virtual bool virt84(Object *obj, int flag) = 0;
	virtual void virt88(Object *obj) = 0;
};

class Object
{
public:
	char m_pad[0x204];
	BfmeDeepE0 *m_deep;
	char m_mid[0x214 - 0x208];
	void *m_other;
};

class BfmeFlagE0
{
public:
	char m_pad[0x151];
	unsigned char m_flag;
};

class Gen_002217E0
{
public:
	void bfmeGate(Object *obj, void *a, void *b);
};

// ?bfmeGate@Gen_002217E0@@QAEXPAVObject@@PAX1@Z
void Gen_002217E0::bfmeGate(Object *obj, void *a, void *b)
{
	Gen_002217E0 *self = this;
	Object *o = obj;
	if (o == 0)
		return;
	BfmeDeepE0 *deep = o->m_deep;
	if (deep == 0)
		return;
	void *key = *(void **)((char *)self - 0x1C);
	if (deep->virt1C4() != key)
		return;
	if (!((BfmeIface48 *)((char *)self - 0x24))->virt48(o))
		return;
	BfmeIface84 *iface = (BfmeIface84 *)((char *)self - 4);
	if (!iface->virt84(o, 1))
		return;
	if (o->m_other == *(void **)((char *)self - 0x1C))
		return;
	if ((*(BfmeFlagE0 **)((char *)self - 0x20))->m_flag == 0)
		return;
	iface->virt88(o);
}
