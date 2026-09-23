// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/terrainlogic /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
// Retail RVA 00756F00, 1645 bytes, ends at RET 4 (0075756A) then INT3.
// Identity: W3DLaserDraw vtable VA 01122A00 slot 9 -> ILT 00026BF2 -> body.
// The LaserUpdate key and Zero Hour doDrawModule algorithm independently agree.
// BFME differences witnessed here: texture vector +14, rotating index +28,
// envelope +34 and color update after points, plus two-argument Set_Width.
// Module-data offsets follow constructor 00757960 and FieldParse table 01122858.
// Address-derived views preserve unlanded ABI spellings without semantic guesses.
#define Matrix4x4 Matrix4
#define __PLACEMENT_VEC_NEW_INLINE
#include "Lib/BaseType.h"
#include "Common/NameKeyGenerator.h"
#include "GameClient/Drawable.h"
#include "GameClient/Color.h"
#include "GameLogic/TerrainLogic.h"
#include "../../../../../../Libraries/Source/WWVegas/WW3D2/segline.h"
#include <vector>

// BFME virtual ground-height entry is slot 6 (retail calls at +2D9/+303/+33D/+367).
// The shared terrain shim has the older slot 5, so use a receiver-only ABI view.
class Rva00756F00TerrainLogic
{
public:
 virtual void slot00(); virtual void slot01(); virtual void slot02();
 virtual void slot03(); virtual void slot04(); virtual void slot05();
 virtual Real getGroundHeight(Real, Real, Coord3D *normal=0);
};
// Constructor 00757960 and its INI table prove these BFME member offsets.
class W3DLaserDrawModuleData
{
public:
    virtual void slot00();
    unsigned int m_at04;
    Color m_innerColor, m_outerColor;
    Real m_innerBeamWidth, m_outerBeamWidth, m_scrollRate;
    Bool m_tile;
    UnsignedInt m_numBeams, m_maxIntensityFrames, m_fadeFrames;
    std::vector<AsciiString> m_textureName;
    UnsignedInt m_segments;
    Real m_arcHeight, m_segmentOverlapRatio, m_tilingScalar, m_fanWidth;
    unsigned char m_envelope[0x28];
};

// BFME's update stores its endpoints at C/18 and dirty bit at 24.
class Rva00756F00LaserUpdate
{
public:
    char m_at00[0xC];
    Coord3D m_startPos, m_endPos;
    Bool m_dirty;
    char m_at25[0x3C-0x25];
    Real m_currentWidthScalar;
    const Coord3D *getStartPos() const { return &m_startPos; }
    const Coord3D *getEndPos() const { return &m_endPos; }
    Bool isDirty() const { return m_dirty; }
    void setDirty(Bool dirty) { m_dirty=dirty; }
    Real getWidthScale() const { return m_currentWidthScalar; }
};

// Address-derived ABI views for BFME methods absent from the shared header.
// 94F960 adds E0 then tails to 960050, which dereferences its texture argument.
class Rva0094F960 { public: void apply(TextureClass *const &); };
class Rva0094F970 { public: void apply(Real); };
class Rva0094FCF0 { public: void apply(Real, Real); };
class Rva001048C0
{
public:
    Bool update(const Real *, Real *);
    unsigned char m_data[0x28];
};

class W3DLaserDraw
{
public:
    virtual void doDrawModule(const Matrix3D *);
    W3DLaserDrawModuleData *m_moduleData; // +4
    Drawable *m_drawable;              // +8
    void *m_interface0C;
    SegmentedLineClass **m_line3D;     // +10
    std::vector<TextureClass *> m_textures; // +14, destructor 757A50
    Real m_textureAspectRatio;         // +20
    Bool m_selfDirty;                  // +24
    UnsignedInt m_at28;
    Real m_at2C, m_at30;
    Rva001048C0 m_envelope;             // +34
    const W3DLaserDrawModuleData *getW3DLaserDrawModuleData() const { return m_moduleData; }
    Drawable *getDrawable() const { return m_drawable; }
};

