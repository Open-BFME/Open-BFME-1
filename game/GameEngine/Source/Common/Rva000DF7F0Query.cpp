// cl: /O2 /Ob0

class Rva000DF7F0Player
{
public:
	bool active() const;
};

class Rva000DF7F0
{
	char m_pad[0x0C];
	Rva000DF7F0Player *m_player;

public:
	int inactive() const;
};

int Rva000DF7F0::inactive() const
{
	return !m_player->active();
}
