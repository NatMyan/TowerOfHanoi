#ifndef NCURSES_WINDOW_HPP
#define NCURSES_WINDOW_HPP

#include "Window.hpp"
#include <ncurses.h>

class NcursesWindow : public Window {    
    private:
        int width;
        int height;
        //Printable board; 
    public:
        NcursesWindow(const int diskAmount);
        ~NcursesWindow();
    public:
        void drawBoard (const Board::Tower tower, int selection);  //a.k.a. the entire Tower
        void drawMenu (Menu sections, int selection, const int printSqrBracketCase);
        int input ();
    private:
        void drawRod (const int y, const int x, const Rod &rod, bool isRodSelected) const;
        void drawDisk (const int y, const int x, const int diskIndex, const Disk &disk, bool isSelected) const;
        void drawNavigator (const int y, const int x, const int selection, const int disksAmount);
        void drawGround (const int y, const int x, const int disksAmount);
        void drawRodSticks (const int y, const int x, const int disksAmount);
        //void createRod (const Disks &rodOfDisks, bool isRodSelected);
        //void createDisk (const int diskIndex, const Disk &disk, bool isSelected);
};

#endif //NCURSES_WINDOW_HPP
