//
//  hunt.cpp
//  p1
//
//  Created by zewei yu on 1/12/22.
//
//40FB54C86566B9DDEAB902CC80E8CE85C1C62AAD

#include <iostream>
#include <getopt.h>
#include <string>
#include <cstring>
#include <sstream>
#include <vector>
#include <deque>
//#include "xcode_redirect.hpp"
#include "map.hpp"

using namespace std;

struct Commands{
    string capOption="STACK";
    string firstOption="QUEUE";
    string huntOrder="NESW";
    string path;
    bool ifVerbose=false;
    bool ifStats=false;
};





// Prsize_t help for the user when requested.
// argv[0] is the name of the currently executing program
void printHelp() {
    cout << "Usage:\n";
    cout <<" [-c QUEUE|STACK]\n";
    cout <<" [-f QUEUE|STACK]\n";
    cout <<" [-o <ORDER>]\n";
    cout <<" [-v]\n";
    cout <<" [-s]\n";
    cout <<" [-p M|L]\n";
} // prsize_tHelp()

struct option longOpts[] = {
    {"captain", required_argument, nullptr, 'c'},
    {"first-mate", required_argument, nullptr, 'f'},
    {"hunt-order", required_argument, nullptr, 'o'},
    {"verbose", no_argument, nullptr, 'v'},
    {"stats", no_argument, nullptr, 's'},
    {"show-path", required_argument, nullptr, 'p'},
    {"help", no_argument, nullptr, 'h'},
    { nullptr, 0,                 nullptr, '\0' }
};

bool checkOrder(string order){
    if(order.length()!=4){return false;}
    vector<char> v;
    
    for(size_t i=0;i<4;++i){
        for(size_t j=0;j<v.size();++j){
            if(v[j]==order[i]){return false;}
        }
        v.push_back(order[i]);
    }
    return true;
}

// Finish this function, look for the individual TODO comments size_ternally.
// Process the command line; the only thing we need to return is the mode
// when the user specifies the -m/--mode option.
Commands getMode(int argc, char * argv[]) {
    Commands commands;
    // These are used with getopt_long()
    opterr = false; // Let us handle all error output for command line options
    int choice;
    int option_index = 0;
    string mode;
    //option long_options[] =longOpts;
    unsigned int pathNum=0;
    // TODO: Fill in the double quotes, to match the mode and help options.
    while ((choice = getopt_long(argc, argv, "c:f:o:vsp:h", longOpts, &option_index)) != -1) {
        switch (choice) {
            case 'h':
                printHelp();
                exit(0);
                
            case 'c':
               mode = optarg;
                if (mode != "STACK" && mode != "QUEUE") {
                    cerr << "Invalid argument to --captain\n";  // autograder displays
                    cerr << "  Invalid argument is: " << optarg << "\n";  // personal debug

                    exit(1);
                } // if
                commands.capOption=mode;
                break;
                
            case 'f':
                mode = optarg;
                if (mode != "STACK" && mode != "QUEUE") {
                    cerr << "Invalid argument to --first-mate\n";  // autograder displays
                        cerr << "  Invalid argument is: " << optarg << "\n";  // personal debug

                    exit(1);
                } // if
                commands.firstOption=mode;
                break;
                
            case 'v':
                commands.ifVerbose=true;
                break;
            case 'o':
                mode = optarg;
                if (!checkOrder(mode)) {
                    cerr << "Invalid argument to --hunt-order\n";  // autograder displays
                        cerr << "  Invalid argument is: " << optarg <<"\n";  // personal debug

                    exit(1);
                } // if
                commands.huntOrder=mode;
                break;
                
            case 's':
                commands.ifStats=true;
                break;
            case 'p':
                mode = optarg;
                if (mode != "M" && mode != "L"){
                    cerr << "Invalid argument to --show-path\n";  // autograder displays
                        cerr << "  Invalid argument is: " << optarg <<"\n";  // personal debug

                    exit(1);} // if
                if (pathNum>=1){
                    cout<<"Specify --show-path only once\n";
                    exit(1);
                }
                commands.path=mode;
                ++pathNum;
                break;
            default:
                cout<<"Unknown option";
                exit(1);
             // switch
        }
    }
    return commands;
} // getMode()



int main(int argc, char* argv[]){
    ios_base::sync_with_stdio(false);
    //xcode_redirect(argc, argv);
    Commands commands=getMode(argc, argv);
    string line;
    //avoid reading in comments
    while(cin.peek()=='#'){getline(cin,line);}
    
    char inputModel;
    string order=commands.huntOrder;
    
    cin>>inputModel;
    uint32_t length;
    
    cin>>length;
    getline(cin,line);
    
    Map map;
    map.createVector(length);
    map.setOrder(order);
    if (inputModel=='M'){
        map.readMap();}
    else{map.readList();}
    
    string capOption=commands.capOption;
    string firstOption=commands.firstOption;
    map.hunt(capOption,firstOption);
    
    if(commands.ifVerbose==true){map.printVerbose();}
    bool ifFound=map.getifFound();
    if(ifFound){map.getPath();}
    if(commands.ifStats==true){map.printStats();}
    if(ifFound&&commands.path=="M"){map.printMap();}
    if(ifFound&&commands.path=="L"){map.printList();}
    map.printOutput();
    
    return 0;
}
            
            

            

        
        
           
            
            
        
        
        
        
        
    
        
        
    

    
    
    
    

    
    
    
    
    
    
    


