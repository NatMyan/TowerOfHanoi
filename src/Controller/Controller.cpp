#include "Controller.hpp"

Controller::~Controller () {
    delete window;
}

Keys Controller::getKey () const {
    return static_cast<Keys>(window->input());
}

int Controller::handleMenuKeys (Menu sections, int &selection) {
    switch (getKey()) {
        case Keys::KeyUp:
            goUpInMenu(selection);
            break;
        case Keys::KeyDown:
            goDownInMenu(selection, sections);
            break;
        case Keys::Enter:
            return selection;
            break;
        case Keys::Space:
        case Keys::KeyLeft:
        case Keys::KeyRight:
        case Keys::Esc:
            break;
    }
    return -1;
}

void Controller::handleGameKeys(int &selection, bool &exit) {
    switch (getKey()) {
    case Keys::KeyLeft:
        goLeftInGame(selection);
        break;
    case Keys::KeyRight:
        goRightInGame(selection);
        break;
    case Keys::Enter: 
        selectOrMoveDisk(selection);
        break;
    case Keys::Esc:
        exit = true;
        board.isFinished();
        break;
    case Keys::Space:
        startAnimatedSolution(selection);
        break;
    case Keys::KeyUp:
    case Keys::KeyDown:    
        break;
    }
}

void Controller::goUpInMenu (int &selection) {
    if (selection > 0)
        --selection;
}

void Controller::goDownInMenu (int &selection, const Menu sections) {
    if (selection < static_cast<int>(sections.size()) - 1)
        ++selection;
}

void Controller::goLeftInGame (int &selection) {
    if (selection > 0) {
        --selection;
    }
}

void Controller::goRightInGame (int &selection) {
    if (selection < 2) {
        ++selection;
    }
}

void Controller::selectOrMoveDisk (const int selection) {
    if (selected != -1) {
        board.move(selected, selection);
        selected = -1;
    }
    else {
        selected = selection;
    } 
}

void Controller::menu () {
    Menu sections = {"Play", "How To Play", "Exit"};
    int selection = 0;
    bool exit = false;
    while (!exit) {
        int enterCase = handleMenuKeys(sections, selection);
        if (enterCase != -1)
            chooseInMenu(sections, enterCase, exit);
        window->drawMenu(sections, selection, 2);
    }
}

void Controller::playGame () {
    bool exit = false;
    int selection = 0;
    while (!exit) {
        handleGameKeys(selection, exit);
        window->drawBoard(board.getTower(), selection);
    }
}

void Controller::chooseInMenu (Menu sections, int enterCase, bool &exit) {
    if (sections[enterCase] == "Play")
        playGame();
    else if (sections[enterCase] == "How To Play")
        rules();
    else if (sections[enterCase] == "Exit")
        exit = true;
}

void Controller::startAnimatedSolution (int &selection) {
    selected = -1;
    board.resetBoard();
    int source = static_cast<int>(RodType::Source);
    int destination = static_cast<int>(RodType::Destination);
    int auxilary = static_cast<int>(RodType::Auxilary);
    window->drawBoard(board.getTower(), selection);
    sleep(1);
    animatedSolution(board.getdisksAmount(), source, destination, auxilary);
}

void Controller::animatedSolution (const int disk, const int currentPlace, const int newPlace, const int mediatorPlace) {
    if (disk == 1) {
        board.move(currentPlace, newPlace);
        window->drawBoard(board.getTower(), selected);
        sleep(2);
    }
    else {
        int tmp = 3 - currentPlace - newPlace;
        animatedSolution (disk - 1, currentPlace, mediatorPlace, newPlace);
        board.move(currentPlace, newPlace);
        window->drawBoard(board.getTower(), selected);
        sleep(2);        
        animatedSolution (disk - 1, mediatorPlace, newPlace, currentPlace);
    }
}

void Controller::rules () {
    Menu sections;
    sections.push_back("> How To Play <");
    sections.push_back("\n\n");
    sections.push_back("Use the left and right arrow keys to select the rods");
    sections.push_back("Press the Enter key to select or move the disk");
    sections.push_back("Press the spacebar, if you want the automatic solution"); 
    sections.push_back("You can only select the top disk");
    sections.push_back("You can only put a disk on top of a larger disk or an empty rod");      
    sections.push_back("\n\n");         
    sections.push_back("Go Back");
    int selection = 0;
    bool exit = false;
    while (!exit) {        
        int enterCase = handleMenuKeys(sections, selection);
        selection = sections.size() - 1;
        if (enterCase != -1)
            exit = true;
        window->drawMenu(sections, selection, 0);
    }
}