// cl: /O2 /Ob0

class Player;
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	Player *getControllingPlayer() const;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Player.h
class Player
{
public:
	char m_lead[0x2C];
	int m_type;
};

class HoldRva002C6050
{
public:
	char m_lead[0x70];
	float m_value;
};

class Rva002C6050
{
public:
	float get() const;
};

float Rva002C6050::get() const
{
	if ((*(Object *const *)((const char *)this - 0x338))->getControllingPlayer()->m_type == 1)
		return (*(HoldRva002C6050 *const *)((const char *)this - 0x33C))->m_value
			+ (*(HoldRva002C6050 *const *)((const char *)this - 0x33C))->m_value;
	return (*(HoldRva002C6050 *const *)((const char *)this - 0x33C))->m_value;
}
