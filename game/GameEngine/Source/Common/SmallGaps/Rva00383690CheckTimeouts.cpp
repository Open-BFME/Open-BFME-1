// ?checkTimeouts@Rva00383690Owner@@QAEXXZ
class NetworkInterface;
extern NetworkInterface *TheNetwork;
extern "C" unsigned long __stdcall bfme_timeGetTime(void);
struct Rva00383690Owner {
	char m_pad[0x10c];
	int m_state;
	char m_pad2[0x120 - 0x110];
	bool m_ready[8];
	int m_since[8];
	bool m_timedOut;
	void checkTimeouts();
};
void Rva00383690Owner::checkTimeouts()
{
	if (m_state != 1 && m_state != 5)
		return;
	if (!TheNetwork)
		return;
	if (m_timedOut)
		return;
	for (int i = 0; i < 8; ++i) {
		if (!m_ready[i]) {
			int now = (int)bfme_timeGetTime();
			for (int j = 0; j < 8; ++j) {
				if (!m_ready[j] && m_since[j] + 90000 > now)
					return;
			}
			m_timedOut = true;
			return;
		}
	}
}
