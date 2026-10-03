// BFME's HTTP pump predates the later source-level crash guard.  The retail
// body keeps the asynchronous DNS state machine, then tail-calls ghttpThink
// when HTTP processing remains enabled.

extern unsigned char bfmeAsyncDNSLookupInProgress;
extern unsigned char bfmeCantConnectBeforeOnline;
extern unsigned char bfmeHttpOk;

extern int asyncGethostbyname(char *name);
extern void bfmeReallyStartPatchCheck();
// Defined by the matched retail body at 0x0062EA60 (Rva0062EA60StartOnline.cpp).
extern void Rva0062EA60StartOnline();
// Retail tail JMP at RVA00630488 reaches the C export at RVA0087AC30.
extern "C" void ghttpThink(void);

void HTTPThinkWrapper()
{
	if (bfmeAsyncDNSLookupInProgress)
	{
		int dnsLookupStatus = asyncGethostbyname("servserv.generals.ea.com");
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
		ghttpThink();
}
