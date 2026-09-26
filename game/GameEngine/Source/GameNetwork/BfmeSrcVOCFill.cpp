// BfmeSrcVOC message fill at retail 0x00686A60.

typedef unsigned short WideChar;

extern "C" __declspec(dllimport) WideChar *__cdecl wcsncpy(
	WideChar *destination, const WideChar *source, unsigned int count );
extern "C" __declspec(dllimport) char *__cdecl strncpy(
	char *destination, const char *source, unsigned int count );

struct BfmeVOCMessage
{
	unsigned char m_prefix[4];
	WideChar m_wide[13];
	char m_first[2];
	char m_second[2];
};

class BfmeSrcVOC
{
public:
	void bfmeFillVOC( BfmeVOCMessage *message );

	unsigned char m_prefix[0x10];
	const char *m_first;
	const char *m_second;
	const char *m_third;
};

void BfmeSrcVOC::bfmeFillVOC( BfmeVOCMessage *message )
{
	if( message == 0 )
		return;

	const WideChar *wideSource = m_first
		? (const WideChar *)(m_first + 8)
		: (const WideChar *)0x0107388C;
	wcsncpy( message->m_wide, wideSource, 12 );
	message->m_wide[12] = 0;

	const char *firstSource = m_second
		? m_second + 8
		: (const char *)0x0107388B;
	strncpy( message->m_first, firstSource, 1 );
	message->m_first[1] = 0;

	const char *secondSource = m_third
		? m_third + 8
		: (const char *)0x0107388B;
	strncpy( message->m_second, secondSource, 1 );
	message->m_second[1] = 0;
}
