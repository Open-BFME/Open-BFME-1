// ?W3DGadgetImageComboBoxDraw@@YAXPAVGameWindow@@PAVWinInstanceData@@@Z
// partial score=0.8589 date=2026-10-03
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/w3ddisplaystring /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
#define Matrix4x4 Matrix4  // BFME renamed it
#define __PLACEMENT_VEC_NEW_INLINE  // always.h/GameMemory.h define array placement-new themselves
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

// FILE: W3DComboBox.cpp ///////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
//                                                                          
//                       Westwood Studios Pacific.                          
//                                                                          
//                       Confidential Information                           
//                Copyright (C) 2001 - All Rights Reserved                  
//                                                                          
//-----------------------------------------------------------------------------
//
// Project:   RTS3
//
// File name: W3DComboBox.cpp
//
// Created:   Colin Day, June 2001
//
// Desc:      W3D implementation for the Combo box control
//
//-----------------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////

// SYSTEM INCLUDES ////////////////////////////////////////////////////////////
#include <stdlib.h>

#include "GameClient/DisplayString.h"

// USER INCLUDES //////////////////////////////////////////////////////////////
#include "GameClient/GameWindowGlobal.h"
#include "GameClient/GameWindowManager.h"
#include "GameClient/GadgetComboBox.h"
#include "GameClient/GadgetListBox.h"
#include "W3DDevice/GameClient/W3DGadget.h"
#include "W3DDevice/GameClient/W3DDisplay.h"


#include "GameClient/Image.h"
class Gen_004b5a50 { public: void *m(int); };
class Gen_004b5a70 { public: void m(); };
class BfmeC1040 { public: int bfmeGo1040C(); };
struct Rva00790970Adapter {
 GameWindow *window;
 Rva00790970Adapter(GameWindow *w) { ((Gen_004b5a50 *)this)->m((int)w); }
 ~Rva00790970Adapter() { ((Gen_004b5a70 *)this)->m(); }
 int selected() { return ((BfmeC1040 *)this)->bfmeGo1040C(); }
};
struct Rva00790970Combo { int m_00; GameWindow *m_04,*m_08; };
struct Rva00790970Cell { int m_00; Color m_04; const Image *m_08; int m_0c,m_10,m_14; };
struct Rva00790970Entry { int m_00,m_04; Rva00790970Cell *m_08; };
struct Rva00790970List { char m_00[0x18]; Rva00790970Entry *m_18; };
void W3DGadgetImageComboBoxDraw(GameWindow *window,WinInstanceData *instData) {
 ICoord2D position;
 GameWindow *list;
 ICoord2D size;
 window->winGetScreenPosition(&position.x,&position.y);
 window->winGetSize(&size.x,&size.y);
 Rva00790970Adapter combo(window);
 int selected=combo.selected();
 if(selected>=0) {
  list=((Rva00790970Combo *)combo.window->winGetUserData())->m_08;
  Rva00790970Entry *entry=&((Rva00790970List *)((Rva00790970Combo *)combo.window->winGetUserData())->m_08->winGetUserData())->m_18[selected];
  int width=entry->m_08->m_10;
  const Image *image=entry->m_08->m_08;
  int height=entry->m_08->m_14;
  if(width<0) width=image->getImageWidth();
  if(height<0) height=image->getImageHeight();
  if(!(list->winGetStatus()&0x10)) {
   int w,h;
   list->winGetSize(&w,&h);
   size.y-=h;
  }
  ICoord2D button={0,0};
  if(!((Rva00790970Combo *)combo.window->winGetUserData())->m_04->winIsHidden()) {
   GameWindow *buttonWindow=((Rva00790970Combo *)combo.window->winGetUserData())->m_04;
   buttonWindow->winGetSize(&button.x,&button.y);
  }
  ICoord2D start,end;
  start.y=(size.y-height)/2+position.y;
  start.x=(2*position.x-button.x-width+size.x)/2;
  end.x=start.x+width;
  end.y=start.y+height;
  TheWindowManager->winDrawImage(image,start.x,start.y,end.x,end.y,entry->m_08->m_04);
 }
}
