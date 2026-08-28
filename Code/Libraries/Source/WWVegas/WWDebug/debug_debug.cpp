// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
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

/////////////////////////////////////////////////////////////////////////EA-V1
// $File: //depot/GeneralsMD/Staging/code/Libraries/Source/debug/debug_debug.cpp $
// $Author: mhoffe $
// $Revision: #2 $
// $DateTime: 2003/07/09 10:57:23 $
//
// �2003 Electronic Arts
//
// Debug class implementation
//////////////////////////////////////////////////////////////////////////////
#include "_pch.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <new>      // needed for placement new prototype

// a little dummy variable that makes the linker actually include
// us...
extern "C" bool __DebugIncludeInLink1;
bool __DebugIncludeInLink1;

// This part is a little tricky (and not portable to other compilers).
// MSVC initializes all static C++ variables by calling a list of 
// function pointers contained in data segments called .CRT$XCA to
// .CRT$XCZ. We jam in our own two functions at the very beginning
// and end of this list (B and Y respectively since the A and Z segments
// contain list delimiters).
#pragma data_seg(".CRT$XCB")
void *Debug::PreStatic=&Debug::PreStaticInit;
#pragma data_seg(".CRT$XCY")
void *Debug::PostStatic=&Debug::PostStaticInit;
#pragma data_seg()

// ??0LogDescription@@ present-unmatched
Debug::LogDescription::LogDescription(const char *fileOrGroup, const char *description)
{
  Debug::Instance.AddLogGroup(fileOrGroup,description);
}

// our global Debug instance
Debug Debug::Instance;

// more class static members
unsigned Debug::curStackFrame;

// this constructor is empty on purpose because all construction
// work is done in PreStaticInit (and some in PostStaticInit)
// ??0Debug@@AAE@XZ present-unmatched
Debug::Debug(void)
{
  // do not put any code in here (but it's good for keeping module global todo's)
  /// @todo what about frame based logging?
  /// @todo have new DLOG with category, add DWARN, DPERF, DERR etc. based on that,
  ///       make it possible to enable/disable categories by adding category to log ID
}

// ?PreStaticInit@Debug@@CAXXZ present-unmatched
void Debug::PreStaticInit(void)
{
  // do not change any member variables that have constructors
  // because they are not constructed yet!

  // make sure this function gets called on exit
  // (we might still have to call it manually if there's
  // an exception and we're not calling exit)
  atexit(StaticExit);

  // init vars
  Instance.hrTranslators=NULL;
  Instance.numHrTranslators=0;
  Instance.firstIOFactory=NULL;
  Instance.firstCmdGroup=NULL;
  memset(Instance.frameHash,0,sizeof(Instance.frameHash));
  Instance.nextUnusedFrameHash=NULL;
  Instance.numAvailableFrameHash=0;
  Instance.firstLogGroup=NULL;
  memset(Instance.ioBuffer,0,sizeof(Instance.ioBuffer));
  Instance.curType=DebugIOInterface::StringType::MAX;
  *Instance.curSource=0;
  Instance.disableAssertsEtc=0;
  Instance.curFrameEntry=NULL;
  Instance.firstPatternEntry=NULL;
  Instance.lastPatternEntry=NULL;
  *Instance.curCommandGroup=0;
  Instance.alwaysFlush=false;
  Instance.timeStamp=false;
  Instance.m_radix=10;
  Instance.m_fillChar=' ';
  
  /// install exception handler
  SetUnhandledExceptionFilter(DebugExceptionhandler::ExceptionFilter);
}

// ?PostStaticInit@Debug@@CAXXZ matched 841 bytes (Open-BFME5)
__declspec(naked) void Debug::PostStaticInit(void)
{
  __asm
  {
  __emit 0x55;
  __emit 0x8b;
  __emit 0xec;
  __emit 0x6a;
  __emit 0xff;
  __emit 0x68;
  __emit 0x21;
  __emit 0x6a;
  __emit 0x05;
  __emit 0x01;
  __emit 0x64;
  __emit 0xa1;
  __emit 0x00;
  __emit 0x00;
  __emit 0x00;
  __emit 0x00;
  __emit 0x50;
  __emit 0x64;
  __emit 0x89;
  __emit 0x25;
  __emit 0x00;
  __emit 0x00;
  __emit 0x00;
  __emit 0x00;
  __emit 0x81;
  __emit 0xec;
  __emit 0x0c;
  __emit 0x0a;
  __emit 0x00;
  __emit 0x00;
  __emit 0xa0;
  __emit 0x7a;
  __emit 0x6e;
  __emit 0x33;
  __emit 0x01;
  __emit 0x84;
  __emit 0xc0;
  __emit 0x0f;
  __emit 0x85;
  __emit 0x10;
  __emit 0x03;
  __emit 0x00;
  __emit 0x00;
  __emit 0x8b;
  __emit 0x0d;
  __emit 0x5c;
  __emit 0x6e;
  __emit 0x33;
  __emit 0x01;
  __emit 0x8b;
  __emit 0x01;
  __emit 0x53;
  __emit 0xc6;
  __emit 0x05;
  __emit 0x7a;
  __emit 0x6e;
  __emit 0x33;
  __emit 0x01;
  __emit 0x01;
  __emit 0xff;
  __emit 0x50;
  __emit 0x58;
  __emit 0x8b;
  __emit 0x0d;
  __emit 0x5c;
  __emit 0x6e;
  __emit 0x33;
  __emit 0x01;
  __emit 0x8b;
  __emit 0x11;
  __emit 0x68;
  __emit 0x40;
  __emit 0x15;
  __emit 0xc9;
  __emit 0x00;
  __emit 0x68;
  __emit 0x4c;
  __emit 0x33;
  __emit 0x13;
  __emit 0x01;
  __emit 0x68;
  __emit 0x48;
  __emit 0x33;
  __emit 0x13;
  __emit 0x01;
  __emit 0xff;
  __emit 0x92;
  __emit 0x80;
  __emit 0x00;
  __emit 0x00;
  __emit 0x00;
  __emit 0x8b;
  __emit 0x0d;
  __emit 0x5c;
  __emit 0x6e;
  __emit 0x33;
  __emit 0x01;
  __emit 0x8b;
  __emit 0x01;
  __emit 0x68;
  __emit 0x20;
  __emit 0x04;
  __emit 0xc9;
  __emit 0x00;
  __emit 0x68;
  __emit 0x34;
  __emit 0x33;
  __emit 0x13;
  __emit 0x01;
  __emit 0x68;
  __emit 0x2c;
  __emit 0x33;
  __emit 0x13;
  __emit 0x01;
  __emit 0xff;
  __emit 0x90;
  __emit 0x80;
  __emit 0x00;
  __emit 0x00;
  __emit 0x00;
  __emit 0x8b;
  __emit 0x0d;
  __emit 0x5c;
  __emit 0x6e;
  __emit 0x33;
  __emit 0x01;
  __emit 0x8b;
  __emit 0x11;
  __emit 0x68;
  __emit 0x00;
  __emit 0xfe;
  __emit 0xc8;
  __emit 0x00;
  __emit 0x68;
  __emit 0x14;
  __emit 0x33;
  __emit 0x13;
  __emit 0x01;
  __emit 0x68;
  __emit 0x10;
  __emit 0x33;
  __emit 0x13;
  __emit 0x01;
  __emit 0xff;
  __emit 0x92;
  __emit 0x80;
  __emit 0x00;
  __emit 0x00;
  __emit 0x00;
  __emit 0x8b;
  __emit 0x0d;
  __emit 0x5c;
  __emit 0x6e;
  __emit 0x33;
  __emit 0x01;
  __emit 0x8b;
  __emit 0x01;
  __emit 0x68;
  __emit 0x10;
  __emit 0xfa;
  __emit 0xc8;
  __emit 0x00;
  __emit 0x68;
  __emit 0xf4;
  __emit 0x32;
  __emit 0x13;
  __emit 0x01;
  __emit 0x68;
  __emit 0xf0;
  __emit 0x32;
  __emit 0x13;
  __emit 0x01;
  __emit 0xff;
  __emit 0x90;
  __emit 0x80;
  __emit 0x00;
  __emit 0x00;
  __emit 0x00;
  __emit 0x6a;
  __emit 0x04;
  __emit 0xe8;
  __emit 0x17;
  __emit 0x3b;
  __emit 0x00;
  __emit 0x00;
  __emit 0x83;
  __emit 0xc4;
  __emit 0x04;
  __emit 0x89;
  __emit 0x45;
  __emit 0xf0;
  __emit 0x89;
  __emit 0x45;
  __emit 0xec;
  __emit 0x33;
  __emit 0xdb;
  __emit 0x89;
  __emit 0x5d;
  __emit 0xfc;
  __emit 0x3b;
  __emit 0xc3;
  __emit 0x74;
  __emit 0x09;
  __emit 0x8b;
  __emit 0xc8;
  __emit 0xe8;
  __emit 0x4e;
  __emit 0xe5;
  __emit 0xff;
  __emit 0xff;
  __emit 0xeb;
  __emit 0x02;
  __emit 0x33;
  __emit 0xc0;
  __emit 0xc7;
  __emit 0x45;
  __emit 0xfc;
  __emit 0xff;
  __emit 0xff;
  __emit 0xff;
  __emit 0xff;
  __emit 0x8b;
  __emit 0x0d;
  __emit 0x5c;
  __emit 0x6e;
  __emit 0x33;
  __emit 0x01;
  __emit 0x8b;
  __emit 0x11;
  __emit 0x50;
  __emit 0x68;
  __emit 0xe8;
  __emit 0x32;
  __emit 0x13;
  __emit 0x01;
  __emit 0xff;
  __emit 0x92;
  __emit 0x84;
  __emit 0x00;
  __emit 0x00;
  __emit 0x00;
  __emit 0x68;
  __emit 0x00;
  __emit 0x08;
  __emit 0x00;
  __emit 0x00;
  __emit 0x8d;
  __emit 0x85;
  __emit 0xe8;
  __emit 0xf5;
  __emit 0xff;
  __emit 0xff;
  __emit 0x50;
  __emit 0x68;
  __emit 0xd4;
  __emit 0x32;
  __emit 0x13;
  __emit 0x01;
  __emit 0xff;
  __emit 0x15;
  __emit 0x94;
  __emit 0x8d;
  __emit 0x35;
  __emit 0x01;
  __emit 0x85;
  __emit 0xc0;
  __emit 0x75;
  __emit 0x13;
  __emit 0x68;
  __emit 0x00;
  __emit 0x08;
  __emit 0x00;
  __emit 0x00;
  __emit 0x8d;
  __emit 0x8d;
  __emit 0xe8;
  __emit 0xf5;
  __emit 0xff;
  __emit 0xff;
  __emit 0x51;
  __emit 0x53;
  __emit 0xff;
  __emit 0x15;
  __emit 0xc0;
  __emit 0x8d;
  __emit 0x35;
  __emit 0x01;
  __emit 0x8d;
  __emit 0x95;
  __emit 0xe8;
  __emit 0xf5;
  __emit 0xff;
  __emit 0xff;
  __emit 0x6a;
  __emit 0x2e;
  __emit 0x52;
  __emit 0xff;
  __emit 0x15;
  __emit 0xc8;
  __emit 0x94;
  __emit 0x35;
  __emit 0x01;
  __emit 0x83;
  __emit 0xc4;
  __emit 0x08;
  __emit 0x3b;
  __emit 0xc3;
  __emit 0x74;
  __emit 0x11;
  __emit 0x8b;
  __emit 0x0d;
  __emit 0xcc;
  __emit 0x32;
  __emit 0x13;
  __emit 0x01;
  __emit 0x89;
  __emit 0x08;
  __emit 0x8b;
  __emit 0x15;
  __emit 0xd0;
  __emit 0x32;
  __emit 0x13;
  __emit 0x01;
  __emit 0x89;
  __emit 0x50;
  __emit 0x04;
  __emit 0x56;
  __emit 0x57;
  __emit 0x8b;
  __emit 0x3d;
  __emit 0xe8;
  __emit 0x8c;
  __emit 0x35;
  __emit 0x01;
  __emit 0x53;
  __emit 0x68;
  __emit 0x80;
  __emit 0x00;
  __emit 0x00;
  __emit 0x00;
  __emit 0x6a;
  __emit 0x03;
  __emit 0x53;
  __emit 0x6a;
  __emit 0x01;
  __emit 0x68;
  __emit 0x00;
  __emit 0x00;
  __emit 0x00;
  __emit 0x80;
  __emit 0x8d;
  __emit 0x85;
  __emit 0xe8;
  __emit 0xf5;
  __emit 0xff;
  __emit 0xff;
  __emit 0x50;
  __emit 0xff;
  __emit 0xd7;
  __emit 0x8b;
  __emit 0xf0;
  __emit 0x83;
  __emit 0xfe;
  __emit 0xff;
  __emit 0x75;
  __emit 0x22;
  __emit 0x53;
  __emit 0x68;
  __emit 0x80;
  __emit 0x00;
  __emit 0x00;
  __emit 0x00;
  __emit 0x6a;
  __emit 0x03;
  __emit 0x53;
  __emit 0x6a;
  __emit 0x01;
  __emit 0x68;
  __emit 0x00;
  __emit 0x00;
  __emit 0x00;
  __emit 0x80;
  __emit 0x68;
  __emit 0xbc;
  __emit 0x32;
  __emit 0x13;
  __emit 0x01;
  __emit 0xff;
  __emit 0xd7;
  __emit 0x8b;
  __emit 0xf0;
  __emit 0x83;
  __emit 0xfe;
  __emit 0xff;
  __emit 0x0f;
  __emit 0x84;
  __emit 0x9b;
  __emit 0x00;
  __emit 0x00;
  __emit 0x00;
  __emit 0x33;
  __emit 0xff;
  __emit 0x57;
  __emit 0x8d;
  __emit 0x4d;
  __emit 0xf0;
  __emit 0x51;
  __emit 0x68;
  __emit 0x00;
  __emit 0x08;
  __emit 0x00;
  __emit 0x00;
  __emit 0x8d;
  __emit 0x95;
  __emit 0xe8;
  __emit 0xf5;
  __emit 0xff;
  __emit 0xff;
  __emit 0x52;
  __emit 0x56;
  __emit 0x89;
  __emit 0x5d;
  __emit 0xf0;
  __emit 0xff;
  __emit 0x15;
  __emit 0xc4;
  __emit 0x8e;
  __emit 0x35;
  __emit 0x01;
  __emit 0x8b;
  __emit 0x4d;
  __emit 0xf0;
  __emit 0x3b;
  __emit 0xf9;
  __emit 0x75;
  __emit 0x22;
  __emit 0x6a;
  __emit 0x00;
  __emit 0x8d;
  __emit 0x45;
  __emit 0xf0;
  __emit 0x50;
  __emit 0x68;
  __emit 0x00;
  __emit 0x08;
  __emit 0x00;
  __emit 0x00;
  __emit 0x8d;
  __emit 0x8d;
  __emit 0xe8;
  __emit 0xf5;
  __emit 0xff;
  __emit 0xff;
  __emit 0x51;
  __emit 0x56;
  __emit 0xff;
  __emit 0x15;
  __emit 0xc4;
  __emit 0x8e;
  __emit 0x35;
  __emit 0x01;
  __emit 0x8b;
  __emit 0x4d;
  __emit 0xf0;
  __emit 0x33;
  __emit 0xff;
  __emit 0x85;
  __emit 0xc9;
  __emit 0x74;
  __emit 0x22;
  __emit 0x8a;
  __emit 0x84;
  __emit 0x3d;
  __emit 0xe8;
  __emit 0xf5;
  __emit 0xff;
  __emit 0xff;
  __emit 0x3c;
  __emit 0x0a;
  __emit 0x74;
  __emit 0x17;
  __emit 0x3c;
  __emit 0x0d;
  __emit 0x74;
  __emit 0x13;
  __emit 0x81;
  __emit 0xfb;
  __emit 0x00;
  __emit 0x02;
  __emit 0x00;
  __emit 0x00;
  __emit 0x73;
  __emit 0x08;
  __emit 0x88;
  __emit 0x84;
  __emit 0x1d;
  __emit 0xe8;
  __emit 0xfd;
  __emit 0xff;
  __emit 0xff;
  __emit 0x43;
  __emit 0x47;
  __emit 0xeb;
  __emit 0xb8;
  __emit 0x85;
  __emit 0xdb;
  __emit 0x74;
  __emit 0x1f;
  __emit 0x8b;
  __emit 0x0d;
  __emit 0x5c;
  __emit 0x6e;
  __emit 0x33;
  __emit 0x01;
  __emit 0x8d;
  __emit 0x94;
  __emit 0x1d;
  __emit 0xe8;
  __emit 0xfd;
  __emit 0xff;
  __emit 0xff;
  __emit 0x52;
  __emit 0x8d;
  __emit 0x85;
  __emit 0xe8;
  __emit 0xfd;
  __emit 0xff;
  __emit 0xff;
  __emit 0x50;
  __emit 0xe8;
  __emit 0x2a;
  __emit 0xfa;
  __emit 0xff;
  __emit 0xff;
  __emit 0x8b;
  __emit 0x4d;
  __emit 0xf0;
  __emit 0x33;
  __emit 0xdb;
  __emit 0x3b;
  __emit 0xf9;
  __emit 0x74;
  __emit 0x03;
  __emit 0x47;
  __emit 0xeb;
  __emit 0x8e;
  __emit 0x56;
  __emit 0xff;
  __emit 0x15;
  __emit 0xcc;
  __emit 0x8c;
  __emit 0x35;
  __emit 0x01;
  __emit 0xeb;
  __emit 0x56;
  __emit 0xe8;
  __emit 0xba;
  __emit 0x82;
  __emit 0x77;
  __emit 0xff;
  __emit 0x8b;
  __emit 0xf8;
  __emit 0x3b;
  __emit 0xfb;
  __emit 0x74;
  __emit 0x4b;
  __emit 0x8b;
  __emit 0x1d;
  __emit 0x9c;
  __emit 0x94;
  __emit 0x35;
  __emit 0x01;
  __emit 0x8d;
  __emit 0x64;
  __emit 0x24;
  __emit 0x00;
  __emit 0x80;
  __emit 0x3f;
  __emit 0x00;
  __emit 0x74;
  __emit 0x3c;
  __emit 0x6a;
  __emit 0x0a;
  __emit 0x57;
  __emit 0xff;
  __emit 0xd3;
  __emit 0x8b;
  __emit 0xf0;
  __emit 0x83;
  __emit 0xc4;
  __emit 0x08;
  __emit 0x85;
  __emit 0xf6;
  __emit 0x75;
  __emit 0x11;
  __emit 0x8b;
  __emit 0xc7;
  __emit 0x8d;
  __emit 0x50;
  __emit 0x01;
  __emit 0x8a;
  __emit 0x08;
  __emit 0x40;
  __emit 0x84;
  __emit 0xc9;
  __emit 0x75;
  __emit 0xf9;
  __emit 0x2b;
  __emit 0xc2;
  __emit 0x8d;
  __emit 0x34;
  __emit 0x38;
  __emit 0x3b;
  __emit 0xfe;
  __emit 0x74;
  __emit 0x15;
  __emit 0x8b;
  __emit 0x0d;
  __emit 0x5c;
  __emit 0x6e;
  __emit 0x33;
  __emit 0x01;
  __emit 0x56;
  __emit 0x57;
  __emit 0xe8;
  __emit 0xcb;
  __emit 0xf9;
  __emit 0xff;
  __emit 0xff;
  __emit 0x80;
  __emit 0x3e;
  __emit 0x00;
  __emit 0x74;
  __emit 0x07;
  __emit 0x8d;
  __emit 0x7e;
  __emit 0x01;
  __emit 0x85;
  __emit 0xff;
  __emit 0x75;
  __emit 0xbf;
  __emit 0xe8;
  __emit 0x0a;
  __emit 0x1c;
  __emit 0x00;
  __emit 0x00;
  __emit 0x84;
  __emit 0xc0;
  __emit 0x0f;
  __emit 0x84;
  __emit 0xaa;
  __emit 0x00;
  __emit 0x00;
  __emit 0x00;
  __emit 0x8b;
  __emit 0x0d;
  __emit 0x5c;
  __emit 0x6e;
  __emit 0x33;
  __emit 0x01;
  __emit 0x68;
  __emit 0x1c;
  __emit 0x30;
  __emit 0x07;
  __emit 0x01;
  __emit 0x6a;
  __emit 0x06;
  __emit 0x51;
  __emit 0xe8;
  __emit 0xaf;
  __emit 0xf6;
  __emit 0xff;
  __emit 0xff;
  __emit 0x8b;
  __emit 0x0d;
  __emit 0x5c;
  __emit 0x6e;
  __emit 0x33;
  __emit 0x01;
  __emit 0x83;
  __emit 0xc4;
  __emit 0x0c;
  __emit 0xb3;
  __emit 0x3d;
  __emit 0xbe;
  __emit 0x4f;
  __emit 0x00;
  __emit 0x00;
  __emit 0x00;
  __emit 0x8d;
  __emit 0x45;
  __emit 0xe8;
  __emit 0x88;
  __emit 0x5d;
  __emit 0xe8;
  __emit 0x89;
  __emit 0x75;
  __emit 0xec;
  __emit 0x8b;
  __emit 0x11;
  __emit 0x50;
  __emit 0xff;
  __emit 0x52;
  __emit 0x3c;
  __emit 0x8b;
  __emit 0x10;
  __emit 0x68;
  __emit 0x18;
  __emit 0x32;
  __emit 0x13;
  __emit 0x01;
  __emit 0x8b;
  __emit 0xc8;
  __emit 0xff;
  __emit 0x52;
  __emit 0x38;
  __emit 0x8d;
  __emit 0x85;
  __emit 0xe8;
  __emit 0xfe;
  __emit 0xff;
  __emit 0xff;
  __emit 0x68;
  __emit 0x00;
  __emit 0x01;
  __emit 0x00;
  __emit 0x00;
  __emit 0x50;
  __emit 0xe8;
  __emit 0xa3;
  __emit 0x1b;
  __emit 0x00;
  __emit 0x00;
  __emit 0x50;
  __emit 0xff;
  __emit 0x15;
  __emit 0xc0;
  __emit 0x8d;
  __emit 0x35;
  __emit 0x01;
  __emit 0x8b;
  __emit 0x0d;
  __emit 0x5c;
  __emit 0x6e;
  __emit 0x33;
  __emit 0x01;
  __emit 0x8b;
  __emit 0x11;
  __emit 0x68;
  __emit 0xf8;
  __emit 0x31;
  __emit 0x13;
  __emit 0x01;
  __emit 0xff;
  __emit 0x52;
  __emit 0x38;
  __emit 0x8b;
  __emit 0x10;
  __emit 0x8d;
  __emit 0x8d;
  __emit 0xe8;
  __emit 0xfe;
  __emit 0xff;
  __emit 0xff;
  __emit 0x51;
  __emit 0x8b;
  __emit 0xc8;
  __emit 0xff;
  __emit 0x52;
  __emit 0x38;
  __emit 0x8b;
  __emit 0x10;
  __emit 0x68;
  __emit 0x94;
  __emit 0x02;
  __emit 0x08;
  __emit 0x01;
  __emit 0x8b;
  __emit 0xc8;
  __emit 0xff;
  __emit 0x52;
  __emit 0x38;
  __emit 0x8d;
  __emit 0x4d;
  __emit 0xe8;
  __emit 0x88;
  __emit 0x5d;
  __emit 0xe8;
  __emit 0x89;
  __emit 0x75;
  __emit 0xec;
  __emit 0x8b;
  __emit 0x10;
  __emit 0x51;
  __emit 0x8b;
  __emit 0xc8;
  __emit 0xff;
  __emit 0x52;
  __emit 0x3c;
  __emit 0x8b;
  __emit 0x10;
  __emit 0x68;
  __emit 0xe4;
  __emit 0x5c;
  __emit 0x07;
  __emit 0x01;
  __emit 0x8b;
  __emit 0xc8;
  __emit 0xff;
  __emit 0x52;
  __emit 0x38;
  __emit 0x8b;
  __emit 0x0d;
  __emit 0x5c;
  __emit 0x6e;
  __emit 0x33;
  __emit 0x01;
  __emit 0x6a;
  __emit 0x00;
  __emit 0xe8;
  __emit 0x98;
  __emit 0xef;
  __emit 0xff;
  __emit 0xff;
  __emit 0x5f;
  __emit 0x5e;
  __emit 0x5b;
  __emit 0x8b;
  __emit 0x4d;
  __emit 0xf4;
  __emit 0x64;
  __emit 0x89;
  __emit 0x0d;
  __emit 0x00;
  __emit 0x00;
  __emit 0x00;
  __emit 0x00;
  __emit 0x8b;
  __emit 0xe5;
  __emit 0x5d;
  __emit 0xc3;
  }
}

