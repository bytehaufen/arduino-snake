#include "Game.h"

Game::Game(DIFFICULTY difficulty) {
  selectedDifficulty = difficulty;
  // Initialize snake segment array
  for (int i = 0; i < Display::ROWS; i++) {
    for (int j = 0; j < Display::COLS; j++) {
      segment[i][j] = ELEMENT::NONE;
    }
  }
  // Initialize snake head and tail position
  xHead = (uint8_t)Display::COLS / 2;
  yHead = (uint8_t)Display::ROWS / 2;
  xTail = xHead;
  yTail = yHead;
  segment[yHead][xHead] = ELEMENT::BODY | DIRECTION::DOWN;
  emptyFields = Display::COLS * Display::ROWS - 1;
  // Set up display
  display = &Display::getInstance();
  display->clear();
  display->drawGameBorder(Display::X_OFFSET, Display::Y_OFFSET,
                          Display::SCREEN_WIDTH - 2 * Display::X_OFFSET,
                          Display::SCREEN_HEIGHT - 2 * Display::Y_OFFSET);
  display->drawSegment(xHead, yHead, Display::SEGMENT::HEAD_SOUTH);

  display->printScoreInfo(0, true);
}

uint16_t Game::run() {
  Input::BUTTON bAction;
  static uint8_t clk = 0;

  if (!isFruitSpawned) {
    isFruitSpawned = true;

    uint16_t freeRandomfield = rand() % emptyFields;
    for (int i = 0; i < Display::ROWS; i++) {
      for (int j = 0; j < Display::COLS; j++) {
        if (segment[i][j] == ELEMENT::NONE && freeRandomfield-- == 0) {
          isFruitSpawned = false;
          segment[i][j] = ELEMENT::FOOD;
          placeRandomFood(j, i);
          emptyFields--;
          break;
        }
      }
    }

    isFruitSpawned = true;
  }

  // Skip 100 clk cycles -> execute every 1s
  if (clk++ < (100 / static_cast<uint8_t>(selectedDifficulty))) {
    return GAME_RUNNING;
  }
  clk = 0;

  // Read input and set direction
  bAction = Input::getInstance().getPressedButton();
  switch (bAction) {
  case Input::BUTTON::UP:
    if (direc == DIRECTION::DOWN) {
      break;
    }
    direc = DIRECTION::UP;
    break;
  case Input::BUTTON::DOWN:
    if (direc == DIRECTION::UP) {
      break;
    }
    direc = DIRECTION::DOWN;
    break;
  case Input::BUTTON::LEFT:
    if (direc == DIRECTION::RIGHT) {
      break;
    }
    direc = DIRECTION::LEFT;
    break;
  case Input::BUTTON::RIGHT:
    if (direc == DIRECTION::LEFT) {
      break;
    }
    direc = DIRECTION::RIGHT;
    break;
  case Input::BUTTON::MIDDLE:
    break;
  case Input::BUTTON::NONE:
    break;
  default:
    break;
  }

  // Overwrite last head with body
  display->drawSegment(xHead, yHead, Display::SEGMENT::BODY);
  // Delete old head from array
  // Set direction of last head segment to point to new head
  segment[yHead][xHead] = ELEMENT::BODY | direc;

  // Set position for new head
  switch (direc) {
  case DIRECTION::RIGHT:
    xHead += 1;
    break;
  case DIRECTION::UP:
    yHead -= 1;
    break;
  case DIRECTION::LEFT:
    xHead -= 1;
    break;
  case DIRECTION::DOWN:
    yHead += 1;
    break;
  default:
    break;
  }

  // Collision detection
  // Check snake dies
  if (((segment[yHead][xHead] &
        ELEMENT::BODY) && // if snake hits itself but not tail
       !(xHead == xTail && yHead == yTail)) ||
      (xHead >= Display::COLS) || // if the head is right of border
      (xHead < 0) ||              // if the head is left of border
      (yHead >= Display::ROWS) || // if the head is under border
      (yHead < 0)) {              // if the head is above border
    // TODO: Implement Game finished
    return snakedItems;
  }
  // Check head hits food
  if (segment[yHead][xHead] & ELEMENT::FOOD) {
    segment[yHead][xHead] &= ~ELEMENT::FOOD;
    display->printScoreInfo(++snakedItems);
    isFruitSpawned = false;
  } else {
    // Erase tail otherwise if its not the head
    if (!(xHead == xTail && yHead == yTail)) {
      display->drawSegment(xTail, yTail, Display::SEGMENT::NONE);
    }

    // Filter direction and set new Tail
    switch (segment[yTail][xTail] & (DIRECTION::RIGHT | DIRECTION::UP |
                                     DIRECTION::LEFT | DIRECTION::DOWN)) {
    case DIRECTION::RIGHT:
      segment[yTail][xTail++] = 0;
      break;
    case DIRECTION::UP:
      segment[yTail--][xTail] = 0;
      break;
    case DIRECTION::LEFT:
      segment[yTail][xTail--] = 0;
      break;
    case DIRECTION::DOWN:
      segment[yTail++][xTail] = 0;
      break;
    default:
      break;
    }
  }

  // Set new head
  segment[yHead][xHead] = direc | ELEMENT::BODY;
  // Draw new head
  display->drawSegment(xHead, yHead,
                       direc == DIRECTION::RIGHT ? Display::SEGMENT::HEAD_EAST
                       : direc == DIRECTION::UP  ? Display::SEGMENT::HEAD_NORTH
                       : direc == DIRECTION::LEFT
                           ? Display::SEGMENT::HEAD_WEST
                           : Display::SEGMENT::HEAD_SOUTH);

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
