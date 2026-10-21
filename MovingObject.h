//MovingObject.h

#ifndef MOVINGOBJECT_H
#define MOVINGOBJECT_H
//we only want the header to be implemented once 
//if def -- in case it is not defined 
// define -- define so that it is included
// pragma once does the same but is less universially used.


// we need our class to be derived from TObject 
// Tobject is a part of the root framework and defines how root stores the data 
// We also have a root class and it allows for compatability with the c++ script
// In addition we use a object to call the function in root to define and show the vector 
// we do that with e.g. obj2.SetVelocity(6.0, 8.0, 10.0);

#include <TObject.h>

class MovingObject : public TObject {
public:
    MovingObject();
    MovingObject(Double_t vx, Double_t vy, Double_t vz);
    ~MovingObject() override;

    Double_t Vx() const;
    Double_t Vy() const;
    Double_t Vz() const;

    Double_t Speed() const;
    Double_t HorizontalSpeed() const;

    void SetVelocity(Double_t vx, Double_t vy, Double_t vz);

private:
    Double_t fVx;
    Double_t fVy;
    Double_t fVz;

    ClassDef(MovingObject, 1);
};

#endif


// The difference between class and struct is that for class, members are private by default 
// for struct, members are public by default 
// for structs are used for storing and organizing data while
// classes are used commonly for object-oriented programs