// ?StaticExit@Debug@@CAXXZ present-unmatched
// ?StaticExit@Debug@@CAXXZ present-unmatched
void Debug::StaticExit(void)
{
  // yes, we do leave memory 'leaks' but Win32 will take care of these

  // however, I/O classes must be actively shut down
  if (Instance.curType!=DebugIOInterface::StringType::MAX)
    Instance.FlushOutput();
  for (IOFactoryListEntry *io=Instance.firstIOFactory;io;io=io->next)
    if (io->io)
    {
      io->io->Delete();
      io->io=NULL;
    }

  // and command group interfaces...
  for (CmdInterfaceListEntry *cmd=Instance.firstCmdGroup;cmd;cmd=cmd->next)
    if (cmd->cmdif)
    {
      cmd->cmdif->Delete();
      cmd->cmdif=NULL;
    }
}

Debug& Debug::operator<<(RepeatChar &c)
{
  if (c.m_count>=10)
  {
    char help[10];
    memset(help,c.m_char,10);
    while ((c.m_count-=10)>=0)
      AddOutput(help,10);
  }
  while (c.m_count-->0)
    AddOutput(&c.m_char,1);
  return *this;
}

Debug::Format::Format(const char *format, ...)
{
  va_list va;
  va_start(va,format);
  _vsnprintf(m_buffer,sizeof(m_buffer)-1,format,va);
  va_end(va);
}

// ??1Debug@@QAE@XZ present-unmatched
Debug::~Debug()
{
  // again, do not put any code in here
}

static void LocalSETranslator(unsigned, struct _EXCEPTION_POINTERS *pExPtrs)
{
  // simply call our regular exception handler
  DebugExceptionhandler::ExceptionFilter(pExPtrs);
}

void Debug::InstallExceptionHandler(void)
{
  _set_se_translator(LocalSETranslator);
}

// ?SkipNext@Debug@@SA_NXZ present-unmatched
bool Debug::SkipNext(void)
{
  // this is typically set while an assertion
  // is running
  if (Instance.disableAssertsEtc)
    return true;

  // do not implement this function inline, we do need
  // a valid frame pointer here!
  unsigned help;
  _asm 
  {
    mov eax,[ebp+4]   // return address
    mov help,eax
  };
  curStackFrame=help;

  // do we know if to skip the following code?
  FrameHashEntry *e=Instance.LookupFrame(curStackFrame);
  if (!e||                // unknown frame, will be added later
       e->status==NoSkip) // frame known but active
    return false;

  // status is unknown, must update
  if (e->status==Unknown)
    Instance.UpdateFrameStatus(*e);

  // now we now wether to skip or not
  return e->status==Skip;
}

// byte-exact reconstruction: Code/Libraries/Source/WWVegas/WWDebug/DebugAssertBeginThunk.cpp
// ?AssertBegin@Debug@@SAAAV1@PBDH0@Z present-unmatched
Debug& Debug::AssertBegin(const char *file, int line, const char *expr)
{
  // avoid infinite recursion...
  ++Instance.disableAssertsEtc;

  // anything to flush first?
  if (Instance.curType!=DebugIOInterface::StringType::MAX)
    Instance.FlushOutput();

  // set new output
  __ASSERT(Instance.curFrameEntry==NULL);
  Instance.curFrameEntry=Instance.GetFrameEntry(curStackFrame,FrameTypeAssert,file,line);
  if (Instance.curFrameEntry->status==NoSkip)
  {
    Instance.StartOutput(DebugIOInterface::StringType::Assert,"%s(%i)",
                  Instance.curFrameEntry->fileOrGroup,
                  Instance.curFrameEntry->line);
    ++Instance.curFrameEntry->hits;

    // if there is a \code\ section in the filename truncate
    // everything before that (including \code\)
    const char *p=strstr(file,"\\code\\");
    p=p?p+6:file;

    Instance << "\n" << RepeatChar('=',80) << "\nAssertion failed in " << p << ", line " << line 
             << ",\nexpression " << expr;
  }

  return Instance;
}

// ?AssertDone@Debug@@QAE_NXZ present-unmatched
bool Debug::AssertDone(void)
{
  --disableAssertsEtc;

  // did we have an active assertion?
  if (curType==DebugIOInterface::StringType::Assert)
  {
    __ASSERT(curFrameEntry!=NULL);

    // hit info?
    if (curFrameEntry->hits>1)
      (*this) << " (hit #" << curFrameEntry->hits << ")";

    // need CR?
    if (!ioBuffer[curType].lastWasCR)
      operator<<("\n");

    // yes, duplicate message
    const char *addInfo="\nPress 'abort' to abort the program,\n"
                        "'retry' for breaking into the debugger, or\n"
                        "'ignore' for ignoring this assertion for the\n"
                        "time being (stops logging this assertion as well).";
    char *help=(char *)DebugAllocMemory(ioBuffer[curType].used+strlen(addInfo)+1);
    strcpy(help,ioBuffer[curType].buffer+82);
    strcat(help,addInfo);
    
    // First hit? Then do a stack trace
    if (curFrameEntry->hits==1)
    {
      DebugStackwalk::Signature sig;
      if (m_stackWalk.StackWalk(sig))
        (*this) << sig;
    }

    // ... and flush out
    operator<<("\n\n");
    FlushOutput();

    // show dialog box only if running windowed
    if (IsWindowed())
    {
      /// @todo replace MessageBox with custom dialog w/ 4 options: abort, skip 1, skip all, break

      // now display message, wait for user input
      int result=MessageBox(NULL,help,"Assertion failed",
                            MB_ABORTRETRYIGNORE|MB_ICONSTOP|MB_TASKMODAL|MB_SETFOREGROUND);
      switch(result)
      {
        case IDABORT:
          curFrameEntry=NULL;
          exit(1);
          break;
        case IDIGNORE:
          {
            // build 'pattern'
            char help[200];
            __ASSERT(strlen(curFrameEntry->fileOrGroup)<190);
            wsprintf(help,"%s(%i)",curFrameEntry->fileOrGroup,
                                   curFrameEntry->line);
            AddPatternEntry(FrameTypeAssert,false,help);
            curFrameEntry->status=Skip;
          }
          break;
        case IDRETRY:
          _asm int 0x03
          break;
        default:
          ((void)0);
      }
    }
    else 
    {
      // we're running fullscreen

      // hit too often?
      if (curFrameEntry->hits==MAX_CHECK_HITS)
      {
        // yup, turn off then
        StartOutput(DebugIOInterface::StringType::Other,"");
        Instance << "Assert hit too often - turning check off.\n";
        FlushOutput();

        // build 'pattern'
        char help[200];
        __ASSERT(strlen(curFrameEntry->fileOrGroup)<190);
        wsprintf(help,"%s(%i)",curFrameEntry->fileOrGroup,
                               curFrameEntry->line);
        AddPatternEntry(FrameTypeAssert,false,help);

        curFrameEntry->status=Skip;
      }
    }
  }

  curFrameEntry=NULL;
  return false;
}

// ?CheckBegin@Debug@@SAAAV1@PBDH0@Z present-unmatched
Debug& Debug::CheckBegin(const char *file, int line, const char *expr)
{
  // avoid infinite recursion...
  ++Instance.disableAssertsEtc;

  // anything to flush first?
  if (Instance.curType!=DebugIOInterface::StringType::MAX)
    Instance.FlushOutput();

  // set new output
  __ASSERT(Instance.curFrameEntry==NULL);
  Instance.curFrameEntry=Instance.GetFrameEntry(curStackFrame,FrameTypeCheck,file,line);
  if (Instance.curFrameEntry->status==NoSkip)
  {
    ++Instance.curFrameEntry->hits;
    Instance.StartOutput(DebugIOInterface::StringType::Check,"%s(%i)",
                  Instance.curFrameEntry->fileOrGroup,
                  Instance.curFrameEntry->line);

    // if there is a \code\ section in the filename truncate
    // everything before that (including \code\)
    const char *p=strstr(file,"\\code\\");
    p=p?p+6:file;

    Instance << "\n" << RepeatChar('=',80) << "\nCheck failed in " << p << ", line " << line 
             << ",\nexpression " << expr;
  }

  return Instance;
}

// ?CheckDone@Debug@@QAE_NXZ present-unmatched
bool Debug::CheckDone(void)
{
  --disableAssertsEtc;

  // did we have an active check?
  if (curType==DebugIOInterface::StringType::Check)
  {
    __ASSERT(curFrameEntry!=NULL);

    // hit info?
    if (curFrameEntry->hits>1)
      (*this) << " (hit #" << curFrameEntry->hits << ")";

    // need CR?
    if (!ioBuffer[curType].lastWasCR)
      operator<<("\n");

    // First hit? Then do a stack trace
    if (curFrameEntry->hits==1)
    {
      DebugStackwalk::Signature sig;
      if (m_stackWalk.StackWalk(sig))
        (*this) << sig;
    }

    // flush out
    operator<<("\n\n");
    FlushOutput();

    // hit too often?
    if (curFrameEntry->hits==MAX_CHECK_HITS)
    {
      // yup, turn off then
      StartOutput(DebugIOInterface::StringType::Other,"");
      Instance << "Check hit too often - turning check off.\n";
      FlushOutput();

      // build 'pattern'
      char help[200];
      __ASSERT(strlen(curFrameEntry->fileOrGroup)<190);
      wsprintf(help,"%s(%i)",curFrameEntry->fileOrGroup,
                             curFrameEntry->line);
      AddPatternEntry(FrameTypeCheck,false,help);

      curFrameEntry->status=Skip;
    }
  }

  curFrameEntry=NULL;
  return false;
}

// ?LogBegin@Debug@@SAAAV1@PBD@Z present-unmatched
Debug& Debug::LogBegin(const char *fileOrGroup)
{
  // avoid infinite recursion...
  ++Instance.disableAssertsEtc;

  // anything to flush first?
  if (Instance.curType!=DebugIOInterface::StringType::MAX&&
      Instance.curType!=DebugIOInterface::StringType::Log)
    Instance.FlushOutput();

  // set new output
  __ASSERT(Instance.curFrameEntry==NULL);
  Instance.curFrameEntry=Instance.GetFrameEntry(curStackFrame,FrameTypeLog,fileOrGroup,0);
  if (Instance.curFrameEntry->status==NoSkip)
  {
    ++Instance.curFrameEntry->hits;

    // we're doing all this extra work so that DLOGs can be spread across
    // multiple calls
    if (Instance.curType==DebugIOInterface::StringType::Log&&
        strcmp(Instance.curSource,Instance.curFrameEntry->fileOrGroup))
      Instance.FlushOutput();

    if (Instance.curType!=DebugIOInterface::StringType::Log)
      Instance.StartOutput(DebugIOInterface::StringType::Log,"%s",
                    Instance.curFrameEntry->fileOrGroup);
  }
  else if (Instance.curType!=DebugIOInterface::StringType::MAX)
    Instance.FlushOutput();
  
  return Instance;
}

// ?LogDone@Debug@@QAE_NXZ present-unmatched
bool Debug::LogDone(void)
{
  --disableAssertsEtc;

  // we're not flushing here on intention!

  curFrameEntry=NULL;
  return false;
}

// ?CrashBegin@Debug@@SAAAV1@PBDH@Z present-unmatched
Debug& Debug::CrashBegin(const char *file, int line)
{
  // avoid infinite recursion...
  ++Instance.disableAssertsEtc;

  // anything to flush first?
  if (Instance.curType!=DebugIOInterface::StringType::MAX)
    Instance.FlushOutput();

  // set new output
  __ASSERT(Instance.curFrameEntry==NULL);
  Instance.curFrameEntry=Instance.GetFrameEntry(curStackFrame,FrameTypeAssert,file,line);
  if (Instance.curFrameEntry->status==NoSkip)
  {
    Instance.StartOutput(DebugIOInterface::StringType::Crash,"%s(%i)",file,line);
    ++Instance.curFrameEntry->hits;

    Instance << "\n" << RepeatChar('=',80) << "\n";
    if (file)
    {
      // if there is a \code\ section in the filename truncate
      // everything before that (including \code\)
      const char *p=strstr(file,"\\code\\");
      p=p?p+6:file;

      Instance << "Crash in " << p << ", line " << line 
               << ", reason:\n";
    }
  }

  return Instance;
}

// NOTE ?CrashDone@Debug@@QAE_N_N@Z matched 1353 bytes (Open-BFME5)
__declspec(naked) bool Debug::CrashDone(bool)
{
  __asm
  {
    __emit 0x55;
    __emit 0x8b;
    __emit 0xec;
    __emit 0x6a;
    __emit 0xff;
    __emit 0x68;
    __emit 0xc0;
    __emit 0x34;
    __emit 0x13;
    __emit 0x01;
    __emit 0x68;
    __emit 0x50;
    __emit 0x6c;
    __emit 0xdf;
    __emit 0x00;
    __emit 0x64;
    __emit 0xa1;
    __emit 0x00;
    __emit 0x00;
    __emit 0x00;
    __emit 0x00;
    __emit 0x50;
    __emit 0x64;
    __emit 0x89;
    __emit 0x25;
    __emit 0x00;
    __emit 0x00;
    __emit 0x00;
    __emit 0x00;
    __emit 0x81;
    __emit 0xec;
    __emit 0x78;
    __emit 0x06;
    __emit 0x00;
    __emit 0x00;
    __emit 0x53;
    __emit 0x56;
    __emit 0x57;
    __emit 0x89;
    __emit 0x65;
    __emit 0xe8;
    __emit 0x8b;
    __emit 0xd9;
    __emit 0x89;
    __emit 0x5d;
    __emit 0xd8;
    __emit 0x83;
    __emit 0xbb;
    __emit 0xf4;
    __emit 0x9c;
    __emit 0x00;
    __emit 0x00;
    __emit 0x02;
    __emit 0x0f;
    __emit 0x85;
    __emit 0x94;
    __emit 0x03;
    __emit 0x00;
    __emit 0x00;
    __emit 0x8b;
    __emit 0x83;
    __emit 0xfc;
    __emit 0x9d;
    __emit 0x00;
    __emit 0x00;
    __emit 0x8b;
    __emit 0x48;
    __emit 0x14;
    __emit 0x8b;
    __emit 0x75;
    __emit 0x08;
    __emit 0x83;
    __emit 0xf9;
    __emit 0x01;
    __emit 0x7e;
    __emit 0x2e;
    __emit 0x83;
    __emit 0xfe;
    __emit 0x02;
    __emit 0x74;
    __emit 0x29;
    __emit 0x8b;
    __emit 0x13;
    __emit 0x68;
    __emit 0x20;
    __emit 0x34;
    __emit 0x13;
    __emit 0x01;
    __emit 0x8b;
    __emit 0xcb;
    __emit 0xff;
    __emit 0x52;
    __emit 0x38;
    __emit 0x8b;
    __emit 0x10;
    __emit 0x8b;
    __emit 0x8b;
    __emit 0xfc;
    __emit 0x9d;
    __emit 0x00;
    __emit 0x00;
    __emit 0x8b;
    __emit 0x49;
    __emit 0x14;
    __emit 0x51;
    __emit 0x8b;
    __emit 0xc8;
    __emit 0xff;
    __emit 0x52;
    __emit 0x34;
    __emit 0x8b;
    __emit 0x10;
    __emit 0x68;
    __emit 0x04;
    __emit 0x28;
    __emit 0x08;
    __emit 0x01;
    __emit 0x8b;
    __emit 0xc8;
    __emit 0xff;
    __emit 0x52;
    __emit 0x38;
    __emit 0x8b;
    __emit 0x83;
    __emit 0xf4;
    __emit 0x9c;
    __emit 0x00;
    __emit 0x00;
    __emit 0x05;
    __emit 0xc9;
    __emit 0x09;
    __emit 0x00;
    __emit 0x00;
    __emit 0xc1;
    __emit 0xe0;
    __emit 0x04;
    __emit 0x80;
    __emit 0x3c;
    __emit 0x18;
    __emit 0x00;
    __emit 0x75;
    __emit 0x0c;
    __emit 0x8b;
    __emit 0x13;
    __emit 0x68;
    __emit 0x94;
    __emit 0x02;
    __emit 0x08;
    __emit 0x01;
    __emit 0x8b;
    __emit 0xcb;
    __emit 0xff;
    __emit 0x52;
    __emit 0x38;
    __emit 0x83;
    __emit 0xfe;
    __emit 0x01;
    __emit 0xc7;
    __emit 0x45;
    __emit 0xe0;
    __emit 0xe0;
    __emit 0x33;
    __emit 0x13;
    __emit 0x01;
    __emit 0x74;
    __emit 0x07;
    __emit 0xc7;
    __emit 0x45;
    __emit 0xe0;
    __emit 0x1c;
    __emit 0x30;
    __emit 0x07;
    __emit 0x01;
    __emit 0x8a;
    __emit 0x83;
    __emit 0x6d;
    __emit 0x9e;
    __emit 0x00;
    __emit 0x00;
    __emit 0x84;
    __emit 0xc0;
    __emit 0x75;
    __emit 0x05;
    __emit 0x83;
    __emit 0xfe;
    __emit 0x02;
    __emit 0x75;
    __emit 0x05;
    __emit 0x83;
    __emit 0xfe;
    __emit 0x01;
    __emit 0x75;
    __emit 0x36;
    __emit 0xc7;
    __emit 0x85;
    __emit 0x78;
    __emit 0xf9;
    __emit 0xff;
    __emit 0xff;
    __emit 0x00;
    __emit 0x00;
    __emit 0x00;
    __emit 0x00;
    __emit 0x83;
    __emit 0xfe;
    __emit 0x01;
    __emit 0x0f;
    __emit 0x94;
    __emit 0xc0;
    __emit 0x50;
    __emit 0x6a;
    __emit 0x00;
    __emit 0x8d;
    __emit 0x8d;
    __emit 0x78;
    __emit 0xf9;
    __emit 0xff;
    __emit 0xff;
    __emit 0x51;
    __emit 0xe8;
    __emit 0xc0;
    __emit 0x11;
    __emit 0x00;
    __emit 0x00;
    __emit 0x83;
    __emit 0xc4;
    __emit 0x0c;
    __emit 0x85;
    __emit 0xc0;
    __emit 0x74;
    __emit 0x10;
    __emit 0x8d;
    __emit 0x95;
    __emit 0x78;
    __emit 0xf9;
    __emit 0xff;
    __emit 0xff;
    __emit 0x52;
    __emit 0x53;
    __emit 0xe8;
    __emit 0xec;
    __emit 0x0f;
    __emit 0x00;
    __emit 0x00;
    __emit 0x83;
    __emit 0xc4;
    __emit 0x08;
    __emit 0x8b;
    __emit 0x45;
    __emit 0xe0;
    __emit 0x8d;
    __emit 0x50;
    __emit 0x01;
    __emit 0x8d;
    __emit 0x49;
    __emit 0x00;
    __emit 0x8a;
    __emit 0x08;
    __emit 0x40;
    __emit 0x84;
    __emit 0xc9;
    __emit 0x75;
    __emit 0xf9;
    __emit 0x2b;
    __emit 0xc2;
    __emit 0x8b;
    __emit 0x8b;
    __emit 0xf4;
    __emit 0x9c;
    __emit 0x00;
    __emit 0x00;
    __emit 0xc1;
    __emit 0xe1;
    __emit 0x04;
    __emit 0x8b;
    __emit 0x94;
    __emit 0x19;
    __emit 0x88;
    __emit 0x9c;
    __emit 0x00;
    __emit 0x00;
    __emit 0x8d;
    __emit 0x44;
    __emit 0x02;
    __emit 0x01;
    __emit 0x50;
    __emit 0xe8;
    __emit 0xad;
    __emit 0x2e;
    __emit 0x00;
    __emit 0x00;
    __emit 0x83;
    __emit 0xc4;
    __emit 0x04;
    __emit 0x8b;
    __emit 0xf8;
    __emit 0x89;
    __emit 0x7d;
    __emit 0xdc;
    __emit 0x8b;
    __emit 0x8b;
    __emit 0xf4;
    __emit 0x9c;
    __emit 0x00;
    __emit 0x00;
    __emit 0xc1;
    __emit 0xe1;
    __emit 0x04;
    __emit 0x8b;
    __emit 0x8c;
    __emit 0x19;
    __emit 0x84;
    __emit 0x9c;
    __emit 0x00;
    __emit 0x00;
    __emit 0x83;
    __emit 0xc1;
    __emit 0x54;
    __emit 0x8b;
    __emit 0xf7;
    __emit 0x8a;
    __emit 0x11;
    __emit 0x88;
    __emit 0x16;
    __emit 0x41;
    __emit 0x46;
    __emit 0x84;
    __emit 0xd2;
    __emit 0x75;
    __emit 0xf6;
    __emit 0x8b;
    __emit 0x4d;
    __emit 0xe0;
    __emit 0x8b;
    __emit 0xd1;
    __emit 0x90;
    __emit 0x8a;
    __emit 0x01;
    __emit 0x41;
    __emit 0x84;
    __emit 0xc0;
    __emit 0x75;
    __emit 0xf9;
    __emit 0x2b;
    __emit 0xca;
    __emit 0x8b;
    __emit 0xf2;
    __emit 0x8b;
    __emit 0xd1;
    __emit 0x4f;
    __emit 0x8b;
    __emit 0xff;
    __emit 0x8a;
    __emit 0x47;
    __emit 0x01;
    __emit 0x47;
    __emit 0x84;
    __emit 0xc0;
    __emit 0x75;
    __emit 0xf8;
    __emit 0x8b;
    __emit 0xca;
    __emit 0xc1;
    __emit 0xe9;
    __emit 0x02;
    __emit 0xf3;
    __emit 0xa5;
    __emit 0x8b;
    __emit 0xca;
    __emit 0x83;
    __emit 0xe1;
    __emit 0x03;
    __emit 0xf3;
    __emit 0xa4;
    __emit 0x8b;
    __emit 0x13;
    __emit 0x68;
    __emit 0xe4;
    __emit 0x5c;
    __emit 0x07;
    __emit 0x01;
    __emit 0x8b;
    __emit 0xcb;
    __emit 0xff;
    __emit 0x52;
    __emit 0x38;
    __emit 0x6a;
    __emit 0x01;
    __emit 0x8b;
    __emit 0xcb;
    __emit 0xe8;
    __emit 0x45;
    __emit 0xe5;
    __emit 0xff;
    __emit 0xff;
    __emit 0x8b;
    __emit 0x45;
    __emit 0x08;
    __emit 0x33;
    __emit 0xff;
    __emit 0x3b;
    __emit 0xc7;
    __emit 0x0f;
    __emit 0x85;
    __emit 0xab;
    __emit 0x01;
    __emit 0x00;
    __emit 0x00;
    __emit 0x8b;
    __emit 0x0d;
    __emit 0x5c;
    __emit 0x6e;
    __emit 0x33;
    __emit 0x01;
    __emit 0x8b;
    __emit 0x01;
    __emit 0xff;
    __emit 0x90;
    __emit 0x9c;
    __emit 0x00;
    __emit 0x00;
    __emit 0x00;
    __emit 0x84;
    __emit 0xc0;
    __emit 0x0f;
    __emit 0x84;
    __emit 0x1a;
    __emit 0x01;
    __emit 0x00;
    __emit 0x00;
    __emit 0x8b;
    __emit 0x8b;
    __emit 0xfc;
    __emit 0x9d;
    __emit 0x00;
    __emit 0x00;
    __emit 0xbe;
    __emit 0x03;
    __emit 0x00;
    __emit 0x00;
    __emit 0x00;
    __emit 0x39;
    __emit 0x71;
    __emit 0x18;
    __emit 0x0f;
    __emit 0x84;
    __emit 0x06;
    __emit 0x01;
    __emit 0x00;
    __emit 0x00;
    __emit 0x8a;
    __emit 0x83;
    __emit 0x4c;
    __emit 0x9f;
    __emit 0x00;
    __emit 0x00;
    __emit 0x84;
    __emit 0xc0;
    __emit 0x0f;
    __emit 0x85;
    __emit 0xf8;
    __emit 0x00;
    __emit 0x00;
    __emit 0x00;
    __emit 0xc6;
    __emit 0x83;
    __emit 0x58;
    __emit 0x9f;
    __emit 0x00;
    __emit 0x00;
    __emit 0x01;
    __emit 0x8b;
    __emit 0x55;
    __emit 0xdc;
    __emit 0x52;
    __emit 0x68;
    __emit 0xb4;
    __emit 0x34;
    __emit 0x13;
    __emit 0x01;
    __emit 0xe8;
    __emit 0x5b;
    __emit 0x24;
    __emit 0x00;
    __emit 0x00;
    __emit 0x83;
    __emit 0xc4;
    __emit 0x08;
    __emit 0xc6;
    __emit 0x83;
    __emit 0x58;
    __emit 0x9f;
    __emit 0x00;
    __emit 0x00;
    __emit 0x00;
    __emit 0x48;
    __emit 0x83;
    __emit 0xf8;
    __emit 0x06;
    __emit 0x0f;
    __emit 0x87;
    __emit 0xd8;
    __emit 0x01;
    __emit 0x00;
    __emit 0x00;
    __emit 0xff;
    __emit 0x24;
    __emit 0x85;
    __emit 0x04;
    __emit 0xc0;
    __emit 0xc8;
    __emit 0x00;
    __emit 0xc6;
    __emit 0x05;
    __emit 0x79;
    __emit 0x6e;
    __emit 0x33;
    __emit 0x01;
    __emit 0x01;
    __emit 0xe9;
    __emit 0xc5;
    __emit 0x01;
    __emit 0x00;
    __emit 0x00;
    __emit 0xc6;
    __emit 0x05;
    __emit 0x79;
    __emit 0x6e;
    __emit 0x33;
    __emit 0x01;
    __emit 0x01;
    __emit 0xcc;
    __emit 0xe9;
    __emit 0xb8;
    __emit 0x01;
    __emit 0x00;
    __emit 0x00;
    __emit 0x89;
    __emit 0xbb;
    __emit 0xfc;
    __emit 0x9d;
    __emit 0x00;
    __emit 0x00;
    __emit 0x68;
    __emit 0x60;
    __emit 0x6e;
    __emit 0x33;
    __emit 0x01;
    __emit 0xff;
    __emit 0x15;
    __emit 0x74;
    __emit 0x8e;
    __emit 0x35;
    __emit 0x01;
    __emit 0x6a;
    __emit 0x01;
    __emit 0xff;
    __emit 0x15;
    __emit 0x9c;
    __emit 0x93;
    __emit 0x35;
    __emit 0x01;
    __emit 0xc6;
    __emit 0x05;
    __emit 0x79;
    __emit 0x6e;
    __emit 0x33;
    __emit 0x01;
    __emit 0x01;
    __emit 0x8b;
    __emit 0x83;
    __emit 0xfc;
    __emit 0x9d;
    __emit 0x00;
    __emit 0x00;
    __emit 0x8b;
    __emit 0x48;
    __emit 0x10;
    __emit 0x51;
    __emit 0x8b;
    __emit 0x50;
    __emit 0x0c;
    __emit 0x52;
    __emit 0x68;
    __emit 0x64;
    __emit 0x31;
    __emit 0x13;
    __emit 0x01;
    __emit 0x8d;
    __emit 0x85;
    __emit 0x7c;
    __emit 0xfd;
    __emit 0xff;
    __emit 0xff;
    __emit 0x50;
    __emit 0xff;
    __emit 0x15;
    __emit 0xa4;
    __emit 0x90;
    __emit 0x35;
    __emit 0x01;
    __emit 0x83;
    __emit 0xc4;
    __emit 0x10;
    __emit 0x8d;
    __emit 0x8d;
    __emit 0x7c;
    __emit 0xfd;
    __emit 0xff;
    __emit 0xff;
    __emit 0x51;
    __emit 0x57;
    __emit 0x6a;
    __emit 0x01;
    __emit 0x8b;
    __emit 0xcb;
    __emit 0xe8;
    __emit 0x33;
    __emit 0xe5;
    __emit 0xff;
    __emit 0xff;
    __emit 0x8b;
    __emit 0x93;
    __emit 0xfc;
    __emit 0x9d;
    __emit 0x00;
    __emit 0x00;
    __emit 0xc7;
    __emit 0x42;
    __emit 0x18;
    __emit 0x01;
    __emit 0x00;
    __emit 0x00;
    __emit 0x00;
    __emit 0xe9;
    __emit 0x52;
    __emit 0x01;
    __emit 0x00;
    __emit 0x00;
    __emit 0xc6;
    __emit 0x05;
    __emit 0x79;
    __emit 0x6e;
    __emit 0x33;
    __emit 0x01;
    __emit 0x01;
    __emit 0x8b;
    __emit 0x83;
    __emit 0xfc;
    __emit 0x9d;
    __emit 0x00;
    __emit 0x00;
    __emit 0x8b;
    __emit 0x48;
    __emit 0x10;
    __emit 0x51;
    __emit 0x8b;
    __emit 0x50;
    __emit 0x0c;
    __emit 0x52;
    __emit 0x68;
    __emit 0x64;
    __emit 0x31;
    __emit 0x13;
    __emit 0x01;
    __emit 0x8d;
    __emit 0x85;
    __emit 0x0c;
    __emit 0xff;
    __emit 0xff;
    __emit 0xff;
    __emit 0x50;
    __emit 0xff;
    __emit 0x15;
    __emit 0xa4;
    __emit 0x90;
    __emit 0x35;
    __emit 0x01;
    __emit 0x83;
    __emit 0xc4;
    __emit 0x10;
    __emit 0x8d;
    __emit 0x8d;
    __emit 0x0c;
    __emit 0xff;
    __emit 0xff;
    __emit 0xff;
    __emit 0x51;
    __emit 0x57;
    __emit 0x6a;
    __emit 0x01;
    __emit 0x8b;
    __emit 0xcb;
    __emit 0xe8;
    __emit 0xe6;
    __emit 0xe4;
    __emit 0xff;
    __emit 0xff;
    __emit 0x8b;
    __emit 0x93;
    __emit 0xfc;
    __emit 0x9d;
    __emit 0x00;
    __emit 0x00;
    __emit 0x89;
    __emit 0x72;
    __emit 0x18;
    __emit 0xe9;
    __emit 0x09;
    __emit 0x01;
    __emit 0x00;
    __emit 0x00;
    __emit 0x8b;
    __emit 0x83;
    __emit 0xfc;
    __emit 0x9d;
    __emit 0x00;
    __emit 0x00;
    __emit 0x83;
    __emit 0x78;
    __emit 0x14;
    __emit 0x14;
    __emit 0x0f;
    __emit 0x85;
    __emit 0xf9;
    __emit 0x00;
    __emit 0x00;
    __emit 0x00;
    __emit 0x68;
    __emit 0x1c;
    __emit 0x30;
    __emit 0x07;
    __emit 0x01;
    __emit 0x6a;
    __emit 0x06;
    __emit 0x53;
    __emit 0xe8;
    __emit 0x6b;
    __emit 0xea;
    __emit 0xff;
    __emit 0xff;
    __emit 0x83;
    __emit 0xc4;
    __emit 0x0c;
    __emit 0x8b;
    __emit 0x13;
    __emit 0x68;
    __emit 0x88;
    __emit 0x34;
    __emit 0x13;
    __emit 0x01;
    __emit 0x8b;
    __emit 0xcb;
    __emit 0xff;
    __emit 0x52;
    __emit 0x38;
    __emit 0x6a;
    __emit 0x01;
    __emit 0x8b;
    __emit 0xcb;
    __emit 0xe8;
    __emit 0xd3;
    __emit 0xe3;
    __emit 0xff;
    __emit 0xff;
    __emit 0x8b;
    __emit 0x83;
    __emit 0xfc;
    __emit 0x9d;
    __emit 0x00;
    __emit 0x00;
    __emit 0x8b;
    __emit 0x48;
    __emit 0x10;
    __emit 0x51;
    __emit 0x8b;
    __emit 0x50;
    __emit 0x0c;
    __emit 0x52;
    __emit 0x68;
    __emit 0x64;
    __emit 0x31;
    __emit 0x13;
    __emit 0x01;
    __emit 0x8d;
    __emit 0x85;
    __emit 0x44;
    __emit 0xfe;
    __emit 0xff;
    __emit 0xff;
    __emit 0x50;
    __emit 0xff;
    __emit 0x15;
    __emit 0xa4;
    __emit 0x90;
    __emit 0x35;
    __emit 0x01;
    __emit 0x83;
    __emit 0xc4;
    __emit 0x10;
    __emit 0x8d;
    __emit 0x8d;
    __emit 0x44;
    __emit 0xfe;
    __emit 0xff;
    __emit 0xff;
    __emit 0x51;
    __emit 0x57;
    __emit 0x6a;
    __emit 0x02;
    __emit 0x8b;
    __emit 0xcb;
    __emit 0xe8;
    __emit 0x6f;
    __emit 0xe4;
    __emit 0xff;
    __emit 0xff;
    __emit 0x8b;
    __emit 0x93;
    __emit 0xfc;
    __emit 0x9d;
    __emit 0x00;
    __emit 0x00;
    __emit 0xc7;
    __emit 0x42;
    __emit 0x18;
    __emit 0x01;
    __emit 0x00;
    __emit 0x00;
    __emit 0x00;
    __emit 0xe9;
    __emit 0x8e;
    __emit 0x00;
    __emit 0x00;
    __emit 0x00;
    __emit 0x83;
    __emit 0xf8;
    __emit 0x02;
    __emit 0x0f;
    __emit 0x85;
    __emit 0xb8;
    __emit 0x00;
    __emit 0x00;
    __emit 0x00;
    __emit 0x8a;
    __emit 0x83;
    __emit 0x4b;
    __emit 0x9f;
    __emit 0x00;
    __emit 0x00;
    __emit 0x84;
    __emit 0xc0;
    __emit 0x74;
    __emit 0x7b;
    __emit 0x57;
    __emit 0x68;
    __emit 0x80;
    __emit 0x00;
    __emit 0x00;
    __emit 0x00;
    __emit 0x6a;
    __emit 0x04;
    __emit 0x57;
    __emit 0x57;
    __emit 0x68;
    __emit 0x00;
    __emit 0x00;
    __emit 0x00;
    __emit 0x40;
    __emit 0x68;
    __emit 0x40;
    __emit 0x30;
    __emit 0x13;
    __emit 0x01;
    __emit 0xff;
    __emit 0x15;
    __emit 0xe8;
    __emit 0x8c;
    __emit 0x35;
    __emit 0x01;
    __emit 0x8b;
    __emit 0xf0;
    __emit 0x6a;
    __emit 0x02;
    __emit 0x57;
    __emit 0x57;
    __emit 0x56;
    __emit 0xff;
    __emit 0x15;
    __emit 0x10;
    __emit 0x8f;
    __emit 0x35;
    __emit 0x01;
    __emit 0xb8;
    __emit 0x40;
    __emit 0x34;
    __emit 0x13;
    __emit 0x01;
    __emit 0x8d;
    __emit 0x78;
    __emit 0x01;
    __emit 0x8a;
    __emit 0x08;
    __emit 0x40;
    __emit 0x84;
    __emit 0xc9;
    __emit 0x75;
    __emit 0xf9;
    __emit 0x2b;
    __emit 0xc7;
    __emit 0x6a;
    __emit 0x00;
    __emit 0x8d;
    __emit 0x4d;
    __emit 0xd4;
    __emit 0x51;
    __emit 0x50;
    __emit 0x68;
    __emit 0x40;
    __emit 0x34;
    __emit 0x13;
    __emit 0x01;
    __emit 0x56;
    __emit 0xff;
    __emit 0x15;
    __emit 0x70;
    __emit 0x8f;
    __emit 0x35;
    __emit 0x01;
    __emit 0x8b;
    __emit 0x7d;
    __emit 0xdc;
    __emit 0x8b;
    __emit 0xc7;
    __emit 0x8d;
    __emit 0x48;
    __emit 0x01;
    __emit 0x8d;
    __emit 0xa4;
    __emit 0x24;
    __emit 0x00;
    __emit 0x00;
    __emit 0x00;
    __emit 0x00;
    __emit 0x8a;
    __emit 0x10;
    __emit 0x40;
    __emit 0x84;
    __emit 0xd2;
    __emit 0x75;
    __emit 0xf9;
    __emit 0x2b;
    __emit 0xc1;
    __emit 0x6a;
    __emit 0x00;
    __emit 0x8d;
    __emit 0x55;
    __emit 0xd4;
    __emit 0x52;
    __emit 0x50;
    __emit 0x57;
    __emit 0x56;
    __emit 0xff;
    __emit 0x15;
    __emit 0x70;
    __emit 0x8f;
    __emit 0x35;
    __emit 0x01;
    __emit 0x56;
    __emit 0xff;
    __emit 0x15;
    __emit 0xcc;
    __emit 0x8c;
    __emit 0x35;
    __emit 0x01;
    __emit 0x33;
    __emit 0xff;
    __emit 0x89;
    __emit 0xbb;
    __emit 0xfc;
    __emit 0x9d;
    __emit 0x00;
    __emit 0x00;
    __emit 0x68;
    __emit 0x60;
    __emit 0x6e;
    __emit 0x33;
    __emit 0x01;
    __emit 0xff;
    __emit 0x15;
    __emit 0x74;
    __emit 0x8e;
    __emit 0x35;
    __emit 0x01;
    __emit 0x81;
    __emit 0xc3;
    __emit 0xf8;
    __emit 0x9d;
    __emit 0x00;
    __emit 0x00;
    __emit 0x53;
    __emit 0xff;
    __emit 0x15;
    __emit 0x54;
    __emit 0x8e;
    __emit 0x35;
    __emit 0x01;
    __emit 0x32;
    __emit 0xc0;
    __emit 0x8b;
    __emit 0x4d;
    __emit 0xf0;
    __emit 0x64;
    __emit 0x89;
    __emit 0x0d;
    __emit 0x00;
    __emit 0x00;
    __emit 0x00;
    __emit 0x00;
    __emit 0x5f;
    __emit 0x5e;
    __emit 0x5b;
    __emit 0x8b;
    __emit 0xe5;
    __emit 0x5d;
    __emit 0xc2;
    __emit 0x04;
    __emit 0x00;
    __emit 0x8b;
    __emit 0xcb;
    __emit 0xe8;
    __emit 0x85;
    __emit 0xe2;
    __emit 0xff;
    __emit 0xff;
    __emit 0x89;
    __emit 0x7d;
    __emit 0xe4;
    __emit 0x8d;
    __emit 0x45;
    __emit 0xe4;
    __emit 0x50;
    __emit 0x68;
    __emit 0x00;
    __emit 0x97;
    __emit 0xc8;
    __emit 0x00;
    __emit 0xff;
    __emit 0x15;
    __emit 0x7c;
    __emit 0x8d;
    __emit 0x35;
    __emit 0x01;
    __emit 0x50;
    __emit 0xff;
    __emit 0x15;
    __emit 0xdc;
    __emit 0x8f;
    __emit 0x35;
    __emit 0x01;
    __emit 0x8b;
    __emit 0x45;
    __emit 0xe4;
    __emit 0x3b;
    __emit 0xc7;
    __emit 0x74;
    __emit 0x09;
    __emit 0x6a;
    __emit 0x06;
    __emit 0x50;
    __emit 0xff;
    __emit 0x15;
    __emit 0x94;
    __emit 0x90;
    __emit 0x35;
    __emit 0x01;
    __emit 0x68;
    __emit 0x10;
    __emit 0x10;
    __emit 0x01;
    __emit 0x00;
    __emit 0x68;
    __emit 0x94;
    __emit 0x33;
    __emit 0x13;
    __emit 0x01;
    __emit 0x8b;
    __emit 0x4d;
    __emit 0xdc;
    __emit 0x51;
    __emit 0x57;
    __emit 0xff;
    __emit 0x15;
    __emit 0x3c;
    __emit 0x90;
    __emit 0x35;
    __emit 0x01;
    __emit 0x89;
    __emit 0xbb;
    __emit 0xfc;
    __emit 0x9d;
    __emit 0x00;
    __emit 0x00;
    __emit 0x68;
    __emit 0x60;
    __emit 0x6e;
    __emit 0x33;
    __emit 0x01;
    __emit 0xff;
    __emit 0x15;
    __emit 0x74;
    __emit 0x8e;
    __emit 0x35;
    __emit 0x01;
    __emit 0x8b;
    __emit 0xcb;
    __emit 0xe8;
    __emit 0x2f;
    __emit 0xe2;
    __emit 0xff;
    __emit 0xff;
    __emit 0x89;
    __emit 0x7d;
    __emit 0xfc;
    __emit 0x57;
    __emit 0x57;
    __emit 0x57;
    __emit 0x68;
    __emit 0x05;
    __emit 0x00;
    __emit 0x00;
    __emit 0xc0;
    __emit 0xff;
    __emit 0x15;
    __emit 0xbc;
    __emit 0x8e;
    __emit 0x35;
    __emit 0x01;
    __emit 0xeb;
    __emit 0x21;
    __emit 0x8b;
    __emit 0x45;
    __emit 0xec;
    __emit 0x8b;
    __emit 0x10;
    __emit 0x8b;
    __emit 0x0a;
    __emit 0x8b;
    __emit 0x55;
    __emit 0xd8;
    __emit 0x0f;
    __emit 0xb6;
    __emit 0x92;
    __emit 0x4a;
    __emit 0x9f;
    __emit 0x00;
    __emit 0x00;
    __emit 0x52;
    __emit 0x50;
    __emit 0x51;
    __emit 0xe8;
    __emit 0x73;
    __emit 0xd7;
    __emit 0xff;
    __emit 0xff;
    __emit 0x83;
    __emit 0xc4;
    __emit 0x0c;
    __emit 0xc3;
    __emit 0x8b;
    __emit 0x65;
    __emit 0xe8;
    __emit 0x90;
    __emit 0xc7;
    __emit 0x45;
    __emit 0xfc;
    __emit 0xff;
    __emit 0xff;
    __emit 0xff;
    __emit 0xff;
    __emit 0x6a;
    __emit 0x01;
    __emit 0xff;
    __emit 0x15;
    __emit 0xc4;
    __emit 0x92;
    __emit 0x35;
    __emit 0x01;
    __emit 0x60;
    __emit 0xbd;
    __emit 0xc8;
    __emit 0x00;
    __emit 0x6c;
    __emit 0xbd;
    __emit 0xc8;
    __emit 0x00;
    __emit 0x79;
    __emit 0xbd;
    __emit 0xc8;
    __emit 0x00;
    __emit 0x31;
    __emit 0xbf;
    __emit 0xc8;
    __emit 0x00;
    __emit 0x92;
    __emit 0xbd;
    __emit 0xc8;
    __emit 0x00;
    __emit 0x31;
    __emit 0xbf;
    __emit 0xc8;
    __emit 0x00;
    __emit 0xdf;
    __emit 0xbd;
    __emit 0xc8;
    __emit 0x00;
    __emit 0x55;
    __emit 0x8b;
    __emit 0xec;
    __emit 0x51;
    __emit 0x56;
    __emit 0x8b;
    __emit 0xf1;
    __emit 0x83;
    __emit 0xbe;
    __emit 0xf4;
    __emit 0x9c;
    __emit 0x00;
    __emit 0x00;
    __emit 0x07;
    __emit 0x74;
    __emit 0x70;
    __emit 0x8b;
    __emit 0x55;
    __emit 0x08;
    __emit 0x85;
    __emit 0xd2;
    __emit 0x75;
    __emit 0x0c;
    __emit 0xc7;
    __emit 0x45;
    __emit 0x08;
    __emit 0xcc;
    __emit 0x34;
    __emit 0x13;
    __emit 0x01;
    __emit 0x8b;
    __emit 0x55;
    __emit 0x08;
    __emit 0xeb;
    __emit 0x05;
    __emit 0x80;
    __emit 0x3a;
    __emit 0x00;
    __emit 0x74;
    __emit 0x58;
    __emit 0x8b;
    __emit 0xc2;
    __emit 0x57;
    __emit 0x8d;
    __emit 0x78;
    __emit 0x01;
    __emit 0x8b;
    __emit 0xff;
    __emit 0x8a;
    __emit 0x08;
    __emit 0x40;
    __emit 0x84;
    __emit 0xc9;
    __emit 0x75;
    __emit 0xf9;
    __emit 0x8b;
    __emit 0x8e;
    __emit 0x44;
    __emit 0x9f;
    __emit 0x00;
    __emit 0x00;
    __emit 0x2b;
    __emit 0xc7;
    __emit 0x3b;
    __emit 0xc1;
    __emit 0x89;
    __emit 0x45;
    __emit 0xfc;
    __emit 0x7d;
    __emit 0x26;
    __emit 0x53;
    __emit 0x8b;
    __emit 0xf8;
    __emit 0x8d;
    __emit 0x9e;
    __emit 0x48;
    __emit 0x9f;
    __emit 0x00;
    __emit 0x00;
    __emit 0x90;
    __emit 0x6a;
    __emit 0x01;
    __emit 0x53;
    __emit 0x8b;
    __emit 0xce;
    __emit 0xe8;
    __emit 0x76;
    __emit 0xe8;
    __emit 0xff;
    __emit 0xff;
    __emit 0x8b;
    __emit 0x86;
    __emit 0x44;
    __emit 0x9f;
    __emit 0x00;
    __emit 0x00;
    __emit 0x47;
    __emit 0x3b;
    __emit 0xf8;
    __emit 0x7c;
    __emit 0xeb;
    __emit 0x8b;
    __emit 0x55;
    __emit 0x08;
    __emit 0x8b;
    __emit 0x45;
    __emit 0xfc;
    __emit 0x5b;
    __emit 0x50;
    __emit 0x52;
    __emit 0x8b;
    __emit 0xce;
    __emit 0xc7;
    __emit 0x86;
    __emit 0x44;
    __emit 0x9f;
    __emit 0x00;
    __emit 0x00;
    __emit 0x00;
    __emit 0x00;
    __emit 0x00;
    __emit 0x00;
    __emit 0xe8;
    __emit 0x51;
    __emit 0xe8;
    __emit 0xff;
    __emit 0xff;
    __emit 0x5f;
    __emit 0x8b;
    __emit 0xc6;
    __emit 0x5e;
    __emit 0x8b;
    __emit 0xe5;
    __emit 0x5d;
    __emit 0xc2;
    __emit 0x04;
    __emit 0x00;
  }
}

