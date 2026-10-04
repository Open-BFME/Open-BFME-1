// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /DBFME_STLP_NODE_ALLOC /Iinputs/reference/shims/stlp_nodealloc /Iinputs/reference/shims/stringbaseascii /Iinputs/reference/shims/stringbaseunicode /Iinputs/reference/shims/sweep /Igame/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// BFME PopulateCustomLadderComboBox, RVA 0x004D6420 (936 bytes).
// Identity: the name is proved by the five retail callers, all of them named
// PopupHostGame/PopupLadderSelect bodies (PopupHostGameInit, PopupHostGameSystem,
// ladderSelectedCallback, PopupLadderSelectInput) and by the Zero Hour donor
// PopupHostGame.cpp, which declares the same free function in the same file.
// It replaces the 2026-08-11 Open-BFME5 naked __emit lift
// PopulateCustomLadderComboBoxThunk.cpp, which scored as a dump.
// BFME differences from the ZH donor, all witnessed in the retail body:
// the preference file is "LoTRB4MEOnline\\CustomPref%d.ini" (0x010810BC), not
// "GeneralsOnline\\..."; the profile id comes from GameSpyInfo slot 28 (+0x70);
// the colour array indices are 25/26 (0x012B9264 / 0x012B9268) rather than the
// GSCOLOR_MAP_* enums; the recent-ladder address compare is StringBase<char>.
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

// FILE: PopupHostGame.cpp /////////////////////////////////////////////////
//-----------------------------------------------------------------------------
//                                                                          
//                       Electronic Arts Pacific.                          
//                                                                          
//                       Confidential Information                           
//                Copyright (C) 2002 - All Rights Reserved                  
//                                                                          
//-----------------------------------------------------------------------------
//
//	created:	Jul 2002
//
//	Filename: 	PopupHostGame.cpp
//
//	author:		Chris Huybregts
//	
//	purpose:	Contains the Callbacks for the Host Game Popus
//
//-----------------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////

//-----------------------------------------------------------------------------
// SYSTEM INCLUDES ////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
#define _BFME_RETAIL_TREE_INSERT_LAYOUT

//-----------------------------------------------------------------------------
// USER INCLUDES //////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

#include "Common/GlobalData.h"
#include "Common/NameKeyGenerator.h"
#include "Common/Version.h"
#include "GameClient/WindowLayout.h"
#include "GameClient/Gadget.h"
#include "GameClient/GameText.h"
#include "GameClient/KeyDefs.h"
#include "GameClient/GadgetTextEntry.h"
#include "GameClient/GadgetCheckBox.h"
#include "GameClient/GadgetComboBox.h"
#include "GameClient/GadgetListBox.h"
#include "GameNetwork/GameSpy/GSConfig.h"
#include "GameNetwork/GameSpy/Peerdefs.h"
#include "GameNetwork/GameSpy/PeerThread.h"
#include "GameNetwork/GameSpyOverlay.h"

#include "GameNetwork/GameSpy/LadderDefs.h"
#include "Common/CustomMatchPreferences.h"
#include "Common/LadderPreferences.h"

// Retail inlines ~AsciiString: temporaries are released by a direct call to
// StringBase<char>::releaseBuffer (0x00887940), not the ??1AsciiString stub.
inline AsciiString::~AsciiString() { ((StringBase<char> *)this)->releaseBuffer(); }
// Retail inlines ~UnicodeString: temporaries are released by a direct call to
// StringBase<unsigned short>::releaseBuffer (0x008881D0), not the ??1UnicodeString stub.
inline UnicodeString::~UnicodeString() { ((StringBase<unsigned short> *)this)->releaseBuffer(); }

namespace _STL
{
template <class Node, class NodeAllocator, class Value>
__forceinline Node *bfmeCreateLadderNode(NodeAllocator &allocator, const Value &value)
{
  Node *node = allocator.allocate(1);
  _Construct(&node->_M_value_field, value);
  return node;
}

template <>
_Rb_tree<const LadderInfo *, const LadderInfo *, _Identity<const LadderInfo *>,
         less<const LadderInfo *>, allocator<const LadderInfo *> >::iterator
_Rb_tree<const LadderInfo *, const LadderInfo *, _Identity<const LadderInfo *>,
         less<const LadderInfo *>, allocator<const LadderInfo *> >::_M_insert(
    _Rb_tree_node_base *__x_, _Rb_tree_node_base *__y_,
    const LadderInfo *const &__v, _Rb_tree_node_base *__w_)
{
  _Link_type __w = (_Link_type)__w_;
  _Link_type __x = (_Link_type)__x_;
  _Link_type __y = (_Link_type)__y_;
  _Link_type __z;

  if (__y == this->_M_header._M_data ||
      (__w == 0 && (__x != 0 || _M_key_compare(_Identity<const LadderInfo *>()(__v), _S_key(__y))))) {
    __z = bfmeCreateLadderNode<_Node>(this->_M_header, __v);
    _S_left(__y) = __z;
    if (__y == this->_M_header._M_data) {
      _M_root() = __z;
      _M_rightmost() = __z;
    } else if (__y == _M_leftmost()) {
      _M_leftmost() = __z;
    }
  } else {
    __z = bfmeCreateLadderNode<_Node>(this->_M_header, __v);
    _S_right(__y) = __z;
    if (__y == _M_rightmost()) {
      _M_rightmost() = __z;
    }
  }
  _S_parent(__z) = __y;
  _S_left(__z) = 0;
  _S_right(__z) = 0;
  _Rb_global_inst::_Rebalance(__z, this->_M_header._M_data->_M_parent);
  ++_M_node_count;
  return iterator(__z);
}

template _Rb_tree<const LadderInfo *, const LadderInfo *, _Identity<const LadderInfo *>,
                  less<const LadderInfo *>, allocator<const LadderInfo *> >::_Link_type
_Rb_tree<const LadderInfo *, const LadderInfo *, _Identity<const LadderInfo *>,
         less<const LadderInfo *>, allocator<const LadderInfo *> >::_M_create_node(
    const LadderInfo *const &);
}

