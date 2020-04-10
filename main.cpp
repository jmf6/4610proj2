#include <iostream>
#include <vector>

using namespace std;

int main(){
    int frames = 0;
    int prev = -1;
    int faults = 0;
    int counter = 0;
    bool match = false;
    vector<int> sequence = {700, 701, 702, 651, 652, 831, 832, 833, 285, 286, 653, 654, 325, 655, 457, 458, 287, 288, 289, 290, 326, 327, 328, 656, 670, 671, 329, 330, 291, 292, 834, 835, 836, 293, 294, 295, 672, 673, 674, 837, 838, 839, 703, 704, 705, 675, 676, 677, 678, 840};
    vector<int> reference;

    for(int i = 0; i < sequence.size(); i++){
        frames = sequence.at(i)/100;
        if(frames != prev){
            reference.push_back(frames);
        }
        prev = frames;
    }

    cout << "Please enter the number of frames allocated to the processes: ";
    cin >> frames;

    while(frames <= 0){
        cout << "Invalid input, please enter a number larger than 0" << endl;
        cin >> frames;
    }

    int allocated[frames];
    int count[frames];

    for(int i = 0; i < frames; i++){
        allocated[i] = -1;
        count[i] = -1;
    }

    cout << "The reference string is: ";
    for(int i = 0; i < reference.size(); i++){
        cout << reference.at(i) << " ";
    }
    cout << endl;

    cout << "Now running the FIFO Page Replacement Algorithm..." << endl;
    cout << "Below are the page allocations to the frames." << endl;
    cout << "------------------------------" << endl;

    for(int i = 0; i < reference.size(); i++){
        for(int j = 0; j < frames; j++){
            if(reference.at(i) == allocated[j]){
                match = true;
                break;
            }
        }

        if(match == false){
            allocated[counter] = reference.at(i);
            for(int k = 0; k < frames; k++){
                if(allocated[k] != -1){
                    cout << allocated[k] << "\t";
                }
            }
            cout << endl;
            counter++;
            faults++;
        }

        if(counter >= frames){
            counter = 0;
        }

        match = false;
    }
    cout << "------------------------------" << endl;
    cout << "Total page faults: " << faults << endl << endl;

    faults = 0;
    for(int i = 0; i < frames; i++){
        allocated[i] = -1;
    }

    cout <<"Now running the LRU Page Replacement Algorithm..." << endl;
    cout << "Below are the page allocations to the frames." << endl;
    
    //doesn't work correctly 

    for(int i = 0; i < reference.size(); i++){
        cout << "now testing: " << reference.at(i) << endl;
        for(int j = 0; j < frames; j++){
            cout << "entered first loop, now testing if " << reference.at(i) << " is in the frame set" << endl;
            if(reference.at(i) == allocated[j]){
                cout << "found " << reference.at(i) << " in frame set at location " << j << endl;
                count[j] = 0;
                for(int k = 0; k < frames; k++){
                    if(count[k] != -1){
                        count[k]++;
                    }
                }
            break;
            }
            else if(allocated[j] == -1){
                allocated[j] = reference.at(i);
                count[j] = 0;
                faults++;
                cout << "entered " << reference.at(i) << " into slot " << j << endl;
                for(int k = 0; k < frames; k++){
                    if(allocated[k] != -1){
                        cout << allocated[k] << "\t";
                    }
                    if(count[k] != -1){
                        count[k]++;
                    }
                }
                break;
            }
            else{
                int LRU = 0;
                for(int k = 0; k < frames; k++){
                    if(count[k] > count[LRU]){
                        LRU = k;
                    }
                }
                allocated[LRU] = reference.at(i);
                faults++;
                count[LRU] = 0;

                cout << "replaced slot " << j << " with " << reference.at(i) << endl;
                for(int k = 0; k < frames; k++){
                    if(allocated[k] != -1){
                        cout << allocated[k] << "\t";
                    }
                    if(count[k] != -1){
                        count[k]++;
                    }
                }
                cout << endl;
            }
        }
    }
    cout << "-------------------------" << endl;
    cout << "Total page faults: " << faults << endl;
}
                                                          
