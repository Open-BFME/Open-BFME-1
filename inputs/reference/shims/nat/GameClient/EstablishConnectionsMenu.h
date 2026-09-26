/*
**	Command & Conquer Generals Zero Hour(tm)
**	Copyright 2025 Electronic Arts Inc.
**
**	This program is free software: you can redistribute it and/or modify
**	it under the terms of the GNU General Public License as published by
**	the Free Software Foundation, either version 3 of the License, or
**	(at your option) any later version.
**
**	This program is distributed in the hope that it will be useful,
**	but WITHOUT ANY WARRANTY; without even the implied warranty of
**	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**	GNU General Public License for more details.
**
**	You should have received a copy of the GNU General Public License
**	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

////////////////////////////////////////////////////////////////////////////////
//																																						//
//  (c) 2001-2003 Electronic Arts Inc.																				//
//																																						//
////////////////////////////////////////////////////////////////////////////////

//// EstablishConnectionsMenu.h /////////////////////////

#include "GameNetwork/NetworkDefs.h"
#include "GameNetwork/NAT.h"

enum EstablishConnectionsMenuStateType {
	ESTABLISHCONNECTIONSMENUSTATETYPE_SCREENON,
	ESTABLISHCONNECTIONSMENUSTATETYPE_SCREENOFF
};

class EstablishConnectionsMenu {
public:
	EstablishConnectionsMenu();
	virtual ~EstablishConnectionsMenu();

	// BFME makes these virtual: NAT::setConnectionState @0x670DC0 calls
	// setPlayerStatus through slot 0x14 (index 5) on TheEstablishConnections
	// Menu's vtable, where this header has them as plain calls. With the
	// destructor at slot 0, declaring the five public methods virtual in
	// their existing order lands setPlayerStatus exactly at index 5.
	virtual void initMenu();
	virtual void endMenu();
	virtual void abortGame();

	virtual void setPlayerName(Int slot, UnicodeString name);
	virtual void setPlayerStatus(Int slot, NATConnectionState state);

protected:
	EstablishConnectionsMenuStateType m_menuState;

	static char *m_playerReadyControlNames[MAX_SLOTS];
	static char *m_playerNameControlNames[MAX_SLOTS];
	static char *m_playerStatusControlNames[MAX_SLOTS];
};

extern EstablishConnectionsMenu *TheEstablishConnectionsMenu;