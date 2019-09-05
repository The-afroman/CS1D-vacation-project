
#ifdef CITY_H
#define CITY_H

#include <string>


class city{

    public: 

        city();

        city(string name, double distance, string * food[], string * foodDesc[]);

        ~city();

        string getName() const;
        double getDistanceFromParis() const;
      



    private: 

        string name;
        double distFromParis;
        string * foodItems[];
        string * foodDescriptions[];

        void setName(string);
        void setDistanceToParis(double);
        void setFoodItems(string *[]);
        void setFoodDesc(string *[]);

};




#endif