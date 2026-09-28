// ?d_0019f1e0@@YAXXZ
// partial score=0.526 date=2026-09-28
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Iinputs/reference/shims/stlp_nodealloc /Iinputs/reference/shims/stringbaseascii /Iinputs/reference/shims/buildlistinfo /Iinputs/reference/shims/moduledata /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWLib /Igame/GameEngine/Source/GameLogic/Map
// stlport
#define _STLP_NO_EXCEPTIONS 1
#define BFME_STLP_NODE_ALLOC 1
#include "PreRTS.h"
#include "Common/DataChunk.h"
#define protected public
#include "GameLogic/SidesList.h"
#undef protected
#include <vector>
struct VectorPoint0019E880 {int field00,field04,field08;};
class Gen_00193D50;
class MapVectorAppend0019DE10 {public:void append(int,const Gen_00193D50&);};
class MapVectorAppend0019E880 {public:void append(int,const _STL::vector<VectorPoint0019E880>&);};
namespace _STL {
  template<> __declspec(noinline) void vector<VectorPoint0019E880>::_M_insert_overflow(pointer __position, const VectorPoint0019E880& __x, const __false_type&, 
			  size_type __fill_len, bool __atend) {
    const size_type __old_size = size();
    const size_type __len = __old_size + (max)(__old_size, __fill_len);
    
    pointer __new_start = this->_M_end_of_storage.allocate(__len);
    pointer __new_finish = __new_start;
    _STLP_TRY {
      __new_finish = __uninitialized_copy(this->_M_start, __position, __new_start, __false_type());
      // handle insertion
      if (__fill_len == 1) {
        _Construct(__new_finish, __x);
        ++__new_finish;
      } else
        __new_finish = __uninitialized_fill_n(__new_finish, __fill_len, __x, __false_type());
      if (!__atend)
        // copy remainder
        __new_finish = __uninitialized_copy(__position, this->_M_finish, __new_finish, __false_type());
    }
    _STLP_UNWIND((_Destroy(__new_start,__new_finish), 
                  this->_M_end_of_storage.deallocate(__new_start,__len)));
    _M_clear();
    _M_set(__new_start, __new_finish, __new_start + __len);
  }

template<> __forceinline void vector<VectorPoint0019E880>::push_back(const VectorPoint0019E880& x) {
 if (_M_finish != _M_end_of_storage._M_data) { _Construct(_M_finish,x); ++_M_finish; }
 else { __false_type tag; _M_insert_overflow(_M_finish,x,tag,1,true); }
}
}
class BuildListsReader0019F1E0 {
public:
    bool read(DataChunkInput& input, DataChunkInfo* chunk);
};
bool BuildListsReader0019F1E0::read(DataChunkInput& input, DataChunkInfo* chunk) {
    int key = input.readNameKey();
    BuildListInfo item;
    for(int n=input.readInt(); n>0; --n) {
        item.setBuildingName(input.readAsciiString());
        item.setTemplateName(input.readAsciiString());
        Coord3D pos;
        pos.x=input.readReal();pos.y=input.readReal();pos.z=input.readReal();
        Coord3D location;location.set(&pos);item.setLocation(location);
        item.setAngle(input.readReal());
        ((MapVectorAppend0019DE10*)this)->append(key,(const Gen_00193D50&)item);
    }
    if(chunk->version >= 2) {
        for(int n=input.readInt(); n>0; --n) {
            int count=input.readInt();
            if(count) {
                _STL::vector<VectorPoint0019E880> values;
                for(int j=count; j>0; --j) {
                    VectorPoint0019E880 point;
                    point.field00=input.readInt();
                    point.field04=input.readInt();
                    point.field08=input.readInt();
                    values.push_back(point);
                }
                ((MapVectorAppend0019E880*)this)->append(key,values);
            }
        }
    }
    return true;
}

