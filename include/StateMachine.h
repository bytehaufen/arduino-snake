#include "Menu.h"

enum class STATE { INTRO, MENU, GAME, SCORE };

class StateMachine {
private:
  STATE currentState;
  Menu menu;

public:
  StateMachine();

  void setState(STATE newState);
  STATE getState();

  void run();
};
