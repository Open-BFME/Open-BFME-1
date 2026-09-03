// cl: /O2 /Ob0

class Player;
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	Player *getControllingPlayer() const;
};

struct Rva2225E0Filter
{
	bool accepts(Object *value, Player *player);
};

struct HoldRva002CDBF0
{
	char m_lead[0x10];
	Rva2225E0Filter m_filter;
};

class Rva002CDBF0
{
public:
	bool check(Object *value);

	char m_pad[0x69];
	unsigned char m_flag;
};

bool Rva002CDBF0::check(Object *value)
{
	Object *ctx = *(Object **)((char *)this - 0x18);
	HoldRva002CDBF0 *hold = *(HoldRva002CDBF0 **)((char *)this - 0x1C);
	if (hold->m_filter.accepts(value, ctx->getControllingPlayer()) && !m_flag)
		return true;
	return false;
}
