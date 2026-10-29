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

// Retail 0x01336E5C is ?g_Rva00F36E5C@@3PAXA (data_rows.csv,
// debug/Rva00F36E5C.cpp); g_rva00889690 was only a pin.
extern void *g_Rva00F36E5C;
#define g_rva00889690 ( *(Rva00889690Obj **)&g_Rva00F36E5C )

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
