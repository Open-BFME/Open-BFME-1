// cl: /DNDEBUG /MD /EHsc

// Two opaque retail accessors whose rows used to sit on the pristine Zero Hour
// PeerDefs.cpp under its GameSpyInfo layout:
// - 0x000F8510 (7 B): return the dword at +0x21C (ZH GameSpyInfo::getExternalIP);
// - 0x000FB8A0 (13 B): store the argument at +0x220 (ZH
//   GameSpyInfo::setMaxMessagesPerUpdate).
// BFME's GameSpyInfo (game PeerDefs.cpp) keeps those members at +0x24C/+0x250,
// so the owner of these offsets is unproven and keeps an address-derived name.

class Rva000F8510Info
{
public:
	unsigned int get21C(void);
	void set220(int value);

	unsigned char m_pad[0x21C];
	unsigned int m_field21C;
	int m_field220;
};

unsigned int Rva000F8510Info::get21C(void)
{
	return m_field21C;
}

void Rva000F8510Info::set220(int value)
{
	m_field220 = value;
}
