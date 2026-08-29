// cl: /DNDEBUG /MD /EHsc

class BfmeSMCTarget
{
public:
	void bfmeApply(int condition, const void *animation, int frames);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	void bfmeApplySpecialModelCondition(int condition, const void *animation, int frames);

private:
	unsigned char m_bfmePrefix[0x1f8];
	BfmeSMCTarget *m_smcHelper;
	unsigned char m_bfmeMiddle[0x18];
	Object *m_next;
};

// The retail spelling and the optional descriptor's canonical type are
// unrecovered.  The bytes prove the Object chain traversal and all three
// arguments forwarded unchanged to the tail Object's SMC helper.
void Object::bfmeApplySpecialModelCondition(
	int condition, const void *animation, int frames)
{
	Object *last = this;
	while (last->m_next != 0)
		last = last->m_next;

	if (last->m_smcHelper != 0)
		last->m_smcHelper->bfmeApply(condition, animation, frames);
}
