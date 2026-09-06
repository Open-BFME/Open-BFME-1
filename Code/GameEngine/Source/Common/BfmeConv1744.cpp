class ClientSubsystem;

extern ClientSubsystem *TheAudioClientUpdate;

void __cdecl bfmeSendAT(void *first, void *second);

void __cdecl bfmeRepeatAT(void *first, void *second)
{
	if (TheAudioClientUpdate == 0)
		return;

	int count = 3;

	do
	{
		bfmeSendAT(first, second);
		--count;
	}
	while (count != 0);
}
