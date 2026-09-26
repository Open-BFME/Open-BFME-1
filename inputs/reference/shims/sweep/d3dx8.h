#pragma once
// Route to the validated BFME DX8/D3DX shim (types, FVF, math).
#include "../d3d8_shim_validated.h"

// wwshade declares Preprocess_And_Assemble_Shader_From_File with
// LPD3DXBUFFER out-parameters and never dereferences one, so an opaque
// forward is all the sweep needs. Without it seven wwshade translation
// units stop at a syntax error on that declaration and contribute no
// COMDATs at all. (Six more are blocked on generated .vsh_code.h headers
// that were build artifacts and are not in the tree.)
typedef struct ID3DXBuffer ID3DXBuffer, *LPD3DXBUFFER;
