#include "core/engine.hpp"

// Setting up stb_image.h flag at entry point to prevent any errors
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

int main(void) {
    Engine engine = Engine();
    engine.run();
    return 0;
}