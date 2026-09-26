// ?detectionBeginUpdate@FirewallHelperClass@@QAE_NXZ
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/firewall /Iinputs/reference/shims/ini /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
#define Matrix4x4 Matrix4  // BFME renamed it
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


/***********************************************************************************************
 ***              C O N F I D E N T I A L  ---  W E S T W O O D  S T U D I O S               ***
 ***********************************************************************************************
 *                                                                                             *
 *                 Project Name : Command & Conquer                                            *
 *                                                                                             *
 *                     $Archive:: /RedAlert2/NAT.CPP                                          $*
 *                                                                                             *
 *                      $Author:: Steve_t                                                     $*
 *                                                                                             *
 *                     $Modtime:: 3/15/01 12:00PM                                             $*
 *                                                                                             *
 *                    $Revision:: 1                                                           $*
 *                                                                                             *
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 *                                                                                             *
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 *                                                                                             *
 * Functions:                                                                                  *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

#include "Common/crc.h"
#include "Common/UserPreferences.h"
#include "GameNetwork/FirewallHelper.h"
#include "GameNetwork/NAT.h"
#include "GameNetwork/udp.h"
#include "GameNetwork/NetworkDefs.h"
#include "GameNetwork/GameSpy/GSConfig.h"

#ifdef _INTERNAL
// for occasional debugging...
//#pragma optimize("", off)
//#pragma MESSAGE("************************************** WARNING, optimization disabled for debugging purposes")
#endif

// Retail body RVA 0x0066EFA0, 774 bytes through RET at 0x0066F2A5;
// padding begins at 0x0066F2A6. The ILT at 0x000205F4 is recorded under
// its address-only thunk identity; the proven method name belongs here.
// BFME inlines the source-port search and spare-socket cleanup here.
// Whole-buffer initialization matches the four retail DWORD zero stores.
// The discarded ntohl call receives the address of the four-byte slot,
// exactly as the decoded retail code does; do not silently correct it.

Bool FirewallHelperClass::detectionBeginUpdate() {
//	UnsignedShort mangler_port = MANGLER_PORT;
	 m_packetID = 0x7f00;
	//int current_mangler = 0;

	/*
	** Well, we are going to need some manglers.
	*/
	UnsignedByte mangler_addresses[4][4];
	memset(mangler_addresses, 0, sizeof mangler_addresses);

