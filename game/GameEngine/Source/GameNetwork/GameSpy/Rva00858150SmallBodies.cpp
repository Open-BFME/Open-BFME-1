// cl: /DNDEBUG /MD /EHsc
// Six small GameSpy bodies sharing one connection layout, plus the +0xAF0
// record helper they call. 0x00858150 stores the incoming pointer at +0xB48
// and then runs the Rva008667A0 helper from Rva008667A0.cpp on the same
// owner; 0x00861020/0x00861050/0x00861510 format one IRC line each onto the
// socket at +0x1C through ciSocketSendf, guarded on the connected flag at +0.
// IDENTITY IS NOT RECOVERED for the owner; every name is derived from an
// address. The format strings ride as literals the gate verifies against
// retail ("MODE %s -b %s", "SETGROUP %s %s", "KICK %s %s :%s").
// The null KICK reason falls back to the empty-string literal.
//
// WHAT THE BYTES SHOW for each body is spelled above it. Retail loads the
// two/three stack arguments with arg2 (eax) before arg1 (edx); the source
// keeps that order by declaring the format-argument locals arg-first.

typedef void *CHAT;

extern "C" void ciSocketSendf(void *socket, const char *format, ...);

class Rva00866770Owner
{
public:
	char m_bfmeHeadA[0xAF0];
	void *m_bfmeAF0;					// +0xAF0
};

void Rva008667A0(Rva00866770Owner *peer);

struct Rva00858150Owner
{
	char m_head[0xAF0];					// +0x000
	void *m_AF0;						// +0xAF0
	char m_tail[0xB48 - 0xAF4];			// +0xAF4
	void *m_B48;						// +0xB48
};

// 0x00858150: mov eax,[esp+4] / mov ecx,[esp+8] / mov [eax+0xB48],ecx /
// mov ecx,[eax+0xAF0] / test ecx,ecx / je end / push eax / call Rva008667A0.
 // ?dup_00858150@@YAXPAURva00858150Owner@@PAX@Z
void dup_00858150(Rva00858150Owner *owner, void *value)
{
	owner->m_B48 = value;
	void *record = owner->m_AF0;
	if (record)
		Rva008667A0((Rva00866770Owner *)owner);
}

struct Rva00861000Conn
{
	int m_connected;					// +0x00
	char m_pad[0x18];					// +0x04
	char m_chatSocket;					// +0x1C
};

// 0x00861020: guard chat+connected, then
// ciSocketSendf(socket+0x1c, "MODE %s -b %s", arg2, arg1).
// ?dup_00861020@@YAXPAXPBD1@Z
void dup_00861020(void *chat, const char *a, const char *b)
{
	Rva00861000Conn *connection = (Rva00861000Conn *)chat;
	if (!chat || !connection->m_connected)
		return;
	ciSocketSendf(&connection->m_chatSocket, "MODE %s -b %s", a, b);
}

// 0x00861050: guard chat+connected+nonempty reason, then
// ciSocketSendf(socket+0x1c, "SETGROUP %s %s", arg2, arg1).
// ?dup_00861050@@YAXPAXPBD1@Z
void dup_00861050(void *chat, const char *a, const char *b)
{
	Rva00861000Conn *connection = (Rva00861000Conn *)chat;
	if (!chat || !connection->m_connected || !b || !*b)
		return;
	ciSocketSendf(&connection->m_chatSocket, "SETGROUP %s %s", a, b);
}

// 0x00861510: guard chat+connected, default a null reason to the empty
// string, then ciSocketSendf(socket+0x1c, "KICK %s %s :%s", arg2, arg1).
// ?dup_00861510@@YAXPAXPBD11@Z
void dup_00861510(void *chat, const char *a, const char *b, const char *c)
{
	Rva00861000Conn *connection = (Rva00861000Conn *)chat;
	if (!chat || !connection->m_connected)
		return;
	if (!c)
		c = "";
	ciSocketSendf(&connection->m_chatSocket, "KICK %s %s :%s", a, b, c);
}
