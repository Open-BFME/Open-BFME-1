#include "../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"

extern const char g_bfmeEmptyAscii[];

class BfmeUniETA;

struct BfmeStrDataETA
{
	int m_bfmeRefETA;
	int m_bfmeLenETA;
	char m_bfmeTextETA[1];
};

class BfmeInfoETA
{
public:
	virtual void bfmeSlot00ETA();
	virtual void bfmeSlot01ETA();
	virtual void bfmeSlot02ETA();
	virtual void bfmeSlot03ETA();
	virtual void bfmeSlot04ETA();
	virtual void bfmeSlot05ETA();
	virtual void bfmeSlot06ETA();
	virtual void bfmeSlot07ETA();
	virtual void bfmeSlot08ETA();
	virtual void bfmeSlot09ETA();
	virtual void bfmeSlot10ETA();
	virtual void bfmeSlot11ETA();
	virtual void bfmeSlot12ETA();
	virtual void bfmeSlot13ETA();
	virtual void bfmeSlot14ETA();
	virtual void bfmeSlot15ETA();
	virtual void bfmeSlot16ETA();
	virtual void bfmeSlot17ETA();
	virtual void bfmeSlot18ETA();
	virtual void *bfmeSlot19ETA(const char *text);
};

class GameSpyInfoInterface;
extern GameSpyInfoInterface *TheGameSpyInfo;

void *bfmeLookupETA(const BfmeUniETA &name)
{
	AsciiString text(reinterpret_cast<const UnicodeString &>(name));
	const BfmeStrDataETA *data = *reinterpret_cast<BfmeStrDataETA *const *>(&text);

	return reinterpret_cast<BfmeInfoETA *>(TheGameSpyInfo)->bfmeSlot19ETA(
		data ? data->m_bfmeTextETA : g_bfmeEmptyAscii);
}
