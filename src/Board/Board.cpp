#include "Board.hpp"

Board::Board (const int disksAmount) : disksAmount (disksAmount) {
    resetBoard ();
}

Board::~Board () {
    tower.clear();
}

void Board::resetBoard () {
    tower.clear();
    tower.push_back(Rod(disksAmount, Source));
    tower.push_back(Rod(disksAmount, Auxilary));
    tower.push_back(Rod(disksAmount, Destination));
}

void Board::move (const int currentPlace, const int newPlace) {
    if (isMoveValid(currentPlace, newPlace)) {
        const auto disk = tower.at(currentPlace).getTopDisk();
        tower.at(currentPlace).removeTopDisk();
        tower.at(newPlace).addTopDisk(disk);
        
    }
}

bool Board::isFinished () {
    return tower.back().getRod().size() == disksAmount;
}

bool Board::isMoveValid (const int currentPlace, const int newPlace) const {  
    return (!tower.at(currentPlace).getRod().empty() 
           && (tower.at(newPlace).getTopDisk() > tower.at(currentPlace).getTopDisk() 
           || tower.at(newPlace).getRod().empty())); //make sure that the person cannot move more than 3rd rod
}

Board::Tower Board::getTower () const {
    return this->tower;
}

int Board::getdisksAmount () const {
    return this->disksAmount;
}

int Board::getRodAmount () const {
    return this->rodAmount;
}
