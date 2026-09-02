// cl: /DNDEBUG /MD /EHsc
// Open-BFME: DataChunkInput::registerParser, retail 0x00103840.
//
// BFME's UserParser keeps an intrusive previous-link (pointer to the previous
// node's next field) alongside its next pointer.  The extra link is why this
// body allocates 0x1c bytes and why insertion updates both the old head and
// the list head.

typedef bool Bool;

class DataChunkInput;
struct DataChunkInfo;
typedef Bool (*DataChunkParserPtr)(DataChunkInput &, DataChunkInfo *, void *);

class AsciiString
{
	void *m_data;

public:
	AsciiString(void) : m_data(0) {}
	void set(const AsciiString &stringSrc);
};

class UserParser
{
public:
	virtual void v(void);

	UserParser *next;
	UserParser **previous;
	DataChunkParserPtr parser;
	AsciiString label;
	AsciiString parentLabel;
	void *userData;
};

void UserParser::v(void)
{
}

class DataChunkInput
{
	char m_prefix[0x18];
	UserParser *m_parserList;

public:
	UserParser *registerParser(const AsciiString &label,
		const AsciiString &parentLabel,
		DataChunkParserPtr parser,
		void *userData);
};

// ?registerParser@DataChunkInput@@QAEPAVUserParser@@ABVAsciiString@@0P6A_NAAV1@PAUDataChunkInfo@@PAX@Z3@Z
UserParser *DataChunkInput::registerParser(const AsciiString &label,
	const AsciiString &parentLabel,
	DataChunkParserPtr parser,
	void *userData)
{
	UserParser *p;
	DataChunkInput *self = this;

	p = new UserParser;
	p->label.set(label);
	p->parentLabel.set(parentLabel);
	p->parser = parser;

	void *ud = userData;
	UserParser **head = &self->m_parserList;
	p->userData = ud;

	UserParser *next = *head;
	UserParser **pn = &p->next;
	*pn = next;
	if (next != 0)
		next->previous = pn;
	p->previous = head;
	*head = p;
	return p;
}
