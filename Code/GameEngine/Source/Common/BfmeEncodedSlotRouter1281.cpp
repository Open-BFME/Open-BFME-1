extern unsigned char g_bfmeDispatchEnabled1281;

class BfmeSlotDispatcher1281
{
public:
	void bfmeDispatchDirect1281(unsigned int encoded);
	void bfmeDispatchVisible1281(int group, void *encoded);
	void bfmePrepare1281(int group, int slot, unsigned int encoded);
	void bfmeDispatchSlots1281(int group, int slot, void *encoded);
	void bfmeMirror1281(int group, int slot, unsigned int encoded);
	void bfmeResolve1281(int group, int slot, void **result, bool *handled);
	void bfmeFallback1281(void *result, int group, int slot);
	void bfmeRouteEncoded1281(unsigned int encoded);
};

void BfmeSlotDispatcher1281::bfmeRouteEncoded1281(unsigned int encoded)
{
	unsigned int kind = encoded & 3;
	if (kind == 0) {
		if (g_bfmeDispatchEnabled1281 != 0)
			bfmeDispatchDirect1281(encoded);
		return;
	}
	if (kind != 1)
		return;

	int group = encoded >> 17;
	if (group == 502 || group == 501) {
		bfmeDispatchVisible1281(group, (void *)encoded);
		return;
	}

	int slot = (encoded >> 10) & 0x7f;
	void *result = 0;
	bool handled;
	bfmePrepare1281(group, slot, encoded);
	bfmeDispatchSlots1281(group, slot, (void *)encoded);
	if (g_bfmeDispatchEnabled1281 != 0)
		bfmeMirror1281(group, slot, encoded);

	bfmeResolve1281(group, slot, &result, &handled);
	if (!handled)
		bfmeFallback1281(result, group, slot);
}
// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD
