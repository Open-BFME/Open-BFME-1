// cl: /O2 /Ob0

class Player;
class Object
{
public:
	Player *getControllingPlayer() const;
};

class Player
{
public:
	char m_lead[0x2C];
	int m_type;
};

class HoldRva002C84E0
{
public:
	char m_lead[0x7C];
	float m_value;
};

class Rva002C84E0
{
public:
	float get() const;
};

float Rva002C84E0::get() const
{
	if ((*(Object *const *)((const char *)this - 0x33C))->getControllingPlayer()->m_type == 1)
		return (*(HoldRva002C84E0 *const *)((const char *)this - 0x340))->m_value
			+ (*(HoldRva002C84E0 *const *)((const char *)this - 0x340))->m_value;
	return (*(HoldRva002C84E0 *const *)((const char *)this - 0x340))->m_value;
}
