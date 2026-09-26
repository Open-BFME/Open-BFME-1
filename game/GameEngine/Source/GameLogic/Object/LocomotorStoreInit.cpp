// cl: /O2

// The LocomotorStore vtable identifies this one-byte init slot at retail
// 0x005D2CC0. The Zero Hour header declares init inline, so this TU gives the
// BFME body a concrete source owner without changing the shared header.
class LocomotorStore
{
public:
	virtual void init(void);
};

void LocomotorStore::init(void)
{
}
