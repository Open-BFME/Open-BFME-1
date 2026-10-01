// The receiver of bfmeNotifyGG is an Object: the model-condition word array
// sits at Object+0x110 and is indexed by (bit >> 5), and the call it makes is
// the ILT 0x0002191D thunk to Object::notifyModelConditionChanged.

#define OBJECT_TU_MEMBERS void notifyModelConditionChanged();
#include "../GameLogic/Object/object.h"

class BfmeSrcGG
{
public:
	unsigned char m_bfmeGapGG[0x64];
	unsigned int m_bfmeBitGG;
};

class BfmeMaskGG
{
public:
	void bfmeSetBitGG(bool on);

	unsigned char m_bfmeHeadGG[4];
	BfmeSrcGG *m_bfmeSrcGG;
	Object *m_bfmeThingGG;
};

void BfmeMaskGG::bfmeSetBitGG(bool on)
{
	Object *t = m_bfmeThingGG;
	BfmeSrcGG *s = m_bfmeSrcGG;

	if (t != 0 && s != 0)
	{
		unsigned int bit = s->m_bfmeBitGG;

		if (bit != 0xffffffff)
		{
			if (on)
			{
				if ((t->m_modelConditionFlags[bit >> 5] & (1 << (bit & 0x1f))) == 0)
				{
					t->m_modelConditionFlags[bit >> 5] |= (1 << (bit & 0x1f));
					t->notifyModelConditionChanged();
				}
			}
			else
			{
				if ((t->m_modelConditionFlags[bit >> 5] & (1 << (bit & 0x1f))) != 0)
				{
					t->m_modelConditionFlags[bit >> 5] &= ~(1 << (bit & 0x1f));
					t->notifyModelConditionChanged();
				}
			}
		}
	}
}