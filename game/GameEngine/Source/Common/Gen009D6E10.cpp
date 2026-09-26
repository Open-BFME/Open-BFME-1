// cl: /DNDEBUG /MD /O2
// Clean C++ conversion of the peer attach/finalize helper at retail RVA 0x009D6E10.

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
	Gen009D6E10 *bfmeAttach(BfmePeer *peer);

private:
	void *m_channel;
	bool m_enabled;
};

Gen009D6E10 *Gen009D6E10::bfmeAttach(BfmePeer *peer)
{
	if (m_enabled)
		bfmeAccept(peer->bfmeValue());

	bfmeReset(peer);
	if (m_enabled)
		bfmeFinish();
	return this;
}
