// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/stringinline
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
// Real C++ reconstruction of ??1GameState@@UAE@XZ.
// Full503B ends after ret at 0x00110FE6; CC padding starts0x00110FE7.
// The +0x4c list has trivial two-pointer payloads: retail frees16B nodes
// without string destructors. The +0x0c list array separately destroys
// SnapshotBlock strings at node+0x0c before freeing16B nodes.
//
// The 0x00110DF0 boundary was originally represented by the dump-backed naked
// thunk in this file.  The named deleting-destructor caller and the
// getSaveGameInfoFromFile caller establish the GameState identity.  This
// TU-local view is the same ABI/layout view used by the matched GameState
// constructor, retaining the retail multiple-inheritance shape.

#define __PLACEMENT_VEC_NEW_INLINE
#define _STLP_NO_EXCEPTIONS 1
#include <list>
#include "StringInline.h"

typedef int Int;
enum { SNAPSHOT_MAX = 3 };

class SubsystemInterface
{
public:
	SubsystemInterface();
	virtual ~SubsystemInterface();
	virtual void init() = 0;
	virtual void reset() = 0;
	virtual void update() = 0;

private:
	void *m_name;
};

class Snapshot
{
public:
	Snapshot() {}
	virtual ~Snapshot() {}
	virtual void crc(void *xfer) = 0;
	virtual void xfer(void *xfer) = 0;
	virtual void loadPostProcess() = 0;
};

class SaveGameInfo
{
public:
	SaveGameInfo() throw();
	~SaveGameInfo();

private:
	unsigned char m_data[0x30];
};

struct AvailableGameInfo
{
	AsciiString filename;
	SaveGameInfo saveGameInfo;
	AvailableGameInfo *next;
	AvailableGameInfo *prev;
};

class GameState : public SubsystemInterface, public Snapshot
{
public:
	GameState();
	virtual ~GameState();
	virtual void init();
	virtual void reset();
	virtual void update();

protected:
	virtual void crc(void *xfer);
	virtual void xfer(void *xfer);
	virtual void loadPostProcess();

private:
	struct SnapshotBlock
	{
		Snapshot *snapshot;
		AsciiString blockName;
	};
	struct BFMEBlock
	{
		void *first;
		void *second;
	};

	void clearAvailableGames();

	std::list<SnapshotBlock> m_snapshotBlockList[3];
	SaveGameInfo m_gameInfo;
	std::list<Snapshot *> m_snapshotPostProcessList;
	std::list<BFMEBlock> m_bfmeSnapshotBlockList;
	AvailableGameInfo *m_availableGames;
	unsigned char m_isInLoadGame;
};

void GameState::clearAvailableGames()
{
	AvailableGameInfo *gameInfo;

	while (m_availableGames)
	{
		gameInfo = m_availableGames->next;
		delete m_availableGames;
		m_availableGames = gameInfo;
	}
}

// ??1GameState@@UAE@XZ
GameState::~GameState()
{
	std::list<SnapshotBlock> *snapshotBlocks = m_snapshotBlockList;
	for (Int i = 0; i < SNAPSHOT_MAX; ++i)
		 snapshotBlocks[i].clear();

	m_snapshotPostProcessList.clear();
	m_bfmeSnapshotBlockList.clear();
	clearAvailableGames();
}
