#include "NcursesWindow.hpp"

NcursesWindow::NcursesWindow (const int diskAmount) : Window (diskAmount) { 
    initscr();
    curs_set(0);
    keypad(stdscr, true);
    getmaxyx(stdscr, height, width);
    halfdelay(5);
    noecho();
}

NcursesWindow::~NcursesWindow() {
    endwin();
}

int NcursesWindow::input() {
    return getch();
}

void NcursesWindow::drawMenu (Menu sections, int selection, const int printSqrBracketCase) {
    clear();
    const int centreHeight = height / 2 - sections.size();
    const int centreWidth = width / 2 - 5;
    for (int i = 0; i < (int)sections.size(); ++i) {
        if (selection == i) 
            mvprintw (centreHeight + 1 + i, centreWidth - sections[i].length()/2, "[%s]\n", sections[i].c_str());
        else 
            mvprintw (centreHeight + 1 + i, centreWidth - sections[i].length()/2, " %s \n", sections[i].c_str());
    }    
    refresh();
}

void NcursesWindow::drawBoard (const Board::Tower tower, int selection) {
    const int centreHeight = height / 2;
    const int centreWidth = width / 2;
    const int disksAmount = (maxDiskSize - 1) / 2;

    clear ();
    drawRodSticks (centreHeight, centreWidth, disksAmount);
    drawRod (centreHeight, centreWidth * 2/3, tower.at(0), true);    
    drawRod (centreHeight, centreWidth * 2/3 + maxDiskSize + 2, tower.at(1), false);
    drawRod (centreHeight, centreWidth * 2/3 + 2 * maxDiskSize + 4, tower.at(2), false);
    //printw("                                                             %d", selection);
    drawGround (centreHeight, centreWidth, disksAmount);
    drawNavigator (centreHeight, centreWidth, selection, disksAmount);      
    refresh ();
}

void NcursesWindow::drawRodSticks (const int y, const int x, const int disksAmount) {
    for (int i = 0; i < disksAmount + 1; ++i) {
        mvprintw (y - i, x * 2/3 + disksAmount, "|");
    }
    for (int i = 0; i < disksAmount + 1; ++i) {
        mvprintw (y - i, x * 2/3 + disksAmount + maxDiskSize + 2, "|");
    }
    for (int i = 0; i < disksAmount + 1; ++i) {
        mvprintw (y - i, x * 2/3 + disksAmount + 2 * maxDiskSize + 4, "|");
    }
    //mvprintw (y + 2, x * 2/3 + disksAmount + selection * maxDiskSize + cursorSelection, "^");
}

void NcursesWindow::drawGround (const int y, const int x, const int disksAmount) {
    for (int i = -1; i <= 3 * maxDiskSize + 4; ++i) {
        mvprintw (y + 1, x * 2/3 + i, "%d", disksAmount);
    }
}

void NcursesWindow::drawNavigator (const int y, const int x, const int selection, const int disksAmount) {
    int cursorSelection = -1;
    switch (selection) {
        case 0:
            cursorSelection = 0;
            break;
        case 1:
            cursorSelection = 2;
            break;
        case 2:
            cursorSelection = 4;
            break;
    }
    mvprintw (y + 2, x * 2/3 + disksAmount + selection * maxDiskSize + cursorSelection, "^");
}

void NcursesWindow::drawRod (const int y, const int x, const Rod &rod, bool isRodSelected) const {
    const int disksAmount = (maxDiskSize - 1) / 2;
    //printw("%d, ",rod.getRod().size());
    for (int i = 0; i < rod.getRod().size(); ++i) {
        drawDisk (y - i, x, i, rod.getRod().at(i), isRodSelected);
    }
}

void NcursesWindow::drawDisk (const int y, const int x, const int diskIndex, const Disk &disk, bool isSelected) const {
    const int diskSize = disk * 2 + 1;
    const int startOfDisk = (maxDiskSize - diskSize) / 2;
    const int endOfDisk = startOfDisk + diskSize;

        for (int i = 0; i <= maxDiskSize; ++i) {
            if (i >= startOfDisk && i < endOfDisk) 
                mvprintw (y, x + i,"#");
            else 
                mvprintw (y, x + i," ");
            if (isSelected) {
                /*if (diskIndex == 0) {
                    if (i == endOfDisk) 
                        mvprintw (y, x + i,"}");
                    else if (i == startOfDisk - 1)
                        mvprintw (y, x + i, "{");
                }*/
                isSelected = false; 
            }
        }
}


// Stuff that didn't make it to the cut--------------------------------------------------------------------------
    // in constructor:  board = Printable (maxDiskSize, "");

    // below the rods, print "#######..." with the size of 3 rods + 4 \/
    //  ########### ########### ###########
    // 5555555555555555555555555555555555555

/*
from drawDisk:
        if (isSelected && diskIndex == 0) {
        for (int i = 0; i <= maxDiskSize; ++i) {
            if (i == startOfDisk - 1)
                mvprintw (y, x + i, "{");
            else if (i >= startOfDisk && i < endOfDisk) 
                mvprintw (y, x + i,"#");
            else if (i == endOfDisk) 
                mvprintw (y, x + i,"}");
            else 
                mvprintw (y, x + i," ");
        }
        isSelected = false;
    }
    else {
        whatever is in the function
    }
*/

/*void NcursesWindow::createDisk (const int diskIndex, const Disk &disk, bool isSelected) {
    const int diskSize = disk * 2 + 1;
    const int startOfDisk = (maxDiskSize - diskSize) / 2;
    const int endOfDisk = startOfDisk + diskSize;

    if (isSelected && diskIndex == 0) {
        for (int i = 0; i <= maxDiskSize; ++i) {
            if (i == startOfDisk - 1)
                board.at(diskIndex) + "{";
            else if (i >= startOfDisk && i < endOfDisk) 
                board.at(diskIndex) + "#";
            else if (i == endOfDisk) 
                board.at(diskIndex) + "}";
            else 
                board.at(diskIndex) + " ";
        }
        isSelected = false;
    }
    else {
        for (int j = 0; j < maxDiskSize; ++j) {
            for (int i = 0; i <= maxDiskSize; ++i) {
                if (i >= startOfDisk && i < endOfDisk) 
                    board.at(diskIndex) + "#";
                else 
                    board.at(diskIndex) + " ";
            }
        }
        if (isSelected)
            isSelected = false;
    }
}
*/

/*
void NcursesWindow::createBoard (const Disk &disk, bool isSelected) {
    const int diskSize = disk * 2 + 1;
    const int startOfDisk = (maxDiskSize - diskSize) / 2;
    const int endOfDisk = startOfDisk + diskSize;

    board.clear();
    board = Printable (maxDiskSize, "");

    if (isSelected) {
        for (int j = 0; j < maxDiskSize; ++j) {
            for (int i = 0; i <= maxDiskSize; ++i) {
                if (i == startOfDisk - 1)
                    board.at(j) + "{";
                else if (i >= startOfDisk && i < endOfDisk) 
                    board.at(j) + "#";
                else if (i == endOfDisk) 
                    board.at(j) + "}";
                else 
                    board.at(j) + " ";
            }
        }
        isSelected = false;
    }
    else {
        for (int j = 0; j < maxDiskSize; ++j) {
            for (int i = 0; i <= maxDiskSize; ++i) {
                if (i >= startOfDisk && i < endOfDisk) 
                    board.at(j) + "#";
                else 
                    board.at(j) + " ";
            }
        }
    }
}*/
