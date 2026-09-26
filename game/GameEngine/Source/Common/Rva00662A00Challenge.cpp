// cl: /O2 /Ob0

extern "C" char *__cdecl GetChallenge(void *);

class Rva00662A00
{
	char m_lead[0x464];
	void *m_game;

public:
	char *getChallenge();
};

char *Rva00662A00::getChallenge()
{
	return GetChallenge(m_game);
}
