#include "Menu.h"

#include <Arduino.h>

Menu::Menu() : selectedMenuItem(MENU_ITEM::START) {}

void Menu::next() {
  Serial.print("actual item: ");
  Serial.println((int)selectedMenuItem);

  switch (Menu::selectedMenuItem) {
  case MENU_ITEM::START:
    Menu::selectedMenuItem = MENU_ITEM::SCORE;
    break;
  case MENU_ITEM::SCORE:
    break;
  }
  Serial.print("new item: ");
  Serial.println((int)selectedMenuItem);
}

void Menu::prev() {
  Serial.print("actual item: ");
  Serial.println((int)selectedMenuItem);

  switch (Menu::selectedMenuItem) {
  case MENU_ITEM::START:
    break;
  case MENU_ITEM::SCORE:
    Menu::selectedMenuItem = MENU_ITEM::START;
    break;
  }
  Serial.print("actual item: ");
  Serial.println((int)selectedMenuItem);
}

MENU_ITEM Menu::getSelectedMenuItem() { return Menu::selectedMenuItem; }