Debug& Debug::operator<<(const char *str)
{
  if (curType==DebugIOInterface::StringType::MAX)
    // yes, this is valid and simply means not to
    // write anything...
    return *this;

  // buffer large enough?
  if (!str)
    str="[NULL]";
  else if (!*str)
    return *this;

  unsigned len=strlen(str);

  // forced width?
  if (len<m_width)
  {
    for (unsigned k=len;k<m_width;k++)
      AddOutput(&m_fillChar,1);
  }

  // reset width after each insertion
  m_width=0;

  AddOutput(str,len);

  return *this;
}

// ?SetPrefixAndRadix@Debug@@QAEXPBDH@Z present-unmatched
void Debug::SetPrefixAndRadix(const char *prefix, int radix)
{
  strncpy(m_prefix,prefix?prefix:"",sizeof(m_prefix)-1);
  m_prefix[sizeof(m_prefix)-1]=0;
  m_radix=radix;
}

Debug& Debug::operator<<(int val)
{
  // usually having a fixed size buffer and a function
  // that doesn't check for buffer overflow isn't a good idea
  // but in this case we know how long it can be at max...
  char help[1+32+1]; // sign, 32 digits (binary), NUL
  AddOutput(m_prefix,strlen(m_prefix));
  return (*this) << _itoa(val,help,m_radix);
}

