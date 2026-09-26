// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

#include <string.h>

class GameWindow;

void bfmePrepareOnlineHomeGadget( GameWindow *window );
void bfmeBindOnlineHomeMessageGadget( GameWindow *window, int value );
extern void *TheBfmeOnlineHomeSlot;

class BfmeAptScreenOnlineHome
{
public:
	void bfmeOnInitMessageGadget(
		const char *name, const char *argument, GameWindow *window );
	void bfmeRefreshMessageOfTheDay();

private:
	unsigned char m_unmodelled[ 0x3C ];
	GameWindow *m_messageOfTheDay;
};

void BfmeAptScreenOnlineHome::bfmeOnInitMessageGadget(
	const char *name, const char *, GameWindow *window )
{
	if( TheBfmeOnlineHomeSlot && window )
	{
		bfmePrepareOnlineHomeGadget( window );
		if( strcmp( name, "OnlineHome::MessageOfTheDay" ) == 0 )
		{
			m_messageOfTheDay = window;
			bfmeBindOnlineHomeMessageGadget( window, 0 );
			bfmeRefreshMessageOfTheDay();
		}
	}
}
