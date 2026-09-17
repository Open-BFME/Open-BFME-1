// cl: /GS
// 0x007E8E90: Rva007E8810Message::addInt64. Formats %I64d then stores the
// field through Rva007ECE60; a negative result writes -100 at +0x24.

typedef __int64 FeslInt64;

extern "C" int __cdecl sprintf(char *buf, const char *fmt, ...);
int Rva007ECE60(char *record, int size, const char *name, const char *value);

class Rva007E8810Message
{
public:
	void addInt64(const char *key, FeslInt64 value);

private:
	char m_pad[0x10];
	char *m_10;
	int m_14;
	char m_pad18[0x0c];
	int m_24;
};

void Rva007E8810Message::addInt64(const char *key, FeslInt64 value)
{
	char buf[0x20];
	sprintf(buf, "%I64d", value);
	if (Rva007ECE60(m_10, m_14, key, buf) < 0)
		m_24 = -100;
}
