// cl: /O2 /Ob0

// This legacy class spelling is retained because it names the existing exact
// resolver row at 0x008F7B20; the Object field itself is BFME shroud state.
class PartitionData
{
public:
	void maybePrepend();
};

class Rva009A2350
{
public:
	void init();
};

class Rva009F2BA0
{
public:
	void init();
};

class ContainModuleInterface
{
public:
	virtual void asOpenContain() = 0;
	virtual void containReactToTransformChange() = 0; // +0x04
};

class Object
{
protected:
	virtual void bfmeReactToTransformChange();

private:
	unsigned char m_pad04[0x1fc - 4];
	ContainModuleInterface *m_contain;
	unsigned char m_pad200[0x3b0 - 0x200];
	PartitionData *m_shroudData;
	Rva009F2BA0 *m_partitionManagerState;
	Rva009A2350 *m_collisionManagerState;
};

// Thing::setTransformMatrix reaches this Object vtable slot after a transform
// change.  The original retail spelling is unrecovered.
void Object::bfmeReactToTransformChange()
{
	if (m_shroudData)
		m_shroudData->maybePrepend();
	if (m_collisionManagerState)
		m_collisionManagerState->init();
	if (m_partitionManagerState)
		m_partitionManagerState->init();

	ContainModuleInterface *contain = m_contain;
	if (contain)
		contain->containReactToTransformChange();
}
