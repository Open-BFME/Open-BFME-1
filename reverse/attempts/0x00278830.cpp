// ?bfmeLinkedMoveQuery@AIUpdateInterface@@QBE_NXZ
// partial score=0.85 date=2026-09-02
// cl: /DNDEBUG /MD
//
// Retail 0x00278830: walk Object+0x214 while not isKindOf(0x6c), then
// flag at AI+0x324, isIdle at vtable +0x180, locomotor-goal at +0x1d8.

typedef bool Bool;

enum KindOfType
{
	KINDOF_BFME_6C = 0x6C
};

class Thing
{
public:
	Bool isKindOf(KindOfType t) const;
};

#define BFME_AI_SLOT(n) virtual void unusedSlot##n();
class AIUpdateInterface;

class Object : public Thing
{
public:
	unsigned char m_unmodelled_00[0x204];
	AIUpdateInterface *m_ai;
	unsigned char m_unmodelled_208[0x214 - 0x208];
	Object *m_linked;
};

class AIUpdateInterface
{
public:
	BFME_AI_SLOT(0) BFME_AI_SLOT(1) BFME_AI_SLOT(2) BFME_AI_SLOT(3)
	BFME_AI_SLOT(4) BFME_AI_SLOT(5) BFME_AI_SLOT(6) BFME_AI_SLOT(7)
	BFME_AI_SLOT(8) BFME_AI_SLOT(9) BFME_AI_SLOT(10) BFME_AI_SLOT(11)
	BFME_AI_SLOT(12) BFME_AI_SLOT(13) BFME_AI_SLOT(14) BFME_AI_SLOT(15)
	BFME_AI_SLOT(16) BFME_AI_SLOT(17) BFME_AI_SLOT(18) BFME_AI_SLOT(19)
	BFME_AI_SLOT(20) BFME_AI_SLOT(21) BFME_AI_SLOT(22) BFME_AI_SLOT(23)
	BFME_AI_SLOT(24) BFME_AI_SLOT(25) BFME_AI_SLOT(26) BFME_AI_SLOT(27)
	BFME_AI_SLOT(28) BFME_AI_SLOT(29) BFME_AI_SLOT(30) BFME_AI_SLOT(31)
	BFME_AI_SLOT(32) BFME_AI_SLOT(33) BFME_AI_SLOT(34) BFME_AI_SLOT(35)
	BFME_AI_SLOT(36) BFME_AI_SLOT(37) BFME_AI_SLOT(38) BFME_AI_SLOT(39)
	BFME_AI_SLOT(40) BFME_AI_SLOT(41) BFME_AI_SLOT(42) BFME_AI_SLOT(43)
	BFME_AI_SLOT(44) BFME_AI_SLOT(45) BFME_AI_SLOT(46) BFME_AI_SLOT(47)
	BFME_AI_SLOT(48) BFME_AI_SLOT(49) BFME_AI_SLOT(50) BFME_AI_SLOT(51)
	BFME_AI_SLOT(52) BFME_AI_SLOT(53) BFME_AI_SLOT(54) BFME_AI_SLOT(55)
	BFME_AI_SLOT(56) BFME_AI_SLOT(57) BFME_AI_SLOT(58) BFME_AI_SLOT(59)
	BFME_AI_SLOT(60) BFME_AI_SLOT(61) BFME_AI_SLOT(62) BFME_AI_SLOT(63)
	BFME_AI_SLOT(64) BFME_AI_SLOT(65) BFME_AI_SLOT(66) BFME_AI_SLOT(67)
	BFME_AI_SLOT(68) BFME_AI_SLOT(69) BFME_AI_SLOT(70) BFME_AI_SLOT(71)
	BFME_AI_SLOT(72) BFME_AI_SLOT(73) BFME_AI_SLOT(74) BFME_AI_SLOT(75)
	BFME_AI_SLOT(76) BFME_AI_SLOT(77) BFME_AI_SLOT(78) BFME_AI_SLOT(79)
	BFME_AI_SLOT(80) BFME_AI_SLOT(81) BFME_AI_SLOT(82) BFME_AI_SLOT(83)
	BFME_AI_SLOT(84) BFME_AI_SLOT(85) BFME_AI_SLOT(86) BFME_AI_SLOT(87)
	BFME_AI_SLOT(88) BFME_AI_SLOT(89) BFME_AI_SLOT(90) BFME_AI_SLOT(91)
	BFME_AI_SLOT(92) BFME_AI_SLOT(93) BFME_AI_SLOT(94) BFME_AI_SLOT(95)
	virtual Bool isIdle() const;

	Bool bfmeLinkedMoveQuery() const;

private:
	unsigned char m_unmodelled_04[4];
	Object *m_object;
	unsigned char m_unmodelled_0C[0x1D8 - 0x0C];
	int m_locomotorGoalType;
	unsigned char m_unmodelled_1DC[0x324 - 0x1DC];
	unsigned char m_flag324;
};

Bool AIUpdateInterface::bfmeLinkedMoveQuery() const
{
	AIUpdateInterface *next;
	AIUpdateInterface *ai = (AIUpdateInterface *)this;
	Object *linked = ai->m_object->m_linked;
	if (linked)
	{
		do
		{
			next = linked->m_ai;
			if (!next)
				break;
			if (linked->isKindOf(KINDOF_BFME_6C))
				break;
			ai = next;
			linked = ai->m_object->m_linked;
		} while (linked);
	}

	if (ai->m_flag324)
		return true;
	if (ai->isIdle())
		return false;
	return ai->m_locomotorGoalType != 0;
}
