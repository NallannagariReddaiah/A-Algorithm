#include<iostream>
#include<bits/stdc++.h>
using namespace std;
//This snippet of code works when there is a grid with obstackels
//1 represents the node is free and 0 represents the node is with the obstacle
//The distance g in this method is 1 same for moving from one cell to other cells
//Each cell is represented by row and column indices 
//There are eight possible directions in the grid where each node may have an adjacent free node
//This algorithm will be useful for games like snake game
typedef pair<int,int>Pair;
typedef pair<double,pair<int, int>>Node;
typedef  struct{
    int row,col,parent_row,parent_col,cell_type;
    double f,g,h;
}cell;
class Astar{
    public:
    int row_size,col_size;
    cell *Grid;
    Pair Src,Dest;
    Astar(int m,int n,cell *grid,Pair src,Pair dest){
        this->row_size=m;
        this->col_size=n;
        this->Grid=grid;
        this->Src=src;
        this->Dest=dest;
    }
    void setInput(){
        int type;
        for(int i=0;i<this->row_size;i++){
            for(int j=0;j<this->col_size;j++){
                this->Grid[this->col_size*i+j].f=FLT_MAX;
                this->Grid[this->col_size*i+j].g=FLT_MAX;
                this->Grid[this->col_size*i+j].h=FLT_MAX;
                this->Grid[this->col_size*i+j].parent_row=-1;
                this->Grid[this->col_size*i+j].parent_col=-1;
                cout<<endl;
            }
        }
    }
    bool isValidCell(int row,int col){
        if(((row>=0)&&(row<this->row_size))&&((col>=0)&&(col<this->col_size))){
            return true;
        }
        else
        {
            return false;
        }
    }
    bool isUnBlocked(int row,int col){
        if(this->Grid[row*this->col_size+col].cell_type==1){
            return true;
        }
        else{
            return false;
        }
    }
    double calculateHValue(int row,int col){
        return ((double)sqrt(
        (row - this->Dest.first) * (row - this->Dest.first)
        + (col - this->Dest.second) * (col - this->Dest.second)));
    }
    bool isDestination(int row,int col){
        if(this->Dest.first==row && this->Dest.second==col){
            return true;
        }
        else
        {
            return false;
        }
    }
    void tracePath(){
        cout<<"The path is:";
        int row=this->Dest.first;
        int col=this->Dest.second;
        int temp_row,temp_col;
        stack<Pair> Path;
        while(!((this->Grid[row*this->col_size+col].parent_row==row)&&(this->Grid[row*this->col_size+col].parent_col==col))){
            Path.push(make_pair(row,col));
            temp_row=this->Grid[row*this->col_size+col].parent_row;
            temp_col=this->Grid[row*this->col_size+col].parent_col;
            row=temp_row;
            col=temp_col;
        }
        Path.push(make_pair(row,col));
        Pair temp;
        while(!Path.empty()){
            temp=Path.top();
            Path.pop();
            cout<<"Grid["<<temp.first<<"]["<<temp.second<<"]->";
        }
    }
    void Algorithm(){
        if(!isValidCell(this->Src.first,this->Src.second)){
            cout<<"Source is Invalid";
            return;
        }
        if(!isValidCell(this->Dest.first,this->Dest.second)){
            cout<<"Destination is Invalid";
            return;
        }
        if(!isUnBlocked(this->Src.first,this->Src.second)){
            cout<<"Source is Blocked";
            return;
        }
        if(!isUnBlocked(this->Dest.first,this->Dest.second)){
            cout<<"Destination is Blocked";
            return;
        }
        if(isDestination(this->Src.first,this->Src.second)){
            cout<<"Already reached the destination";
            return;
        }
        //Defining a closed list for Noting the cells which are visited
        bool closedList[this->row_size][this->col_size];
        memset(closedList, false, sizeof(closedList));
        this->Grid[this->col_size*this->Src.first+this->Src.second].f=0;
        this->Grid[this->col_size*this->Src.first+this->Src.second].g=0;
        this->Grid[this->col_size*this->Src.first+this->Src.second].h=0;
        this->Grid[this->col_size*this->Src.first+this->Src.second].parent_row=this->Src.first;
        this->Grid[this->col_size*this->Src.first+this->Src.second].parent_col=this->Src.second;
        //definig  a open list for storing the nodes which are needed to be traversed
        set<Node> open_list;
        open_list.insert(make_pair(0.0,make_pair(this->Src.first,this->Src.second)));
        bool destFound=false;
        int i,j,row,col;
        double gNew,fNew,hNew;
        Pair RowCol[]={make_pair(0,1),make_pair(0,-1),make_pair(1,0),make_pair(-1,0),make_pair(1,1),make_pair(1,-1),make_pair(-1,1),make_pair(-1,-1)};
        int Nrow,Ncol;
        while(!open_list.empty()){
            Node p=*open_list.begin();
            open_list.erase(open_list.begin());
            row=p.second.first;
            col=p.second.second;
            closedList[row][col]=true;
            for(i=0;i<8;i++){
                    if(isValidCell(row+RowCol[i].first,col+RowCol[i].second)){
                        Nrow=row+RowCol[i].first;
                        Ncol=col+RowCol[i].second;
                        if(isDestination(Nrow,Ncol)){
                            this->Grid[Nrow*this->col_size+Ncol].parent_row=row;
                            this->Grid[Nrow*this->col_size+Ncol].parent_col=col;
                            cout<<"The destination is found"<<endl;
                            destFound=true;
                            this->tracePath();
                            return;
                        }
                        else if((!closedList[Nrow][Ncol])&&(isUnBlocked(Nrow,Ncol))){
                            gNew=this->Grid[row*this->col_size+col].g+1;
                            hNew=this->calculateHValue(Nrow,Ncol);
                            fNew=gNew+hNew;
                            if(this->Grid[Nrow*this->col_size+Ncol].f==FLT_MAX||this->Grid[Nrow*this->col_size+Ncol].f>fNew){
                                open_list.insert(make_pair(fNew,make_pair(Nrow,Ncol)));
                                this->Grid[Nrow*this->col_size+Ncol].g=gNew;
                                this->Grid[Nrow*this->col_size+Ncol].h=hNew;
                                this->Grid[Nrow*this->col_size+Ncol].f=fNew;
                                this->Grid[Nrow*this->col_size+Ncol].parent_row=row;
                                this->Grid[Nrow*this->col_size+Ncol].parent_col=col;
                            }
                        }
                    }
                }
            }
        }
};
int main(){
    int ROW,COL,p,i,j,ritr=0,citr,src_row,src_col,dest_row,dest_col;
    FILE *fp;
    char file_name[30];
    cout<<"Enter the txt file name:";
    cin>>file_name;
    fp=fopen(file_name,"r");
    ROW=9;
    COL=10;
    int input_pos=0;
    char myString[100];
    char num[10];
     cell *grid;
  while(fgets(myString, 100,fp)) {
      if(input_pos==0){
          p=0;
          for(i=0;i<myString[i]!='\0';i++){
              if(myString[i]==','){
                  num[p]='\0';
                  ROW=atoi(num);
                  p=0;
              }
              else
              {
                  num[p++]=myString[i];
              }
          }
          COL=atoi(num);
          grid=(cell *)malloc(ROW*COL*sizeof(cell));
          input_pos+=1;
      }
      else if(input_pos==1){
          citr=0;
          for(i=0;i<myString[i]!='\0';i++){
              if(myString[i]=='0'){
                  grid[ritr*COL+citr].cell_type=0;
                  citr+=1;
              }
              else if(myString[i]=='1'){
                  grid[ritr*COL+citr].cell_type=1;
                   citr+=1;
              }
          }
          ritr+=1;
          if(ritr>=ROW){
              input_pos+=1;
          }
      }
       else if(input_pos==2){
          p=0;
          for(i=0;i<myString[i]!='\0';i++){
              if(myString[i]==','){
                  num[p]='\0';
                  src_row=atoi(num);
                  p=0;
              }
              else
              {
                  num[p++]=myString[i];
              }
          }
          src_col=atoi(num);
          input_pos+=1;
      }
       else if(input_pos==3){
          p=0;
          for(i=0;i<myString[i]!='\0';i++){
              if(myString[i]==','){
                  num[p]='\0';
                  dest_row=atoi(num);
                  p=0;
              }
              else
              {
                  num[p++]=myString[i];
              }
          }
          dest_col=atoi(num);
          input_pos+=1;
      }
  }
  Pair src={src_row,src_col};
  Pair dest={dest_row,dest_col};
  Astar Algo(ROW,COL,grid,src,dest);
  Algo.setInput();
  Algo.Algorithm();
}
