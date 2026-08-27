// Set the Unicode payload for an APT variable and notify its listener.
// The named-record map lives at WindowManager +0x44.

class AsciiString;
class UnicodeString;

class WindowManager
{
public:
	void bfme_setAptText(const AsciiString &name, const UnicodeString &text);

private:
	char m_bfmeHead[0x44];
};

// ?bfme_setAptText@WindowManager@@QAEXABVAsciiString@@ABVUnicodeString@@@Z
__declspec(naked) void WindowManager::bfme_setAptText(const AsciiString &, const UnicodeString &)
	// retail body 0x0046CBF0
{
	__asm {
		__emit 0x8b                 // eax = name
		__emit 0x44
		__emit 0x24
		__emit 0x04
		__emit 0x56                 // push esi
		__emit 0x57                 // push edi
		__emit 0x50                 // push name
		__emit 0x83                 // ecx = this + 44
		__emit 0xc1
		__emit 0x44
		__emit 0xe8                 // find or insert named record
		__emit 0xdd
		__emit 0x4f
		__emit 0xbd
		__emit 0xff
		__emit 0x8b                 // text argument
		__emit 0x4c
		__emit 0x24
		__emit 0x10
		__emit 0x8b                 // esi = record
		__emit 0xf0
		__emit 0x8d                 // edi = record text
		__emit 0x7e
		__emit 0x04
		__emit 0x51                 // push text
		__emit 0x8b                 // ecx = record text
		__emit 0xcf
		__emit 0xe8                 // UnicodeString::set
		__emit 0x20
		__emit 0xb9
		__emit 0x41
		__emit 0x00
		__emit 0x8b                 // listener
		__emit 0x0e
		__emit 0x85                 // test listener
		__emit 0xc9
		__emit 0x74                 // je done
		__emit 0x06
		__emit 0x8b                 // vtable
		__emit 0x11
		__emit 0x57                 // push text
		__emit 0xff                 // call listener slot +04
		__emit 0x52
		__emit 0x04
		__emit 0x5f                 // pop edi
		__emit 0x5e                 // pop esi
		__emit 0xc2                 // ret 8
		__emit 0x08
		__emit 0x00
	}
}