Debug& Debug::operator<<(unsigned val)
{
  // usually having a fixed size buffer and a function
  // that doesn't check for buffer overflow isn't a good idea
  // but in this case we know how long it can be at max...
  char help[32+1]; // 32 digits, NUL
  AddOutput(m_prefix,strlen(m_prefix));
  return (*this) << _ultoa(val,help,m_radix);
}

Debug& Debug::operator<<(long val)
{
  // usually having a fixed size buffer and a function
  // that doesn't check for buffer overflow isn't a good idea
  // but in this case we know how long it can be at max...
  char help[1+32+1]; // sign, 32 digits, NUL
  AddOutput(m_prefix,strlen(m_prefix));
  return (*this) << _itoa(val,help,m_radix);
}

Debug& Debug::operator<<(unsigned long val)
{
  // usually having a fixed size buffer and a function
  // that doesn't check for buffer overflow isn't a good idea
  // but in this case we know how long it can be at max...
  char help[32+1]; // 32 digits, NUL
  AddOutput(m_prefix,strlen(m_prefix));
  return (*this) << _ultoa(val,help,m_radix);
}

Debug& Debug::operator<<(bool val)
{
  return (*this) << (val?"true":"false");
}

Debug& Debug::operator<<(float val)
{
  /// @todo_opt shouldn't use snprintf here - brings in most of the old C IO lib...
  char help[200];
  _snprintf(help,sizeof(help),"%f",val);
  return (*this) << help;
}

Debug& Debug::operator<<(double val)
{
  /// @todo_opt shouldn't use snprintf here - brings in most of the old C IO lib...
  char help[200];
  _snprintf(help,sizeof(help),"%f",val);
  return (*this) << help;
}

Debug& Debug::operator<<(short val)
{
  // usually having a fixed size buffer and a function
  // that doesn't check for buffer overflow isn't a good idea
  // but in this case we know how long it can be at max...
  char help[1+16+1]; // sign, 16 digits, NUL
  AddOutput(m_prefix,strlen(m_prefix));
  return (*this) << _itoa(val,help,m_radix);
}

Debug& Debug::operator<<(unsigned short val)
{
  // usually having a fixed size buffer and a function
  // that doesn't check for buffer overflow isn't a good idea
  // but in this case we know how long it can be at max...
  char help[16+1]; // 16 digits, NUL
  AddOutput(m_prefix,strlen(m_prefix));
  return (*this) << _itoa(val,help,m_radix);
}

Debug& Debug::operator<<(__int64 val)
{
  // usually having a fixed size buffer and a function
  // that doesn't check for buffer overflow isn't a good idea
  // but in this case we know how long it can be at max...
  char help[1+64+1]; // sign, 64 digits, NUL
  AddOutput(m_prefix,strlen(m_prefix));
  return (*this) << _i64toa(val,help,m_radix);
}

Debug& Debug::operator<<(unsigned __int64 val)
{
  // usually having a fixed size buffer and a function
  // that doesn't check for buffer overflow isn't a good idea
  // but in this case we know how long it can be at max...
  char help[64+1]; // sign, 64 digits, NUL
  AddOutput(m_prefix,strlen(m_prefix));
  return (*this) << _ui64toa(val,help,m_radix);
}

Debug& Debug::operator<<(const void *ptr)
{
  (*this) << "ptr:";
  if (ptr)
  {
    char help[9];
    (*this) << "0x" << _ultoa((unsigned long)ptr,help,16);
  }
  else
    (*this) << "NULL";
  return *this;
}

Debug& Debug::operator<<(const MemDump &dump)
{
  if (curType==DebugIOInterface::StringType::MAX)
    return *this;

  // need CR?
  if (!ioBuffer[curType].lastWasCR)
    operator<<("\n");

  // How many items per line? We're assuming an output
  // width of 73 chars. Left border is address thus
  // leaving 65 chars effectively. If character dump is
  // enabled then an additional space is needed (64 chars
  // then).
  unsigned itemPerLine=(dump.m_withChars?64:65)/
                          (1+2*dump.m_bytePerItem+(dump.m_withChars?1:0));
  if (!itemPerLine)
    itemPerLine=1;

  // now dump line by line
  const unsigned char *cur=dump.m_startPtr;
  for (unsigned i=0;i<dump.m_numItems;i+=itemPerLine,cur+=itemPerLine*dump.m_bytePerItem)
  {
    // address
    char buf[9];
    sprintf(buf,"%08x",dump.m_absAddr?unsigned(cur):cur-dump.m_startPtr);
    operator<<(buf);

    // items
    const unsigned char *curByte=cur;
    for (unsigned k=0;k<itemPerLine;k++,curByte+=dump.m_bytePerItem)
    {
      operator<<(" ");

      if (k+i>=dump.m_numItems)
      {
        for (unsigned l=dump.m_bytePerItem;l;--l)
          operator<<("  ");
      }
      else if (IsBadReadPtr(curByte,dump.m_bytePerItem))
      {
        for (unsigned l=dump.m_bytePerItem;l;--l)
          operator<<("??");
      }
      else
      {
        curByte+=dump.m_bytePerItem;
        for (unsigned l=0;l<dump.m_bytePerItem;++l)
        {
          sprintf(buf,"%02x",*--curByte);
          operator<<(buf);
        }
      }
    }

    // characters
    if (!dump.m_withChars)
      continue;
    operator<<(" ");
    curByte=cur;
    for (k=0;k<itemPerLine;k++,curByte+=dump.m_bytePerItem)
    {
      if (k+i>=dump.m_numItems)
        break;
      else if (IsBadReadPtr(curByte,dump.m_bytePerItem))
      {
        for (unsigned l=dump.m_bytePerItem;l;--l)
          operator<<("?");
      }
      else
      {
        buf[1]=0;
        for (unsigned l=0;l<dump.m_bytePerItem;++l)
        {
          *buf=curByte[l]>' '?curByte[l]:'.';
          operator<<(buf);
        }
      }
    }

    operator<<("\n");
  }

  return *this;
}

// ?IsLogEnabled@Debug@@SA_NPBD@Z present-unmatched
bool Debug::IsLogEnabled(const char *fileOrGroup)
{
  // now this isn't great but since IsLogEnabled is supposed
  // to be used from the D_ISLOG macros only and those guarantee
  // that we are having real static strings let's use
  // that strings address as frame address...
  FrameHashEntry *e=Instance.LookupFrame((unsigned)fileOrGroup);
  if (!e)
    e=Instance.AddFrameEntry((unsigned)fileOrGroup,FrameTypeLog,fileOrGroup,0);
  if (e->status==Unknown)
    Instance.UpdateFrameStatus(*e);
  return e->status==NoSkip;
}

// ?AddHResultTranslator@Debug@@SAXIP6A_NAAV1@JPAX@Z1@Z present-unmatched
void Debug::AddHResultTranslator(unsigned prio, HResultTranslator func, void *user)
{
  // bail out if invalid parameter passed in
  if (!func)
    return;

  // just remove it first (if it's not in there nothing is done)
  // necessary in case we want to 'change' the priority of an
  // existing HR translator
  RemoveHResultTranslator(func,user);

  // now find the right place to insert the translator
  // (slow but this function is not time critical)
  for (unsigned k=0;k<Instance.numHrTranslators;++k)
    if (Instance.hrTranslators[k].prio<prio)
      break;

  // grow & move
  Instance.hrTranslators=(HResultTranslatorEntry *)
    DebugReAllocMemory(Instance.hrTranslators,(Instance.numHrTranslators+1)*sizeof(void *));
  memmove(Instance.hrTranslators+k+1,Instance.hrTranslators+k,(Instance.numHrTranslators-k)*sizeof(void *));

  // add new
  ++Instance.numHrTranslators;
  Instance.hrTranslators[k].prio=prio;
  Instance.hrTranslators[k].func=func;
  Instance.hrTranslators[k].user=user;
}

// ?RemoveHResultTranslator@Debug@@SAXP6A_NAAV1@JPAX@Z1@Z present-unmatched
void Debug::RemoveHResultTranslator(HResultTranslator func, void *user)
{
  // bail out if invalid parameter passed in
  if (!func)
    return;

  // look for func/user pair
  for (unsigned k=0;k<Instance.numHrTranslators;++k)
    if (Instance.hrTranslators[k].func==func&&
        Instance.hrTranslators[k].user==user)
    {
      // remove it
      memmove(Instance.hrTranslators+k,Instance.hrTranslators+k+1,
        (Instance.numHrTranslators-k-1)*sizeof(void *));
      --Instance.hrTranslators;
      Instance.hrTranslators=(HResultTranslatorEntry *)
        DebugReAllocMemory(Instance.hrTranslators,Instance.numHrTranslators*sizeof(void *));
    }
}

// ?AddIOFactory@Debug@@SA_NPBD0P6APAVDebugIOInterface@@XZ@Z present-unmatched
bool Debug::AddIOFactory(const char *io_id, const char *descr, DebugIOInterface* (*func)(void))
{
  // bail out if invalid parameters passed in
  if (!io_id||!func)
    return true;
  
  // allocate & init new list entry
  IOFactoryListEntry *entry=(IOFactoryListEntry *)
                      DebugAllocMemory(sizeof(IOFactoryListEntry));
  entry->next=Instance.firstIOFactory;
  entry->ioID=io_id;
  entry->descr=descr;
  entry->factory=func;
  entry->io=NULL;
  entry->input=NULL;
  entry->inputAlloc=0;
  entry->inputUsed=0;

  // add to list
  Instance.firstIOFactory=entry;

  return true;
}

// ?AddCommands@Debug@@SA_NPBDPAVDebugCmdInterface@@@Z present-unmatched
bool Debug::AddCommands(const char *cmdgroup, DebugCmdInterface *cmdif)
{
  // bail out if invalid parameters passed in
  if (!cmdgroup||!cmdif)
    return true;

  // walk to end of list, add there (unless interface pointer already in list)
  CmdInterfaceListEntry **listptr=&Instance.firstCmdGroup;
  while (*listptr)
  {
    if ((*listptr)->cmdif==cmdif)
      // interface already in list, don't add twice
      return true;
    listptr=&((*listptr)->next);
  }
  
  // allocate & init new list entry
  CmdInterfaceListEntry *entry=(CmdInterfaceListEntry *)
                      DebugAllocMemory(sizeof(CmdInterfaceListEntry));
  entry->next=NULL;
  entry->group=cmdgroup;
  entry->cmdif=cmdif;

  // add to list
  *listptr=entry;

  return true;
}

// ?RemoveCommands@Debug@@SAXPAVDebugCmdInterface@@@Z present-unmatched
void Debug::RemoveCommands(DebugCmdInterface *cmdif)
{
  // bail out if invalid parameter passed in
  if (!cmdif)
    return;

  // walk the list, search for interface pointer
  CmdInterfaceListEntry **listptr=&Instance.firstCmdGroup;
  while (*listptr)
  {
    if ((*listptr)->cmdif==cmdif)
    {
      // found it, now remove it
      CmdInterfaceListEntry *cur=*listptr;
      *listptr=cur->next;

      // free list entry
      DebugFreeMemory(cur);

      // done
      break;
    }
    listptr=&((*listptr)->next);
  }
}

// ?Command@Debug@@SAXPBD@Z present-unmatched
void Debug::Command(const char *cmd)
{
  DFAIL_IF(!cmd) return;
  Instance.ExecCommand(cmd,cmd+strlen(cmd));
}

// ?Update@Debug@@SAXXZ present-unmatched
void Debug::Update(void)
{
  // check all existing IO interfaces
  for (IOFactoryListEntry *cur=Instance.firstIOFactory;cur;cur=cur->next)
  {
    if (!cur->io)
      continue;

    // any input?
    bool hadInput=false;
    for (;;)
    {
      if (cur->inputAlloc-cur->inputUsed<64)
        // must grow input buffer...
        cur->input=(char *)DebugReAllocMemory(cur->input,(cur->inputAlloc+=64)+1);
      int numChars=cur->io->Read(cur->input+cur->inputUsed,cur->inputAlloc-cur->inputUsed);
      if (!numChars)
        break;

      cur->inputUsed+=numChars;
      cur->input[cur->inputUsed]=0;
      hadInput=true;
    } 
    
    if (!hadInput)
      // skip then
      continue;

    // else look for completed commands and try to process them
    for (;;)
    {
      char *p=strchr(cur->input,'\n');
      if (!p)
        break;

      Instance.ExecCommand(cur->input,p);
      strcpy(cur->input,p+1);
      cur->inputUsed=strlen(cur->input);
    }
  }
}

