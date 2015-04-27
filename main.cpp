#include<cmath> 
#include<iostream>
#include<random>
#include<string>
#include<vector>

using namespace std;
using std::string;
using std::vector;

const int MIN_TRACKS = 8, MAX_TRACKS = 256;
const int NUM_ALGOS = 6;

int main(){
    // Define disk parameters
    int trackSelect = 0, startPos = 0, algo = 0;
    string inputString;
    
    cout << "Define the number of tracks per platter [" << MIN_TRACKS << "-" << MAX_TRACKS << "]:" << endl;
    cin >> trackSelect;
    if(trackSelect > MAX_TRACKS || trackSelect < MIN_TRACKS){
        cerr << "Tracks was not in the specified range!" << endl;
        return -1;
    }
    
    cout << "Select a starting track within a range of 0-" << trackSelect << endl;
    cin >> startPos;
    if(startPos < 0 || startPos > trackSelect){
        cerr << "Track selection outside of the specified range!" << endl;
        return -1;
    }

    // Collecting input data
    cout << "Enter a word or phrase to store on the virtual HDD:" << endl;
    cin.ignore();
    getline(cin,inputString);
    if(inputString.empty()){
        cerr << "An input string was not specified!" << endl;
        return -1;
    }

    // Select a disk algorithm
    cout << "Select a scheduling algorithm: " << endl;
    cout << "1.FCFS  2.SSTF  3.SCAN  4.C-SCAN  5.LOOK  6.C-LOOK" << endl;
    cin >> algo;
    if(algo < 0 || algo > NUM_ALGOS){
        cerr << "Algorithm selection outside the specified range!" << endl;
        return -1;
    }

    // Use values to initialize the simulation
    cout << "\nRandomly initializing the disk...\n" << endl;
    
    // Setup a lookup table that is the size of the data
    int lookupTable[inputString.length()];
    
    // Setup data structure to simulate virtual hard disk
    vector<char> vhd(trackSelect, 0);
    
    // Create distribution
    uniform_int_distribution<int> distT(0, trackSelect);

    // Using the Mersenne Twister for randomization
    mt19937 generator;
    generator.seed(time(NULL));
    
    int i, genT;
    bool search = false;
    
    // Populate the VHD according to data
    for(i = 0; i < inputString.length(); i++){
        search = true;
        // Loop while spot is occupied
        while(search){
            // Generate positions
            genT = distT(generator);
            // Check the position
            if(vhd[genT] == 0){
                search = false;
                // Write the position
                vhd[genT] = inputString[i];
                lookupTable[i] = genT;
            }
        }
    }
    
    cout << "Reading data from disk starting at track " << startPos << "\n" << endl;
    
    // Simulate a retrieval of the data using the defined algorithm
    int moveCount = 0;
    
    switch(algo){
        case 1: // FCFS
            for(i = 0; i < inputString.length(); i++){
                cout << "Moving from position " << startPos << " to " << lookupTable[i] << " to retrieve value " << vhd[lookupTable[i]] << endl;
                moveCount += abs(startPos - lookupTable[i]);
                startPos = lookupTable[i];
            }
            break;
        case 2: // SSTF
            break;
        case 3: // SCAN
            break;
        case 4: // C-SCAN
            break;
        case 5: // LOOK
            break;
        case 6: // C-LOOK
            break;
        default:
            cout << "Bad input" << endl;
            break;
    }
    
    // Report results
    cout << "\nMoved a total of " << moveCount << " positions with the given algorithm " << endl;
    
    return 0;
}