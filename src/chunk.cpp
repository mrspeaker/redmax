#import <chunk.hpp>
#import <Vector3.hpp>
#import <tile.hpp>

rm::chunk::chunk()
    : trees{{0.0, 0.0, 0.0}},
      tiles(new tile[width * height]) {
    for (int y = 0; y < height; y++) {
      for (int x = 0; x < width; x++) {
          unsigned char ch = GetRandomValue(0,10) == 1 ? 1 : 0;
          tiles[y*width + x] = tile{ch, 0};
      }
    }
}

void rm::chunk::update() {
    for (int y = 0; y < height; y++) {
      for (int x = 0; x < width; x++) {
          tiles[y*width + x].update();
      }
    }
}
