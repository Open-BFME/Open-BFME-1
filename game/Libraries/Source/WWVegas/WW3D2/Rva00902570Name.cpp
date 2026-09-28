// cl: /O2
// Retail 00902570: INT3 before start; switch returns before its tables.
// Jump table at 00902734; index table at 0090284C through 00902908.
const char* Rva00902570Name(unsigned state)
{
    switch (state) {
    case 7: return "D3DRS_ZENABLE";
    case 8: return "D3DRS_FILLMODE";
    case 9: return "D3DRS_SHADEMODE";
    case 14: return "D3DRS_ZWRITEENABLE";
    case 15: return "D3DRS_ALPHATESTENABLE";
    case 16: return "D3DRS_LASTPIXEL";
    case 19: return "D3DRS_SRCBLEND";
    case 20: return "D3DRS_DESTBLEND";
    case 22: return "D3DRS_CULLMODE";
    case 23: return "D3DRS_ZFUNC";
    case 24: return "D3DRS_ALPHAREF";
    case 25: return "D3DRS_ALPHAFUNC";
    case 26: return "D3DRS_DITHERENABLE";
    case 27: return "D3DRS_ALPHABLENDENABLE";
    case 28: return "D3DRS_FOGENABLE";
    case 29: return "D3DRS_SPECULARENABLE";
    case 34: return "D3DRS_FOGCOLOR";
    case 35: return "D3DRS_FOGTABLEMODE";
    case 36: return "D3DRS_FOGSTART";
    case 37: return "D3DRS_FOGEND";
    case 38: return "D3DRS_FOGDENSITY";
    case 195: return "D3DRS_DEPTHBIAS";
    case 48: return "D3DRS_RANGEFOGENABLE";
    case 52: return "D3DRS_STENCILENABLE";
    case 53: return "D3DRS_STENCILFAIL";
    case 54: return "D3DRS_STENCILZFAIL";
    case 55: return "D3DRS_STENCILPASS";
    case 56: return "D3DRS_STENCILFUNC";
    case 57: return "D3DRS_STENCILREF";
    case 58: return "D3DRS_STENCILMASK";
    case 59: return "D3DRS_STENCILWRITEMASK";
    case 60: return "D3DRS_TEXTUREFACTOR";
    case 128: return "D3DRS_WRAP0";
    case 129: return "D3DRS_WRAP1";
    case 130: return "D3DRS_WRAP2";
    case 131: return "D3DRS_WRAP3";
    case 132: return "D3DRS_WRAP4";
    case 133: return "D3DRS_WRAP5";
    case 134: return "D3DRS_WRAP6";
    case 135: return "D3DRS_WRAP7";
    case 136: return "D3DRS_CLIPPING";
    case 137: return "D3DRS_LIGHTING";
    case 139: return "D3DRS_AMBIENT";
    case 140: return "D3DRS_FOGVERTEXMODE";
    case 141: return "D3DRS_COLORVERTEX";
    case 142: return "D3DRS_LOCALVIEWER";
    case 143: return "D3DRS_NORMALIZENORMALS";
    case 145: return "D3DRS_DIFFUSEMATERIALSOURCE";
    case 146: return "D3DRS_SPECULARMATERIALSOURCE";
    case 147: return "D3DRS_AMBIENTMATERIALSOURCE";
    case 148: return "D3DRS_EMISSIVEMATERIALSOURCE";
    case 151: return "D3DRS_VERTEXBLEND";
    case 152: return "D3DRS_CLIPPLANEENABLE";
    case 154: return "D3DRS_POINTSIZE";
    case 155: return "D3DRS_POINTSIZE_MIN";
    case 156: return "D3DRS_POINTSPRITEENABLE";
    case 157: return "D3DRS_POINTSCALEENABLE";
    case 158: return "D3DRS_POINTSCALE_A";
    case 159: return "D3DRS_POINTSCALE_B";
    case 160: return "D3DRS_POINTSCALE_C";
    case 161: return "D3DRS_MULTISAMPLEANTIALIAS";
    case 162: return "D3DRS_MULTISAMPLEMASK";
    case 163: return "D3DRS_PATCHEDGESTYLE";
    case 165: return "D3DRS_DEBUGMONITORTOKEN";
    case 166: return "D3DRS_POINTSIZE_MAX";
    case 167: return "D3DRS_INDEXEDVERTEXBLENDENABLE";
    case 168: return "D3DRS_COLORWRITEENABLE";
    case 170: return "D3DRS_TWEENFACTOR";
    case 171: return "D3DRS_BLENDOP";
    default: return "UNKNOWN";
    }
}
