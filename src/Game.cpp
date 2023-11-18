#include "Game.h"
#include "Display.h"
#include "Input.h"
#include "Timer.h"
#include "images/Ba.h"
#include "images/Strawberry.h"

Game::Game() {
  // Initialize snake segment array
  for (int i = 0; i < Display::ROWS; i++) {
    for (int j = 0; j < Display::COLS; j++) {
      segment[i][j] = Element::NONE;
    }
  }
  // Initialize snake head and tail position
  xHead = (uint8_t)Display::COLS / 2;
  yHead = (uint8_t)Display::ROWS / 2;
  xTail = xHead;
  yTail = yHead;
  segment[yHead][xHead] = Element::BODY | Direction::DOWN;
  emptyFields = Display::COLS * Display::ROWS - 1;
  // Set up display
  display = &Display::getInstance();
  display->clear();
  display->drawGameBorder(Display::X_OFFSET, Display::Y_OFFSET,
                          Display::SCREEN_WIDTH - 2 * Display::X_OFFSET,
                          Display::SCREEN_HEIGHT - 2 * Display::Y_OFFSET);
  display->drawSegment(xHead, yHead, Display::Segments::HEAD_SOUTH);

  display->printScoreInfo("0", true);
}

uint16_t Game::run() {
  Input::BUTTON bAction;
  static uint8_t clk = 0;

  if (!isFruitSpawned) {
    isFruitSpawned = true;

    uint16_t freeRandomfield = rand() % emptyFields;
    for (int i = 0; i < Display::ROWS; i++) {
      for (int j = 0; j < Display::COLS; j++) {
        if (segment[i][j] == Element::NONE && freeRandomfield-- == 0) {
          isFruitSpawned = false;
          segment[i][j] = Element::FOOD;
          placeRandomFood(j, i);
          emptyFields--;
          break;
        }
      }
    }

    isFruitSpawned = true;
  }

  // Skip 100 clk cycles -> execute every 1s
  if (clk++ < 100) {
    return GAME_RUNNING;
  }
  clk = 0;

  // Read input and set direction
  bAction = Input::getInstance().getPressedButton();
  switch (bAction) {
  case Input::BUTTON::UP:
    if (direc == Direction::DOWN) {
      break;
    }
    direc = Direction::UP;
    break;
  case Input::BUTTON::DOWN:
    if (direc == Direction::UP) {
      break;
    }
    direc = Direction::DOWN;
    break;
  case Input::BUTTON::LEFT:
    if (direc == Direction::RIGHT) {
      break;
    }
    direc = Direction::LEFT;
    break;
  case Input::BUTTON::RIGHT:
    if (direc == Direction::LEFT) {
      break;
    }
    direc = Direction::RIGHT;
    break;
  case Input::BUTTON::MIDDLE:
    break;
  case Input::BUTTON::NONE:
    break;
  default:
    break;
  }

  // Overwrite last head with body
  display->drawSegment(xHead, yHead, Display::Segments::BODY);
  // Delete old head from array
  // Set direction of last head segment to point to new head
  segment[yHead][xHead] = Element::BODY | direc;

  // Set position for new head
  switch (direc) {
  case Direction::RIGHT:
    xHead += 1;
    break;
  case Direction::UP:
    yHead -= 1;
    break;
  case Direction::LEFT:
    xHead -= 1;
    break;
  case Direction::DOWN:
    yHead += 1;
    break;
  default:
    break;
  }

  // Collision detection
  // Check snake dies
  if (((segment[yHead][xHead] &
        Element::BODY) && // if snake hits itself but not tail
       !(xHead == xTail && yHead == yTail)) ||
      (xHead >= Display::COLS) || // if the head is right of border
      (xHead < 0) ||              // if the head is left of border
      (yHead >= Display::ROWS) || // if the head is under border
      (yHead < 0)) {              // if the head is above border
    // TODO: Implement Game finished
    return snakedItems;
  }
  // Check head hits food
  if (segment[yHead][xHead] & Element::FOOD) {
    segment[yHead][xHead] &= ~Element::FOOD;
    display->printScoreInfo(String(++snakedItems));
    isFruitSpawned = false;
  } else {
    // Erase tail otherwise if its not the head
    if (!(xHead == xTail && yHead == yTail)) {
      display->drawSegment(xTail, yTail, Display::Segments::NONE);
    }

    // Filter direction and set new Tail
    switch (segment[yTail][xTail] & (Direction::RIGHT | Direction::UP |
                                     Direction::LEFT | Direction::DOWN)) {
    case Direction::RIGHT:
      segment[yTail][xTail] = 0;
      segment[yTail][++xTail] |= Element::BODY;
      break;
    case Direction::UP:
      segment[yTail][xTail] = 0;
      segment[--yTail][xTail] |= Element::BODY;
      break;
    case Direction::LEFT:
      segment[yTail][xTail] = 0;
      segment[yTail][--xTail] |= Element::BODY;
      break;
    case Direction::DOWN:
      segment[yTail][xTail] = 0;
      segment[++yTail][xTail] |= Element::BODY;
      break;
    default:
      break;
    }
  }

  // Set new head
  segment[yHead][xHead] = direc | Element::BODY;
  // Draw new head
  display->drawSegment(xHead, yHead,
                       direc == Direction::RIGHT ? Display::Segments::HEAD_EAST
                       : direc == Direction::UP  ? Display::Segments::HEAD_NORTH
                       : direc == Direction::LEFT
                           ? Display::Segments::HEAD_WEST
                           : Display::Segments::HEAD_SOUTH);

  return GAME_RUNNING;
}

void Game::placeRandomFood(const uint8_t x, const uint8_t y) {
  const uint8_t FOOD_COUNT = 2;
  switch (rand() % FOOD_COUNT) {
  case 0:
    display->drawFood(x, y, Strawberry::image_data, Strawberry::image_width,
                      Strawberry::image_height);
    break;
  case 1:
    display->drawFood(x, y, Ba::image_data, Ba::image_width, Ba::image_height);
    break;
  }
}
