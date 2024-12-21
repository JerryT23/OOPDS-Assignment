#ifndef BATTLEFIELD_H
#define BATTLEFIELD_H
class Game {
    private:
        Team* teams;
        int width;
        int height;
        int iterations;
    public:
    void init();
    void terminate();
};
#endif