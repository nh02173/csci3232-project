#include<iostream>
#include<string>
#include"vhd.h"

using namespace std;
using std::string;

const int MAX_PLATTERS = 3;
const int MAX_TRACKS = 32;
const int MAX_SECTORS = 64;

int main(){
    // Define disk parameters
    int platterSelect = 0, trackSelect = 0, sectorSelect = 0;
    
    // Check all against maximums
    cout << "Define the number of platters [Max=" << MAX_PLATTERS << "]:" << endl;
    cin >> platterSelect;
    if(platterSelect > MAX_PLATTERS){
        platterSelect = MAX_PLATTERS;
    }
    cout << "Define the number of tracks per platter [Max=" << MAX_TRACKS << "]:" << endl;
    cin >> trackSelect;
    if(trackSelect > MAX_TRACKS){
        trackSelect = MAX_TRACKS;
    }
    cout << "Define the number of sectors per track [Max=" << MAX_SECTORS << "]:" << endl;
    cin >> sectorSelect;
    if(sectorSelect > MAX_SECTORS){
        sectorSelect = MAX_SECTORS;
    }
    
    // Collecting input data
    string inputString;

    cout << "Enter a word or phrase to store on the virtual HDD:" << endl;
    cin.ignore();
    getline(cin,inputString);

    // Select a disk algorithm
    int algoSelect = 0;
    
    cout << "Select a scheduling algorithm: " << endl;
    cout << "1.FCFS  2.SSTF  3.SCAN  4.C-SCAN  5.LOOK  6.C-LOOK" << endl;
    cin >> algoSelect;

    // Use values to initialize the simulation
    Vhd simulation = new Vhd(platterSelect, trackSelect, sectorSelect, inputString);
    
    cout << "\nInitializing the disk...\n" << endl;
    
    simulation.writeDisk();
    
    cout << "\nReading data from disk...\n" << endl;
    
    // Simulate a retrieval of the data using the defined algorithm
    simulation.readDisk(algoSelect);
    
    // Report results
    simulation.showStats();
    
    return 0;
}