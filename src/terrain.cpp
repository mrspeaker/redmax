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
