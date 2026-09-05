// cl: /DNDEBUG /MD /EHsc

class MemoryPoolObject
{
public:
	virtual void memoryPoolAnchor();
};

class AsciiString
{
public:
	~AsciiString();

private:
	void *m_data;
};

class GameFont : public MemoryPoolObject
{
protected:
	virtual ~GameFont();

private:
	GameFont *m_next;
	AsciiString m_nameString;
};

GameFont::~GameFont()
{
}
