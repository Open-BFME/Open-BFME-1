// ?checkTimeouts@Rva00383690Owner@@QAEXXZ
extern void* TheNetwork;
int __cdecl Rva00383690Now();
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
			int now = Rva00383690Now();
			for (int j = 0; j < 8; ++j) {
				if (!m_ready[j] && m_since[j] + 90000 > now)
					return;
			}
			m_timedOut = true;
			return;
		}
	}
}
