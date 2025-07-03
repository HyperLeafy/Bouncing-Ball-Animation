#define SDL_MAIN_USE_CALLBACKS 1
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <cstdint>
#include <vector>
#include <SDL3/SDL_oldnames.h>

constexpr int8_t BALL_RADIUS = 30;

struct AppState {
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    int32_t width = 640, height = 400;
    float x = width / 2.0f, y = height / 2.0f;
    float vx = 150.0f, vy = 100.0f;
    uint64_t last_time = 0;
};

SDL_AppResult SDL_AppInit(void** appstate, int argc, char* argv[]) {
    AppState* state = new AppState();
    SDL_SetAppMetadata("Example Renderer Clear", "1.0", "com.example.renderer-clear");

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("SDL_Init failed: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    state->window = SDL_CreateWindow("SDL3 Bouncing Ball", state->width, state->height, 0);
    if (!state->window) {
        SDL_Log("SDL_CreateWindow failed: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    state->renderer = SDL_CreateRenderer(state->window, nullptr);
    state->last_time = SDL_GetTicks();

    *appstate = state;
    return SDL_APP_CONTINUE;
}


SDL_AppResult SDL_AppIterate(void* ptr) {
    AppState* state = static_cast<AppState*>(ptr);
    uint64_t now = SDL_GetTicks();
    float delta = (now - state->last_time) / 1000.0f;
    state->last_time = now;

    state->x += state->vx * delta;
    state->y += state->vy * delta;

    if (state->x - BALL_RADIUS < 0 || state->x + BALL_RADIUS > state->width) {
        state->vx = -state->vx;
    }
    if (state->y - BALL_RADIUS < 0 || state->y + BALL_RADIUS > state->height) {
        state->vy = -state->vy;
    }

    SDL_SetRenderDrawColor(state->renderer, 0, 0, 0, 255);
    SDL_RenderClear(state->renderer);
    SDL_SetRenderDrawColor(state->renderer, 255, 0, 0, 255);

    for (int dx = -BALL_RADIUS; dx <= BALL_RADIUS; ++dx) {
        for (int dy = -BALL_RADIUS; dy <= BALL_RADIUS; ++dy) {
            if (dx * dx + dy * dy <= BALL_RADIUS * BALL_RADIUS) {
                SDL_RenderPoint(state->renderer, static_cast<int>(state->x + dx), static_cast<int>(state->y + dy));
            }
        }
    }

    SDL_RenderPresent(state->renderer);
    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void* ptr, SDL_Event* event) {
    if (event->type == SDL_EVENT_QUIT) {
        return SDL_APP_SUCCESS;
    }
    return SDL_APP_CONTINUE;
}


void SDL_AppQuit(void* appstate, SDL_AppResult result) {
    if (!appstate) return;
    AppState* state = static_cast<AppState*>(appstate);
    SDL_DestroyRenderer(state->renderer);
    SDL_DestroyWindow(state->window);
    delete state;
    SDL_Quit();
}

