//
//  map.cpp
//  p1
//
//  Created by zewei yu on 1/16/22.
//
//40FB54C86566B9DDEAB902CC80E8CE85C1C62AAD
#include "map.hpp"
bool Map::getifFound(){return ifFound;}
void Map::setOrder(string& huntOrder){order=huntOrder;}
void Map::readMap(){
    string line;
    for(uint32_t i=0;i<mapLength;++i){
        getline(cin,line);
        for(uint32_t j=0;j<mapLength;++j){
            if(line[j]=='@'){
                startRow=i;
                startCol=j;}
            map[i][j]=Spot{line[j]};
        }
    }
}

void Map::createVector(uint32_t size){
    map.resize(size);
    for(uint32_t i=0;i<map.size();++i){
        map[i].resize(size);}
    mapLength=size;
}
    
void Map::readList(){
    uint32_t row;
    uint32_t col;
    char character;

    while(cin>>row>>col>>character){
        if(character!='.'){
            if (character=='@'){
                startRow=row;
                startCol=col;}
            map[row][col].terrian=character;}
    }
}

bool Map::validSpot(const Coordinate&pair){
    uint32_t i=0;
    return (i<=pair.row&&pair.row<mapLength)&&(i<=pair.col&&pair.col<mapLength)&&
            map[pair.row][pair.col].last==0&&map[pair.row][pair.col].terrian!='#';
}

bool Map::validSpot2(const Coordinate&pair){
    uint32_t i=0;
    return (i<=pair.row&&pair.row<mapLength)&&(i<=pair.col&&pair.col<mapLength)&&
            map[pair.row][pair.col].last==0&&(map[pair.row][pair.col].terrian=='$'||map[pair.row][pair.col].terrian=='o');
}

void Map::assignLast(const Coordinate& current,const Coordinate& around){
    if(around.row==current.row){
        if(around.col==current.col-1){
            map[around.row][around.col].last='E';
        }
        else{
            map[around.row][around.col].last='W';
        }
    }
    else{
        if(around.row==current.row-1){
            map[around.row][around.col].last='S';
        }
        else{
            map[around.row][around.col].last='N';
        }
    }
}

void Map::hunt(const string& capOption,const string& firOption){
    deque<Coordinate> cap;
    deque<Coordinate> fir;
    Coordinate currentSail;
    Coordinate currentSearch;
    cap.push_back({startRow,startCol});
    map[startRow][startCol].last='Y';
    while(!cap.empty()&&!ifFound){
        if(capOption=="STACK"){
            currentSail=cap.back();
            cap.pop_back();
        }
        else{
            currentSail=cap.front();
            cap.pop_front();
        }
        ++waterNum;
        for(uint32_t i=0;i<4;++i){
            if(ifFound){break;}
            Coordinate coordinate=currentSail;
            switch (order[i]){
                case 'S':
                    if(validSpot({(currentSail.row+1),currentSail.col})){
                        coordinate.row=currentSail.row+1;
                        coordinate.col=currentSail.col;
                        break;}
                    break;
            
                case 'N':
                    if(validSpot({(currentSail.row-1),currentSail.col})){
                        coordinate.row=currentSail.row-1;
                        coordinate.col=currentSail.col;
                        break;}
                    break;
            
                case 'W':
                    if(validSpot({currentSail.row,(currentSail.col-1)})){
                        coordinate.row=currentSail.row;
                        coordinate.col=currentSail.col-1;
                        break;}
                    break;
            
                case 'E':
                    if(validSpot({currentSail.row,(currentSail.col+1)})){
                        coordinate.row=currentSail.row;
                        coordinate.col=currentSail.col+1;
                        break;}
                    break;
            }
            if (coordinate.col!=currentSail.col||coordinate.row!=currentSail.row){
                if(map[coordinate.row][coordinate.col].terrian=='$'){
                    assignLast(currentSail, coordinate);
                    ifFound=true;
                    treasureRow=coordinate.row;
                    treasureCol=coordinate.col;
                    ++landNum;
                    ashores.push_back(coordinate);}
                
                else if(map[coordinate.row][coordinate.col].terrian=='.'){
                    assignLast(currentSail, coordinate);
                    cap.push_back(coordinate);}
                else{
                    assignLast(currentSail, coordinate);
                    fir.push_back(coordinate);
                    ashores.push_back(coordinate);
                    //firstMate search
                    while(!fir.empty()&&!ifFound){
                        if(firOption=="STACK"){
                            currentSearch=fir.back();
                            fir.pop_back();}
                        else{
                            currentSearch=fir.front();
                            fir.pop_front();}
                        ++landNum;
                        for(uint32_t i=0;i<4;++i){
                            if(ifFound){break;}
                            Coordinate coordinate=currentSearch;
                            switch (order[i]){
                                case 'S':
                                    if(validSpot2({(currentSearch.row+1),currentSearch.col})){
                                        coordinate.row=currentSearch.row+1;
                                        coordinate.col=currentSearch.col;
                                        break;}
                                    break;
                            
                                case 'N':
                                    if(validSpot2({(currentSearch.row-1),currentSearch.col})){
                                        coordinate.row=currentSearch.row-1;
                                        coordinate.col=currentSearch.col;
                                        break;}
                                    break;
                            
                                case 'W':
                                    if(validSpot2({currentSearch.row,(currentSearch.col-1)})){
                                        coordinate.row=currentSearch.row;
                                        coordinate.col=currentSearch.col-1;
                                        break;}
                                    break;
                            
                                case 'E':
                                    if(validSpot2({currentSearch.row,(currentSearch.col+1)})){
                                        coordinate.row=currentSearch.row;
                                        coordinate.col=currentSearch.col+1;
                                        break;}
                                    break;
                            }
                            if (coordinate.col!=currentSearch.col||coordinate.row!=currentSearch.row){
                                if(map[coordinate.row][coordinate.col].terrian=='$'){
                                    assignLast(currentSearch, coordinate);
                                    ifFound=true;
                                    treasureRow=coordinate.row;
                                    treasureCol=coordinate.col;
                                    ++landNum;
                                    break;}
                                else{
                                    assignLast(currentSearch, coordinate);
                                    fir.push_back(coordinate);}
                            }
                        }
                    }
                }
            }
        }
    }
}