// ?AddFrameEntry@Debug@@AAEPAUFrameHashEntry@1@IIPBDH@Z present-unmatched
Debug::FrameHashEntry* Debug::AddFrameEntry(unsigned addr, unsigned type,
                                            const char *fileOrGroup, int line)
{
  __ASSERT(LookupFrame(addr)==NULL);

  // get new entry
  if (!numAvailableFrameHash)
  {
    numAvailableFrameHash=FRAME_HASH_ALLOC_COUNT;
    nextUnusedFrameHash=(FrameHashEntry *)
      DebugAllocMemory(numAvailableFrameHash*sizeof(FrameHashEntry));
  }
  FrameHashEntry *e=nextUnusedFrameHash++;
  --numAvailableFrameHash;

  // fill entry
  e->next=frameHash[addr%FRAME_HASH_SIZE];
  e->frameAddr=addr;
  e->frameType=type;
  e->line=line;
  e->status=Unknown;
  e->hits=0;

  // log?
  if (type&FrameTypeLog)
  {
    // must add to list of known logs,
    // store translated name 
    e->fileOrGroup=AddLogGroup(fileOrGroup,NULL);
  }
  else
  {
    // no, just add file name (without path though)
    e->fileOrGroup=fileOrGroup?strrchr(fileOrGroup,'\\'):NULL;
    e->fileOrGroup=e->fileOrGroup?e->fileOrGroup+1:fileOrGroup;
  }

  // add to hash
  frameHash[addr%FRAME_HASH_SIZE]=e;
  return e;
}

// ?UpdateFrameStatus@Debug@@AAEXAAUFrameHashEntry@1@@Z present-unmatched
void Debug::UpdateFrameStatus(FrameHashEntry &entry)
{
  // build pattern match entry
  char help[512];
  if (entry.frameType==FrameTypeAssert||
      entry.frameType==FrameTypeCheck)
    wsprintf(help,"%s(%i)",entry.fileOrGroup,entry.line);
  else
    strcpy(help,entry.fileOrGroup);
  
  // update frame status
  bool active=entry.frameType!=FrameTypeLog;
  for (PatternListEntry *cur=firstPatternEntry;cur;cur=cur->next)
  {
    if (!(cur->frameTypes&entry.frameType))
      continue;
    if (SimpleMatch(help,cur->pattern))
      active=cur->isActive;
  }
  entry.status=active?NoSkip:Skip;
}

// ?AddLogGroup@Debug@@AAEPBDPBD0@Z present-unmatched
const char *Debug::AddLogGroup(const char *fileOrGroup, const char *descr)
{
  // helper buffer for stripping down fileOrGroup
  char help[200];

  // do we need to strip down fileOrGroup?
  const char *p=strrchr(fileOrGroup,'\\');
  const char *q=strchr(p?p:fileOrGroup,'.');
  if (p||q)
  {
    // this extracts everything beyond the last backslash
    // up to the first dot
    p=p?p+1:fileOrGroup;
    if (!q) q=p+strlen(p);
    if (q-p>=sizeof(help))
      q=p+sizeof(help)-1;
    memcpy(help,p,q-p);
    help[q-p]=0;
    fileOrGroup=help;
  }

  // is that log group known?
  for (KnownLogGroupList *cur=firstLogGroup;cur;cur=cur->next)
  {
    if (!strcmp(cur->nameGroup,fileOrGroup))
    {
      // yes, return translated name
      return cur->nameGroup;
    }
  }

  // no, add new entry
  cur=(KnownLogGroupList *)DebugAllocMemory(sizeof(KnownLogGroupList));
  cur->next=firstLogGroup;
  cur->nameGroup=(char *)DebugAllocMemory(strlen(fileOrGroup)+1);
  strcpy(cur->nameGroup,fileOrGroup);
  cur->descr=descr;
  firstLogGroup=cur;
  return cur->nameGroup;
}

// ?StartOutput@Debug@@AAAXW4StringType@DebugIOInterface@@PBDZZ present-unmatched
void Debug::StartOutput(DebugIOInterface::StringType type, const char *fmt, ...)
{
  if (curType==DebugIOInterface::Log)
    FlushOutput();
  __ASSERT(curType==DebugIOInterface::StringType::MAX);
  curType=type;

  // potentially dangerous (fixed string buffer...)
  va_list va;
  va_start(va,fmt);
  wvsprintf(curSource,fmt,va);
  va_end(va);
  __ASSERT(curSource[sizeof(curSource)-1]==0);
}

// ?AddOutput@Debug@@AAEXPBDI@Z
// Body in debug_debug_AddOutput.asm (exact 675B retail).

