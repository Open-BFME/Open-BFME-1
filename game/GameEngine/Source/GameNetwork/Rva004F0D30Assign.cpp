// cl: /O2 /Ob0

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/GameInfo.h
class GameSlot
{
public:
	GameSlot &operator=(const GameSlot &other);

private:
	char m_pad[0x44];
};

// callees.py 0x4F0D30: the five string-member assignments call 0x00887C90,
// the ledger row set@?$StringBase@D@@QAEXABV1@@Z.
template <class T> class StringBase
{
public:
	void set(const StringBase<T> &other);

private:
	void *m_data;
};

class Rva004F0D30 : public GameSlot
{
	int m_44;
	StringBase<char> m_48;
	StringBase<char> m_4C;
	StringBase<char> m_50;
	int m_54;
	int m_58;
	int m_5C;
	int m_60;
	int m_64;
	int m_68;
	int m_6C;
	StringBase<char> m_70;
	StringBase<char> m_74;

public:
	Rva004F0D30 &operator=(const Rva004F0D30 &other);
};

Rva004F0D30 &Rva004F0D30::operator=(const Rva004F0D30 &other)
{
	GameSlot::operator=(other);
	m_44 = other.m_44;
	m_48.set(other.m_48);
	m_4C.set(other.m_4C);
	m_50.set(other.m_50);
	m_54 = other.m_54;
	m_58 = other.m_58;
	m_5C = other.m_5C;
	m_60 = other.m_60;
	m_64 = other.m_64;
	m_68 = other.m_68;
	m_6C = other.m_6C;
	m_70.set(other.m_70);
	m_74.set(other.m_74);
	return *this;
}
