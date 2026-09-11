// cl: /DNDEBUG /MD /EHsc
// BFME retail RVA 0x002B5600: DeployStyleAIUpdate::aiDoCommand.
// The command interface is the secondary subobject at primary+0x20.

typedef bool Bool;
typedef int Int;

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0,
	CMD_FROM_SCRIPT = 1,
	CMD_FROM_AI = 2
};

class Rva002B5600Object
{
public:
	unsigned char m_beforeField74[0x74];
	unsigned int m_field74;
	unsigned int getID() const { return m_field74; }
};

struct Rva002B5600Coord3D
{
	Int x;
	Int y;
	Int z;
};

struct AICommandParms
{
	Int m_cmd;
	CommandSourceType m_cmdSource;
	Int m_value08;
	Int m_value0c;
	Int m_value10;
	Rva002B5600Object *m_obj;
};

class AICommandInterface
{
public:
	virtual void aiDoCommand(const AICommandParms *parms) = 0;
	void aiIdle(CommandSourceType source);
};

class AICommandParmsStorage
{
public:
	void store(const AICommandParms &parms);
	unsigned char m_payload[0xa0];
};

class AIUpdateInterface
{
public:
	virtual void aiDoCommand(const AICommandParms *parms);
};

// The guard is primary-vtable slot 0x210.  The intervening slots are the
// witnessed AIUpdateInterface command surface; the body only needs the slot
// count, while the raw fields below preserve the BFME member offsets.
class Rva002B5600DeployStylePrimary
{
#define RVA_PRIMARY_SLOT(n) virtual void primarySlot##n() = 0;
	RVA_PRIMARY_SLOT(0)
	RVA_PRIMARY_SLOT(1)
	RVA_PRIMARY_SLOT(2)
	RVA_PRIMARY_SLOT(3)
	RVA_PRIMARY_SLOT(4)
	RVA_PRIMARY_SLOT(5)
	RVA_PRIMARY_SLOT(6)
	RVA_PRIMARY_SLOT(7)
	RVA_PRIMARY_SLOT(8)
	RVA_PRIMARY_SLOT(9)
	RVA_PRIMARY_SLOT(10)
	RVA_PRIMARY_SLOT(11)
	RVA_PRIMARY_SLOT(12)
	RVA_PRIMARY_SLOT(13)
	RVA_PRIMARY_SLOT(14)
	RVA_PRIMARY_SLOT(15)
	RVA_PRIMARY_SLOT(16)
	RVA_PRIMARY_SLOT(17)
	RVA_PRIMARY_SLOT(18)
	RVA_PRIMARY_SLOT(19)
	RVA_PRIMARY_SLOT(20)
	RVA_PRIMARY_SLOT(21)
	RVA_PRIMARY_SLOT(22)
	RVA_PRIMARY_SLOT(23)
	RVA_PRIMARY_SLOT(24)
	RVA_PRIMARY_SLOT(25)
	RVA_PRIMARY_SLOT(26)
	RVA_PRIMARY_SLOT(27)
	RVA_PRIMARY_SLOT(28)
	RVA_PRIMARY_SLOT(29)
	RVA_PRIMARY_SLOT(30)
	RVA_PRIMARY_SLOT(31)
	RVA_PRIMARY_SLOT(32)
	RVA_PRIMARY_SLOT(33)
	RVA_PRIMARY_SLOT(34)
	RVA_PRIMARY_SLOT(35)
	RVA_PRIMARY_SLOT(36)
	RVA_PRIMARY_SLOT(37)
	RVA_PRIMARY_SLOT(38)
	RVA_PRIMARY_SLOT(39)
	RVA_PRIMARY_SLOT(40)
	RVA_PRIMARY_SLOT(41)
	RVA_PRIMARY_SLOT(42)
	RVA_PRIMARY_SLOT(43)
	RVA_PRIMARY_SLOT(44)
	RVA_PRIMARY_SLOT(45)
	RVA_PRIMARY_SLOT(46)
	RVA_PRIMARY_SLOT(47)
	RVA_PRIMARY_SLOT(48)
	RVA_PRIMARY_SLOT(49)
	RVA_PRIMARY_SLOT(50)
	RVA_PRIMARY_SLOT(51)
	RVA_PRIMARY_SLOT(52)
	RVA_PRIMARY_SLOT(53)
	RVA_PRIMARY_SLOT(54)
	RVA_PRIMARY_SLOT(55)
	RVA_PRIMARY_SLOT(56)
	RVA_PRIMARY_SLOT(57)
	RVA_PRIMARY_SLOT(58)
	RVA_PRIMARY_SLOT(59)
	RVA_PRIMARY_SLOT(60)
	RVA_PRIMARY_SLOT(61)
	RVA_PRIMARY_SLOT(62)
	RVA_PRIMARY_SLOT(63)
	RVA_PRIMARY_SLOT(64)
	RVA_PRIMARY_SLOT(65)
	RVA_PRIMARY_SLOT(66)
	RVA_PRIMARY_SLOT(67)
	RVA_PRIMARY_SLOT(68)
	RVA_PRIMARY_SLOT(69)
	RVA_PRIMARY_SLOT(70)
	RVA_PRIMARY_SLOT(71)
	RVA_PRIMARY_SLOT(72)
	RVA_PRIMARY_SLOT(73)
	RVA_PRIMARY_SLOT(74)
	RVA_PRIMARY_SLOT(75)
	RVA_PRIMARY_SLOT(76)
	RVA_PRIMARY_SLOT(77)
	RVA_PRIMARY_SLOT(78)
	RVA_PRIMARY_SLOT(79)
	RVA_PRIMARY_SLOT(80)
	RVA_PRIMARY_SLOT(81)
	RVA_PRIMARY_SLOT(82)
	RVA_PRIMARY_SLOT(83)
	RVA_PRIMARY_SLOT(84)
	RVA_PRIMARY_SLOT(85)
	RVA_PRIMARY_SLOT(86)
	RVA_PRIMARY_SLOT(87)
	RVA_PRIMARY_SLOT(88)
	RVA_PRIMARY_SLOT(89)
	RVA_PRIMARY_SLOT(90)
	RVA_PRIMARY_SLOT(91)
	RVA_PRIMARY_SLOT(92)
	RVA_PRIMARY_SLOT(93)
	RVA_PRIMARY_SLOT(94)
	RVA_PRIMARY_SLOT(95)
	RVA_PRIMARY_SLOT(96)
	RVA_PRIMARY_SLOT(97)
	RVA_PRIMARY_SLOT(98)
	RVA_PRIMARY_SLOT(99)
	RVA_PRIMARY_SLOT(100)
	RVA_PRIMARY_SLOT(101)
	RVA_PRIMARY_SLOT(102)
	RVA_PRIMARY_SLOT(103)
	RVA_PRIMARY_SLOT(104)
	RVA_PRIMARY_SLOT(105)
	RVA_PRIMARY_SLOT(106)
	RVA_PRIMARY_SLOT(107)
	RVA_PRIMARY_SLOT(108)
	RVA_PRIMARY_SLOT(109)
	RVA_PRIMARY_SLOT(110)
	RVA_PRIMARY_SLOT(111)
	RVA_PRIMARY_SLOT(112)
	RVA_PRIMARY_SLOT(113)
	RVA_PRIMARY_SLOT(114)
	RVA_PRIMARY_SLOT(115)
	RVA_PRIMARY_SLOT(116)
	RVA_PRIMARY_SLOT(117)
	RVA_PRIMARY_SLOT(118)
	RVA_PRIMARY_SLOT(119)
	RVA_PRIMARY_SLOT(120)
	RVA_PRIMARY_SLOT(121)
	RVA_PRIMARY_SLOT(122)
	RVA_PRIMARY_SLOT(123)
	RVA_PRIMARY_SLOT(124)
	RVA_PRIMARY_SLOT(125)
	RVA_PRIMARY_SLOT(126)
	RVA_PRIMARY_SLOT(127)
	RVA_PRIMARY_SLOT(128)
	RVA_PRIMARY_SLOT(129)
	RVA_PRIMARY_SLOT(130)
	RVA_PRIMARY_SLOT(131)
#undef RVA_PRIMARY_SLOT
	public:
	virtual Bool isAllowedToRespondToAiCommands(const AICommandParms *parms) = 0;
};

