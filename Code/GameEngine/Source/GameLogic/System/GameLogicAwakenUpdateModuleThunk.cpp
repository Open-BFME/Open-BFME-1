// cl: /DNDEBUG /MD /EHsc
// Incremental-link route0x00009944 to GameLogic::friend_awakenUpdateModule
// at0x0038D870. The body is recovered in GameLogicAwakenUpdate.cpp.
class Object;
class UpdateModule;
class GameLogic {
public:
 void friend_awakenUpdateModule(Object *, UpdateModule *, unsigned int);
 void j_00009944(Object *, UpdateModule *, unsigned int);
};
void GameLogic::j_00009944(Object *obj, UpdateModule *mod, unsigned int frame) {
 friend_awakenUpdateModule(obj,mod,frame);
}