void Map::getPath(){
    path.push_back(map[treasureRow][treasureCol].last);
    uint32_t row=treasureRow;
    uint32_t col=treasureCol;
    size_t i=0;
    bool ifBack=false;
    while(!ifBack){
        switch (path[i]){
            case 'Y':
                path.pop_back();
                ifBack=true;
                break;
            case 'N':
                path.push_back(map[row-1][col].last);
                --row;
                ++i;
                break;
            case 'S':
                path.push_back(map[row+1][col].last);
                ++row;
                ++i;
                break;
            case 'E':
                path.push_back(map[row][col+1].last);
                ++col;
                ++i;
                break;
            case 'W':
                path.push_back(map[row][col-1].last);
                --col;
                ++i;
                break;
        }
    }
    pathLength=uint32_t(path.size());
}
void Map::printVerbose(){
    cout<<"Treasure hunt started at: "<<startRow<<","<<startCol<<"\n";
    uint32_t size=uint32_t(ashores.size());

    for(uint32_t i=0;i<size;++i){
        if(ifFound&&(ashores[i].row==treasureRow&&ashores[i].col==treasureCol)){
            cout<<"Went ashore at: "<<treasureRow<<","<<treasureCol<<"\n";
            cout<<"Searching island... party found treasure at "<<treasureRow<<","<<treasureCol<<".\n";
        }
        else{
            if(ifFound&&i==size-1){
                cout<<"Went ashore at: "<<ashores[i].row<<","<<ashores[i].col<<"\n";
                cout<<"Searching island... party found treasure at "<<treasureRow<<","<<treasureCol<<".\n";
            }
            else{
                cout<<"Went ashore at: "<<ashores[i].row<<","<<ashores[i].col<<"\n";
                cout<<"Searching island... party returned with no treasure.\n";
            }
        }
    }
    if(!ifFound){
        cout<<"Treasure hunt failed\n";
    }
}

void Map::printStats(){
    cout<<"--- STATS ---\n";
    cout<<"Starting location: "<<startRow<<","<<startCol<<"\n";
    cout<<"Water locations investigated: "<<waterNum<<"\n";
    cout<<"Land locations investigated: "<<landNum<<"\n";
    cout<<"Went ashore: "<<ashores.size()<<"\n";
    if(ifFound){
        cout<<"Path length: "<<pathLength<<"\n";
        cout<<"Treasure location: "<<treasureRow<<","<<treasureCol<<"\n";}
    cout<<"--- STATS ---\n";
}

void Map::printMap(){
    map[treasureRow][treasureCol].terrian='X';
    uint32_t row=treasureRow;
    uint32_t col=treasureCol;
    for(uint32_t i=0;i<pathLength-1;++i){
        char current=path.front();
        path.pop_front();
        char next=path.front();
        //Coordinate nextNext=path[i+2];
        if(current=='N'&&current==next){
            map[row-1][col].terrian='|';
            --row;
        }
        else if(current=='S'&&current==next){
            map[row+1][col].terrian='|';
            ++row;
        }
        else if(current=='E'&&current==next){
            map[row][col+1].terrian='-';
            ++col;
        }
        else if(current=='W'&&current==next){
            map[row][col-1].terrian='-';
            --col;
        }
        else{
            if(current=='N'){
                map[row-1][col].terrian='+';
                --row;}
            else if(current=='S'){
                map[row+1][col].terrian='+';
                ++row;}
            else if(current=='E'){
                map[row][col+1].terrian='+';
                ++col;}
            else{
                map[row][col-1].terrian='+';
                --col;}
        }
    }
    for(uint32_t i=0;i<map.size();++i){
        for(uint32_t j=0;j<map.size();++j){
            cout<<map[i][j].terrian;}
        cout<<"\n";}
}

void Map::printList(){
    if(!ifFound){return;}
    cout<<"Sail:\n";
    bool ifSearch=false;
    cout<<startRow<<","<<startCol<<"\n";
    uint32_t row=startRow;
    uint32_t col=startCol;

    for(uint32_t i=0;i<pathLength;++i){
        if(path.back()=='E'){--col;}
        else if(path.back()=='W'){++col;}
        else if(path.back()=='N'){++row;}
        else{--row;}
        
        if((map[row][col].terrian=='o'||map[row][col].terrian=='$')&&!ifSearch){
            cout<<"Search:\n";
            ifSearch=true;}
        cout<<row<<","<<col<<"\n";
        path.pop_back();
    }
    
}

void Map::printOutput(){
    if(ifFound){
        cout<<"Treasure found at "<<treasureRow<<","<<treasureCol<<" with path length "<<pathLength<<".\n";}
    else{
        cout<<"No treasure found after investigating "<<landNum+waterNum<<" locations.\n";}
}

Map::~Map(){}