void W3DLaserDraw::doDrawModule(const Matrix3D* transformMtx)
{
	//UnsignedInt currentFrame = TheGameClient->getFrame();
	const W3DLaserDrawModuleData *data = getW3DLaserDrawModuleData();

	//Get the updatemodule that drives it...
	Drawable *draw = getDrawable();
	static NameKeyType key_LaserUpdate = NAMEKEY( "LaserUpdate" );
	Rva00756F00LaserUpdate *update = (Rva00756F00LaserUpdate*)draw->findClientUpdateModule( key_LaserUpdate );
	if( !update )
	{
		return;
	}

	//If the update has moved the laser, it requires a reset of the laser.
	if (update->isDirty() || m_selfDirty)
	{
		update->setDirty(false);
		m_selfDirty = false;

		Vector3 laserPoints[ 2 ];

		for( int segment = 0; segment < data->m_segments; segment++ )
		{
			if( data->m_arcHeight > 0.0f && data->m_segments > 1 )
			{
				//CALCULATE A CURVED LINE BASED ON TOTAL LENGTH AND DESIRED HEIGHT INCREASE
				//To do this we will use a portion of the cos wave ranging between -0.25PI
				//and +0.25PI. 0PI is 1.0 and 0.25PI is 0.70 -- resulting in a somewhat
				//gentle curve depending on the line height and length. We also have to make
				//the line *level* for this phase of the calculations.

				//Get the desired direct line
				Coord3D lineStart, lineEnd, lineVector;
				lineStart.set( update->getStartPos() );
				lineEnd.set( update->getEndPos() );
				//This is critical -- in the case we have sloped lines (at the end, we'll fix it)
//				lineEnd.z = lineStart.z;

				//Get the length of the line
				lineVector.set( &lineEnd );
				lineVector.sub( &lineStart );
				Real lineLength = lineVector.length();

				//Get the middle point (we'll use this to determine how far we are from
				//that to calculate our height -- middle point is the highest).
				Coord3D lineMiddle;
				lineMiddle.set( &lineStart );
				lineMiddle.add( &lineEnd );
				lineMiddle.scale( 0.5 );

				//The half length is used to scale with the distance from middle to 
				//get our cos( 0 to 0.25 PI) cos value
				Real halfLength = lineLength * 0.5f;

				//Now calculate which segment we will use.
				Real startSegmentRatio = segment / ((Real)data->m_segments);
				Real endSegmentRatio = (segment + 1.0f) / ((Real)data->m_segments);

				//Offset the segment ever-so-slightly to minimize overlap -- only apply
				//to segments that are not the start/end point
				if( segment > 0 ) 
				{
					startSegmentRatio -= data->m_segmentOverlapRatio;
				}
				if( segment < data->m_segments - 1 )
				{
					endSegmentRatio += data->m_segmentOverlapRatio;
				}

				//Calculate our start segment position on the *ground*.
				Coord3D segmentStart, segmentEnd, vector;
				vector.set( &lineVector );
				vector.scale( startSegmentRatio );
				segmentStart.set( &lineStart );
				segmentStart.add( &vector );

				//Calculate our end segment position on the *ground*.
				vector.set( &lineVector );
				vector.scale( endSegmentRatio );
				segmentEnd.set( &lineStart );
				segmentEnd.add( &vector );

				//--------------------------------------------------------------------------------
				//Now at this point, we have our segment line in the level positions that we want.
				//Calculate the raised height for the start/end segment positions using cosine.
				//--------------------------------------------------------------------------------

				//Calculate the distance from midpoint for the start positions.
				vector.set( &lineMiddle );
				vector.sub( &segmentStart );
				Real dist = vector.length();
				Real scaledRadians = dist / halfLength * PI * 0.5f; 
				Real height = cos( scaledRadians );
				height *= data->m_arcHeight;
				segmentStart.z += height;

				//Now do the same thing for the end position.
				vector.set( &lineMiddle );
				vector.sub( &segmentEnd );
				dist = vector.length();
				scaledRadians = dist / halfLength * PI * 0.5f; 
				height = cos( scaledRadians );
				height *= data->m_arcHeight;
				segmentEnd.z += height;
				
				//This makes the laser skim the ground rather than penetrate it!
				laserPoints[ 0 ].Set( segmentStart.x, segmentStart.y, 
					MAX( segmentStart.z, 2.0f + reinterpret_cast<Rva00756F00TerrainLogic *>(TheTerrainLogic)->getGroundHeight(segmentStart.x, segmentStart.y) ) );
				laserPoints[ 1 ].Set( segmentEnd.x, segmentEnd.y, 
					MAX( segmentEnd.z, 2.0f + reinterpret_cast<Rva00756F00TerrainLogic *>(TheTerrainLogic)->getGroundHeight(segmentEnd.x, segmentEnd.y) ) );
				
			}
			else
			{
				//No arc -- way simpler!
				laserPoints[ 0 ].Set( update->getStartPos()->x, update->getStartPos()->y, update->getStartPos()->z );
				laserPoints[ 1 ].Set( update->getEndPos()->x, update->getEndPos()->y, update->getEndPos()->z );
			}

			//Get the color components for calculation purposes.
			Real innerRed, innerGreen, innerBlue, innerAlpha, outerRed, outerGreen, outerBlue, outerAlpha;
			GameGetColorComponentsReal( data->m_innerColor, &innerRed, &innerGreen, &innerBlue, &innerAlpha );
			GameGetColorComponentsReal( data->m_outerColor, &outerRed, &outerGreen, &outerBlue, &outerAlpha );

			for( Int i = data->m_numBeams - 1; i >= 0; i-- )
			{

				Real width;
				int index = segment * data->m_numBeams + i;

				if( data->m_numBeams == 1 )
				{	
					width = data->m_innerBeamWidth * update->getWidthScale();
				}
				else
				{
					//Calculate the scale between min and max values
					//0 means use min value, 1 means use max value
					//0.2 means min value + 20% of the diff between min and max
					Real scale = i / ( data->m_numBeams - 1.0f);
					Real ultimateScale = update->getWidthScale();
					width		= (data->m_innerBeamWidth	+ scale * (data->m_outerBeamWidth - data->m_innerBeamWidth));
					width *= ultimateScale;
				}


				//Calculate the number of times to tile the line based on the height of the texture used.
				if( m_textures[0] && data->m_tile )
				{
					//Calculate the length of the line.
					Vector3 lineVector;
					Vector3::Subtract( laserPoints[1], laserPoints[0], &lineVector );
					Real length = lineVector.Length();

					//Adjust tile factor so texture is NOT stretched but tiled equally in both width and length.
					Real tileFactor = data->m_tilingScalar/width*m_textureAspectRatio*length;

					//Set the tile factor
					reinterpret_cast<Rva0094F970 *>(m_line3D[index])->apply(tileFactor);	//number of times to tile texture across each segment
				}

				reinterpret_cast<Rva0094FCF0 *>(m_line3D[index])->apply(width, m_at30);
				m_line3D[ index ]->Set_Points( 2, &laserPoints[0] );
                Real red, green, blue;
                if (data->m_numBeams == 1) {
                    red = innerRed * innerAlpha;
                    green = innerGreen * innerAlpha;
                    blue = innerBlue * innerAlpha;
                } else {
                    Real scale = i / (data->m_numBeams - 1.0f);
                    red = innerRed + scale * (outerRed-innerRed) * innerAlpha;
                    green = innerGreen + scale * (outerGreen-innerGreen) * innerAlpha;
                    blue = innerBlue + scale * (outerBlue-innerBlue) * innerAlpha;
                }
                m_envelope.update(&m_at2C, &m_at2C);
                m_line3D[index]->Set_Color(Vector3(red*m_at2C, green*m_at2C, blue*m_at2C));
                reinterpret_cast<Rva0094F960 *>(m_line3D[index])->apply(m_textures[m_at28]);
			}
		}
	}
	
	if (++m_at28 >= m_textures.size()) m_at28=0;
	return;
}