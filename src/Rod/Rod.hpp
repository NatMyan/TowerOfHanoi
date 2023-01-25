#ifndef ROD_HPP
#define ROD_HPP

#include "../Redefinitions.hpp"

enum RodType {
    Source,
    Auxilary,
    Destination
};

class Rod {
    private:
        Disks rodOfDisks;
        RodType type;
    public:
        Rod (Disk disksAmount, RodType type); 
        ~Rod () {}  
    private:
        bool isRodSource (const RodType type);
    public:
        void removeTopDisk ();
        void addTopDisk (const Disk &someDisk);
    public:                
        Disk getTopDisk () const;
        Disks getRod () const;
        void setRod (const Disks rodOfDisks, const RodType type);
        //Disk getBottomDisk () const;
        //void setBottomDisk (Disk disk);
        //void setTopDisk (Disk disk);             
};

#endif //ROD_HPP
