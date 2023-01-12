#include "vector2d.cpp"
#include <simplecpp>

/**
* Stores the coordinates of click into a vector2d param
* */
void registerClick(Vector2d *vector2d) {
    const int twoPower16 = 65536;
    int point;
    point = getClick();
    int x = point / twoPower16;
    int y = point % twoPower16;
    vector2d->set(x, y);
}
