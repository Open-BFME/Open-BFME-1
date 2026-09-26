// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/asciistring8outofline /Iinputs/reference/shims/terrainlogic /Iinputs/reference/shims/water /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
#define Matrix4x4 Matrix4
#include "PreRTS.h"
#include "sphere.h"
#include "aabox.h"
#include "dx8vertexbuffer.h"
#include "dx8indexbuffer.h"
#include "texture.h"
#include "shader.h"
#include "rinfo.h"
#include "W3DDevice/GameClient/W3DWaterTracks.h"
#include <stdio.h>
#include <string.h>

class BFMETerrainLogic
{
public:
	virtual void slot00() = 0; virtual void slot01() = 0;
	virtual void slot02() = 0; virtual void slot03() = 0;
	virtual void slot04() = 0; virtual void slot05() = 0;
	virtual void slot06() = 0; virtual void slot07() = 0;
	virtual void slot08() = 0; virtual void slot09() = 0;
	virtual void slot10() = 0; virtual void slot11() = 0;
	virtual void slot12() = 0; virtual void slot13() = 0;
	virtual void slot14() = 0; virtual void slot15() = 0;
	virtual void slot16() = 0;
	virtual AsciiString getSourceFilename() = 0;
};

extern BFMETerrainLogic *TheTerrainLogic;

void WaterTracksRenderSystem::saveTracks()
{
	if (TheTerrainLogic == 0) {
		return;
	}
	AsciiString file_name = TheTerrainLogic->getSourceFilename();
	char path[256];
	strcpy(path, file_name.str());
	Int length = strlen(path);
	strcpy(path + length - 4, ".wak");

	Int track_count = 0;
	FILE *file = fopen(path, "wb");
	if (file != 0) {
		WaterTracksObj *track = m_usedModules;
		while (track != 0) {
			if (track->m_initTimeOffset == 0) {
				fwrite(&track->m_initStartPos, sizeof(track->m_startPos), 1, file);
				fwrite(&track->m_initEndPos, sizeof(track->m_perpDir), 1, file);
				fwrite(&track->m_type, sizeof(track->m_type), 1, file);
				++track_count;
			}
			track = track->m_nextSystem;
		}
		fwrite(&track_count, sizeof(track_count), 1, file);
		fclose(file);
	}
}
