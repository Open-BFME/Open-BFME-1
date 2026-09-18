// Open-BFME5: CommandSet's complete destructor.
//
// The retail body is a compiler-generated destructor for the CommandSet
// layout from ControlBar.h.  The two small ABI shims below retain the exact
// one-slot virtual override route and StringBase-owned name cleanup that the
// retail body uses, while the derived type carries the authentic class name.

class BfmeStrVUJ
{
public:
	~BfmeStrVUJ() { bfmeClearVUJ(); }
	char *m_bfme00;

private:
	void bfmeClearVUJ();
};

class BfmeSinkVUJ
{
public:
	virtual void bfmeSlot0VUJ(int flags);
};

class BfmeBaseVUJ
{
public:
	~BfmeBaseVUJ()
	{
		BfmeSinkVUJ *sink = m_bfme04;

		if (sink != 0)
			sink->bfmeSlot0VUJ(1);

		m_bfme04 = 0;
	}

	virtual void bfmeSlot0VUJ();
	BfmeSinkVUJ *m_bfme04;
	char m_bfmePad08[4];
};

class CommandSet : public BfmeBaseVUJ
{
public:
	friend void forceCommandSetCompleteDestructor();

protected:
	virtual ~CommandSet();
	BfmeStrVUJ m_bfme0c;
};

CommandSet::~CommandSet()
{
}

void forceCommandSetCompleteDestructor()
{
	CommandSet value;
}
