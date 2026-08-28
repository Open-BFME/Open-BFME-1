// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

// Base then two maps, and the body is empty -- everything here is member
// construction.
//
// Each map allocates one 0x1c node and wires it as its own header: colour byte
// zeroed, parent null, left and right pointing back at the node. Twenty-eight
// bytes is sixteen of node header plus a twelve-byte value, which fixes the
// mapped type at eight bytes beside a four-byte key.
//
// The unwind states count up, 0 before the first map and 1 before the second,
// which is the base followed by two destructible members.
#include <map>

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	AsciiString();
	~AsciiString();

	bool operator<(const AsciiString &other) const;

private:
	char *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/HotKey.h
struct HotKey
{
	void *m_a;
	void *m_b;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/SubsystemInterface.h
class SubsystemInterface
{
public:
	SubsystemInterface();

	virtual ~SubsystemInterface();

private:
	int m_04;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/HotKey.h
class HotKeyManager : public SubsystemInterface
{
public:
	HotKeyManager();

private:
	std::map<AsciiString, HotKey> m_hotKeys;
	std::map<AsciiString, HotKey> m_commandKeys;
};

// ??0HotKeyManager@@QAE@XZ
HotKeyManager::HotKeyManager()
{
}
