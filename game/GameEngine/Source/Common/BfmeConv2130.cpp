// Retail calls ILT 0x20824 -> 0x001BE3F0, matched Object::getControllingPlayer.
class Player;
class Object
{
public:
	Player *getControllingPlayer() const;
};

class BfmeK1094
{
public:
	void bfmeApplyABG(void *a, void *b);
};

struct BfmeNodeABG
{
	BfmeNodeABG *m_bfmeNextABG;
	BfmeNodeABG *m_bfmePrevABG;
	BfmeK1094 *m_bfme08ABG;
};

class BfmeHostABG
{
public:
	void bfmeVisitABG(void *a, void *b);

	unsigned char m_bfmeHeadABG[4];
	BfmeNodeABG *m_bfme04ABG;
};

void BfmeHostABG::bfmeVisitABG(void *a, void *b)
{
	for (BfmeNodeABG *n = m_bfme04ABG->m_bfmeNextABG; n != m_bfme04ABG; n = n->m_bfmeNextABG)
	{
		BfmeK1094 *it = n->m_bfme08ABG;

		if (reinterpret_cast<Object *>(it)->getControllingPlayer() != 0)
		{
			it->bfmeApplyABG(a, b);
			return;
		}
	}
}
