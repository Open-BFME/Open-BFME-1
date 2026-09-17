// cl: /O2
// 0x007E8930: Rva007E8810Message::getInt64. Five matched callers already
// name this member. Lookup goes through Rva007EBCA0; missing keys return
// the __int64 default; a hit is sscanf("%I64d").

typedef __int64 FeslInt64;

char *Rva007EBCA0(const char *record, const char *key);
extern "C" int __cdecl sscanf(const char *buf, const char *fmt, ...);

class Rva007E8810Message
{
public:
	FeslInt64 getInt64(const char *key, FeslInt64 defaultValue);

private:
	char m_pad[0x10];
	const char *m_10;
};

FeslInt64 Rva007E8810Message::getInt64(const char *key, FeslInt64 defaultValue)
{
	char *s = Rva007EBCA0(m_10, key);
	if (s == 0)
		return defaultValue;
	FeslInt64 v;
	sscanf(s, "%I64d", &v);
	return v;
}
