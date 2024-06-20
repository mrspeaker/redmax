#include <terrain.hpp>

#import <chunk.hpp>

rm::terrain::terrain() {
    const auto size = 4;
    for (int j = -size; j <= size; j++) {
        for (int i = -size; i <= size; i++) {
            rm::chunk ch{};
            ch.x = i;
            ch.z = j;
            ch.col = abs(i + j) % 3;
            chunks.push_back(ch);
        }
    }

}

rm::tile* rm::terrain::get_tile_from_pos(float x, float y) {
    auto chunk_x = static_cast<int>(std::floor((x + 50.0) / 100.0f));
    auto chunk_y = static_cast<int>(std::floor((y + 50.0) / 100.0f));
    auto chunk_idx = (chunk_y + 4) * 9 + (chunk_x + 4);

    // Find tile index
    int tile_x;
    int tile_y;
    if (x-50 >= 0) {
        tile_x = static_cast<int>((std::fmod(x-50,100.0f) / 100.0f) * 16);
    } else {
        tile_x = static_cast<int>((std::fmod(100 - std::fabs(x-50),100.0f) / 100.0f) * 16);
    }
    tile_y = static_cast<int>((std::fmod(y-50,100.0f) / 100.0f) * 16);

    auto chunk = &chunks[chunk_idx];
    return &(chunk->tiles[tile_y * 16 + tile_x]);
}
