// cl: /DNDEBUG /MD /EHs-c-
// Open-BFME-1: debug reporting flag accessors

class Gen001336E5C
{
public:
	virtual void slot00();
	char m_pad4[0x9F4B - 4];
	bool m_reportingEnabled;
	bool m_reportingSomething;
};

extern Gen001336E5C *TheGen001336E5C;

// ?_bfme_debugReportingEnabled@@YA_NXZ @ 0x008896D0
bool _bfme_debugReportingEnabled( void )
{
	return TheGen001336E5C->m_reportingEnabled;
}

// ?d_00889690@@YAXXZ @ 0x00889690
void d_00889690( void )
{
	TheGen001336E5C->m_reportingSomething = true;
}
