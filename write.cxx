
#include "MovingObject.h"


#include <TRandom.h>
#include <iostream> 
#include <TFile.h>
#include <TTree.h>
#include <TF1.h> 
#include <cmath>

void write(){

// Initialize your object e.g. as a pointer
MovingObject *obj = new MovingObject();

// Create your root file here
TFile *file = new TFile("tree_file.root", "RECREATE");

// Create your TTree here
 TTree *tree = new TTree("tree", "Velocity measurements");

    //define variables we will need later 
    Double_t speed;
    Double_t horizontalSpeed;


// And the associated branches underneath
    tree->Branch("object", "MovingObject", &obj);
    
    /*
    We can have more branches for eg. speed and horizontal speed 
    tree->Branch("Speed", &speed, "Speed/D");
    tree->Branch("HorizontalSpeed", &horizontalSpeed, "HorizontalSpeed/D");
    */ 


     // Generate measurements
    const Int_t nEvents = 1000;

    // Now we create our loop for filling the tree with some random data
    gRandom->SetSeed(12345);

    // how many events we want 
    for (Int_t i{0}; i < nEvents; i++)
    {
        // Generate random velocity components between -10 and 10
        Double_t vx = gRandom->Gaus(0, 0.30);
        Double_t vy = gRandom->Gaus(0, 0.30);
        Double_t vz = gRandom->Gaus(0, 0.30);

        // Set the velocity components in the object
        obj->SetVelocity(vx, vy, vz);

        // Total speed
        speed = obj->Speed();

        // Horizontal speed in x and y directions
        horizontalSpeed = obj->HorizontalSpeed();

        // put in tree 
        tree->Fill();
    }


     std::cout << "Number of entries: " << tree->GetEntries() << std::endl;

    std::cout << "Write has been run to completion! " << std::endl;

    // save the tree/file
    // cd is current root file 
    //save tree and store measurements 
    //closes file 
    file->cd();
    tree->Write();
    file->Close();


// Remember to delete it again otherwise you will have memory leak!

    // Clean up movingobject and Tfile 
    delete obj;
    delete file;

} 


