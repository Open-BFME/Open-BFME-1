// ??0Rva000C8480Owner@@QAE@XZ
struct Rva000C8480Owner {
	virtual ~Rva000C8480Owner();
	int m_a[0x20];
	int m_aCount;
	int m_b[0x20];
	int m_bCount;
	Rva000C8480Owner();
};
Rva000C8480Owner::Rva000C8480Owner()
{
	for (int i = 0; i < 0x20; ++i) {
		m_a[i] = 0;
		m_b[i] = 0;
	}
	m_aCount = 0;
	m_bCount = 0;
}
