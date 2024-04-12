#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

using namespace std; 

int main(int argc, char** argv) {
    SDL_Init(SDL_INIT_VIDEO);              // Khởi tạo SDL2

    // Tạo cửa sổ
    SDL_Window* window = SDL_CreateWindow("Hang man",
                                          SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                          640, 480,
                                          SDL_WINDOW_SHOWN);

    // Tạo renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

    // Tải hình ảnh
    SDL_Surface* image = IMG_Load("image/hang1.png");
    if (!image) {
        cout << "Can't " ;
        // handle error
    }

    // Tạo texture từ hình ảnh
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, image);

    // Vẽ texture lên renderer
    SDL_RenderCopy(renderer, texture, NULL, NULL);

    // Hiển thị renderer
    SDL_RenderPresent(renderer);

    // Đợi 5 giây
    SDL_Delay(5000);

    // Dọn dẹp và thoát
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(image);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}