// cl: /DNDEBUG /MD /EHsc

class MemoryPoolObject
{
public:
	virtual void memoryPoolAnchor();
};

class AsciiString
{
public:
	AsciiString() : m_data(0) {}

private:
	void *m_data;
};

class GameFont : public MemoryPoolObject
{
public:
	GameFont();

protected:
	virtual ~GameFont();

private:
	GameFont *m_next;
	AsciiString m_nameString;
};

GameFont::GameFont()
{
}
