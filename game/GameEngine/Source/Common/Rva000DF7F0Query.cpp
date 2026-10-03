// cl: /O2 /Ob0

class Rva000DF7F0Player
{
public:
	bool active() const;
};

extern void j_000179bd();

typedef bool (__fastcall *Rva000DF7F0ActiveCall)(const Rva000DF7F0Player *);

class Rva000DF7F0
{
	char m_pad[0x0C];
	Rva000DF7F0Player *m_player;

public:
	int inactive() const;
};

int Rva000DF7F0::inactive() const
{
	return !((Rva000DF7F0ActiveCall)j_000179bd)(m_player);
}
