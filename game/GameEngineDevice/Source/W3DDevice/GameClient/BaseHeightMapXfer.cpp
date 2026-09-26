// cl: /DNDEBUG /MD /EHsc
// BaseHeightMapRenderObjClass::xfer, retail 0x006C8FF0.
// BFME uses a different Xfer virtual order from the shared source headers.

typedef unsigned char UnsignedByte;
typedef bool Bool;

struct BaseHeightMapXferVersion
{
	UnsignedByte currentVersion;
	UnsignedByte version;
};

extern void __declspec(noreturn) __stdcall _CxxThrowException(
	void *object, void *throwInfo);

class Xfer
{
public:
	virtual void slot0(void) = 0;
	virtual void slot1(void) = 0;
	virtual void slot2(void) = 0;
	virtual void slot3(void) = 0;
	virtual Bool isLightCRC(void) = 0;
	virtual void slot5(void) = 0;
	virtual void slot6(void) = 0;
	virtual void slot7(void) = 0;
	virtual void slot8(void) = 0;
	virtual void slot9(void) = 0;
	virtual void xferVersion(BaseHeightMapXferVersion *version) = 0;
	virtual void slot11(void) = 0;
	virtual void xferSnapshot(void *snapshot) = 0;
};

class BaseHeightMapRenderObjClass
{
	protected:
	virtual void xfer(Xfer *xfer);

private:
	char padding[0x2fc4];
	void *m_treeBuffer;
	void *m_buffer3098;
	void *m_propBuffer;
	char padding2[4];
	void *m_waypointBuffer;
};

// ?xfer@BaseHeightMapRenderObjClass@@MAEXPAVXfer@@@Z
void BaseHeightMapRenderObjClass::xfer(Xfer *xfer)
{
	if (xfer->isLightCRC())
		return;

	BaseHeightMapXferVersion version = { 1, 3 };
	xfer->xferVersion(&version);
	if (version.version < 3)
	{
		int error = 2;
		_CxxThrowException(&error, (void *)0x01239ce0);
	}

	xfer->xferSnapshot(m_treeBuffer);
	xfer->xferSnapshot(m_buffer3098);
	xfer->xferSnapshot(m_propBuffer);
	if (version.version >= 2)
		xfer->xferSnapshot(m_waypointBuffer);
}
