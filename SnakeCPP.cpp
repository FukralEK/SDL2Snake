#include <SDL2/SDL.h>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <vector>

// Struct Vector

struct Vec2 {
  int X;
  int Y;
};

// SDL2 Stuff
SDL_Event e;
SDL_Window *window = nullptr;
SDL_Renderer *renderer = nullptr;
SDL_Rect rect;

// Game Variables
std::vector<Vec2> snake;
Vec2 direction;
Vec2 fruit;
bool isUp = false, isDown = false, isRight = false, isLeft = false;

bool running = true;

void updateKeys();
void update();
void draw();
void repositionFruit();
void restart();

int main(int argc, char **argv) {
  SDL_Init(SDL_INIT_EVERYTHING);
  SDL_CreateWindowAndRenderer(1280, 720, 0, &window, &renderer);
  srand(time(NULL));
  {
    Vec2 vec2;

    vec2.X = 49 / 2;
    vec2.Y = 26 / 2;

    snake.push_back(vec2);

    direction.X = 0;
    direction.Y = 0;

    repositionFruit();
  }

  while (running) {
    updateKeys();

    update();

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    draw();

    SDL_RenderPresent(renderer);
    SDL_Delay(100);
  }
  return 0;
}

void updateKeys() {
  while (SDL_PollEvent(&e)) {
    switch (e.type) {
    case SDL_QUIT:
      running = false;
      break;
    case SDL_KEYDOWN:
      switch (e.key.keysym.sym) {
      case SDLK_ESCAPE:
        running = false;
        break;
      case SDLK_d:
        isRight = true;
        break;
      case SDLK_w:
        isUp = true;
        break;
      case SDLK_s:
        isDown = true;
        break;
      case SDLK_a:
        isLeft = true;
        break;
      }
      break;
    case SDL_KEYUP:
      switch (e.key.keysym.sym) {
      case SDLK_d:
        isRight = false;
        break;
      case SDLK_w:
        isUp = false;
        break;
      case SDLK_s:
        isDown = false;
        break;
      case SDLK_a:
        isLeft = false;
        break;
      case SDLK_F2:
        repositionFruit();
        break;
      case SDLK_F3:
        restart();
        break;
      }
      break;
    }
  }
}

void update() {
  Vec2 snakeLastPosition = snake[0];
  if (isUp) {
    if (direction.Y != 1) {
      direction.X = 0;
      direction.Y = -1;
    }
  }
  if (isDown) {
    if (direction.Y != -1) {
      direction.X = 0;
      direction.Y = 1;
    }
  }
  if (isRight) {
    if (direction.X != -1) {
      direction.X = 1;
      direction.Y = 0;
    }
  }
  if (isLeft) {
    if (direction.X != 1) {
      direction.X = -1;
      direction.Y = 0;
    }
  }

  for (int i = snake.size() - 1; i > 0; i--) {
    snake[i] = snake[i - 1];
  }

  snake[0].X += direction.X;
  snake[0].Y += direction.Y;

  if (snake[0].X == fruit.X && snake[0].Y == fruit.Y) {
    repositionFruit();
    snake.push_back(snakeLastPosition);
  }

  if (snake[0].X < -4) {
    snake[0].X = 52;
  }
  if (snake[0].X > 54) {
    snake[0].X = -2;
  }
  if (snake[0].Y < -4) {
    snake[0].Y = 32;
  }
  if (snake[0].Y > 34) {
    snake[0].Y = -2;
  }

  for (int i = 1; i < snake.size(); i++) {
    if (snake[0].X == snake[i].X && snake[0].Y == snake[i].Y) {
      restart();
    }
  }
}

void draw() {
  rect.w = 26;
  rect.h = 26;
  for (int i = 0; i < snake.size(); i++) {
    rect.x = snake[i].X * 26;
    rect.y = snake[i].Y * 26;
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_RenderFillRect(renderer, &rect);
  }
  rect.x = fruit.X * 26;
  rect.y = fruit.Y * 26;
  SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
  SDL_RenderFillRect(renderer, &rect);
}

void repositionFruit() {
  fruit.X = (rand() % 49);
  fruit.Y = (rand() % 26);
}

void restart() {
  snake.clear();
  srand(time(NULL));
  Vec2 vec2;

  vec2.X = 49 / 2;
  vec2.Y = 26 / 2;

  snake.push_back(vec2);

  direction.X = 0;
  direction.Y = 0;

  repositionFruit();
}