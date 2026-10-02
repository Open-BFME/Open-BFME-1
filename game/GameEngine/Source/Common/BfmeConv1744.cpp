// Retail's AudioManager singleton (0x012ED668); only its null-ness is tested.
class AudioManager;

extern AudioManager *TheAudio;

void __cdecl bfmeRepeatAT(void *first, void *second)
{
	if (TheAudio == 0)
		return;

	int count = 3;

	do
	{
		bfmeRepeatAT(first, second);
		--count;
	}
	while (count != 0);
}
