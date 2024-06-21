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
    width_in_chunks = size * 2 + 1;
    height_in_chunks = size * 2 + 1;
}

rm::tile* rm::terrain::get_tile_from_pos(float x, float y) {
    auto chunk_x = static_cast<int>(std::floor(x / 100.0f));
    auto chunk_y = static_cast<int>(std::floor(y / 100.0f));
    auto chunk_idx = (chunk_y + height_in_chunks / 2) * width_in_chunks + (chunk_x + width_in_chunks / 2);
    auto chunk = &chunks[chunk_idx];

    int tile_x = static_cast<int>((std::fmod(std::fabs(x),100.0f) / 100.0f) * 16);
    if (x < 0) {
        tile_x = 15-tile_x;
    }
    int tile_y = static_cast<int>((std::fmod(std::fabs(y),100.0f) / 100.0f) * 16);
    if (y < 0) {
        tile_y = 15-tile_y;
    }

    return &(chunk->tiles[tile_y * 16 + tile_x]);
}