//	Int delta = 0;


	/*
	** If the user specified a particular port to use then we act as if there is no firewall.
	*/
	if (TheWritableGlobalData->m_firewallPortOverride != 0) {
		m_behavior = FIREWALL_TYPE_SIMPLE;
		DEBUG_LOG(("Source port %d specified by user\n", TheGlobalData->m_firewallPortOverride));

		if (TheGlobalData->m_firewallSendDelay) {
			UnsignedInt addbehavior = FIREWALL_TYPE_NETGEAR_BUG;
			addbehavior |= (UnsignedInt)m_behavior;
			m_behavior = (FirewallBehaviorType) addbehavior;
			DEBUG_LOG(("Netgear bug specified by command line or SendDelay flag\n"));
		}
		m_currentState = DETECTIONSTATE_DONE;
		return TRUE;
	}



	m_timeoutStart = timeGetTime();
	m_timeoutLength = 5000;
	DEBUG_LOG(("About to call gethostbyname for the mangler address\n"));
	int namenum = 0;

	do {
		AsciiString host;
		UnsignedShort port;
		TheGameSpyConfig->getManglerLocation(namenum, host, port);
		const char *mangler_name_ptr = host.str();
		DEBUG_LOG(("Looking at %s:%d", host.str(), port));

		/*
		** Use the wolapi supplied mangler info if available.
		*/
//		if (NumManglerServers > namenum) {
//			mangler_name_ptr = &ManglerServerAddress[namenum][0];
//			mangler_port = ManglerServerPort[namenum];
			//current_mangler = CurrentManglerServer;
//			DEBUG_LOG(("Using mangler from servserv\n"));
//		}
		namenum++;

		if (strlen(mangler_name_ptr) == 0) {
			break;
		}

		/*
		** Do the lookup.
		*/
		char temp_name[256];
		strcpy(temp_name, mangler_name_ptr);
		struct hostent *host_info = gethostbyname(temp_name);

		if (!host_info) {
			DEBUG_LOG(("gethostbyname failed! Error code %d\n", WSAGetLastError()));
			break;
		}

		/*
		** See if we already have that address in the list.
		*/
		Bool found = FALSE;
		for (Int i=0 ; i<m_numManglers; i++) {
			if (memcmp(mangler_addresses[i], &host_info->h_addr_list[0][0], 4) == 0) {
				found = TRUE;
				break;
			}
		}
		/*
		** Add the address in if we didn't find it.
		*/
		if (!found) {
			Int m = m_numManglers++;
			memcpy(&mangler_addresses[m][0], &host_info->h_addr_list[0][0], 4);
			ntohl((UnsignedInt)mangler_addresses[m]);
			DEBUG_LOG(("Found mangler address at %d.%d.%d.%d\n", mangler_addresses[m][0], mangler_addresses[m][1], mangler_addresses[m][2], mangler_addresses[m][3]));
		}

	} while ((m_numManglers < MAX_NUM_MANGLERS) && ((timeGetTime() - m_timeoutStart) < m_timeoutLength));


	DEBUG_ASSERTCRASH(m_numManglers > 2, ("not enough mangler addresses found."));
	if (m_numManglers < 3) {
		m_currentState = DETECTIONSTATE_DONE;
		return TRUE;
	}

	for (Int i=0 ; i<m_numManglers ; i++) {
		UnsignedInt temp = 0;
		temp = mangler_addresses[i][3];
		temp += mangler_addresses[i][2] << 8;
		temp += mangler_addresses[i][1] << 16;
		temp += mangler_addresses[i][0] << 24;
		m_manglers[i] = temp;
//		memcpy(&(m_manglers[i]), &mangler_addresses[i][0], 4);
	}

	DEBUG_LOG(("FirewallHelperClass::detectionBeginUpdate - Testing for Netgear bug\n"));

	/*
	** See if the user specified a netgear firewall - that will save us the trouble.
	*/
	if (TheGlobalData->m_firewallSendDelay) {
		UnsignedInt addbehavior = FIREWALL_TYPE_NETGEAR_BUG;
		addbehavior |= (UnsignedInt)m_behavior;
		m_behavior = (FirewallBehaviorType) addbehavior;
		DEBUG_LOG(("FirewallHelperClass::detectionBeginUpdate - Netgear bug specified by command line or SendDelay flag\n"));
	} else {
		DEBUG_LOG(("FirewallHelperClass::detectionBeginUpdate - Netgear bug not specified\n"));
	}

	/*
	** OK, we have our manglers.
	**
	** First test, see if there is any port mangling at all.
	**
	**
	**
	*/

	DEBUG_LOG(("About to start mangler test 1\n"));
	/*
	** Get a spare port number and create a new socket to bind it to.
	*/
	UnsignedShort source_port;
	Int tries = 256;
	while (tries--) {
		m_sourcePortPool += 1;
		source_port = (UnsignedShort)m_sourcePortPool;
		if (m_sourcePortPool > 65535) {
			m_sourcePortPool = 2048;
		}
		if (openSpareSocket(source_port)) {
			for (Int i = 0; i < MAX_SPARE_SOCKETS; ++i) {
				if (m_spareSockets[i].port == source_port) {
					if (m_spareSockets[i].udp != NULL) {
						delete m_spareSockets[i].udp;
						m_spareSockets[i].udp = NULL;
					}
					m_spareSockets[i].port = 0;
					break;
				}
			}
			break;
		}
	}
	m_sparePorts[0] = source_port;
	if (!openSpareSocket(m_sparePorts[0])) {
		m_currentState = DETECTIONSTATE_DONE;
		return TRUE;
	}

	/*
	** Send to the mangler from this port until we get a response.
	*/
	m_timeoutStart = timeGetTime();
	m_timeoutLength = 6000;

	sendToManglerFromPort(m_manglers[0], m_sparePorts[0], m_packetID);
	m_currentState = DETECTIONSTATE_TEST1;
	return FALSE;
}



// Preserve the separate five-byte ILT without assigning it a second body identity.
class FirewallHelperDetectionBeginUpdateShim
{
public:
    Bool thunk();
};
// ?thunk@FirewallHelperDetectionBeginUpdateShim@@QAE_NXZ present-unmatched
Bool FirewallHelperDetectionBeginUpdateShim::thunk()
{
    return ((FirewallHelperClass *)this)->detectionBeginUpdate();
}
