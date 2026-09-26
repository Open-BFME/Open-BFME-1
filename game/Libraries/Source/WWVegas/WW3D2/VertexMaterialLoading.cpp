// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WW3D2 /Igame/Libraries/Source/WWVegas/WWSaveLoad /Igame/Libraries/Source/WWVegas/Wwutil /Igame/Libraries/Source/WWVegas/WWDownload /Igame/Libraries/Source/Compression /Igame/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/shims/sweep /Iinputs/toolchains/dx81/include
/*
** Copyright 2025 Electronic Arts Inc.
** This program is free software: you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
** GNU General Public License for more details.
** You should have received a copy of the GNU General Public License
** along with this program. If not, see <http://www.gnu.org/licenses/>.
*/
// BFME VertexMaterialClass::Parse_W3dVertexMaterialStruct at 0x00921C80,
// complete 421 bytes. The material reader at 0x00923520 calls this at
// 0x0092363A after reading a W3dVertexMaterialStruct and optional name.
// Four original RGB-to-float conversions fill the pointed D3D material;
// shininess, opacity and the two material flags follow. Retail uses the
// material pointer at +8, flags at +0x0C, name at +0x1C and dirty byte +0x68.
// RET 4 at 0x00921E22 ends before INT3 padding at 0x00921E25.
// Keeping this pure parser visible also preserves ECX for the subsequent
// mapper-argument call in Load_W3D, as in the retail translation unit.
// Original bodies: GeneralsMD WW3D2/vertmaterial.cpp and w3d_util.cpp.
#include "wwstring.h"
#include "w3d_file.h"
#include "w3d_obsolete.h"
#include "w3d_util.h"
#include "vector3.h"
#include "d3d8.h"
inline void W3dUtilityClass::Convert_Color(const W3dRGBStruct &rgb,Vector3 *set) { set->X=(float)rgb.R/255.0f; set->Y=(float)rgb.G/255.0f; set->Z=(float)rgb.B/255.0f; }
class ChunkLoadClass {
public:
    bool Open_Chunk();
    bool Close_Chunk();
    unsigned long Cur_Chunk_ID();
    unsigned long Cur_Chunk_Length();
    unsigned long Read(void *,unsigned long);
};
class VertexMaterialClass {
    unsigned char beforeMaterial[8];
    D3DMATERIAL8 *Material;
    unsigned int Flags;
    unsigned char beforeName[0x1c-0x10];
    StringClass Name;
    unsigned char beforeDirty[0x68-0x20];
    bool CRCDirty;
public:
    enum FlagsType { DEPTH_CUE=0,DEPTH_CUE_TO_ALPHA,COPY_SPECULAR_TO_DIFFUSE };
    void Set_Flag(FlagsType flag,bool onoff) { CRCDirty=true; if (onoff) Flags|=(1<<flag); else Flags&=~(1<<flag); }
    void Set_Ambient(const Vector3 &color) { CRCDirty=true; Material->Ambient.r=color.X; Material->Ambient.g=color.Y; Material->Ambient.b=color.Z; }
    void Set_Diffuse(const Vector3 &color) { CRCDirty=true; Material->Diffuse.r=color.X; Material->Diffuse.g=color.Y; Material->Diffuse.b=color.Z; }
    void Set_Specular(const Vector3 &color) { CRCDirty=true; Material->Specular.r=color.X; Material->Specular.g=color.Y; Material->Specular.b=color.Z; }
    void Set_Emissive(const Vector3 &color) { CRCDirty=true; Material->Emissive.r=color.X; Material->Emissive.g=color.Y; Material->Emissive.b=color.Z; }
    void Set_Shininess(float shin) { CRCDirty=true; Material->Power=shin; }
    void Set_Opacity(float o) { CRCDirty=true; Material->Diffuse.a=o; }
    void Set_Name(const char *name) { Name=name; }
    void Init_From_Material3(const W3dMaterial3Struct &);
    void Parse_W3dVertexMaterialStruct(const W3dVertexMaterialStruct &);
    void Parse_Mapping_Args(const W3dVertexMaterialStruct &,char *,char *);
    bool Load_W3D(ChunkLoadClass &);
};
void VertexMaterialClass::Parse_W3dVertexMaterialStruct(const W3dVertexMaterialStruct & vmat)
{
	Vector3 tmp;
	W3dUtilityClass::Convert_Color(vmat.Ambient,&tmp);
	Set_Ambient(tmp);
	
	W3dUtilityClass::Convert_Color(vmat.Diffuse,&tmp);
	Set_Diffuse(tmp);
	
	W3dUtilityClass::Convert_Color(vmat.Specular,&tmp);
	Set_Specular(tmp);

	W3dUtilityClass::Convert_Color(vmat.Emissive,&tmp);
	Set_Emissive(tmp);

	Set_Shininess(vmat.Shininess);
	Set_Opacity(vmat.Opacity);

	if (vmat.Attributes & W3DVERTMAT_USE_DEPTH_CUE) {
		Set_Flag(VertexMaterialClass::DEPTH_CUE,true);
	}

	if (vmat.Attributes & W3DVERTMAT_COPY_SPECULAR_TO_DIFFUSE) {
		Set_Flag(VertexMaterialClass::COPY_SPECULAR_TO_DIFFUSE,true);
	}
}



