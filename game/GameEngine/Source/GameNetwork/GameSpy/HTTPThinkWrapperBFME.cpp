// BFME's HTTP pump predates the later source-level crash guard.  The retail
// body keeps the asynchronous DNS state machine, then tail-calls ghttpThink
// when HTTP processing remains enabled.

extern unsigned char bfmeAsyncDNSLookupInProgress;
extern unsigned char bfmeCantConnectBeforeOnline;
extern unsigned char bfmeHttpOk;

extern int bfmeAsyncGethostbyname(char *name);
extern void bfmeReallyStartPatchCheck();
// Defined by the matched retail body at 0x0062EA60 (Rva0062EA60StartOnline.cpp).
extern void Rva0062EA60StartOnline();
extern void bfmeGhttpThink();

void HTTPThinkWrapper()
{
	if (bfmeAsyncDNSLookupInProgress)
	{
		int dnsLookupStatus = bfmeAsyncGethostbyname("servserv.generals.ea.com");
		switch (dnsLookupStatus)
		{
		case 1:
			bfmeCantConnectBeforeOnline = 1;
			Rva0062EA60StartOnline();
			break;
		case 2:
			bfmeReallyStartPatchCheck();
			break;
		}
	}

	if (bfmeHttpOk)
		bfmeGhttpThink();
}
