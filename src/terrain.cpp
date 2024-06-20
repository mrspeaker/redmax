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
    auto chunk_x = static_cast<int>(std::floor((x + 50.0) / 100.0f));
    auto chunk_y = static_cast<int>(std::floor((y + 50.0) / 100.0f));
    auto chunk_idx = (chunk_y + height_in_chunks / 2) * width_in_chunks + (chunk_x + width_in_chunks / 2);
    auto chunk = &chunks[chunk_idx];

    // Find tile index: todo: c'mon, this is gnarly and doesn't work for "0" chunks
    int tile_x;
    int tile_y;
    if (x - 50 > 0) {
        tile_x = static_cast<int>((std::fmod(x-50,100.0f) / 100.0f) * 16);
    } else {
        tile_x = 15 + static_cast<int>((std::fmod( 100 - std::fabs(x - 50),100.0f) / 100.0f) * 16);
    }
    if (y - 50 > 0) {
        tile_y = (static_cast<int>((std::fmod(y-50,100.0f) / 100.0f) * 16)) % 16;
    } else {
        tile_y = (15 + static_cast<int>((std::fmod( 100 - std::fabs(y -50),100.0f) / 100.0f) * 16)) % 16;
    }

    return &(chunk->tiles[tile_y * 16 + tile_x]);
}
