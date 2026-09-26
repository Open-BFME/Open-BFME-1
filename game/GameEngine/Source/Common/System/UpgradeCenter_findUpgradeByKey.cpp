// cl: /DNDEBUG /MD /EHsc
// Retail 0x0010A9B0: walk TheUpgradeCenter's template list by NameKey.
// BFME keeps the name key at UpgradeTemplate+0x0C (same as ZH) and the
// next-link at +0x108 (ZH +0xF8). List head is UpgradeCenter+0x08.

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

class UpgradeTemplate
{
public:
	NameKeyType getUpgradeNameKey() const { return m_nameKey; }
	UpgradeTemplate *friend_getNext() { return m_next; }
	const UpgradeTemplate *friend_getNext() const { return m_next; }

private:
	unsigned char m_unreconstructed_000[0x0C];
	NameKeyType m_nameKey;					///< retail this+0x0C
	unsigned char m_unreconstructed_010[0x108 - 0x10];
	UpgradeTemplate *m_next;				///< retail this+0x108
};

class UpgradeCenter
{
public:
	const UpgradeTemplate *findUpgradeByKey(NameKeyType key) const;

protected:
	UpgradeTemplate *findNonConstUpgradeByKey(NameKeyType key);

private:
	unsigned char m_unreconstructed_000[0x08];
	UpgradeTemplate *m_upgradeList;			///< retail this+0x08
};

// ?findUpgradeByKey@UpgradeCenter@@QBEPBVUpgradeTemplate@@W4NameKeyType@@@Z
const UpgradeTemplate *UpgradeCenter::findUpgradeByKey(NameKeyType key) const
{
	const UpgradeTemplate *upgrade;

	for (upgrade = m_upgradeList; upgrade; upgrade = upgrade->friend_getNext())
		if (upgrade->getUpgradeNameKey() == key)
			return upgrade;

	return 0;
}

// Adjacent retail copy of the same walk; ZH names the non-const sibling
// findNonConstUpgradeByKey (protected). Bytes at 0x0010A980.
// ?findNonConstUpgradeByKey@UpgradeCenter@@IAEPAVUpgradeTemplate@@W4NameKeyType@@@Z
UpgradeTemplate *UpgradeCenter::findNonConstUpgradeByKey(NameKeyType key)
{
	UpgradeTemplate *upgrade;

	for (upgrade = m_upgradeList; upgrade; upgrade = upgrade->friend_getNext())
		if (upgrade->getUpgradeNameKey() == key)
			return upgrade;

	return 0;
}
