// ?releaseStacks@Rva00923880Owner@@QAEXXZ
struct Rva00923880Ref { virtual void destroy(); int m_refs; };
struct Rva00923880Owner {
	char m_pad[0x24];
	Rva00923880Ref* m_first[0x20];
	int m_firstCount;
	int m_firstSkip;
	char m_pad2[0x130 - 0xac];
	Rva00923880Ref* m_second[0x20];
	int m_secondCount;
	int m_secondSkip;
	void releaseStacks();
};
void Rva00923880Owner::releaseStacks()
{
	while (m_firstCount) {
		if (m_firstSkip == 0) {
			m_firstCount--;
			Rva00923880Ref* p = m_first[m_firstCount];
			if (p) {
				if (--p->m_refs == 0)
					p->destroy();
			}
		} else {
			m_firstSkip--;
		}
	}
	while (m_secondCount) {
		if (m_secondSkip) {
			m_secondSkip--;
		} else {
			m_secondCount--;
			Rva00923880Ref* p = m_second[m_secondCount];
			if (p) {
				if (--p->m_refs == 0)
					p->destroy();
			}
		}
	}
}
