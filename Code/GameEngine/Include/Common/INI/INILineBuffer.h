#pragma once

#include <vector>

typedef int Int;

struct INILine
{
	const char *m_text;
	Int m_unknown4;
};

class INILineBuffer
{
public:
	~INILineBuffer();
	const char *getText( Int index ) const;
	void clear( void );

private:
	void *m_unknown0;
	char *m_buffer;
	std::vector<INILine> m_lines;
};
