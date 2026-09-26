// cl: /O2 /EHsc
// stlport
#include <vector>

// Retail 0x00423460 is Eva::setShouldPlay(EvaMessage), the one-argument
// sibling of the position-aware overload at 0x004233A0.
enum EvaMessage
{
	EvaMessage_Invalid = -1
};

// EvaCheckInfo records occupy 28 bytes in the parsed table at this+0x0c.
struct EvaCheckInfo
{
	unsigned char m_pad[28];
};

// EvaCheck records occupy 24 bytes in the live table at this+0x4c.
struct EvaCheck
{
	// EvaCheck::resetFromInfo is the established body at 0x00422B70.
	void resetFromInfo(const EvaCheckInfo *info);

	unsigned char m_pad[24];
};

class Eva
{
public:
	void setShouldPlay(EvaMessage message);

	unsigned char m_head[0xc];
	_STL::vector<EvaCheckInfo> m_checkInfos;
	unsigned char m_mid[0x4c - 0x18];
	_STL::vector<EvaCheck> m_checks;
};

void Eva::setShouldPlay(EvaMessage message)
{
	if (message == EvaMessage_Invalid)
		return;

	if (message < 0)
		return;

	unsigned int checksCount = (unsigned int)m_checks.size();
	if ((unsigned int)message >= checksCount)
		return;

	unsigned int infoCount = (unsigned int)m_checkInfos.size();
	unsigned int liveCount = (unsigned int)m_checks.size();
	if (liveCount != infoCount)
		return;

	m_checks[message].resetFromInfo(&m_checkInfos[message]);
}