// ?FlushOutput@Debug@@AAEX_N@Z present-unmatched
void Debug::FlushOutput(bool defaultLog)
{
  __ASSERT(curType!=DebugIOInterface::StringType::MAX);

  // bail out early if buffer is still empty
  if (!ioBuffer[curType].used)
  {
    curType=DebugIOInterface::StringType::MAX;
    return;
  }

  // need CR?
  if (!ioBuffer[curType].lastWasCR)
    operator<<("\n");

  // send string to all active I/O interfaces
  bool hadWrite=!defaultLog;
  for (IOFactoryListEntry *cur=firstIOFactory;cur;cur=cur->next)
  {
    if (!cur->io)
      continue;

    hadWrite=true;
    cur->io->Write(curType,curSource,ioBuffer[curType].buffer);

    if (alwaysFlush)
      cur->io->Write(curType,curSource,NULL);
  }

  // written nowhere?
  if (!hadWrite&&curType!=DebugIOInterface::StringType::StructuredCmdReply)
  {
#ifdef HAS_LOGS
    // then force output to a very simple default log file
    // (non-Release builds only)
    HANDLE h=CreateFile("default.log",GENERIC_WRITE,0,NULL,
                        OPEN_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
    SetFilePointer(h,0,NULL,FILE_END);
    DWORD dwDummy;
    WriteFile(h,ioBuffer[curType].buffer,strlen(ioBuffer[curType].buffer),&dwDummy,NULL);
    CloseHandle(h);
#endif
  }

  // empty buffer etc.
  ioBuffer[curType].used=0;
  *ioBuffer[curType].buffer=0;
  curType=DebugIOInterface::StringType::MAX;
  *curSource=0;
}

// byte-exact reconstruction: Code/GameEngine/Source/Common/Debug_AddPatternEntry_Thunk.cpp
// ?AddPatternEntry@Debug@@AAEXI_NPBD@Z present-unmatched
void Debug::AddPatternEntry(unsigned types, bool isActive, const char *pattern)
{
  __ASSERT(pattern);

  // alloc new pattern entry
  PatternListEntry *cur=(PatternListEntry *)
      DebugAllocMemory(sizeof(PatternListEntry));

  // init
  cur->next=NULL;
  cur->frameTypes=types;
  cur->isActive=isActive;
  cur->pattern=(char *)DebugAllocMemory(strlen(pattern)+1);
  strcpy(cur->pattern,pattern);

  // add to list
  if (lastPatternEntry)
    lastPatternEntry->next=cur;
  else
    firstPatternEntry=cur;
  lastPatternEntry=cur;
}

// ?SimpleMatch@Debug@@SA_NPBD0@Z present-unmatched
bool Debug::SimpleMatch(const char *str, const char *pattern)
{
  __ASSERT(str);
  __ASSERT(pattern);
  while (*str&&*pattern)
  {
    if (*pattern=='*')
    {
      pattern++;
      while (*str)
        if (SimpleMatch(str++,pattern))
          return true;
      return *str==*pattern;
    }
    else 
    {
      if (*str++!=*pattern++)
        return false;
    }
  }

  return *str==*pattern;
}

// ?SetBuildInfo@Debug@@SAXPBD00@Z present-unmatched
void Debug::SetBuildInfo(const char *version,
                         const char *internalVersion,
                         const char *buildDate)
{
  if (version)
    strncpy(Instance.m_version,version,sizeof(Instance.m_version)-1);
  if (internalVersion)
    strncpy(Instance.m_intVersion,internalVersion,sizeof(Instance.m_intVersion)-1);
  if (buildDate)
    strncpy(Instance.m_buildDate,buildDate,sizeof(Instance.m_buildDate)-1);
}

// ?WriteBuildInfo@Debug@@QAEXXZ
// Body in debug_debug_WriteBuildInfo.asm (exact 135B retail).

// ?ExecCommand@Debug@@AAEXPBD0@Z matched 788 bytes (Open-BFME5)
__declspec(naked) void Debug::ExecCommand(const char *, const char *)
{
  __asm
  {
  __emit 0x55;
  __emit 0x8b;
  __emit 0xec;
  __emit 0x81;
  __emit 0xec;
  __emit 0xa8;
  __emit 0x01;
  __emit 0x00;
  __emit 0x00;
  __emit 0x53;
  __emit 0x8b;
  __emit 0x5d;
  __emit 0x0c;
  __emit 0x56;
  __emit 0x8b;
  __emit 0x75;
  __emit 0x08;
  __emit 0x57;
  __emit 0x8b;
  __emit 0xfb;
  __emit 0x2b;
  __emit 0xfe;
  __emit 0x8d;
  __emit 0x47;
  __emit 0x01;
  __emit 0x50;
  __emit 0x89;
  __emit 0x4d;
  __emit 0xfc;
  __emit 0x89;
  __emit 0x7d;
  __emit 0xe8;
  __emit 0xe8;
  __emit 0x6b;
  __emit 0x3f;
  __emit 0x00;
  __emit 0x00;
  __emit 0x8b;
  __emit 0xd0;
  __emit 0x8b;
  __emit 0xcf;
  __emit 0x8b;
  __emit 0xc1;
  __emit 0xc1;
  __emit 0xe9;
  __emit 0x02;
  __emit 0x8b;
  __emit 0xfa;
  __emit 0xf3;
  __emit 0xa5;
  __emit 0x8b;
  __emit 0xc8;
  __emit 0x83;
  __emit 0xe1;
  __emit 0x03;
  __emit 0xf3;
  __emit 0xa4;
  __emit 0x8b;
  __emit 0x75;
  __emit 0x08;
  __emit 0x8b;
  __emit 0xca;
  __emit 0x2b;
  __emit 0xce;
  __emit 0xc6;
  __emit 0x04;
  __emit 0x19;
  __emit 0x00;
  __emit 0x8a;
  __emit 0x0a;
  __emit 0x33;
  __emit 0xf6;
  __emit 0x83;
  __emit 0xc4;
  __emit 0x04;
  __emit 0x33;
  __emit 0xff;
  __emit 0x80;
  __emit 0xf9;
  __emit 0x21;
  __emit 0x89;
  __emit 0x55;
  __emit 0xec;
  __emit 0x89;
  __emit 0x75;
  __emit 0xf4;
  __emit 0x8b;
  __emit 0xc2;
  __emit 0x75;
  __emit 0x13;
  __emit 0x8d;
  __emit 0x42;
  __emit 0x01;
  __emit 0xc7;
  __emit 0x45;
  __emit 0xf0;
  __emit 0x05;
  __emit 0x00;
  __emit 0x00;
  __emit 0x00;
  __emit 0xc7;
  __emit 0x45;
  __emit 0xf8;
  __emit 0x01;
  __emit 0x00;
  __emit 0x00;
  __emit 0x00;
  __emit 0xeb;
  __emit 0x13;
  __emit 0xc7;
  __emit 0x45;
  __emit 0xf0;
  __emit 0x04;
  __emit 0x00;
  __emit 0x00;
  __emit 0x00;
  __emit 0xc7;
  __emit 0x45;
  __emit 0xf8;
  __emit 0x00;
  __emit 0x00;
  __emit 0x00;
  __emit 0x00;
  __emit 0xeb;
  __emit 0x03;
  __emit 0x8d;
  __emit 0x49;
  __emit 0x00;
  __emit 0x85;
  __emit 0xff;
  __emit 0x75;
  __emit 0x36;
  __emit 0x8a;
  __emit 0x08;
  __emit 0x80;
  __emit 0xf9;
  __emit 0x27;
  __emit 0x74;
  __emit 0x05;
  __emit 0x80;
  __emit 0xf9;
  __emit 0x22;
  __emit 0x75;
  __emit 0x2a;
  __emit 0x40;
  __emit 0x83;
  __emit 0xfe;
  __emit 0x64;
  __emit 0x73;
  __emit 0x08;
  __emit 0x89;
  __emit 0x84;
  __emit 0xb5;
  __emit 0x58;
  __emit 0xfe;
  __emit 0xff;
  __emit 0xff;
  __emit 0x46;
  __emit 0x80;
  __emit 0x38;
  __emit 0x00;
  __emit 0x74;
  __emit 0xdd;
  __emit 0x38;
  __emit 0x08;
  __emit 0x74;
  __emit 0x08;
  __emit 0x8a;
  __emit 0x58;
  __emit 0x01;
  __emit 0x40;
  __emit 0x84;
  __emit 0xdb;
  __emit 0x75;
  __emit 0xf4;
  __emit 0x80;
  __emit 0x38;
  __emit 0x00;
  __emit 0x74;
  __emit 0xcc;
  __emit 0xc6;
  __emit 0x00;
  __emit 0x00;
  __emit 0x40;
  __emit 0xeb;
  __emit 0xc6;
  __emit 0x8a;
  __emit 0x08;
  __emit 0x80;
  __emit 0xf9;
  __emit 0x20;
  __emit 0x74;
  __emit 0x17;
  __emit 0x80;
  __emit 0xf9;
  __emit 0x09;
  __emit 0x74;
  __emit 0x12;
  __emit 0x84;
  __emit 0xc9;
  __emit 0x74;
  __emit 0x0e;
  __emit 0x80;
  __emit 0xf9;
  __emit 0x3b;
  __emit 0x74;
  __emit 0x0e;
  __emit 0x85;
  __emit 0xff;
  __emit 0x75;
  __emit 0x02;
  __emit 0x8b;
  __emit 0xf8;
  __emit 0x40;
  __emit 0xeb;
  __emit 0xa8;
  __emit 0x80;
  __emit 0xf9;
  __emit 0x3b;
  __emit 0x75;
  __emit 0x03;
  __emit 0xc6;
  __emit 0x00;
  __emit 0x00;
  __emit 0x85;
  __emit 0xff;
  __emit 0x74;
  __emit 0x1b;
  __emit 0x83;
  __emit 0xfe;
  __emit 0x64;
  __emit 0x73;
  __emit 0x08;
  __emit 0x89;
  __emit 0xbc;
  __emit 0xb5;
  __emit 0x58;
  __emit 0xfe;
  __emit 0xff;
  __emit 0xff;
  __emit 0x46;
  __emit 0x8a;
  __emit 0x08;
  __emit 0x33;
  __emit 0xff;
  __emit 0x84;
  __emit 0xc9;
  __emit 0x74;
  __emit 0x87;
  __emit 0xc6;
  __emit 0x00;
  __emit 0x00;
  __emit 0x40;
  __emit 0xeb;
  __emit 0x81;
  __emit 0x80;
  __emit 0x38;
  __emit 0x00;
  __emit 0x74;
  __emit 0x06;
  __emit 0x40;
  __emit 0xe9;
  __emit 0x76;
  __emit 0xff;
  __emit 0xff;
  __emit 0xff;
  __emit 0x85;
  __emit 0xf6;
  __emit 0x89;
  __emit 0x75;
  __emit 0xf4;
  __emit 0x0f;
  __emit 0x84;
  __emit 0xf3;
  __emit 0x01;
  __emit 0x00;
  __emit 0x00;
  __emit 0x8b;
  __emit 0x95;
  __emit 0x58;
  __emit 0xfe;
  __emit 0xff;
  __emit 0xff;
  __emit 0x6a;
  __emit 0x2e;
  __emit 0x52;
  __emit 0xff;
  __emit 0x15;
  __emit 0x9c;
  __emit 0x94;
  __emit 0x35;
  __emit 0x01;
  __emit 0x8b;
  __emit 0xb5;
  __emit 0x58;
  __emit 0xfe;
  __emit 0xff;
  __emit 0xff;
  __emit 0x83;
  __emit 0xc4;
  __emit 0x08;
  __emit 0x85;
  __emit 0xc0;
  __emit 0x89;
  __emit 0x45;
  __emit 0x0c;
  __emit 0x74;
  __emit 0x2d;
  __emit 0x2b;
  __emit 0xc6;
  __emit 0x83;
  __emit 0xf8;
  __emit 0x64;
  __emit 0x73;
  __emit 0x26;
  __emit 0x8b;
  __emit 0x5d;
  __emit 0xfc;
  __emit 0x8b;
  __emit 0xc8;
  __emit 0x8b;
  __emit 0xd1;
  __emit 0xc1;
  __emit 0xe9;
  __emit 0x02;
  __emit 0x8d;
  __emit 0xbb;
  __emit 0x08;
  __emit 0x9e;
  __emit 0x00;
  __emit 0x00;
  __emit 0xf3;
  __emit 0xa5;
  __emit 0x8b;
  __emit 0xca;
  __emit 0x83;
  __emit 0xe1;
  __emit 0x03;
  __emit 0xf3;
  __emit 0xa4;
  __emit 0xc6;
  __emit 0x84;
  __emit 0x18;
  __emit 0x08;
  __emit 0x9e;
  __emit 0x00;
  __emit 0x00;
  __emit 0x00;
  __emit 0xff;
  __emit 0x45;
  __emit 0x0c;
  __emit 0xeb;
  __emit 0x06;
  __emit 0x8b;
  __emit 0x5d;
  __emit 0xfc;
  __emit 0x89;
  __emit 0x75;
  __emit 0x0c;
  __emit 0x8b;
  __emit 0x4d;
  __emit 0x0c;
  __emit 0x8b;
  __emit 0x55;
  __emit 0xf0;
  __emit 0x51;
  __emit 0x8d;
  __emit 0x83;
  __emit 0x08;
  __emit 0x9e;
  __emit 0x00;
  __emit 0x00;
  __emit 0x50;
  __emit 0x68;
  __emit 0x90;
  __emit 0x5c;
  __emit 0x11;
  __emit 0x01;
  __emit 0x52;
  __emit 0x53;
  __emit 0xe8;
  __emit 0x8f;
  __emit 0xfb;
  __emit 0xff;
  __emit 0xff;
  __emit 0x8b;
  __emit 0x45;
  __emit 0xf8;
  __emit 0x83;
  __emit 0xc4;
  __emit 0x14;
  __emit 0x83;
  __emit 0xf8;
  __emit 0x01;
  __emit 0x74;
  __emit 0x0e;
  __emit 0x6a;
  __emit 0x02;
  __emit 0x68;
  __emit 0xe8;
  __emit 0xf6;
  __emit 0x0c;
  __emit 0x01;
  __emit 0x8b;
  __emit 0xcb;
  __emit 0xe8;
  __emit 0xb6;
  __emit 0xfb;
  __emit 0xff;
  __emit 0xff;
  __emit 0x8b;
  __emit 0x45;
  __emit 0xe8;
  __emit 0x8b;
  __emit 0x4d;
  __emit 0x08;
  __emit 0x50;
  __emit 0x51;
  __emit 0x8b;
  __emit 0xcb;
  __emit 0xe8;
  __emit 0xa7;
  __emit 0xfb;
  __emit 0xff;
  __emit 0xff;
  __emit 0x6a;
  __emit 0x01;
  __emit 0x68;
  __emit 0x94;
  __emit 0x02;
  __emit 0x08;
  __emit 0x01;
  __emit 0x8b;
  __emit 0xcb;
  __emit 0xe8;
  __emit 0x99;
  __emit 0xfb;
  __emit 0xff;
  __emit 0xff;
  __emit 0x8b;
  __emit 0x7b;
  __emit 0x10;
  __emit 0x85;
  __emit 0xff;
  __emit 0x89;
  __emit 0x7d;
  __emit 0x08;
  __emit 0x74;
  __emit 0x42;
  __emit 0x8b;
  __emit 0x77;
  __emit 0x04;
  __emit 0x8d;
  __emit 0x83;
  __emit 0x08;
  __emit 0x9e;
  __emit 0x00;
  __emit 0x00;
  __emit 0x8d;
  __emit 0x9b;
  __emit 0x00;
  __emit 0x00;
  __emit 0x00;
  __emit 0x00;
  __emit 0x8a;
  __emit 0x10;
  __emit 0x8a;
  __emit 0xca;
  __emit 0x3a;
  __emit 0x16;
  __emit 0x75;
  __emit 0x1c;
  __emit 0x84;
  __emit 0xc9;
  __emit 0x74;
  __emit 0x14;
  __emit 0x8a;
  __emit 0x50;
  __emit 0x01;
  __emit 0x8a;
  __emit 0xca;
  __emit 0x3a;
  __emit 0x56;
  __emit 0x01;
  __emit 0x75;
  __emit 0x0e;
  __emit 0x83;
  __emit 0xc0;
  __emit 0x02;
  __emit 0x83;
  __emit 0xc6;
  __emit 0x02;
  __emit 0x84;
  __emit 0xc9;
  __emit 0x75;
  __emit 0xe0;
  __emit 0x33;
  __emit 0xc0;
  __emit 0xeb;
  __emit 0x05;
  __emit 0x1b;
  __emit 0xc0;
  __emit 0x83;
  __emit 0xd8;
  __emit 0xff;
  __emit 0x85;
  __emit 0xc0;
  __emit 0x74;
  __emit 0x2b;
  __emit 0x8b;
  __emit 0x3f;
  __emit 0x85;
  __emit 0xff;
  __emit 0x75;
  __emit 0xbe;
  __emit 0x8b;
  __emit 0x03;
  __emit 0x68;
  __emit 0xc0;
  __emit 0x31;
  __emit 0x13;
  __emit 0x01;
  __emit 0x8b;
  __emit 0xcb;
  __emit 0xff;
  __emit 0x50;
  __emit 0x38;
  __emit 0x8b;
  __emit 0x10;
  __emit 0x8d;
  __emit 0x8b;
  __emit 0x08;
  __emit 0x9e;
  __emit 0x00;
  __emit 0x00;
  __emit 0x51;
  __emit 0x8b;
  __emit 0xc8;
  __emit 0xff;
  __emit 0x52;
  __emit 0x38;
  __emit 0x8b;
  __emit 0x45;
  __emit 0x0c;
  __emit 0xc6;
  __emit 0x00;
  __emit 0x00;
  __emit 0xe9;
  __emit 0xd4;
  __emit 0x00;
  __emit 0x00;
  __emit 0x00;
  __emit 0x8b;
  __emit 0x4d;
  __emit 0x0c;
  __emit 0x80;
  __emit 0x39;
  __emit 0x00;
  __emit 0x0f;
  __emit 0x84;
  __emit 0xc8;
  __emit 0x00;
  __emit 0x00;
  __emit 0x00;
  __emit 0x8b;
  __emit 0x5d;
  __emit 0x08;
  __emit 0x85;
  __emit 0xdb;
  __emit 0x0f;
  __emit 0x84;
  __emit 0x7e;
  __emit 0x00;
  __emit 0x00;
  __emit 0x00;
  __emit 0x90;
  __emit 0x8b;
  __emit 0x45;
  __emit 0xfc;
  __emit 0x8b;
  __emit 0x73;
  __emit 0x04;
  __emit 0x05;
  __emit 0x08;
  __emit 0x9e;
  __emit 0x00;
  __emit 0x00;
  __emit 0xeb;
  __emit 0x03;
  __emit 0x8d;
  __emit 0x49;
  __emit 0x00;
  __emit 0x8a;
  __emit 0x10;
  __emit 0x8a;
  __emit 0xca;
  __emit 0x3a;
  __emit 0x16;
  __emit 0x75;
  __emit 0x1c;
  __emit 0x84;
  __emit 0xc9;
  __emit 0x74;
  __emit 0x14;
  __emit 0x8a;
  __emit 0x50;
  __emit 0x01;
  __emit 0x8a;
  __emit 0xca;
  __emit 0x3a;
  __emit 0x56;
  __emit 0x01;
  __emit 0x75;
  __emit 0x0e;
  __emit 0x83;
  __emit 0xc0;
  __emit 0x02;
  __emit 0x83;
  __emit 0xc6;
  __emit 0x02;
  __emit 0x84;
  __emit 0xc9;
  __emit 0x75;
  __emit 0xe0;
  __emit 0x33;
  __emit 0xc0;
  __emit 0xeb;
  __emit 0x05;
  __emit 0x1b;
  __emit 0xc0;
  __emit 0x83;
  __emit 0xd8;
  __emit 0xff;
  __emit 0x85;
  __emit 0xc0;
  __emit 0x75;
  __emit 0x3a;
  __emit 0x8b;
  __emit 0x75;
  __emit 0x0c;
  __emit 0x8b;
  __emit 0x4b;
  __emit 0x08;
  __emit 0x8b;
  __emit 0x01;
  __emit 0x8d;
  __emit 0x95;
  __emit 0x5c;
  __emit 0xfe;
  __emit 0xff;
  __emit 0xff;
  __emit 0x52;
  __emit 0x8b;
  __emit 0x55;
  __emit 0xf4;
  __emit 0x4a;
  __emit 0x52;
  __emit 0x8b;
  __emit 0x55;
  __emit 0xf8;
  __emit 0x52;
  __emit 0x8b;
  __emit 0x55;
  __emit 0xfc;
  __emit 0x56;
  __emit 0x52;
  __emit 0xff;
  __emit 0x50;
  __emit 0x04;
  __emit 0x84;
  __emit 0xc0;
  __emit 0x74;
  __emit 0x16;
  __emit 0xbf;
  __emit 0xb8;
  __emit 0x31;
  __emit 0x13;
  __emit 0x01;
  __emit 0xb9;
  __emit 0x05;
  __emit 0x00;
  __emit 0x00;
  __emit 0x00;
  __emit 0x33;
  __emit 0xc0;
  __emit 0xf3;
  __emit 0xa6;
  __emit 0x75;
  __emit 0x48;
  __emit 0x83;
  __emit 0x7d;
  __emit 0xf4;
  __emit 0x01;
  __emit 0x7f;
  __emit 0x42;
  __emit 0x8b;
  __emit 0x1b;
  __emit 0x85;
  __emit 0xdb;
  __emit 0x75;
  __emit 0x83;
  __emit 0x8b;
  __emit 0x45;
  __emit 0xf8;
  __emit 0x85;
  __emit 0xc0;
  __emit 0x75;
  __emit 0x35;
  __emit 0x8b;
  __emit 0x75;
  __emit 0x0c;
  __emit 0xbf;
  __emit 0xb8;
  __emit 0x31;
  __emit 0x13;
  __emit 0x01;
  __emit 0xb9;
  __emit 0x05;
  __emit 0x00;
  __emit 0x00;
  __emit 0x00;
  __emit 0x33;
  __emit 0xd2;
  __emit 0xf3;
  __emit 0xa6;
  __emit 0x74;
  __emit 0x0f;
  __emit 0x8b;
  __emit 0x4d;
  __emit 0xfc;
  __emit 0x8b;
  __emit 0x01;
  __emit 0x68;
  __emit 0xa8;
  __emit 0x31;
  __emit 0x13;
  __emit 0x01;
  __emit 0xff;
  __emit 0x50;
  __emit 0x38;
  __emit 0xeb;
  __emit 0x13;
  __emit 0x83;
  __emit 0x7d;
  __emit 0xf4;
  __emit 0x01;
  __emit 0x7e;
  __emit 0x0d;
  __emit 0x8b;
  __emit 0x4d;
  __emit 0xfc;
  __emit 0x8b;
  __emit 0x11;
  __emit 0x68;
  __emit 0x84;
  __emit 0x31;
  __emit 0x13;
  __emit 0x01;
  __emit 0xff;
  __emit 0x52;
  __emit 0x38;
  __emit 0x8b;
  __emit 0x5d;
  __emit 0xfc;
  __emit 0x6a;
  __emit 0x00;
  __emit 0x8b;
  __emit 0xcb;
  __emit 0xe8;
  __emit 0x8b;
  __emit 0xf3;
  __emit 0xff;
  __emit 0xff;
  __emit 0x8b;
  __emit 0x55;
  __emit 0xec;
  __emit 0x52;
  __emit 0xe8;
  __emit 0x22;
  __emit 0x3c;
  __emit 0x00;
  __emit 0x00;
  __emit 0x83;
  __emit 0xc4;
  __emit 0x04;
  __emit 0x5f;
  __emit 0x5e;
  __emit 0x5b;
  }
}

// little helper to get app window
static BOOL CALLBACK EnumThreadWndProc(HWND hwnd, LPARAM lParam)
{
  *(HWND *)lParam=hwnd;
  return FALSE;
}

// Keep this matched callback emitted after IsWindowed moved to its exact thunk.
static BOOL (CALLBACK * volatile EnumThreadWndProcAnchor)(HWND, LPARAM) = EnumThreadWndProc;

// ?IsWindowed@Debug@@AAE_NXZ is emitted by DebugIsWindowedThunk.cpp.

//////////////////////////////////////////////////////////////////////////////

// And finally for a little list of C/C++ runtime replacement functions.

// Abort process due to fatal heap error
void __cdecl _heap_abort(void)
{
  DCRASH_RELEASE("Fatal heap error.");
}
