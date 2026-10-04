// cl: /Igame/Libraries/Source/WWVegas/WWLib /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
#include "Rva00453480MapPointerCollector.h"

// Retail map-list population (0x00456A90), sharing the native map filter above.
// Its old MapCache::addMap lift identity is refuted by the GUI callees and cdecl ABI.
// See targets/game/reverse/identity_evidence/00456A90-map-list-population.md.
#include "ascii_string.h"
#include "unicode_string.h"
#include <algorithm>
class GameWindow;
struct ICoord2D {int x,y;};
class Image {public:char field00[0x24];ICoord2D m_imageSize;int getImageWidth()const{return m_imageSize.x;}};
class ImageCollection {public:const Image *findImageByName(const AsciiString&);};extern ImageCollection *TheMappedImageCollection;
class SkirmishPreferences {public:SkirmishPreferences();virtual ~SkirmishPreferences();UnicodeString getUserName();private:char field04[0x14];};
class SkirmishBattleHonors {public:SkirmishBattleHonors(UnicodeString);virtual ~SkirmishBattleHonors();int getEnduranceMedal(AsciiString,int)const;private:char field04[0x38];};
class MapMetaData {public:char field00[0x24];bool m_isMultiplayer;char field25[0x2b];AsciiString m_fileName;UnicodeString getFileName()const;};
void GadgetListBoxSetListLength(GameWindow*,int);
int GadgetListBoxGetNumColumns(GameWindow*);
int GadgetListBoxGetColumnWidth(GameWindow*,int);
void GadgetListBoxReset(GameWindow*);
int GadgetListBoxAddEntryImage(GameWindow*,const Image*,int,int,int,int,bool,int);
int GadgetListBoxAddEntryText(GameWindow*,UnicodeString,int,int,int,bool);
void GadgetListBoxSetItemData(GameWindow*,void*,int,int);
void GadgetListBoxSetSelected(GameWindow*,const int*,int);
int GadgetListBoxGetTopVisibleEntry(GameWindow*);
int GadgetListBoxGetBottomVisibleEntry(GameWindow*);
void GadgetListBoxSetTopVisibleEntry(GameWindow*,int);

struct Q3SortElem4;
struct Q3SortCompare {bool field0;Q3SortCompare():field0(false){}};
void Rva00456860(Q3SortElem4*,Q3SortElem4*,Q3SortCompare);
template<class T> inline const T &minValue(const T&a,const T&b){return a<b?a:b;}
template<class T> inline const T &maxValue(const T&a,const T&b){return a>b?a:b;}
// Both routes are independently decoded from retail calls at +0x1d5 and +0x1ee.
int populateMapListboxRva00456A90(GameWindow *listbox,unsigned flags,const AsciiString &mapToSelect) {
 if(!TheMapCache)return -1;if(!listbox)return -1;
 GadgetListBoxSetListLength(listbox,1000);
 const Image *easyImage=0,*mediumImage=0,*brutalImage=0;
 SkirmishBattleHonors *battleHonors=0;int selectionIndex;int w=10,h=10;
 SkirmishPreferences prefs;
 int numColumns=GadgetListBoxGetNumColumns(listbox);
 if(numColumns>1) {
 easyImage=TheMappedImageCollection->findImageByName("Star-Bronze");
 mediumImage=TheMappedImageCollection->findImageByName("Star-Silver");
 brutalImage=TheMappedImageCollection->findImageByName("Star-Gold");
 battleHonors=new SkirmishBattleHonors(prefs.getUserName());
 w=brutalImage?brutalImage->getImageWidth():10;
 w=minValue(GadgetListBoxGetColumnWidth(listbox,0),w);h=w;
 }
 if(!(flags&0x40))GadgetListBoxReset(listbox);
 std::vector<const MapMetaData*> maps;Rva00453480Collect(flags,&maps);
 Rva00456860((Q3SortElem4*)maps.begin(),(Q3SortElem4*)maps.end(),Q3SortCompare());
 selectionIndex=-1;
 for(std::vector<const MapMetaData*>::iterator it=maps.begin();it!=maps.end();++it) {
 const MapMetaData *md=*it;int index=-1,imageItemData=-1;
 if(numColumns>1 && md->m_isMultiplayer) {
 int numEasy=battleHonors->getEnduranceMedal(md->m_fileName.str(),2);
 int numMedium=battleHonors->getEnduranceMedal(md->m_fileName.str(),3);
 int numBrutal=battleHonors->getEnduranceMedal(md->m_fileName.str(),4);
 if(numBrutal){imageItemData=3;index=GadgetListBoxAddEntryImage(listbox,brutalImage,index,0,w,h,true,-1);}
 else if(numMedium){imageItemData=2;index=GadgetListBoxAddEntryImage(listbox,mediumImage,index,0,w,h,true,-1);}
 else if(numEasy){imageItemData=1;index=GadgetListBoxAddEntryImage(listbox,easyImage,index,0,w,h,true,-1);}
 else {imageItemData=0;index=GadgetListBoxAddEntryImage(listbox,0,index,0,w,h,true,-1);}
 }
 index=GadgetListBoxAddEntryText(listbox,md->getFileName(),-1,index,numColumns-1,true);
 if(md->m_fileName.StringBase<char>::compare(mapToSelect)==0)selectionIndex=index;
 GadgetListBoxSetItemData(listbox,(void*)md->m_fileName.str(),index,0);
 if(numColumns>1)GadgetListBoxSetItemData(listbox,(void*)imageItemData,index,1);
 }
 GadgetListBoxSetSelected(listbox,&selectionIndex,1);
 if(selectionIndex>=0) {int topIndex=GadgetListBoxGetTopVisibleEntry(listbox);int bottomIndex=GadgetListBoxGetBottomVisibleEntry(listbox);int rowsOnScreen=bottomIndex-topIndex;
 if(selectionIndex>=bottomIndex) {int newTop=maxValue(0,selectionIndex-maxValue(1,rowsOnScreen/2));GadgetListBoxSetTopVisibleEntry(listbox,newTop);}}
 if(battleHonors){delete battleHonors;battleHonors=0;}
 return selectionIndex;
}
