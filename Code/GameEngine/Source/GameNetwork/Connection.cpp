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
//   0x000  m_id                compared against -1, and seeded to -1 here
//   0x004  m_openedTime        set from timeGetTime() next to m_id, and read back
//                              with a 0x7530 (30s) timeout added by 0x00661F10
//   0x018  m_netCommandList    isQueueEmpty reads m_first through it
//   0x01C  m_retryTime         seeded to 2000; mods/features/033-retrytime rewrites
//                              this imm32 to 400 at RVA 0x006623DE
//   0x020  m_averageLatency    processAck (0x00661CC0) keeps the running mean here
//   0x024  m_latencies[200]    the constructor's rep stosd clears exactly 0xC8 dwords
//   0x344  m_frameGrouping     seeded to 1
//   0x350  m_numRetries        zeroed every 10 seconds
//   0x354  m_retryMetricsTime  that window's start
//
// The 0xC8-dword clear settles the gap the earlier bodies had to leave as padding:
// from m_netCommandList on, BFME keeps the reference's field order verbatim, and
// m_numRetries sits 0x198 past the reference's slot only because BFME added six
// bytes ahead of m_netCommandList and one dword at 0x34C. Same layout that
// mods/features/035-adaptretry derived independently from processAck.
//
// Declared here rather than in a shim header on purpose: a shim directory makes
// every commit run the full gate, and nothing outside this file needs any of it.

#define CONNECTION_LATENCY_HISTORY_LENGTH 200

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

// Retail zeroes this+0x0C, this+0x10 (a word) and this+0x14 before it saves edi,
// and MSVC only puts the register save there when those stores come from a
// sub-object constructor inlined ahead of the constructor body. Nothing else
// identifies the sub-object, so it is named for its offset.
struct ConnectionBlock0C
{
	ConnectionBlock0C() : m_unknown00( 0 ), m_unknown04( 0 ), m_unknown08( 0 ) {}
	UnsignedInt m_unknown00;
	UnsignedShort m_unknown04;			// +0x10; +0x12 is never written
	UnsignedInt m_unknown08;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/Connection.h
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
	UnsignedInt m_unknown08;							// this+0x008
	ConnectionBlock0C m_block0C;						// this+0x00C
	ConnectionNetCommandList *m_netCommandList;			// this+0x018
	time_t m_retryTime;									// this+0x01C
	Real m_averageLatency;								// this+0x020
	Real m_latencies[CONNECTION_LATENCY_HISTORY_LENGTH];	// this+0x024
	time_t m_frameGrouping;								// this+0x344
	time_t m_lastTimeSent;								// this+0x348
	UnsignedInt m_unknown34C;							// this+0x34C
	Int m_numRetries;									// this+0x350
	UnsignedInt m_retryMetricsTime;						// this+0x354
};

// The store order below is retail's: at /O2 MSVC keeps it, and moving any line
// reschedules the inlined rep stosd or the edi save out of position.
Connection::Connection() {
	m_numRetries = 0;
	m_retryMetricsTime = 0;
	m_unknown08 = 0;
	m_netCommandList = NULL;
	m_lastTimeSent = 0;
	m_unknown34C = 0;
	m_openedTime = 0;
	m_averageLatency = 0.0f;
	m_retryTime = 2000;
	m_frameGrouping = 1;
	m_id = -1;
	for (Int i = 0; i < CONNECTION_LATENCY_HISTORY_LENGTH; ++i) {
		m_latencies[i] = 0.0f;
	}
}

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
