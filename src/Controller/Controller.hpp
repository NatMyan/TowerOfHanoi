#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include "../Window/NcursesWindow.hpp"
#include "../Board/Board.hpp"
#include "../Rod/Rod.hpp"
#include <unistd.h> // sleep

enum Keys {
    KeyUp = 259,
    KeyDown = 258,
    KeyLeft = 260,
    KeyRight = 261,
    Enter = 10,
    Space = 32,
    Esc = 27
};

class Controller {
    private:
        Board board;
        Window *window;
        Keys key;
        int selected = -1;
    public:
        Controller (const int disksAmount) : board (disksAmount), window (new NcursesWindow(disksAmount)) {}
        ~Controller();
    public:
        void handleGameKeys (int &selection, bool &exit);
        int handleMenuKeys (const Menu sections, int &selection);
        Keys getKey () const;
    public:
        void run ();
        void menu ();
        void rules ();
        void playGame ();    
    private:
        void goLeftInGame (int &selection);
        void goRightInGame (int &selection);
        void selectOrMoveDisk (const int selection);
        void goUpInMenu (int &selection);
        void goDownInMenu (int &selection, const Menu sections);   
        void chooseInMenu (Menu sections, int enterCase, bool &exit);
        void animatedSolution (const int disk, const int currentPlace, const int newPlace, const int mediatorPlace);
        void startAnimatedSolution (int &selection);
};

#endif //CONTROLLER_HPP
