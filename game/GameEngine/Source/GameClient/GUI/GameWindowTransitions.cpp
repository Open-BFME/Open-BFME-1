// cl: /DNDEBUG /MD /EHsc
// The matched GameWindowManager caller's compiled relocations and the upstream
// definition establish this exact pointer type. This provider only needs its
// opaque declaration because it stores a pointer without accessing the object.
class GameWindowTransitionsHandler;

GameWindowTransitionsHandler *TheTransitionHandler = 0;
