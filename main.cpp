#include<iostream>
#include<random>
#include<string>
#include<vector>

using namespace std;
using std::string;
using std::vector;

const int MIN_PLATTERS = 1, MAX_PLATTERS = 3;
const int MIN_TRACKS = 8, MAX_TRACKS = 32;
const int MIN_SECTORS = 16, MAX_SECTORS = 64;
const int NUM_ALGOS = 6;

// Coordinates
struct Coords {
  int posP = 0, posT = 0, posS = 0;
};

int main(){
    // Define disk parameters
    int platterSelect = 0, trackSelect = 0, sectorSelect = 0;
    int platters = 0, tracks = 0, sectors = 0;
    int algo = 0;
    
    // Check all against maximums
    cout << "Define the number of platters [" << MIN_PLATTERS << "-" << MAX_PLATTERS << "]:" << endl;
    cin >> platterSelect;
    if(platterSelect < MAX_PLATTERS && platterSelect >= MIN_PLATTERS){
        platters = platterSelect;
    } else {
        cerr << "Platters was not in the specified range!" << endl;
        return -1;
    }
    
    cout << "Define the number of tracks per platter [" << MIN_TRACKS << "-" << MAX_TRACKS << "]:" << endl;
    cin >> trackSelect;
    if(trackSelect < MAX_TRACKS && trackSelect >= MIN_TRACKS){
        tracks = trackSelect;
    } else {
        cerr << "Tracks was not in the specified range!" << endl;
        return -1;
    }
    
    cout << "Define the number of sectors per track [" << MIN_SECTORS << "-" << MAX_SECTORS << "]:" << endl;
    cin >> sectorSelect;
    if(sectorSelect < MAX_SECTORS && sectorSelect <= MIN_SECTORS){
        sectors = sectorSelect;
    } else {
        cerr << "Sectors was not in the specified range!" << endl;
        return -1;
    }
    
    // Collecting input data
    string inputString;

    cout << "Enter a word or phrase to store on the virtual HDD:" << endl;
    cin.ignore();
    getline(cin,inputString);
    if(inputString.empty()){
        cerr << "An input string was not specified!" << endl;
        return -1;
    }

    // Select a disk algorithm
    int algoSelect = 0;
    
    cout << "Select a scheduling algorithm: " << endl;
    cout << "1.FCFS  2.SSTF  3.SCAN  4.C-SCAN  5.LOOK  6.C-LOOK" << endl;
    cin >> algoSelect;
    if(algoSelect > 0 && algoSelect <= NUM_ALGOS){
        algo = algoSelect;
    } else {
        cerr << "Invalid algorithm selection!" << endl;
        return -1;
    }

    // Use values to initialize the simulation
    cout << "\nInitializing the disk...\n" << endl;
    
    // Setup a lookup table that is the size of the data
    Coords lookupTable[inputString.length()];
    
    // Setup a data structure to simulate virtual hard disk
    char vhd[platters][tracks][sectors];
    
    // Create distributions for each level of the structure 
    uniform_int_distribution<int> distP(MIN_PLATTERS,platters);
    uniform_int_distribution<int> distT(MIN_TRACKS,tracks);
    uniform_int_distribution<int> distS(MIN_SECTORS,sectors);
    
    // Using the Mersenne Twister for randomization
    mt19937 generator;
    generator.seed(time(NULL));
    
    int i, genP, genT, genS;
    bool search = false;
    
    // Populate the VHD according to data
    for(i = 0; i < inputString.length(); i++){
        search = true;
        // Loop while spot is occupied
        while(search){
            // Generate positions
            genP = distP(generator);
            genT = distT(generator);
            genS = distS(generator);
            // Check the position
            char checkVal = vhd[genP][genT][genS];
            // Write the position
            if(!checkVal){
                search = false;
                vhd[genP][genT][genS] = inputString[i];
                lookupTable[i].posP = genP;
                lookupTable[i].posT = genT;
                lookupTable[i].posS = genS;
            }
        }
    }
    
    cout << "\nReading data from disk...\n" << endl;
    
    // Simulate a retrieval of the data using the defined algorithm
    switch(algo){
        case 1: // FCFS
            break;
        case 2: // SSTF
            break;
        case 3: // SCAN
            break;
        case 4: // C-SCAN
            break:
        case 5: // LOOK
            break;
        case 6: // C-LOOK
            break;
        default:
            cout << "Bad input" << endl;
            break;
    }
    
    // Report results

    return 0;
}