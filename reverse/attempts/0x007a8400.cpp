// ?drawRiverWater@WaterRenderObjClass@@IAEXPAVPolygonTrigger@@@Z
// partial score=0.7 date=2026-09-18
// ?drawRiverWater@WaterRenderObjClass@@IAEXPAVPolygonTrigger@@@Z
void WaterRenderObjClass::drawRiverWater(PolygonTrigger *pTrig)
{
    struct BfmeRiverPolygonView
    {
        unsigned char unknown00[8];
        Int riverStart;
        unsigned char unknown0c[0x18];
        TextureClass *riverTexture;
        unsigned char unknown28[0x14];
        unsigned char additiveBlend;
        Real shadeR;
        Real shadeG;
        Real shadeB;
        unsigned char unknown4c[8];
        ICoord3D *points;
        Int numPoints;
        Real riverVOrigin;
    };

    BfmeRiverPolygonView *river = (BfmeRiverPolygonView *)pTrig;

    DX8Wrapper::Invalidate_Cached_Render_States();
    Int rectangleCount = river->numPoints/2;
    rectangleCount--;
    Real bumpFactor = 5;
    static Bool doWobble = true;
    if (m_disableRiver) return;
    *(volatile unsigned char *)((char *)this + 0x2c4) = 1;

    DynamicIBAccessClass ib_access(BUFFER_TYPE_DYNAMIC_DX8,(rectangleCount+1)*2*3);
    {
        DynamicIBAccessClass::WriteLockClass lockib(&ib_access);
        UnsignedShort *curIb = lockib.Get_Index_Array();
        for (Int i=0; i<rectangleCount; i++)
        {
            curIb[0] = i*2;
            curIb[1] = i*2+1;
            curIb[2] = i*2+3;
            curIb[3] = i*2;
            curIb[4] = i*2+3;
            curIb[5] = i*2+2;
            curIb += 6;
        }
        IndexBufferExceptionFunc();
    }

    Real shadeR=river->shadeR;
    Real shadeG=river->shadeG;
    Real shadeB=river->shadeB;
    if ( shadeR==1.0f && shadeG==1.0f && shadeB==1.0f)
    {
        shadeR = TheGlobalData->m_terrainAmbient[0].red;
        shadeG = TheGlobalData->m_terrainAmbient[0].green;
        shadeB = TheGlobalData->m_terrainAmbient[0].blue;
        for (Int lightIndex=0; lightIndex < TheGlobalData->m_numGlobalLights; lightIndex++)
        {
            if (-TheGlobalData->m_terrainLightPos[lightIndex].z > 0)
            {
                shadeR += -TheGlobalData->m_terrainLightPos[lightIndex].z * TheGlobalData->m_terrainDiffuse[lightIndex].red;
                shadeG += -TheGlobalData->m_terrainLightPos[lightIndex].z * TheGlobalData->m_terrainDiffuse[lightIndex].green;
                shadeB += -TheGlobalData->m_terrainLightPos[lightIndex].z * TheGlobalData->m_terrainDiffuse[lightIndex].blue;
            }
        }
        Real waterShadeR = (m_settings[m_tod].waterDiffuse & 0xff) / 255.0f;
        Real waterShadeG = ((m_settings[m_tod].waterDiffuse >> 8) & 0xff) / 255.0f;
        Real waterShadeB = ((m_settings[m_tod].waterDiffuse >> 16) & 0xff) / 255.0f;
        shadeR=shadeR*waterShadeR*255.0f;
        shadeG=shadeG*waterShadeG*255.0f;
        shadeB=shadeB*waterShadeB*255.0f;
    }
    else
    {
        shadeR=shadeR*255.0f;
        shadeG=shadeG*255.0f;
        shadeB=shadeB*255.0f;
        if (shadeR == 0 && shadeG == 0 && shadeB == 0)
        {
            shadeR=255;
            shadeG=255;
            shadeB=255;
        }
    }
    Int diffuse=REAL_TO_INT(shadeB) | (REAL_TO_INT(shadeG) << 8) | (REAL_TO_INT(shadeR) << 16);
    diffuse |= m_settings[m_tod].waterDiffuse & 0xff000000;

    Int innerNdx = river->riverStart;
    Int outerNdx = innerNdx+1;
    Real endLen=0;
    Real totalLen=0;
    Int i;
    for (i=0; i<river->numPoints-1; i++)
    {
        ICoord3D innerPt = river->points[i];
        ICoord3D outerPt = river->points[i+1];
        Real dx = innerPt.x-outerPt.x;
        Real dy = innerPt.y-outerPt.y;
        Real curLen = sqrt(dx*dx+dy*dy);
        totalLen += curLen;
        if ( i==innerNdx) endLen = curLen;
    }
    bumpFactor = endLen/BUMP_SIZE;
    Real lengthOfRiver = (totalLen/2)-endLen;
    Real repeatCount = lengthOfRiver / (endLen);
    Real vScale=(Real)repeatCount/(Real)rectangleCount;

#define HEIGHT_TO_USE (0.5f)
    if (innerNdx >= river->numPoints-1) return;
    DynamicVBAccessClass vb_access(BUFFER_TYPE_DYNAMIC_DX8,dynamic_fvf_type,(rectangleCount+1)*2);
    {
        DynamicVBAccessClass::WriteLockClass lock(&vb_access);
        VertexFormatXYZNDUV2* vb=lock.Get_Formatted_Vertex_Array();
        Real constA=3*river->riverVOrigin;
        for (i=0; i<(river->numPoints/2); i++)
        {
            Real x,y;
            ICoord3D innerPt = river->points[outerNdx];
            ICoord3D outerPt = river->points[innerNdx];
            outerNdx++;
            innerNdx--;
            if (innerNdx<0) innerNdx = river->numPoints-1;
            if (outerNdx >= river->numPoints) outerNdx = 0;
            x=innerPt.x;
            y=innerPt.y;
            vb->x=x;
            vb->y=y;
            vb->z=innerPt.z;
            vb->diffuse= diffuse;
            Real wobbleConst=-river->riverVOrigin+vScale*(Real)i + WWMath::Fast_Sin(2*PI*(vScale*(Real)i) - constA)/22.0f;
            vb->v1=wobbleConst;
            vb->u1=HEIGHT_TO_USE;
            vb->v2=wobbleConst;
            vb->u2=1.0f;
            vb->nx = 0;
            vb->ny = 0;
            vb->nz = 1.0f;
            vb++;
            x=outerPt.x;
            y=outerPt.y;
            vb->x=x;
            vb->y=y;
            vb->z=outerPt.z;
            vb->diffuse= diffuse;
            vb->v1=wobbleConst;
            vb->u1=0;
            vb->v2=wobbleConst;
            vb->u2 = 0;
            vb->nx = 0;
            vb->ny = 0;
            vb->nz = 1.0f;
            vb++;
        }
    }

    Matrix3D tm(1);
    DX8Wrapper::Set_Transform(D3DTS_WORLD,tm);
    DX8Wrapper::Set_Index_Buffer(ib_access,0);
    DX8Wrapper::Set_Vertex_Buffer(vb_access);
    DX8Wrapper::Set_Texture(0,river->riverTexture);
    setupJbaWaterShader();
    if (river->additiveBlend)
        DX8Wrapper::Set_DX8_Render_State(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
    if (m_riverWaterPixelShader) DX8Wrapper::_Get_D3D_Device8()->SetPixelShader(m_riverWaterPixelShader);
    DWORD cull;
    DX8Wrapper::_Get_D3D_Device8()->GetRenderState(D3DRS_CULLMODE, &cull);
    DX8Wrapper::_Get_D3D_Device8()->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
    if (wireframeForDebug)
        DX8Wrapper::_Get_D3D_Device8()->SetRenderState(D3DRS_FILLMODE,D3DFILL_WIREFRAME);
    DX8Wrapper::Draw_Triangles(0,rectangleCount*2,0,(rectangleCount+1)*2);
    if (wireframeForDebug)
        DX8Wrapper::_Get_D3D_Device8()->SetRenderState(D3DRS_FILLMODE,D3DFILL_SOLID);
    if (m_riverWaterPixelShader) DX8Wrapper::_Get_D3D_Device8()->SetPixelShader(NULL);
    if (river->additiveBlend)
        DX8Wrapper::Set_DX8_Render_State(D3DRS_SRCBLEND, D3DBLEND_ONE);
    if (TheTerrainRenderObject->getShroud())
    {
        W3DShaderManager::setTexture(0,TheTerrainRenderObject->getShroud()->getShroudTexture());
        W3DShaderManager::setShader(W3DShaderManager::ST_SHROUD_TEXTURE, 0);
        DX8Wrapper::_Get_D3D_Device8()->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
        DX8Wrapper::_Get_D3D_Device8()->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
        DX8Wrapper::Draw_Triangles(0,rectangleCount*2,0,(rectangleCount+1)*2);
        DX8Wrapper::_Get_D3D_Device8()->SetRenderState(D3DRS_ZFUNC, D3DCMP_EQUAL);
        W3DShaderManager::resetShader(W3DShaderManager::ST_SHROUD_TEXTURE);
    }
    DX8Wrapper::_Get_D3D_Device8()->SetRenderState(D3DRS_CULLMODE, cull);
}
