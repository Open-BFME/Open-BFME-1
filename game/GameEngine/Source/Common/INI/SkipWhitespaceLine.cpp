// cl: /DNDEBUG /MD /EHsc
#include <ctype.h>

class LineScanner
{
public:
	const char *skipWhitespace(const char *s);

private:
	void *m_unused0;
	void *m_unused4;
	const char *m_lineStart;
	int m_lineNumber;
};

// @?skipWhitespace@LineScanner@@QAEPBDPBD@Z 0x0035E760
const char *LineScanner::skipWhitespace(const char *s)
{
	char ch = *s;
	if (ch)
	{
		do
		{
			if (!isspace(ch))
				break;
			if (*s == '\n')
			{
				m_lineStart = s + 1;
				++m_lineNumber;
			}
			ch = *++s;
		} while (ch);
	}
	return s;
}
