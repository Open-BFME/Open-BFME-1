// cl: /DNDEBUG /DWIN32 /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
#include "PreRTS.h"
#include "Common/DataChunk.h"
// BFME GlobalLighting version 7 writer. The old PolygonTrigger identity
// conflicts with the chunk literal, write-only callees and cdecl argument.
// GlobalData offsets 0x218, 0x290 and 0x518 are name_oracle witnesses.
struct Rva00748860LightingData {
    char padding0000[0x218];
    int m_timeOfDay;
    char padding021c[0x290-0x21c];
    float m_terrainLighting[4][3][9];
    char padding0440[0x518-0x440];
    float m_terrainObjectsLighting[4][3][9];
    char padding06c8[0x7a0-0x6c8];
    float field_07a0[4][3][9];
    char padding0950[0xdbc-0x950];
    bool field_0dbc;
    char field_0dbd;
};
struct Rva00748860Triple { float x, y, z; };
extern Rva00748860Triple g_lighting012B4FC8;
extern Rva00748860Triple g_lighting012B4FD8;
extern Rva00748860Triple g_lighting012B4FE8;
extern Rva00748860LightingData *lightingData;
void WriteGlobalLighting00748860(DataChunkOutput *output)
{
    output->openDataChunk("GlobalLighting", 7);
    output->writeInt(lightingData->m_timeOfDay);
    for (int i=0; i<4; ++i) {
        output->writeReal(lightingData->m_terrainLighting[i][0][0]);
        output->writeReal(lightingData->m_terrainLighting[i][0][1]);
        output->writeReal(lightingData->m_terrainLighting[i][0][2]);
        output->writeReal(lightingData->m_terrainLighting[i][0][3]);
        output->writeReal(lightingData->m_terrainLighting[i][0][4]);
        output->writeReal(lightingData->m_terrainLighting[i][0][5]);
        output->writeReal(lightingData->m_terrainLighting[i][0][6]);
        output->writeReal(lightingData->m_terrainLighting[i][0][7]);
        output->writeReal(lightingData->m_terrainLighting[i][0][8]);
        output->writeReal(lightingData->m_terrainObjectsLighting[i][0][0]);
        output->writeReal(lightingData->m_terrainObjectsLighting[i][0][1]);
        output->writeReal(lightingData->m_terrainObjectsLighting[i][0][2]);
        output->writeReal(lightingData->m_terrainObjectsLighting[i][0][3]);
        output->writeReal(lightingData->m_terrainObjectsLighting[i][0][4]);
        output->writeReal(lightingData->m_terrainObjectsLighting[i][0][5]);
        output->writeReal(lightingData->m_terrainObjectsLighting[i][0][6]);
        output->writeReal(lightingData->m_terrainObjectsLighting[i][0][7]);
        output->writeReal(lightingData->m_terrainObjectsLighting[i][0][8]);
        for (int j=1; j<3; ++j) {
            output->writeReal(lightingData->m_terrainObjectsLighting[i][j][0]);
            output->writeReal(lightingData->m_terrainObjectsLighting[i][j][1]);
            output->writeReal(lightingData->m_terrainObjectsLighting[i][j][2]);
            output->writeReal(lightingData->m_terrainObjectsLighting[i][j][3]);
            output->writeReal(lightingData->m_terrainObjectsLighting[i][j][4]);
            output->writeReal(lightingData->m_terrainObjectsLighting[i][j][5]);
            output->writeReal(lightingData->m_terrainObjectsLighting[i][j][6]);
            output->writeReal(lightingData->m_terrainObjectsLighting[i][j][7]);
            output->writeReal(lightingData->m_terrainObjectsLighting[i][j][8]);
        }
        for (int j=1; j<3; ++j) {
            output->writeReal(lightingData->m_terrainLighting[i][j][0]);
            output->writeReal(lightingData->m_terrainLighting[i][j][1]);
            output->writeReal(lightingData->m_terrainLighting[i][j][2]);
            output->writeReal(lightingData->m_terrainLighting[i][j][3]);
            output->writeReal(lightingData->m_terrainLighting[i][j][4]);
            output->writeReal(lightingData->m_terrainLighting[i][j][5]);
            output->writeReal(lightingData->m_terrainLighting[i][j][6]);
            output->writeReal(lightingData->m_terrainLighting[i][j][7]);
            output->writeReal(lightingData->m_terrainLighting[i][j][8]);
        }
        for (int j=0; j<3; ++j) {
            output->writeReal(lightingData->field_07a0[i][j][0]);
            output->writeReal(lightingData->field_07a0[i][j][1]);
            output->writeReal(lightingData->field_07a0[i][j][2]);
            output->writeReal(lightingData->field_07a0[i][j][3]);
            output->writeReal(lightingData->field_07a0[i][j][4]);
            output->writeReal(lightingData->field_07a0[i][j][5]);
            output->writeReal(lightingData->field_07a0[i][j][6]);
            output->writeReal(lightingData->field_07a0[i][j][7]);
            output->writeReal(lightingData->field_07a0[i][j][8]);
        }
    }
    float x,y,z;
    float multiplier = lightingData->field_0dbc ? 2.0f : 1.0f;
    output->writeReal(multiplier);
    output->writeInt(lightingData->field_0dbd != 0);
    x = g_lighting012B4FC8.x; y = g_lighting012B4FC8.y; z = g_lighting012B4FC8.z;
      output->writeReal(x);
      output->writeReal(y);
      output->writeReal(z);
    x = g_lighting012B4FD8.x; y = g_lighting012B4FD8.y; z = g_lighting012B4FD8.z;
      output->writeReal(x);
      output->writeReal(y);
      output->writeReal(z);
    x = g_lighting012B4FE8.x; y = g_lighting012B4FE8.y; z = g_lighting012B4FE8.z;
      output->writeReal(x);
      output->writeReal(y);
      output->writeReal(z);
    output->writeInt(*(int*)(*(char**)0x01306EEC + 4));
    output->closeDataChunk();
}
