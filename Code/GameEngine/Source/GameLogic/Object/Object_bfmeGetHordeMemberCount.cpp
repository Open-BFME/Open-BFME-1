// cl: /DNDEBUG /MD /EHsc

typedef int Int;
typedef bool Bool;

#define SLOT(N) virtual Int slot##N() = 0

class HordeContainInterface
{
public:
	SLOT(00); SLOT(01); SLOT(02); SLOT(03); SLOT(04); SLOT(05); SLOT(06); SLOT(07);
	SLOT(08); SLOT(09); SLOT(10); SLOT(11); SLOT(12); SLOT(13); SLOT(14); SLOT(15);
	SLOT(16); SLOT(17); SLOT(18); SLOT(19); SLOT(20); SLOT(21); SLOT(22); SLOT(23);
	SLOT(24); SLOT(25); SLOT(26); SLOT(27); SLOT(28); SLOT(29); SLOT(30); SLOT(31);
	SLOT(32); SLOT(33); SLOT(34); SLOT(35); SLOT(36); SLOT(37); SLOT(38); SLOT(39);
	SLOT(40); SLOT(41); SLOT(42); SLOT(43); SLOT(44); SLOT(45); SLOT(46); SLOT(47);
	SLOT(48); SLOT(49); SLOT(50); SLOT(51); SLOT(52); SLOT(53); SLOT(54); SLOT(55);
	SLOT(56); SLOT(57); SLOT(58); SLOT(59); SLOT(60); SLOT(61); SLOT(62); SLOT(63);
	SLOT(64); SLOT(65); SLOT(66); SLOT(67); SLOT(68); SLOT(69); SLOT(70); SLOT(71);
	SLOT(72); SLOT(73); SLOT(74); SLOT(75); SLOT(76); SLOT(77); SLOT(78); SLOT(79);
	SLOT(80); SLOT(81); SLOT(82); SLOT(83);
	virtual Int getHordeMemberCount(Bool countRiders) const = 0; // +0x150
};

class ContainModuleInterface
{
public:
	SLOT(00); SLOT(01); SLOT(02); SLOT(03); SLOT(04); SLOT(05); SLOT(06); SLOT(07);
	SLOT(08); SLOT(09); SLOT(10); SLOT(11); SLOT(12); SLOT(13); SLOT(14); SLOT(15);
	SLOT(16); SLOT(17); SLOT(18); SLOT(19); SLOT(20); SLOT(21); SLOT(22); SLOT(23);
	SLOT(24); SLOT(25);
	virtual HordeContainInterface *getHordeContainInterface() = 0; // +0x68
};

#undef SLOT

class Object
{
public:
	Int bfmeGetHordeMemberCount() const;

private:
	unsigned char m_bfmePrefix[0x1fc];
	ContainModuleInterface *m_contain;
};

// The retail method and interface spellings are unrecovered.  The bytes prove
// both virtual slots, the false argument, and standalone objects counting as 1.
Int Object::bfmeGetHordeMemberCount() const
{
	ContainModuleInterface *contain = m_contain;
	if (contain != 0)
	{
		HordeContainInterface *horde = contain->getHordeContainInterface();
		if (horde != 0)
			return horde->getHordeMemberCount(false);
	}

	return 1;
}
