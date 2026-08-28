// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: Object conditional current-victim query, retail 0x001BE070,
// 46 bytes. BFME stores the AIUpdateInterface pointer at Object +0x204. Its
// isIdle virtual is independently established at slot 96 (+0x180), and the
// recovered source declares isAttacking immediately after it, identifying the
// slot used here at +0x184. When that query succeeds, this wrapper tail-calls
// AIUpdateInterface::getCurrentVictim through its pinned ILT thunk.
//
// No named caller or surviving reference exposes this Object wrapper's retail
// spelling. The bfme-prefixed name is deliberately descriptive. This no-arg
// thiscall body also cannot prove cv-qualification; const records its observed
// query-only behavior.

typedef int Int;
typedef bool Bool;

class Object;

class AIUpdateInterface
{
public:
	// Only the slot count is asserted for the declarations before isAttacking.
	// Their placeholder names and signatures are intentionally nonsemantic.
#define BFME_SLOT(n) virtual Int bfmeSlot##n() = 0
	BFME_SLOT(00); BFME_SLOT(01); BFME_SLOT(02); BFME_SLOT(03);
	BFME_SLOT(04); BFME_SLOT(05); BFME_SLOT(06); BFME_SLOT(07);
	BFME_SLOT(08); BFME_SLOT(09); BFME_SLOT(10); BFME_SLOT(11);
	BFME_SLOT(12); BFME_SLOT(13); BFME_SLOT(14); BFME_SLOT(15);
	BFME_SLOT(16); BFME_SLOT(17); BFME_SLOT(18); BFME_SLOT(19);
	BFME_SLOT(20); BFME_SLOT(21); BFME_SLOT(22); BFME_SLOT(23);
	BFME_SLOT(24); BFME_SLOT(25); BFME_SLOT(26); BFME_SLOT(27);
	BFME_SLOT(28); BFME_SLOT(29); BFME_SLOT(30); BFME_SLOT(31);
	BFME_SLOT(32); BFME_SLOT(33); BFME_SLOT(34); BFME_SLOT(35);
	BFME_SLOT(36); BFME_SLOT(37); BFME_SLOT(38); BFME_SLOT(39);
	BFME_SLOT(40); BFME_SLOT(41); BFME_SLOT(42); BFME_SLOT(43);
	BFME_SLOT(44); BFME_SLOT(45); BFME_SLOT(46); BFME_SLOT(47);
	BFME_SLOT(48); BFME_SLOT(49); BFME_SLOT(50); BFME_SLOT(51);
	BFME_SLOT(52); BFME_SLOT(53); BFME_SLOT(54); BFME_SLOT(55);
	BFME_SLOT(56); BFME_SLOT(57); BFME_SLOT(58); BFME_SLOT(59);
	BFME_SLOT(60); BFME_SLOT(61); BFME_SLOT(62); BFME_SLOT(63);
	BFME_SLOT(64); BFME_SLOT(65); BFME_SLOT(66); BFME_SLOT(67);
	BFME_SLOT(68); BFME_SLOT(69); BFME_SLOT(70); BFME_SLOT(71);
	BFME_SLOT(72); BFME_SLOT(73); BFME_SLOT(74); BFME_SLOT(75);
	BFME_SLOT(76); BFME_SLOT(77); BFME_SLOT(78); BFME_SLOT(79);
	BFME_SLOT(80); BFME_SLOT(81); BFME_SLOT(82); BFME_SLOT(83);
	BFME_SLOT(84); BFME_SLOT(85); BFME_SLOT(86); BFME_SLOT(87);
	BFME_SLOT(88); BFME_SLOT(89); BFME_SLOT(90); BFME_SLOT(91);
	BFME_SLOT(92); BFME_SLOT(93); BFME_SLOT(94); BFME_SLOT(95);
	BFME_SLOT(96);
#undef BFME_SLOT
	virtual Bool isAttacking() const = 0; // slot 97, +0x184
	Object *getCurrentVictim() const;
};

class Object
{
public:
	Object *bfmeGetCurrentVictimIfAttacking() const;

private:
	Int m_bfmeObjectPrefix[0x204 / sizeof(Int)];
	AIUpdateInterface *m_ai; // +0x204
};

// ?bfmeGetCurrentVictimIfAttacking@Object@@QBEPAV1@XZ
Object *Object::bfmeGetCurrentVictimIfAttacking() const
{
	AIUpdateInterface *ai = m_ai;
	Object *victim = 0;
	if (ai != 0 && ai->isAttacking())
		victim = m_ai->getCurrentVictim();
	return victim;
}
