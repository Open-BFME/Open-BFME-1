// cl: /DNDEBUG /MD /EHsc

typedef int Int;

class AsciiString
{
public:
	AsciiString(const AsciiString &other);

private:
	char *m_text;
};

class Overridable
{
public:
	Overridable() : m_nextOverride(0), m_isOverride(false) {}
	virtual ~Overridable();

private:
	Overridable *m_nextOverride;
	bool m_isOverride;
};

class CommandButton;

class CommandSet : public Overridable
{
public:
	CommandSet(const AsciiString &name);
	virtual ~CommandSet();

private:
	AsciiString m_name;
	const CommandButton *m_command[20];
	CommandSet *m_next;
};

CommandSet::CommandSet(const AsciiString &name) :
	m_name(name),
	m_next(0)
{
	for (Int i = 0; i < 20; ++i)
		m_command[i] = 0;
}
