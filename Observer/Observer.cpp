
#include <iostream>
#include<vector>
#include <algorithm>
using namespace std;

class Observer;

/**
 * Subject interface is implemented by all concrete implementation of Subject 
 * class.These methods will accept Observer instance for register,removal and 
 * notification
 */
class Subject{
    public:
        virtual void RegisterObserver(Observer *obj) = 0;
        virtual void RemoveObserver(Observer *obj) = 0;
        virtual void NotifyObservers() = 0;
};

/**
 * The Observer interface is implemented by all Observers,
 * so they all have to implement the update() method.
 */
class Observer{
    public:
        virtual void update(float temp, float humidity, float pressure) = 0;
};

/**
 * The DisplayElement interface just includes one method,disply()
 * that we will call when the display element needs to be displayed
 */
class DisplayElement{
    virtual void display() = 0;
};

/**
 * Concreate implementation of Subject class, WeatherData implements all interfaces of
 * Subject class
 */
class WeatherData : public Subject
{
    public:
        vector<Observer*> Objlist; //!< Added vector Objlist to hold the Observers 
        float temp;
        float humidity;
        float pressure;
        
        /**
         * When an Observer registers , we just add it to the list
         */
        void RegisterObserver(Observer *obj)
        {
            Objlist.push_back(obj);
        }
        
        /**
         * When an Observer de-register, just remove it from the list
         */
        void RemoveObserver(Observer *obj)
        {
            Objlist.erase(std::remove(Objlist.begin(), Objlist.end(), obj), Objlist.end());  
        }
        
        /** Itertively notify all Observers by taking out the 
         * instance of Observer from the list
         */
        void NotifyObservers()
        {
            for(vector<Observer*>::const_iterator iter = Objlist.begin(); iter != Objlist.end(); ++iter)
            {
                if(*iter != 0)
                {
                    (*iter)->update(temp, humidity, pressure);
                }
            }
        }
        
        /**
         * Notify the Observers when we get updated
         * measurements from the Weather Station
         */
         void MeasurementsChanged()
         {
             NotifyObservers();
         }
         
         /**
          * API to update weather parameters
          */
          void SetMeasurements(float temp, float humidity, float pressure)
          {
              this->temp = temp;
              this->humidity = humidity;
              this->pressure = pressure;
              MeasurementsChanged();
          }
};

/**
 * Concrete implementation of Observer
 */
class CurrentConditionsDisplay: public Observer, public DisplayElement{
    private:
        float temp;
        float humidity;
        float pressure;
        Subject *weatherData;
    
    public:
       CurrentConditionsDisplay(Subject *weatherdata){
           weatherData = weatherdata;
           weatherData->RegisterObserver(this);
       }
       
       void update(float temp, float humidity, float pressure)
       {
           this->temp = temp;
           this->humidity = humidity;
           this->pressure = pressure;
       }
       
       void display()
       {
           std::cout<<" Current temperature is "<<temp<<" "<<" at humidiity level "<<humidity<<" pressure is "<<pressure<<std::endl;
       }
    
};

/**
 * Client program
 */
int main() {
    WeatherData *weatherData = new WeatherData;
    CurrentConditionsDisplay *currentConditionsDisplay = new CurrentConditionsDisplay(weatherData);
    weatherData->SetMeasurements(80,65, 30);
    return 0;
}
