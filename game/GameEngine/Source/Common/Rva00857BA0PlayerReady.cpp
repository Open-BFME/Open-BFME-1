// ?rva00857ba0@@YAHPAXHH@Z

class BfmeThingDA;

extern "C" int __cdecl piGetPlayer(void *peer, int arg2);
int __cdecl bfmeIsReady(const BfmeThingDA *thing);

int __cdecl rva00857ba0(void *self, int arg2, int idx)
{
	if (!*(int *)((char *)self + idx * 4 + 0x390))
		return 0;

	void *player = (void *)piGetPlayer(self, arg2);
	if (!player)
		return 0;

	if (*(int *)((char *)player + 0x4c))
		return *(int *)((char *)self + 0xb40);

	return bfmeIsReady((const BfmeThingDA *)player);
}
