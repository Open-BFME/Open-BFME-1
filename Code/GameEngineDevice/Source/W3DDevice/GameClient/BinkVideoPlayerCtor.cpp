// cl: /DNDEBUG /MD /EHsc

class BfmeBinkPlayerMember
{
public:
	BfmeBinkPlayerMember();
	~BfmeBinkPlayerMember();

private:
	unsigned int m_value;
};

class BfmeBinkOwnedPointers
{
public:
	BfmeBinkOwnedPointers() : m_surface(0) { }
	~BfmeBinkOwnedPointers();

private:
	void *m_surface;
};

class BinkVideoPlayer
{
public:
	BinkVideoPlayer();

private:
	void *m_player;
	BfmeBinkOwnedPointers m_ownedPointers;
	unsigned int m_state;
	BfmeBinkPlayerMember m_member;
	bool m_flag10;
	bool m_flag11;
	bool m_flag12;
	bool m_flag13;
	bool m_flag14;
};

// ??0BinkVideoPlayer@@QAE@XZ
BinkVideoPlayer::BinkVideoPlayer() :
	m_player(0),
	m_ownedPointers(),
	m_state(1),
	m_member(),
	m_flag10(false),
	m_flag11(false),
	m_flag12(false),
	m_flag13(false),
	m_flag14(false)
{
}
