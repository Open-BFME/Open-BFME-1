// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/framedata /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
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

#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

// BFME's Connection is not a MemoryPoolObject: the reference derives from one,
// which would put a vptr at this+0, and retail instead keeps a plain Int there --
// the field ConnectionManager::isPlayerConnected compares against -1 to decide
// whether a slot is open. So the reference's field order does not carry over and
// the class is declared here with only what retail bodies pin:
//
//   0x000  m_id                compared against -1
//   0x004  m_openedTime        set from timeGetTime() next to m_id, and read back
//                              with a 0x7530 (30s) timeout added by 0x00661F10
//   0x018  m_netCommandList    isQueueEmpty reads m_first through it
//   0x350  m_numRetries        zeroed every 10 seconds
//   0x354  m_retryMetricsTime  that window's start
//
// The reference's order would put m_numRetries at 0x1B8; retail has it 0x198
// further on. Whether BFME grew m_latencies or added members is not decidable
// from these two bodies, so the gap stays padding rather than a guess.
//
// Declared here rather than in a shim header on purpose: a shim directory makes
// every commit run the full gate, and nothing outside this file needs any of it.

class NetCommandRef;

// Retail inlines getFirstMessage -- isQueueEmpty reads m_first straight off the
// object (mov ecx,[eax+4]) rather than calling anything.
class ConnectionNetCommandList
{
public:
	NetCommandRef *getFirstMessage() { return m_first; }
private:
	void *m_vptr;
	NetCommandRef *m_first;
};

class Connection
{
public:
	Connection();
	Bool isQueueEmpty();
	void setQuitting( UnsignedInt quitFrame );

protected:
	void doRetryMetrics();

	Int m_id;											// this+0x000
	UnsignedInt m_openedTime;							// this+0x004
	char m_padToCommandList[0x18 - 0x08];				// unpinned
	ConnectionNetCommandList *m_netCommandList;			// this+0x018
	char m_padToRetryMetrics[0x350 - 0x1C];				// unpinned
	Int m_numRetries;									// this+0x350
	UnsignedInt m_retryMetricsTime;						// this+0x354
};

Bool Connection::isQueueEmpty() {
	if (m_netCommandList->getFirstMessage() == NULL) {
		return TRUE;
	}
	return FALSE;
}

void Connection::setQuitting( UnsignedInt quitFrame ) {
	m_id = quitFrame;
	m_openedTime = timeGetTime();
}

void Connection::doRetryMetrics() {
	static Int numSeconds = 0;
	time_t curTime = timeGetTime();

	if ((curTime - m_retryMetricsTime) > 10000) {
		m_retryMetricsTime = curTime;
		++numSeconds;
		m_numRetries = 0;
	}
}
