
enum class State { intro, menu, game, score };

class StateMachine {
private:
  State currentState;

public:
  StateMachine();

  void setState(State newState);
  State getState();

  void run();
};
