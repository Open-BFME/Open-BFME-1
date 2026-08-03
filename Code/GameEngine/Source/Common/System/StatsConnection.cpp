// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: IsStatsConnected returns nonzero when connection id is not -1.

extern int g_statsConnection;

extern "C" int IsStatsConnected(void)
{
	return g_statsConnection != -1;
}
