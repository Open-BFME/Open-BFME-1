// cl: /DNDEBUG /MD /EHs-c-
// Open-BFME-1: debug reporting flag accessors

struct Rva00889690Obj
{
public:
	virtual void slot00();
	char m_pad4[0x9F4B - 4];
	bool m_reportingEnabled;
	bool m_reportingSomething;
};

extern Rva00889690Obj *g_rva00889690;

// ?_bfme_debugReportingEnabled@@YA_NXZ @ 0x008896D0
bool _bfme_debugReportingEnabled( void )
{
	return g_rva00889690->m_reportingEnabled;
}

// Keep this unclaimed helper TU-local to avoid colliding with the generated symbol.
static void markReportingSomething( void )
{
	g_rva00889690->m_reportingSomething = true;
}
