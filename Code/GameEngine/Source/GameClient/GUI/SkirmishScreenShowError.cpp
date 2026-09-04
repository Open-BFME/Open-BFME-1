// cl: /DNDEBUG /MD /EHsc
// Retail 0x00579690: show a supplied skirmish-screen message only when the
// callback flag is set.  The title is the retail empty wide literal.

template <typename T> class StringBase
{
	friend class UnicodeString;

private:
	StringBase() : m_data(0) {}
	StringBase(const T *text);
	StringBase(const StringBase<T> &other);
	~StringBase();

	void *m_data;
};

class UnicodeString : private StringBase<unsigned short>
{
public:
	UnicodeString() : StringBase<unsigned short>() {}
	UnicodeString(const unsigned short *text) : StringBase<unsigned short>(text) {}
	UnicodeString(const UnicodeString &other) : StringBase<unsigned short>(other) {}
	~UnicodeString() {}
};

class GameWindow;
GameWindow *MessageBoxOk(UnicodeString title, UnicodeString body,
	void (*callback)(void));

class BfmeAptScreenSkirmish
{
public:
	void showError(const UnicodeString &message, int show);
};

// ?showError@BfmeAptScreenSkirmish@@QAEXABVUnicodeString@@H@Z
void BfmeAptScreenSkirmish::showError(const UnicodeString &message, int show)
{
	if(--show == 0)
		MessageBoxOk(UnicodeString((const unsigned short *)0x01088AF4),
			message, 0);
}
