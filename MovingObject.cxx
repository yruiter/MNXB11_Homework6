//MovingObject.cxx

#include "MovingObject.h"
#include <TObject.h>
#include <cmath>

//can use root classes 
ClassImp(MovingObject);
        //Constructor 
        //Sets up function with initial values -- dont have to do Double_t vy
        MovingObject::MovingObject()
            : fVx(0.0), fVy(0.0), fVz(0.0)
            { }

        //new value of vectors after initial value 
        MovingObject::MovingObject(Double_t vx, Double_t vy, Double_t vz)
            : fVx(vx), fVy(vy), fVz(vz)
            { }

        //Distructor 
        //cleans up fucntion when the function is destroyed 
        MovingObject::~MovingObject()
            { }

        //Getter 
        //Return the vector Vx as a vector 
        //Defines vx as a part of the class Movingobject without changing the function 
        Double_t MovingObject::Vx() const
        {  return fVx; }

        //same as vx but for y 
        Double_t MovingObject::Vy() const
        { return fVy; }

        //same as vz  but for z 
        Double_t MovingObject::Vz() const
        { return fVz; }

        //creates a void which is defined later containing the functions and the corresponding vector values 
        void MovingObject::SetVelocity(Double_t vx, Double_t vy, Double_t vz)
        {
          fVx = vx;
          fVy = vy;
          fVz = vz;
        }
        
        //defines speed
        Double_t MovingObject::Speed() const
        { return std::sqrt(fVx * fVx + fVy * fVy + fVz * fVz); }
 
        //defines speed in x and y directions 
        Double_t MovingObject::HorizontalSpeed() const
        { return std::sqrt(fVx * fVx + fVy * fVy); }
