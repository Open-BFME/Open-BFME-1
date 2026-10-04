// BFME shim: retail NetCommandRef is de-pooled (no vptr), so its inline accessors
// read msg+0 next+4 prev+8 relay+12 timeLastSent+16, four bytes below this
// Zero Hour layout. Only the accessor bodies differ from the reference header;
// the class layout is unchanged. Retail proof: matched Connection_doSend.cpp,
// Connection_processAck.cpp and NetCommandList* read msg at +0.
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


#pragma once

#ifndef __NETCOMMANDREF_H
#define __NETCOMMANDREF_H

#include "GameNetwork/NetCommandMsg.h"
#include "Common/GameMemory.h"

#if defined(_INTERNAL) || defined(_DEBUG)
//	#define DEBUG_NETCOMMANDREF
#endif

#ifdef DEBUG_NETCOMMANDREF
#define NEW_NETCOMMANDREF(msg) newInstance(NetCommandRef)(msg, __FILE__, __LINE__)
#else
#define NEW_NETCOMMANDREF(msg) newInstance(NetCommandRef)(msg)
#endif
 

class NetCommandRef : public MemoryPoolObject
{
	MEMORY_POOL_GLUE_WITH_USERLOOKUP_CREATE(NetCommandRef, "NetCommandRef")		
public:
#ifdef DEBUG_NETCOMMANDREF
	NetCommandRef(NetCommandMsg *msg, char *filename, int line);
#else
	NetCommandRef(NetCommandMsg *msg);
#endif
	//~NetCommandRef();

	NetCommandMsg *getCommand();
	NetCommandRef *getNext();
	NetCommandRef *getPrev();
	void setNext(NetCommandRef *next);
	void setPrev(NetCommandRef *prev);

	void setRelay(UnsignedByte relay);
	UnsignedByte getRelay() const;

	time_t getTimeLastSent() const;
	void setTimeLastSent(time_t timeLastSent);

protected:
	NetCommandMsg *m_msg;
	NetCommandRef *m_next;
	NetCommandRef *m_prev;
	UnsignedByte m_relay; ///< Need this in the command reference since the relay value will be different depending on where this particular reference is being sent.
	time_t m_timeLastSent;

#ifdef DEBUG_NETCOMMANDREF
	UnsignedInt m_id;
#endif
};

/**
 * Return the command message.
 */
inline NetCommandMsg * NetCommandRef::getCommand() 
{
	return *reinterpret_cast<NetCommandMsg * *>(reinterpret_cast<char *>(this) + 0);
}

/**
 * Return the next command ref in the list.
 */
inline NetCommandRef * NetCommandRef::getNext() 
{
	return *reinterpret_cast<NetCommandRef * *>(reinterpret_cast<char *>(this) + 4);
}

/**
 * Return the previous command ref in the list.
 */
inline NetCommandRef * NetCommandRef::getPrev() 
{
	return *reinterpret_cast<NetCommandRef * *>(reinterpret_cast<char *>(this) + 8);
}

/**
 * Set the next command ref in the list.
 */
inline void NetCommandRef::setNext(NetCommandRef *next) 
{
	*reinterpret_cast<NetCommandRef * *>(reinterpret_cast<char *>(this) + 4) = next;
}

/**
 * Set the previous command ref in the list.
 */
inline void NetCommandRef::setPrev(NetCommandRef *prev) 
{
	*reinterpret_cast<NetCommandRef * *>(reinterpret_cast<char *>(this) + 8) = prev;
}

/**
 * Return the time for the last time this command was sent from this reference.
 */
inline time_t NetCommandRef::getTimeLastSent() const
{
	return *reinterpret_cast<const time_t *>(reinterpret_cast<const char *>(this) + 16);
}

/**
 * Set the time for the last time this command was sent from this reference.
 */
inline void NetCommandRef::setTimeLastSent(time_t timeLastSent) 
{
	*reinterpret_cast<time_t *>(reinterpret_cast<char *>(this) + 16) = timeLastSent;
}

/**
 * Set the send relay for this reference of the command.
 */
inline void NetCommandRef::setRelay(UnsignedByte relay) 
{
	*reinterpret_cast<UnsignedByte *>(reinterpret_cast<char *>(this) + 12) = relay;
}

/**
 * Return the send relay for this refreence of the command.
 */
inline UnsignedByte NetCommandRef::getRelay() const
{
	return *reinterpret_cast<const UnsignedByte *>(reinterpret_cast<const char *>(this) + 12);
}

#endif // #ifndef __NETCOMMANDREF_H