#ifndef BOARD_HPP
#define BOARD_HPP

#include "../Rod/Rod.hpp"

class Board {
    public:
        using Tower = std::vector<Rod>;
    private:
        const int rodAmount = 3;
        const int disksAmount;
        Tower tower;   // tower consists of 3 rods
    public:
        Board (const int disksAmount);
        ~Board ();
    public:
        void solveAutomatically ();
        void resetBoard ();
        void move (const int currentPlace, const int newPlace);
        bool isFinished ();
    private:
        bool isMoveValid (const int currentPlace, const int newPlace) const;
        void hanoiSolution (const int disk, const int currentPlace, const int newPlace, const int mediatorPlace);
    public:
        Tower getTower () const;
        int getRodAmount () const;
        int getdisksAmount () const;    
};

#endif //BOARD_HPP