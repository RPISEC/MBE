#include <iostream>
#include <cstdio>

class Rect {
    public:
        Rect() : width(0), height(0) {}
        int area() { return width*height; }
        void set_vals(int w, int h);
    private:
        int width;
        int height;
};

void
Rect::set_vals(int w, int h)
{
    this->width = w;
    this->height = h;
}

int
main(int argc, char *argv[])
{
    Rect r;

    printf("sizeof(r) = %d\n", sizeof(r));

    int *vars = (int *)&r;

    printf("width = %d, height = %d\n", vars[0], vars[1]);

    r.set_vals(10, 24);
    printf("setvals(10, 24);\n");
    printf("width = %d, height = %d\n", vars[0], vars[1]);

    return 0;
}
