
#ifndef CITY_H
#define CITY_H

#include <string>
#include <vector>

using std::string;

class city{

    struct food{
        string foodItem;
        string foodDisc;
    };

    public: 

        city();

        city(string name, double distance);

        ~city();

        string getName() const;
        double getDistanceFromParis() const;
      



    private: 

        string name;
        double distFromParis;
        std::vector<food> cityFoods;
        void setName(string);
        void setDistanceToParis(double);
        //void setFoodItems(string *[]);
        //void setFoodDesc(string *[]);

};

#endif
