// Retail 0x004E9CF0: teardown of the online-shell singleton state.
//
// The two singleton slots are intentionally kept as raw address-bound globals:
// the retail body only establishes their widths and uses, not their source
// names.  The callee at 0x0055BE40 is already represented by BfmeB1021 in the
// conversion set.

class BfmeB1021
{
public:
	void bfmeGo1021B( void );
};

class BfmeH1086
{
public:
	virtual void slot0( void );
	virtual void slot1( int );
	virtual void slot2( void );
	virtual void slot3( void );
	virtual void slot4( void );
	virtual void slot5( void );
	virtual void slot6( void );
	virtual void slot7( void );
	virtual void slot8( void );
};

class BfmeAptScreenOnlineShell;
extern BfmeAptScreenOnlineShell *g_obj12F4ACC;
extern unsigned char g_g_012F4248;
extern BfmeH1086 *g_h_012F4238;
extern int numOnlineInNotification;
extern bool lastNotificationWasStatus;

void bfmeGo1086B( void )
{
	numOnlineInNotification = 0;
	lastNotificationWasStatus = 0;

	if( reinterpret_cast<BfmeB1021 * &>(g_obj12F4ACC) )
	{
		if( g_g_012F4248 )
		{
			reinterpret_cast<BfmeB1021 * &>(g_obj12F4ACC)->bfmeGo1021B();
			g_g_012F4248 = 0;
		}
	}
	else
	{
		g_g_012F4248 = 0;
		if( g_h_012F4238 )
		{
			g_h_012F4238->slot8();
			if( g_h_012F4238 )
				g_h_012F4238->slot1( 1 );
			g_h_012F4238 = 0;
		}
	}
}