// BFME GameSpyInfo vtable 0x011188D0 places getLocalProfileID at slot 28
// (+0x70), as the ListBox sibling witnesses. Only that dispatch is used here.
struct GameSpyProfileDispatch004D6420 {
    virtual void slot00();
    virtual void slot01();
    virtual void slot02();
    virtual void slot03();
    virtual void slot04();
    virtual void slot05();
    virtual void slot06();
    virtual void slot07();
    virtual void slot08();
    virtual void slot09();
    virtual void slot10();
    virtual void slot11();
    virtual void slot12();
    virtual void slot13();
    virtual void slot14();
    virtual void slot15();
    virtual void slot16();
    virtual void slot17();
    virtual void slot18();
    virtual void slot19();
    virtual void slot20();
    virtual void slot21();
    virtual void slot22();
    virtual void slot23();
    virtual void slot24();
    virtual void slot25();
    virtual void slot26();
    virtual void slot27();
    virtual int getLocalProfileID();
};
static GameWindow *parentPopup;
static GameWindow *comboBoxLadderName;
static bool isPopulatingLadderBox;

void PopulateCustomLadderComboBox( void )
{
	if (!parentPopup || !comboBoxLadderName)
		return;

	isPopulatingLadderBox = true;

	CustomMatchPreferences pref;
	AsciiString userPrefFilename;
	Int localProfile = reinterpret_cast<GameSpyProfileDispatch004D6420 *>(TheGameSpyInfo)->getLocalProfileID();
	userPrefFilename.format("LoTRB4MEOnline\\CustomPref%d.ini", localProfile);
	pref.load(userPrefFilename);

	std::set<const LadderInfo *> usedLadders;

	Color specialColor = GameSpyColor[25] /* BFME RVA 0x012B9264 */;
	Color normalColor = GameSpyColor[26] /* BFME RVA 0x012B9268 */;
	Int index;
	GadgetComboBoxReset( comboBoxLadderName );
	index = GadgetComboBoxAddEntry( comboBoxLadderName, TheGameText->fetch("GUI:NoLadder"), normalColor );
	GadgetComboBoxSetItemData( comboBoxLadderName, index, 0 );

	Int selectedPos = 0;
	AsciiString lastLadderAddr = pref.getLastLadderAddr();
	UnsignedShort lastLadderPort = pref.getLastLadderPort();
	const LadderInfo *info = TheLadderList->findLadder( lastLadderAddr, lastLadderPort );
	if (info && info->validCustom)
	{
		usedLadders.insert(info);
		index = GadgetComboBoxAddEntry( comboBoxLadderName, info->name, specialColor );
		GadgetComboBoxSetItemData( comboBoxLadderName, index, (void *)(info->index) );
		selectedPos = index;
	}

	LadderPreferences ladPref;
	ladPref.loadProfile( localProfile );
	const LadderPrefMap recentLadders = ladPref.getRecentLadders();
	for (LadderPrefMap::const_iterator cit = recentLadders.begin(); cit != recentLadders.end(); ++cit)
	{
		AsciiString addr = cit->second.address;
		UnsignedShort port = cit->second.port;
		if (((const StringBase<char> *)&addr)->compare(*(const StringBase<char> *)&lastLadderAddr) == 0 && port == lastLadderPort)
			continue;
		const LadderInfo *info = TheLadderList->findLadder( addr, port );
		if (info && info->validCustom && usedLadders.find(info) == usedLadders.end())
		{
			usedLadders.insert(info);
			index = GadgetComboBoxAddEntry( comboBoxLadderName, info->name, normalColor );
			GadgetComboBoxSetItemData( comboBoxLadderName, index, (void *)(info->index) );
		}
	}

	index = GadgetComboBoxAddEntry( comboBoxLadderName, TheGameText->fetch("GUI:ChooseLadder"), normalColor );
	GadgetComboBoxSetItemData( comboBoxLadderName, index, (void *)-1 );

	GadgetComboBoxSetSelectedPos( comboBoxLadderName, selectedPos );
	isPopulatingLadderBox = false;
}
