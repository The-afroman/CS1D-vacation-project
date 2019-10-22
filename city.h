
#ifndef CITY_H
#define CITY_H

#include <string>
#include <vector>

using std::string;

/*! Class city holds the city data and food Items for the cities */
class city{

    /*! struct that contains the name of the food and its description */
    struct food{
        string foodItem; //!< name of food
        string foodDisc; //!< Description of the food
    };

    public: 

        //! constructor
        city();

        //! takes in name and distance for the specific city
        city(string name, double distance);

        //! destructor
        ~city();

        //! returns name of city as a string variable
        string getName() const;

        //! returns the distance from Paris as a double value
        double getDistanceFromParis() const;
      
    private: 

        string name; //!< name of city
        double distFromParis;
        std::vector<food> cityFoods; //!< vector for foods
        void setName(string); //!< set name of city
        void setDistanceToParis(double); //!< set distance from city to Paris
        //void setFoodItems(string *[]);
        //void setFoodDesc(string *[]);

};

#endif
