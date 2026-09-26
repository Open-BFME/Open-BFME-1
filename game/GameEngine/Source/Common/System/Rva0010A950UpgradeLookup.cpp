// cl: /DNDEBUG /MD /EHsc
// Retail 0x0010A950: opaque UpgradeCenter list lookup used by the upgrade
// message dispatcher and related upgrade consumers.  The caller evidence
// proves a thiscall lookup taking a NameKeyType-sized value; the target body
// compares the node field at +0x20, unlike the separately claimed +0x0C
// UpgradeCenter copies at 0x0010A980 and 0x0010A9B0.

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

class Rva0010A950UpgradeTemplate
{
public:
	NameKeyType getLookupKey() const { return m_lookupKey; }
	Rva0010A950UpgradeTemplate *getNext() { return m_next; }
	const Rva0010A950UpgradeTemplate *getNext() const { return m_next; }

private:
	unsigned char m_unreconstructed_000[0x20];
	NameKeyType m_lookupKey;
	unsigned char m_unreconstructed_024[0x108 - 0x24];
	Rva0010A950UpgradeTemplate *m_next;
};

class Rva0010A950UpgradeCenter
{
public:
	const Rva0010A950UpgradeTemplate *findByKey(NameKeyType key) const;

private:
	unsigned char m_unreconstructed_000[0x08];
	Rva0010A950UpgradeTemplate *m_upgradeList;
};

const Rva0010A950UpgradeTemplate *Rva0010A950UpgradeCenter::findByKey(NameKeyType key) const
{
	const Rva0010A950UpgradeTemplate *upgrade;

	for (upgrade = m_upgradeList; upgrade; upgrade = upgrade->getNext())
		if (key == upgrade->getLookupKey())
			return upgrade;

	return 0;
}
