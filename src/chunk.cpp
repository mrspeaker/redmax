#import <chunk.hpp>
#import <Vector3.hpp>
#import <tile.hpp>

rm::chunk::chunk()
    : trees{{0.0, 0.0, 0.0}}
    , tiles(new tile[width * height]) {
    dirty = true;
    for (int y = 0; y < height; y++) {
      for (int x = 0; x < width; x++) {
          rm::tile t = tile();
          t.type = 0;
          tiles[y*width + x] = t;
      }
    }
}

void rm::chunk::update() {
    auto ch_x = x;
    auto ch_z = z;
    for (int y = 0; y < height; y++) {
      for (int x = 0; x < width; x++) {
          auto& tile = tiles[y * width + x];

          if (x < width - 1 && tile.type == 0 && tiles[y*width + x + 1].type == 3) {
              tile.next_type = 2;
          }

          auto last_type = tile.type;
          if (tile.update()) {
              dirty = true;
              if (tile.type != last_type && tile.type == 3) {
                  notify(game_event::SPAWN, world_x + (x * 8.0) + 4.0, 0.0, world_z + (y * 8.0) + 4.0);
              }
          }
      }
    }
}
