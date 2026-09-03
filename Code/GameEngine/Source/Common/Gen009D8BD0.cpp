// cl: /DNDEBUG /MD /O2
// Clean C++ conversion of the flagged attach helper at retail RVA 0x009D8BD0.

class Snapshot;

class Xfer
{
public:
	virtual Xfer &operator==(Snapshot &snapshot);
};

class BfmePeer
{
public:
	virtual void slot0();
	virtual void slot1();
	virtual void *bfmeValue();
};

class BfmeHost
{
public:
	virtual void s0();
	virtual void s1();
	virtual void s2();
	virtual void s3();
	virtual void s4();
	virtual void s5();
	virtual void s6();
	virtual void s7();
	virtual void s8();
	virtual void s9();
	virtual void s10();
	virtual void s11();
	virtual void *bfmeQuery();
};

typedef void (__cdecl *BfmeAttachCallback)(void *peer, void *ctx, void *query);

class Gen009D8BD0
{
public:
	virtual void slot0();
	virtual void slot1();
	virtual void slot2();
	virtual void slot3();
	virtual void slot4();
	virtual void bfmeAccept(void *value);
	virtual void bfmeFinish();

	Gen009D8BD0 *bfmeAttach(BfmePeer *peer);

private:
	BfmeAttachCallback m_callback;
	int m_pad;
	void *m_ctx;
	bool m_enabled;
	BfmeHost *m_host;
};

Gen009D8BD0 *Gen009D8BD0::bfmeAttach(BfmePeer *peer)
{
	if (m_enabled)
		bfmeAccept(peer->bfmeValue());

	reinterpret_cast<Xfer *>(this)->Xfer::operator==(*reinterpret_cast<Snapshot *>(peer));
	if (m_enabled)
		bfmeFinish();
	if (m_callback)
		m_callback(peer, m_ctx, m_host->bfmeQuery());
	return this;
}