class Rva002B5600DeployStyleAIUpdate
{
public:
	virtual void aiDoCommand(const AICommandParms *parms);
	unsigned char m_beforeStorage[0x320 - 4];
	AICommandParmsStorage m_storage;
	unsigned char m_field3c0;
	unsigned char m_padding3c1[3];
	Int m_field3c4;
	unsigned char m_padding3c8[4];
	Int m_field3cc;
	Int m_field3d0;
	Rva002B5600Coord3D m_position;
	unsigned char m_field3e0;
	unsigned char m_field3e1;
	unsigned char m_field3e2;
	unsigned char m_field3e3;
	unsigned char m_field3e4;
};

// ?aiDoCommand@DeployStyleAIUpdate@@UAEXPBUAICommandParms@@@Z
void Rva002B5600DeployStyleAIUpdate::aiDoCommand(const AICommandParms *parms)
{
	register const AICommandParms *command = parms;
	Rva002B5600DeployStylePrimary *primary =
		reinterpret_cast<Rva002B5600DeployStylePrimary *>(
			reinterpret_cast<char *>(this) - 0x20);

	if (!primary->isAllowedToRespondToAiCommands(command))
		return;

	if (command->m_cmd != 5 && command->m_cmd != 0x35)
		reinterpret_cast<AICommandInterface *>(this)->aiIdle(CMD_FROM_AI);

	if (command->m_cmdSource != CMD_FROM_AI)
	{
	*reinterpret_cast<Int *>(reinterpret_cast<char *>(primary) + 0x3ec) = 0;
	*reinterpret_cast<unsigned char *>(reinterpret_cast<char *>(primary) + 0x400) = 0;
	*reinterpret_cast<unsigned char *>(reinterpret_cast<char *>(primary) + 0x404) = 0;
	*reinterpret_cast<unsigned char *>(reinterpret_cast<char *>(primary) + 0x403) = 0;
	*reinterpret_cast<unsigned char *>(reinterpret_cast<char *>(primary) + 0x401) = 0;
	*reinterpret_cast<Int *>(reinterpret_cast<char *>(primary) + 0x3f0) = 0;
	*reinterpret_cast<unsigned char *>(reinterpret_cast<char *>(primary) + 0x402) = 0;
	*reinterpret_cast<Int *>(reinterpret_cast<char *>(primary) + 0x3f4) = 0;
	*reinterpret_cast<Int *>(reinterpret_cast<char *>(primary) + 0x3f8) = 0;
	*reinterpret_cast<Int *>(reinterpret_cast<char *>(primary) + 0x3fc) = 0;

	if (command->m_cmd != 5)
	{
		this->m_storage.store(*command);
		this->m_field3c0 = 1;
	}

	Int state = this->m_field3c4;
	if (state != 1 && state != 3)
		reinterpret_cast<AIUpdateInterface *>(this)->AIUpdateInterface::aiDoCommand(command);

	switch (command->m_cmd)
	{
	case 0x1e:
		this->m_position.x = command->m_value08;
		this->m_position.y = command->m_value0c;
		this->m_position.z = command->m_value10;
		this->m_field3e3 = 1;
		this->m_field3e0 = 1;
		break;

	case 0x0b:
	case 0x0c:
	case 0x39:
		this->m_field3e1 = 1;
		this->m_field3d0 = command->m_obj ? command->m_obj->getID() : 0;
		break;

	case 0x0e:
		this->m_field3e2 = 1;
		this->m_position.x = command->m_value08;
		this->m_position.y = command->m_value0c;
		this->m_position.z = command->m_value10;
		break;

	case 0x0f:
	case 0x10:
	case 0x11:
	case 0x12:
	case 0x1f:
	case 0x21:
	case 0x23:
		this->m_field3e0 = 1;
		break;

	default:
		break;
	}
	}
	else
	{
		reinterpret_cast<AIUpdateInterface *>(this)->AIUpdateInterface::aiDoCommand(command);
	}
}
