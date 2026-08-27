// cl: /DNDEBUG /MD /O2
// Clean C++ conversion of the unconditional peer attach helper at retail RVA 0x009D90D0.

class BfmePeer
{
public:
	virtual void slot0();
	virtual void slot1();
	virtual void *bfmeValue();
};

class Gen009D6E10
{
public:
	virtual void slot0();
	virtual void slot1();
	virtual void slot2();
	virtual void slot3();
	virtual void slot4();
	virtual void bfmeAccept(void *value);
	virtual void bfmeFinish();

	void bfmeReset(BfmePeer *peer);
	Gen009D6E10 *bfmeAttachAlways(BfmePeer *peer);
};

Gen009D6E10 *Gen009D6E10::bfmeAttachAlways(BfmePeer *peer)
{
	bfmeAccept(peer->bfmeValue());
	bfmeReset(peer);
	bfmeFinish();
	return this;
}
