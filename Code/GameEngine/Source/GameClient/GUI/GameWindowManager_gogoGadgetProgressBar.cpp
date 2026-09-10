// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/gamewindowlist /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
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

// Retail 0x0047D500 is the reduced BFME progress-bar factory body.  The
// source tree also retains the larger upstream declaration, but this body is
// the three-argument vslot-21 entry selected by the BFME gadget path.

class GameWindow;
class GameFont;

class WinInstanceData
{
public:
	char padBeforeStyle[0xc];
	unsigned int style;
};

class GameWindow
{
public:
	int winSetOwner(GameWindow *owner);
};

// The first argument is a factory input record, not an instantiated window.
// The matched selector at78F8D0 writes its factory field at18 and forwards
// the record; this body reads owner0 and instanceData30 from that record.
struct Rva0047D500FactoryInput
{
	GameWindow *owner;
	char pad[0x2c];
	WinInstanceData *instanceData;
};

class GameWindowManager
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual void v06();
	virtual void v07();
	virtual void v08();
	virtual void v09();
	virtual void v10();
	virtual void v11();
	virtual void v12();
	virtual void v13();
	virtual void v14();
	virtual void v15();
	virtual void v16();
	virtual void v17();
	virtual void v18();
	virtual void v19();
	virtual void v20();
	virtual GameWindow *gogoGadgetProgressBar(Rva0047D500FactoryInput *, GameFont *, bool);
	virtual void v22();
	virtual void v23();
	virtual void v24();
	virtual void assignDefaultGadgetLook(GameWindow *, GameFont *, bool);
	virtual void v26();
	virtual void v27();
	virtual void v28();
	virtual GameWindow *create(Rva0047D500FactoryInput *);
};

extern GameWindowManager *TheWindowManager;

// Complete87B ends47D557CC; ctor483760 installs10F8B60 whose slot21
// points throughILT178FA to47D500. ExistingwinSetOwner pin47230 routes
// to478D80: writesowner44 andreturns0 withret4.

GameWindow *GameWindowManager::gogoGadgetProgressBar(Rva0047D500FactoryInput *input,
	GameFont *defaultFont, bool defaultVisual)
{
	if ((input->instanceData->style & 0x100) == 0)
		return 0;
	GameWindow *progressBar = TheWindowManager->create(input);
	if (progressBar == 0)
		return 0;
	progressBar->winSetOwner(input->owner);
	assignDefaultGadgetLook(progressBar, defaultFont, defaultVisual);
	return progressBar;
}
