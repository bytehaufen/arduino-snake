#ifndef MENU_H
#define MENU_H

enum class MENU_ITEM { START, SCORE };

class Menu {
private:
  MENU_ITEM selectedMenuItem;

public:
  Menu();
  void next();
  void prev();
  MENU_ITEM getSelectedMenuItem();
};

#endif // MENU_H
