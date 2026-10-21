
#include "MovingObject.h"


#include <TRandom.h>
#include <iostream> 
#include <TFile.h>
#include <TTree.h>
#include <TF1.h> 
#include <cmath>

void read ()

{
    // Open the saved file in READ mode 
    // create pointer that refers to file and opens file in read only mode 
    TFile *file = TFile::Open("tree_file.root", "READ");

        //Check that it exists; if not exist then print message 
         if (!file) 
            {
                std::cerr << "Error message: could not open tree_file.root" << std::endl;
                return;
            }

    //create a pointer and find the tree and link pointer to tree 
    TTree *tree; 
    file->GetObject("tree", tree);
   

        if (!tree) 
            {
                std::cerr << "Error: Tree not found" << std::endl;
                file->Close();
                return;
            }

    // Look at tree and its branches
    tree->Print();

    //create a pointer 
    MovingObject *obj = nullptr;

    // put data from tree in branch
    //& allows for pointer setting and running at the same time 
    tree->SetBranchAddress("object", &obj);

    // Get the number of entries of tree  and print answer 
    Long64_t nEntries = tree->GetEntries();
    std::cout << "Number of entries: " << nEntries << std::endl;

    //////////////////////////////////////////////////////////////////////////////////
    //  NOW WE WILL MAKE THE HISTOGRAM vx - vy 

    // Create the 2D histogram: vy versus vx
    //100 bins 
    //range -1.5 until 1.5 
    TH2D *hist = new TH2D(
        "hist",
        "Velocity Components;v_{x} (m/s);v_{y} (m/s)",
        100, -1.5, 1.5,
        100, -1.5, 1.5
    );

    // Read each entry and fill the histogram
    //increases enrty by one 
    for (Long64_t i = 0; i < nEntries; i++)
    // if object pointer valid, use measurement
    {
        tree->GetEntry(i);
            if (obj)
            { hist->Fill(obj->Vx(), obj->Vy()); }
    }

    // Draw and save the histogram with 800 pixels width and 600 hight 
    TCanvas *c1 = new TCanvas(
        "c1", "Velocity Components", 800, 600
    );

    //use color scale and store canvas c1 
    hist->Draw("COLZ");
    c1->SaveAs("velocity_components.pdf");

    //////////////////////////////////////////////////
    //Scatter plot  VXY - VZ 

    //create new canvas with pointer and same amount of pixels 
    TCanvas *c2 = new TCanvas(
        "c2", "Selected Velocity Measurements", 800, 600
    );


    tree->Draw(
            //take vxy on x axis and vz on y axis 
        "sqrt(object.fVx*object.fVx + object.fVy*object.fVy):object.fVz",
            //requirement that total v is larger than 0.5 m/s 
        "sqrt(object.fVx*object.fVx + object.fVy*object.fVy + object.fVz*object.fVz) > 0.50"
    );

    //use internal root functionalities to make grapgh nicer 
    gPad->SetTitle("Horizontal Speed vs. Vertical Velocity");
    gPad->SetGrid();

    // root calls histogram htemp 
    // TH1 means that it is a base class histogram of root used for setting graphics like axes 
    //GetPrimitive() retrieves an object drawn in pad 
    TH1 *point = (TH1*)gPad->GetPrimitive("htemp");
    point->SetTitle("Horizontal Speed vs. Vertical Velocity;v_{z} (m/s);v_{xy} (m/s)");

    c2->SaveAs("velocity_scatter.pdf");

    // Clean up
    delete c2;
    delete c1;
    delete hist;

    //closes tree_file.root 
    //deletes TFile object after opening the root file 
    file->Close();
    delete file;
}

