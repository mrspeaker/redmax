#import <chunk.hpp>
#import <Vector3.hpp>
#import <tile.hpp>

rm::chunk::chunk()
    : trees{{0.0, 0.0, 0.0}}
    , tiles(new tile[width * height]) {
    dirty = true;
    for (int y = 0; y < height; y++) {
      for (int x = 0; x < width; x++) {
          unsigned char ch = GetRandomValue(0,10) == 1 ? 1 : 0;
          rm::tile t = tile();
          t.type = ch;
          tiles[y*width + x] = t;
      }
    }
}

void rm::chunk::update() {
    for (int y = 0; y < height; y++) {
      for (int x = 0; x < width; x++) {
          auto& tile = tiles[y * width + x];

          if (x < width && tile.type == 0 && tiles[y*width + x + 1].type == 3) {
              tile.next_type = 2;
          }

          if (tile.update()) {
              dirty = true;
          };
      }
    }
}
