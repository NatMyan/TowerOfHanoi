#include "Rod.hpp"

Rod::Rod (const Disk disksAmount, const RodType type) {
    if (isRodSource(type)) {
        for (Disk disk = disksAmount; disk >= 1; --disk) 
                rodOfDisks.push_back(disk);
    }
}

void Rod::removeTopDisk () {
    //rodOfDisks.erase(rodOfDisks.begin());
    rodOfDisks.pop_back();
}

void Rod::addTopDisk (const Disk &someDisk) {
    //rodOfDisks.insert(rodOfDisks.begin(), someDisk);
    rodOfDisks.push_back(someDisk);
}

bool Rod::isRodSource (const RodType type) {
    return type == RodType::Source;
}

void Rod::setRod (const Disks rodOfDisks, const RodType type) { 
    this->rodOfDisks = rodOfDisks;
    this->type = type;
}

Disks Rod::getRod () const { 
    return this->rodOfDisks;
}

Disk Rod::getTopDisk () const {
    return !rodOfDisks.empty() ? this->rodOfDisks.back() : 0;
}

/*Disk Rod::getBottomDisk () const {
    return this->rodOfDisks.back();
}*/

/*void Rod::setBottomDisk (Disk disk) {
    this->bottomDisk = disk;
}*/

/*void Rod::setTopDisk (Disk disk) {
    this->topDisk = disk;
}*/