// BFME Load_W3D: RVA 0x00923520, complete 364-byte compiler span.
// The mesh vertex-material reader calls it at 0x0096EB8C after construction.
// It reads the original name/info/mapper-argument chunks, then parses the
// material and both mapper argument strings. RET 4 at 0x00923679 ends the
// code; the four-entry table at 0x0092367C..0x0092368B is part of this body.
// INT3 padding begins at 0x0092368C.
bool VertexMaterialClass::Load_W3D(ChunkLoadClass & cload)
{
	char name[256];

	W3dVertexMaterialStruct vmat;
	bool hasname = false;

	char *mapping0_arg_buffer = NULL;
	char *mapping1_arg_buffer = NULL;
	unsigned int mapping0_arg_len = 0U;
	unsigned int mapping1_arg_len = 0U;

	while (cload.Open_Chunk()) {
		switch (cload.Cur_Chunk_ID()) {
			case W3D_CHUNK_VERTEX_MATERIAL_NAME:
				cload.Read(&name,cload.Cur_Chunk_Length());
				hasname = true;
				break;

			case W3D_CHUNK_VERTEX_MATERIAL_INFO:
				if (cload.Read(&vmat,sizeof(vmat)) != sizeof(vmat)) {
					return false;
				}
				break;

			case W3D_CHUNK_VERTEX_MAPPER_ARGS0:
				mapping0_arg_len = cload.Cur_Chunk_Length();
				mapping0_arg_buffer = new char[mapping0_arg_len];
				if (cload.Read(mapping0_arg_buffer, mapping0_arg_len) != mapping0_arg_len) {
					return false;
				}
				break;

			case W3D_CHUNK_VERTEX_MAPPER_ARGS1:
				mapping1_arg_len = cload.Cur_Chunk_Length();
				mapping1_arg_buffer = new char[mapping1_arg_len];
				if (cload.Read(mapping1_arg_buffer, mapping1_arg_len) != mapping1_arg_len) {
					return false;
				}
				break;
		};
		cload.Close_Chunk();
	}

	if (hasname) {
		Set_Name(name);
	}

	Parse_W3dVertexMaterialStruct(vmat);
	Parse_Mapping_Args(vmat,mapping0_arg_buffer,mapping1_arg_buffer);

	delete [] mapping0_arg_buffer;
	mapping0_arg_buffer = NULL;

	delete [] mapping1_arg_buffer;
	mapping1_arg_buffer = NULL;

	return true;
}


// BFME legacy material initialization at 0x00921A50, complete 558 bytes.
// The version-3 material reader calls this at 0x0096F6E5 after reading a
// 44-byte W3dMaterial3Struct. Original GeneralsMD color/coefficient products,
// emissive and ambient conversion, shininess and opacity update the D3D
// material at +8 and mark its CRC dirty at +0x68. RET4 ends at 0x00921C7D;
// two INT3 bytes separate it from Parse_W3dVertexMaterialStruct at 0x00921C80.
void VertexMaterialClass::Init_From_Material3(const W3dMaterial3Struct & mat3)
{
	Vector3 converted_rgb,converted_coefficient,modulated_rgb;
	
	W3dUtilityClass::Convert_Color(mat3.DiffuseColor,&converted_rgb);
	W3dUtilityClass::Convert_Color(mat3.DiffuseCoefficients,&converted_coefficient);
	modulated_rgb.X = converted_rgb.X * converted_coefficient.X;
	modulated_rgb.Y = converted_rgb.Y * converted_coefficient.Y;
	modulated_rgb.Z = converted_rgb.Z * converted_coefficient.Z;
	Set_Diffuse(modulated_rgb);

	W3dUtilityClass::Convert_Color(mat3.SpecularColor,&converted_rgb);
	W3dUtilityClass::Convert_Color(mat3.SpecularCoefficients,&converted_coefficient);
	modulated_rgb.X = converted_rgb.X * converted_coefficient.X;
	modulated_rgb.Y = converted_rgb.Y * converted_coefficient.Y;
	modulated_rgb.Z = converted_rgb.Z * converted_coefficient.Z;
	Set_Specular(modulated_rgb);

	W3dUtilityClass::Convert_Color(mat3.EmissiveCoefficients,&converted_rgb);
	Set_Emissive(converted_rgb);

	W3dUtilityClass::Convert_Color(mat3.AmbientCoefficients,&converted_rgb);
	Set_Ambient(converted_rgb);

	Set_Shininess(mat3.Shininess);
	Set_Opacity(mat3.Opacity);
}
