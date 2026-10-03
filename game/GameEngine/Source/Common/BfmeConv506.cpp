// Open-BFME5 guarded three-argument element dispatch. The guarded object is the
// thiscall receiver and the three pointers are forwarded to it, which is what
// retail's ILT 0x000160D1 reaches: symbols.csv pins that thunk to
// ObjectCreationList::createInternal (body 0x001D6810), the same name the OCL
// callers in GameLogic/Object already spell.

class Object;

class ObjectCreationList
{
public:
	void createInternal(const Object *primary, const Object *secondary, unsigned int lifetimeFrames) const;
};

// the guarded object's type: it only names this function's signature
class BfmeSubBPB;

void bfmeGoBPB(BfmeSubBPB *sub, void *one, void *two, void *three)
{
	if (sub != 0)
		reinterpret_cast<ObjectCreationList *>(sub)->createInternal(
			static_cast<const Object *>(one),
			static_cast<const Object *>(two),
			reinterpret_cast<unsigned int>(three));
}
