void * __cdecl bfmeCall1WB(void *buffer, void *seventh, void *eighth, void *slot, void *sixth);
void __cdecl bfmeCall2WB(void *out, void *buffer, void *made, void *second, void *third, void *fourth, int zero);

class BfmeOwnerWB
{
public:
	void *bfmeMakeWB(void *out, void *second, void *third, void *fourth, void *fifth, void *sixth, void *seventh, void *eighth);
};

void *BfmeOwnerWB::bfmeMakeWB(void *out, void *second, void *third, void *fourth, void *fifth, void *sixth, void *seventh, void *eighth)
{
	char buffer[0x40];

	void *made = bfmeCall1WB(buffer, seventh, eighth, (char *)this + 0xc, sixth);

	bfmeCall2WB(out, buffer, made, second, third, fourth, 0);

	return out;
}
