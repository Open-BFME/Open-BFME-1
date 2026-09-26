// cl: /DNDEBUG /MD /EHsc
class Rva0083FDF0Forward
{
public:
	virtual void slot0() = 0;
	virtual void slot1() = 0;
	virtual void slot2(void *out, int first, int second, int third) = 0;
	virtual void slot3(void *out, int first, int second, int third) = 0;
	void *forwardSlot2(void *out, int first, int second, int third);
	void *forwardSlot3(void *out, int first, int second, int third);
};

// ?forwardSlot2@Rva0083FDF0Forward@@QAEPAXPAXHHH@Z
void *Rva0083FDF0Forward::forwardSlot2(void *out, int first, int second, int third)
{
	slot2(out, first, second, third);
	return out;
}

// ?forwardSlot3@Rva0083FDF0Forward@@QAEPAXPAXHHH@Z
void *Rva0083FDF0Forward::forwardSlot3(void *out, int first, int second, int third)
{
	slot3(out, first, second, third);
	return out;
}
