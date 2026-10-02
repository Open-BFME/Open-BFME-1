// cl: /O2
// 0x007E8930: Rva007E8810Message::getInt64. Five matched callers already
// name this member. Lookup goes through Rva007EBCA0; missing keys return
// the __int64 default; a hit is sscanf("%I64d").

typedef __int64 FeslInt64;

char *Rva007EBCA0(const char *record, const char *key);
// Retail's call at 0x007E8960 is a rel32 call to the six-byte MSVCR71 thunk at
// 0x009F6FA6 (?ji_009f6fa6@@YAXXZ, gen-import body in imports_000.cpp, IAT slot
// __imp__sscanf = 0x01359494), not a direct import: spelling it `sscanf` left
// `_sscanf` undefined at link time. Declared with an empty parameter list so the
// decorated name stays ?ji_009f6fa6@@YAXXZ, the convention the other matched
// callers of these thunks use (e.g. Rva008981TaggedRecords.cpp).
extern void ji_009f6fa6();
typedef int (__cdecl *Sscanf)(const char *buf, const char *fmt, void *out);

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
	((Sscanf)ji_009f6fa6)(s, "%I64d", &v);
	return v;
}
