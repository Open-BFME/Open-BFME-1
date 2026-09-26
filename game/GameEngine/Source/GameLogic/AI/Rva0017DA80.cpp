// cl: /DNDEBUG /MD /EHsc
// Retail 0x0017DA80: 98-byte opaque AI-state transition. The first call
// determines an early return; the holder at this+0x1c points to an object at
// +0x10. Its virtual slots 0x1f0 and 0x5c gate and perform an action before
// the known AIInternalMoveToState::onEnter thunk. The string is verified
// against retail VA 0x0109A180. No original owner name is claimed.
extern void j_00037e34();
extern void j_0000d3b9();
extern void j_0003a17a();
extern void j_00021e27();
extern bool Glo012F0239;
extern void *TheCRCParameterCheck;

class Rva0017DA80Receiver {};
template<class T> __forceinline T member(void (*f)())
{
	union { void (*raw)(); T method; } u;
	u.raw = f;
	return u.method;
}
#define CALL(T,obj,fn) (((Rva0017DA80Receiver *)(obj))->*member<T>(fn))

class Rva0017DA80Target
{
public:
#define SLOT(n) virtual void unused##n() = 0;
SLOT(0) SLOT(1) SLOT(2) SLOT(3) SLOT(4) SLOT(5) SLOT(6) SLOT(7) SLOT(8) SLOT(9)
SLOT(10) SLOT(11) SLOT(12) SLOT(13) SLOT(14) SLOT(15) SLOT(16) SLOT(17) SLOT(18) SLOT(19)
SLOT(20) SLOT(21) SLOT(22) virtual void slot05c() = 0; SLOT(24) SLOT(25) SLOT(26) SLOT(27) SLOT(28) SLOT(29)
SLOT(30) SLOT(31) SLOT(32) SLOT(33) SLOT(34) SLOT(35) SLOT(36) SLOT(37) SLOT(38) SLOT(39)
SLOT(40) SLOT(41) SLOT(42) SLOT(43) SLOT(44) SLOT(45) SLOT(46) SLOT(47) SLOT(48) SLOT(49)
SLOT(50) SLOT(51) SLOT(52) SLOT(53) SLOT(54) SLOT(55) SLOT(56) SLOT(57) SLOT(58) SLOT(59)
SLOT(60) SLOT(61) SLOT(62) SLOT(63) SLOT(64) SLOT(65) SLOT(66) SLOT(67) SLOT(68) SLOT(69)
SLOT(70) SLOT(71) SLOT(72) SLOT(73) SLOT(74) SLOT(75) SLOT(76) SLOT(77) SLOT(78) SLOT(79)
SLOT(80) SLOT(81) SLOT(82) SLOT(83) SLOT(84) SLOT(85) SLOT(86) SLOT(87) SLOT(88) SLOT(89)
SLOT(90) SLOT(91) SLOT(92) SLOT(93) SLOT(94) SLOT(95) SLOT(96) SLOT(97) SLOT(98) SLOT(99)
SLOT(100) SLOT(101) SLOT(102) SLOT(103) SLOT(104) SLOT(105) SLOT(106) SLOT(107) SLOT(108) SLOT(109)
SLOT(110) SLOT(111) SLOT(112) SLOT(113) SLOT(114) SLOT(115) SLOT(116) SLOT(117) SLOT(118) SLOT(119)
SLOT(120) SLOT(121) SLOT(122) SLOT(123) virtual bool slot1f0() = 0;
#undef SLOT
};
class Rva0017DA80Machine
{
public:
	char pad[0x10];
	void *m_10;
};

typedef int (Rva0017DA80Receiver::*Check)();
typedef Rva0017DA80Target *(Rva0017DA80Receiver::*GetTarget)();
typedef int (Rva0017DA80Receiver::*Enter)();

class Rva0017DA80
{
public:
	virtual void slot0() = 0;
	int m();
	char pad[0x18];
	Rva0017DA80Machine *m_1c;
	char gap[0x2c];
	bool m_4c;
};

int Rva0017DA80::m()
{
	int code = CALL(Check, this, j_00037e34)();
	if (code)
		return code;

	Rva0017DA80Target *target = CALL(GetTarget, m_1c->m_10, j_0000d3b9)();
	if (target && target->slot1f0())
		target->slot05c();

	if (Glo012F0239 && TheCRCParameterCheck)
		((void (__cdecl *)(void *, const char *))j_0003a17a)(
			TheCRCParameterCheck,
			"CritterDesync: setAdjustDestination(FALSE) 58");

	m_4c = false;
	return CALL(Enter, this, j_00021e27)();
}
