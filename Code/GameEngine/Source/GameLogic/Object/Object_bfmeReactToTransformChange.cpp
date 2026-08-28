// cl: /O2 /Ob0

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
	PartitionData *m_partitionData;
	Rva009F2BA0 *m_field3b4;
	Rva009A2350 *m_field3b8;
};

// Thing::setTransformMatrix reaches this Object vtable slot after a transform
// change.  The original retail spelling is unrecovered.
void Object::bfmeReactToTransformChange()
{
	if (m_partitionData)
		m_partitionData->maybePrepend();
	if (m_field3b8)
		m_field3b8->init();
	if (m_field3b4)
		m_field3b4->init();

	ContainModuleInterface *contain = m_contain;
	if (contain)
		contain->containReactToTransformChange();
}
