// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

// Retail replaces both incoming arguments with owner fields and tail-forwards
// them through virtual slot one.  The names remain address-derived because no
// direct named caller survives in the image.
class Rva007FACB0Owner
{
public:
	virtual void reservedSlot();
	virtual int dispatch(void *payload, void *target);

	int forward(void *unusedPayload, void *unusedTarget);

private:
	unsigned char m_prefix[0x4C];
	unsigned char m_payload;
	unsigned char m_between[0x7F];
	void *m_target;
};

int Rva007FACB0Owner::forward(void *, void *)
{
	return dispatch(&m_payload, m_target);
}
