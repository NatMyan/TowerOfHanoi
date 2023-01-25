#ifndef WINDOW_HPP
#define WINDOW_HPP

#include "../Board/Board.hpp"

class Window {
    protected:
        const int maxDiskSize;
    public:
        Window (const int diskAmount) : maxDiskSize (diskAmount * 2 + 1) {} 
        virtual ~Window () {}
    public:
        virtual void drawBoard (const Board::Tower tower, int selection) = 0;
        virtual void drawMenu (const Menu, int, const int) = 0;
        virtual int input () = 0;
};

#endif //WINDOW_HPP
