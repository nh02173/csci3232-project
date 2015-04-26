#include<iostream>
#include<random>
#include<string>
#include<vector>

using namespace std;
using std::string;
using std::vector;

// VHD Coordinates
struct vhdCoords {
  int posP, posT, posS;
  vhdCoords(int p, int t, int s) : posP(p), posT(t), posS(s) {}
};

// Virtual Hard Disk
class Vhd {
public:
    // Fully construct the object
    Vhd(const int &p, const int &t, const int &s, string i){
        // Check against minimums for assignment
        (p > platters) ? platters = p : true;
        (t > tracks) ? tracks = t : true;
        (s > sectors) ? sectors = s : true;
        (i.empty()) ? data = setData("The five boxing wizards jump quickly") : data = setData(i);
        
        // Instantiate dynamic collections
        vDisk = new int[p][t][s];
        lookupTable = vhdCoords[data.size()];
        
    }
    
    // Randomly writes each character to the data structure
    void writeDisk(){
        if(hasData){
            // Create distributions for each level of the structure 
            uniform_int_distribution<int> distP(1,platters);
            uniform_int_distribution<int> distT(1,tracks);
            uniform_int_distribution<int> distS(1,sectors);
            
            // Using the Mersenne Twister
            mt19937 generator;
            generator.seed(time(NULL));
            
            int i, genP, genT, genS;
            char checkVal;
            bool search false;
            
            // Populate the instance according to data
            for(i = 0; i < data.size(); i++){
                search = true;
                // Loop while spot is occupied
                while(search){
                    genP = distP(generator);
                    genT = distT(generator);
                    genS = distS(generator);
                    char checkVal = vDisk[genP][genT][genS]
                    if(!checkVal){
                        search = false;
                        vDisk[genP][genT][genS] = data[i];
                        lookupTable[i] = vhdCoords(genP, genT, genS);
                    }
                }
            }
            
            // Data available
            hasWrite = true;
        } else {
            cerr << "No data was supplied for the write task..." << endl;
        }
    }
    
    // Reads each character off of disk utilizing each algorithm
    void readDisk(int algo){
        if(hasWrite){
            // Select case to algo
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
        } else {
            cerr << "A write did not occur. Cannot read from disk..." << endl;
        }
    }
    
    // Print results
    void showStats(){
        // Print stats
        cout << "Print" << endl;
    }

private:
    // Initialized with minimums
    int platters = 1, tracks = 8, sectors = 16;
    // Prevents a read before data has been written to the structure
    bool hasData = false, hasWrite = false;
    // Dynamically initialized according to parameters
    vhdCoords* lookupTable = NULL;
    int* vDisk = NULL;
    // Holds the converted input data
    vector<char> data;
    
    // Statistical info?
    
    // Converts the string input in to a vector of characters
    vector<char> setData(string subject){
        vector<char> result (subject.begin(), subject.end());
        // Data available
        hasData = true;
        return result;
    }
};
