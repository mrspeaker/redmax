#import <chunk.hpp>
#import <Vector3.hpp>
#import <tile.hpp>

rm::chunk::chunk()
    : trees{{0.0, 0.0, 0.0}}
    , tiles(new tile[width * height]) {
    dirty = true;
    for (int y = 0; y < height; y++) {
      for (int x = 0; x < width; x++) {
          unsigned char ch = 0;//GetRandomValue(0,10) == 1 ? 1 : 0;
          rm::tile t = tile();
          t.type = ch;
          tiles[y*width + x] = t;
      }
    }
}

void rm::chunk::update() {
    for (int y = 0; y < height; y++) {
      for (int x = 0; x < width; x++) {
          if (tiles[y*width + x].update()) {
              dirty = true;
          };
      }
    }
}
