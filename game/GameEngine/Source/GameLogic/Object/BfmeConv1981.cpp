class BfmeArgETB;
class BfmeHostETB;

class BfmeItemETB;

class BfmeSinkETB;

class BfmeHostETB
{
public:
	void bfmeApplyETB(BfmeArgETB *arg);

	unsigned char m_bfmeHeadETB[0x94];
	char m_bfme94ETB;
	unsigned char m_bfmeMid1ETB[0x157];
	BfmeSinkETB *m_bfme1ecETB;
	unsigned char m_bfmeMid2ETB[0x7c];
	BfmeItemETB *m_bfme26cETB[4];
	int m_bfme27cETB;
	unsigned char m_bfmeMid3ETB[0xc4];
	char m_bfme344ETB;
};

// Callees (tools/callees.py 0x001CDA40): ILT 0x978C -> 0x001E6EE0
// Weapon::getStatus, ILT 0x14899 -> 0x001EA630 Weapon::fireWeapon,
// ILT 0x35D0A -> 0x001B3510 Rva001CD990FiringTracker::rva001B3510,
// ILT 0x7513 -> 0x001C9B80 BfmeThing916D::bfmeGo916D.
class Object;
struct Coord3D;

enum WeaponStatus
{
	WEAPON_STATUS_PLACEHOLDER_0
};

class Weapon
{
public:
	WeaponStatus getStatus() const;
	bool fireWeapon(const Object *source, const Coord3D *pos, int *projectileID);
};

class Rva001CD990FiringTracker
{
public:
	void rva001B3510(const Weapon *weapon, int first, const void *arg, unsigned char second);
};

class BfmeThing916D
{
public:
	void bfmeGo916D(void *mode);
};

#define bfmeBusyETB() getStatus()
#define bfmeRunETB(host, arg, mode) fireWeapon((const Object *)(host), (const Coord3D *)(arg), (int *)(mode))
#define bfmeNotifyETB(item, first, arg, second) rva001B3510((item), (first), (arg), (second))
#define bfmeFinishETB(mode) bfmeGo916D((void *)(mode))

void BfmeHostETB::bfmeApplyETB(BfmeArgETB *arg)
{
	if (arg == 0)
		return;

	if ((m_bfme94ETB & 0x10) != 0)
		return;

	Weapon *item = (Weapon *)m_bfme26cETB[m_bfme27cETB];

	if (item == 0)
		return;

	if (item->bfmeBusyETB() != 0)
		return;

	char ok = item->bfmeRunETB(this, arg, 0);

	if (m_bfme1ecETB != 0)
		((Rva001CD990FiringTracker *)m_bfme1ecETB)->bfmeNotifyETB(item, 0, arg, 0);

	if (ok != 0)
		((BfmeThing916D *)this)->bfmeFinishETB(1);

	m_bfme344ETB &= 0xfd;
}
