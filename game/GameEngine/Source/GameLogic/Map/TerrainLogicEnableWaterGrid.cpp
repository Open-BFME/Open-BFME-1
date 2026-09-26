// cl: /Iinputs/reference/shims/campaignmanagerascii /Igame/Libraries/Source/WWVegas/WWLib /Igame/GameEngine/Include /DNDEBUG /DWIN32 /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Igame/GameEngine/Source/Common/System /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
// TerrainLogic::enableWaterGrid, retail RVA 0x001A8820, 718 bytes.
// Identity: ZH TerrainLogic.cpp water-map selection and the four TerrainVisual
// operations agree with the retail strings, field accesses and virtual slots.
// Capstone: INT3 before the start; final ret 4 at 0x001A8AEB, INT3 at 0x001A8AEE.
//
// Use the TerrainLogic declaration and the shared StringBase/AsciiString headers.
// BFME moved the enabled flag to +0x44; the ZH-derived TerrainLogic header does
// not yet describe that layout. The two address-derived views below describe
// only the independently decoded GlobalData fields and TerrainVisual slots.
//
// StringBase accessors are the existing retail implementations, exposed inline
// as they were in this TU. Returning immediately from a nonzero comparison
// keeps its result out of the EH frame (retail allocates 0x0c local bytes).

#include <new>
// GameMemory.h must reuse the placement operators supplied by <new>.
#define _OPERATOR_NEW_DEFINED_
#include <string.h>
#include "Common/AsciiString.h"
#include "GameLogic/TerrainLogic.h"
#pragma intrinsic(strlen)
template<> inline const char* StringBase<char>::str() const { return m_data ? m_data->data : ""; }
template<> inline void StringBase<char>::set(const char* s) { set(s, s ? strlen(s) : 0); }
template<> inline int StringBase<char>::compareNoCase(const char* s, int len) const {
    const int myLen = m_data ? m_data->length : 0;
    const char* data = m_data ? m_data->data : "";
    int result = _memicmp(data, s, myLen < len ? myLen : len);
    if (result != 0) return result; return myLen - len;
}
template<> inline int StringBase<char>::compareNoCase(const char* s) const { return compareNoCase(s, s ? strlen(s) : 0); }
inline AsciiString::~AsciiString() { ((StringBase<char>*)this)->releaseBuffer(); }


class Rva001A8820GlobalData {
public:
    char pad[8];
    AsciiString m_mapName;
    char pad0c[0x90];
    AsciiString m_vertexWaterAvailableMaps[4];
    float m_vertexWaterHeightClampLow[4], m_vertexWaterHeightClampHi[4];
    float m_vertexWaterAngle[4], m_vertexWaterXPosition[4], m_vertexWaterYPosition[4], m_vertexWaterZPosition[4];
    int m_vertexWaterXGridCells[4], m_vertexWaterYGridCells[4];
    float m_vertexWaterGridSize[4], m_vertexWaterAttenuationA[4], m_vertexWaterAttenuationB[4], m_vertexWaterAttenuationC[4], m_vertexWaterAttenuationRange[4];
};
extern Rva001A8820GlobalData* TheGlobalData;
class WaterHandle;
class Rva001A8820TerrainVisual {
public:
    virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0c();
    virtual void slot10(); virtual void slot14(); virtual void slot18(); virtual void slot1c();
    virtual void slot20(); virtual void slot24();
    virtual void enableWaterGrid(bool);
    virtual void setWaterGridHeightClamps(const WaterHandle*,float,float);
    virtual void setWaterAttenuationFactors(const WaterHandle*,float,float,float,float);
    virtual void slot34();
    virtual void setWaterTransform(const WaterHandle*,float,float,float,float);
    virtual void slot3c();
    virtual void setWaterGridResolution(const WaterHandle*,float,float,float);
};
extern Rva001A8820TerrainVisual* TheTerrainVisual;
void TerrainLogic::enableWaterGrid(bool enable) {
    // m_waterGridEnabled in the BFME layout.
    *(bool*)((char*)this + 0x44) = enable;
    if (enable == true) {
        int waterSettingIndex = -1;
        for (int i = 0; i < 4; i++) {
            if (TheGlobalData->m_mapName.compareNoCase(TheGlobalData->m_vertexWaterAvailableMaps[i].str()) == 0) {
                waterSettingIndex = i; break;
            }
            AsciiString strippedMapNameOnly;
            AsciiString strippedCompareMapNameOnly;
            const char* c;
            c = strrchr(TheGlobalData->m_mapName.str(), '\\');
            if(c) strippedMapNameOnly.set(c);
            else strippedMapNameOnly = TheGlobalData->m_mapName;
            c = strrchr(TheGlobalData->m_vertexWaterAvailableMaps[i].str(), '\\');
            if(c) strippedCompareMapNameOnly.set(c);
            else strippedCompareMapNameOnly = TheGlobalData->m_vertexWaterAvailableMaps[i];
            if(strippedMapNameOnly.compareNoCase(strippedCompareMapNameOnly.str()) == 0) { waterSettingIndex = i; break; }
        }
        if(waterSettingIndex == -1) return;
        TheTerrainVisual->setWaterGridHeightClamps(0,TheGlobalData->m_vertexWaterHeightClampLow[waterSettingIndex],TheGlobalData->m_vertexWaterHeightClampHi[waterSettingIndex]);
        TheTerrainVisual->setWaterTransform(0,TheGlobalData->m_vertexWaterAngle[waterSettingIndex],TheGlobalData->m_vertexWaterXPosition[waterSettingIndex],TheGlobalData->m_vertexWaterYPosition[waterSettingIndex],TheGlobalData->m_vertexWaterZPosition[waterSettingIndex]);
        TheTerrainVisual->setWaterGridResolution(0,TheGlobalData->m_vertexWaterXGridCells[waterSettingIndex],TheGlobalData->m_vertexWaterYGridCells[waterSettingIndex],TheGlobalData->m_vertexWaterGridSize[waterSettingIndex]);
        TheTerrainVisual->setWaterAttenuationFactors(0,TheGlobalData->m_vertexWaterAttenuationA[waterSettingIndex],TheGlobalData->m_vertexWaterAttenuationB[waterSettingIndex],TheGlobalData->m_vertexWaterAttenuationC[waterSettingIndex],TheGlobalData->m_vertexWaterAttenuationRange[waterSettingIndex]);
    }
    TheTerrainVisual->enableWaterGrid(enable);
}
