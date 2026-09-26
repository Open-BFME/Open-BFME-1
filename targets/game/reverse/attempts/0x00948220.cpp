// ?Change_Polygon_Renderer_Material@DX8FVFCategoryContainer@@QAEXAAV?$MultiListClass@VDX8PolygonRendererClass@@@@PAVVertexMaterialClass@@1I@Z
// partial score=0.7 date=2026-09-20
// Scratch bank for the full real C++ attempt at retail RVA 0x00948220.
// Canonical production source: Code/Libraries/Source/WWVegas/WW3D2/dx8renderer.cpp.
// This excerpt is intentionally not compiled; the production source was restored clean.
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

/***********************************************************************************************
 ***              C O N F I D E N T I A L  ---  W E S T W O O D  S T U D I O S               ***
 ***********************************************************************************************
 *                                                                                             *
 *                 Project Name : ww3d                                                         *
 *                                                                                             *
 *                     $Archive:: /Commando/Code/ww3d2/dx8renderer.cpp                        $*
 *                                                                                             *
 *              Original Author:: Greg Hjelstrom                                               *
 *                                                                                             *
 *                       Author : Kenny Mitchell                                               * 
 *                                                                                             * 
 *                     $Modtime:: 06/27/02 1:27p                                              $*
 *                                                                                             *
 *                    $Revision:: 111                                                         $*
 *                                                                                             *
 * 06/27/02 KM Changes to max texture stage caps																*
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

//#define ENABLE_CATEGORY_LOG
//#define ENABLE_STRIPING

#include "../WWLib/wwstring.h"
#define MUTEX_H
#include "dx8renderer.h"
#include "dx8wrapper.h"
#include "dx8polygonrenderer.h"
#include "dx8vertexbuffer.h"
#include "dx8indexbuffer.h"
#include "dx8fvf.h"
#include "dx8caps.h"
#include "dx8rendererdebugger.h"

class BfmeHandleCX
{
public:
	TextureClass *p;

	BfmeHandleCX() : p(NULL) {}
	~BfmeHandleCX() throw()
	{
		if (p != NULL)
			p->Release_Ref();
	}

	BfmeHandleCX &operator=(const BfmeHandleCX &other)
	{
		if (other.p != NULL)
			++*reinterpret_cast<unsigned short *>(reinterpret_cast<char *>(other.p) + 4);
		if (p != NULL)
			p->Release_Ref();
		p = other.p;
		return *this;
	}

	bool operator==(const BfmeHandleCX &other) const
	{
		return p == other.p;
	}
};

class Gen_00945490
{
public:
	BfmeHandleCX bfmeGet(int stage) const throw();
};

// --- Change_Polygon_Renderer_Material excerpt ---
// ?Change_Polygon_Renderer_Material@DX8FVFCategoryContainer@@QAEXAAV?$MultiListClass@VDX8PolygonRendererClass@@@@PAVVertexMaterialClass@@1I@Z present-unmatched
void DX8FVFCategoryContainer::Change_Polygon_Renderer_Material(
		DX8PolygonRendererList& polygon_renderer_list,
		VertexMaterialClass* vmat,
		VertexMaterialClass* new_vmat,
		unsigned pass)
{
	WWASSERT(pass<passes);

	PolyRemoverList prl;

	bool foundtexture=false;

	if (vmat==new_vmat) return;

	// Find source texture category, then find all polygon renderers who belong to that category
	// and move them to destination category.
	TextureCategoryListIterator src_it(&texture_category_list[pass]);
	while (!src_it.Is_Done()) {
		DX8TextureCategoryClass* src_tex_category=src_it.Peek_Obj();
		if (src_tex_category->Peek_Material()==vmat) {			
			DX8PolygonRendererListIterator poly_it(&polygon_renderer_list);
			while (!poly_it.Is_Done()) {
				// If source texture category contains polygon renderer, move to destination category
				DX8PolygonRendererClass* polygon_renderer=poly_it.Peek_Obj();
				DX8TextureCategoryClass *prc=polygon_renderer->Get_Texture_Category();
				if (prc==src_tex_category) {
					foundtexture=true;
					DX8TextureCategoryClass* dest_tex_category=Find_Matching_Texture_Category(new_vmat,pass,src_tex_category);

					if (!dest_tex_category) {
						BfmeHandleCX tmp_textures[MeshMatDescClass::MAX_TEX_STAGES];
						for (int s=0;s<MeshMatDescClass::MAX_TEX_STAGES;++s) {
							tmp_textures[s]=reinterpret_cast<const Gen_00945490 *>(src_tex_category)->bfmeGet(s);
						}

						DX8TextureCategoryClass * new_tex_category=W3DNEW DX8TextureCategoryClass(
							this,
							reinterpret_cast<TextureClass **>(tmp_textures),
							src_tex_category->Get_Shader(),
							const_cast<VertexMaterialClass*>(new_vmat),
							pass);
		
						/*
						** Add the texture category object into the list, immediately after any existing
						** texture category object which uses the same texture.  This will result in
						** the list always having matching texture categories next to each other.
						*/
						bool found_similar_category = false;
						TextureCategoryListIterator tex_it(&texture_category_list[pass]);
						while (!tex_it.Is_Done()) {
							// Categorize according to first stage's texture for now
							BfmeHandleCX texture = reinterpret_cast<const Gen_00945490 *>(tex_it.Peek_Obj())->bfmeGet(0);
							if (texture.p == tmp_textures[0].p) {
								texture_category_list[pass].Add_After(new_tex_category,tex_it.Peek_Obj());
								found_similar_category = true;
								break;
							}
							tex_it.Next();
						}

						if (!found_similar_category) {
							texture_category_list[pass].Add_Tail(new_tex_category);
						}
						dest_tex_category=new_tex_category;
					}
					PolyRemover *rem=W3DNEW PolyRemover;
					rem->src=src_tex_category;
					rem->dest=dest_tex_category;
					rem->pr=polygon_renderer;
					prl.Add(rem);
				}
				poly_it.Next();
			} // while			
		} // if 
		else
			if (foundtexture) break;
		src_it.Next();
	} // while

	PolyRemoverListIterator prli(&prl);

	while (!prli.Is_Done())
	{
		PolyRemover *rem=prli.Peek_Obj();
		rem->src->Remove_Polygon_Renderer(rem->pr);
		rem->dest->Add_Polygon_Renderer(rem->pr);		
		prli.Remove_Current_Object();
		delete rem;
	}
}

// ----------------------------------------------------------------------------
