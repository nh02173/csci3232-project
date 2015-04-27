#include<cmath>
#include<iostream>
#include<list>
#include<random>
#include<string>
#include<vector>

using namespace std;
using std::string;
using std::vector;

const int MIN_TRACKS = 8, MAX_TRACKS = 256, NUM_ALGOS = 5;

int main(){
    // Define disk parameters
    int trackSelect = 0, dirSelect = 0, startPos = 0, algo = 0;
    string inputString;
    
    cout << "Define the number of tracks for the simulation [" << MIN_TRACKS << "-" << MAX_TRACKS << "]:" << endl;
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
    
    cout << "Select a starting direction of movement: " << endl;
    cout << "1.Ascending 2.Descending" << endl;
    cin.ignore();
    cin >> dirSelect;
    if(dirSelect < 1 || dirSelect > 2){
        cerr << "Movement selection outside the specified range!" << endl;
        return -1;
    }

    // Collecting input data
    cout << "Enter a word or phrase to store on the virtual Hard Disk:" << endl;
    cin.ignore();
    getline(cin,inputString);
    if(inputString.empty()){
        cerr << "An input string was not specified!" << endl;
        return -1;
    }

    // Select a disk algorithm
    cout << "Select a scheduling algorithm: " << endl;
    cout << "1.FCFS  2.SSTF  3.SCAN  4.C-SCAN  5.C-LOOK" << endl;
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
    uniform_int_distribution<int> distT(1, trackSelect);

    // Using the Mersenne Twister for randomization
    mt19937 generator;
    generator.seed(time(NULL));
    
    unsigned int i,j;
    int genT;
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
                cout << inputString[i] << "->" << genT << endl;
            }
        }
    }
    
    cout << "\nReading data from disk starting at track " << startPos << "\n" << endl;
    
    // Simulate a retrieval of the data using the defined algorithm
    int seekTime = 0, moveCount = 0, foundPos = 0, foundLoc = 0;
    bool look = false;
    
    switch(algo){
        case 1: // FCFS
            for(i = 0; i < inputString.length(); i++){
                cout << "Moving from position " << startPos << " to " << lookupTable[i] << " to retrieve value " << vhd[lookupTable[i]] << endl;
                seekTime += abs(startPos - lookupTable[i]);
                startPos = lookupTable[i];
            }
            break;
        case 2: // SSTF
            for(i = 0; i < inputString.length(); i++){
                moveCount = MAX_TRACKS;
                for(j = 0; j < inputString.length(); j++){
                    if(lookupTable[j] != 0){
                        if(abs(startPos - lookupTable[j]) < moveCount){
                          moveCount = abs(startPos - lookupTable[j]);
                          foundPos = lookupTable[j];
                          foundLoc = j;
                        } 
                    }
                }
                cout << "Moving from position " << startPos << " to " << lookupTable[foundLoc] << " to retrieve value " << vhd[lookupTable[foundLoc]] << endl;
                lookupTable[foundLoc] = 0;
                seekTime += moveCount;
                startPos = foundPos;
            }
            break;
        case 3: // SCAN
            foundPos = startPos;
            for(i = 0; i < inputString.length(); i++){
                if(dirSelect == 1){
                    if((foundPos + 1) > trackSelect){
                        dirSelect = 2;
                        foundPos -= 1;
                    } else {
                        foundPos += 1;
                    }
                } else {
                    if((foundPos - 1) < 1){
                        dirSelect = 1;
                        foundPos += 1;
                    } else {
                        foundPos-=1;
                    }
                }
                for(j = 0; j < inputString.length(); j++){
                    if(lookupTable[j] != 0){
                        if(lookupTable[j] == foundPos){
                            moveCount = abs(startPos - lookupTable[j]);
                            foundLoc = j;
                        }
                    }
                }
                cout << "Moving from position " << startPos << " to " << lookupTable[foundLoc] << " to retrieve value " << vhd[lookupTable[foundLoc]] << endl;
                lookupTable[foundLoc] = 0;
                seekTime += moveCount;
                startPos = foundPos;
            }
            break;
        case 4: // C-SCAN
            foundPos = startPos;
            for(i = 0; i < inputString.length(); i++){
                if(dirSelect == 1){
                    if((foundPos + 1) > trackSelect){
                        foundPos = 1;
                        startPos = 1;
                    } else {
                        foundPos += 1;
                    }
                } else {
                    if((foundPos - 1) < 1){
                        foundPos = trackSelect;
                        startPos = trackSelect;
                    } else {
                        foundPos-=1;
                    }
                }
                for(j = 0; j < inputString.length(); j++){
                    if(lookupTable[j] != 0){
                        if(lookupTable[j] == foundPos){
                            moveCount = abs(startPos - lookupTable[j]);
                            foundLoc = j;
                        }
                    }
                }
                cout << "Moving from position " << startPos << " to " << lookupTable[foundLoc] << " to retrieve value " << vhd[lookupTable[foundLoc]] << endl;
                lookupTable[foundLoc] = 0;
                seekTime += moveCount;
                startPos = foundPos;
            }
            break;
        case 5: // C-LOOK
            foundPos = startPos;
            for(i = 0; i < inputString.length(); i++){
                if(dirSelect == 1){
                    if((foundPos + 1) > trackSelect){
                        foundPos = 1;
                        look = true;
                    } else {
                        foundPos += 1;
                    }
                } else {
                    if((foundPos - 1) < 1){
                        foundPos = trackSelect;
                        look = true;
                    } else {
                        foundPos-=1;
                    }
                }
                for(j = 0; j < inputString.length(); j++){
                    if(lookupTable[j] != 0){
                        if(lookupTable[j] == foundPos){
                            if(look){
                                moveCount = 0;
                                look = false;
                            } else {
                                moveCount = abs(startPos - lookupTable[j]);
                            }
                            foundLoc = j;
                        }
                    }
                }
                cout << "Moving from position " << startPos << " to " << lookupTable[foundLoc] << " to retrieve value " << vhd[lookupTable[foundLoc]] << endl;
                lookupTable[foundLoc] = 0;
                seekTime += moveCount;
                startPos = foundPos;
            }
            break;
        default:
            cout << "Bad input" << endl;
            break;
    }
    
    // Report results
    cout << "\nMoved a total of " << seekTime << " positions with the given algorithm " << endl;
    
    return 0;
}