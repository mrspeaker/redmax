#import <chunk.hpp>
#import <Vector3.hpp>

rm::chunk::chunk()
    : trees{{0.0, 0.0, 0.0}},
      tiles(new unsigned char[width * height]) {
    for (int y = 0; y < height; y++) {
      for (int x = 0; x < width; x++) {
          tiles[y*width + x] = GetRandomValue(0,3) == 1 ? 0 : 1;
      }
    }
}
