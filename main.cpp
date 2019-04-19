#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#define FILE "D:\\C&C++\\HW4\\Blocks.txt"
#define SIZE 300

using namespace std;
struct Unicode{
    long start_value;
    long end_value;
    char name[100];
};
void loadFile(string file, Unicode data[]);
void findUncdName(Unicode data[],long given_value);


int main()
{
    Unicode data[SIZE];
    long given_value=0xE007F;


    loadFile(FILE, data);
    findUncdName(data, given_value);






    return 0;
}

void loadFile(string file, Unicode data[]) {
    ifstream in_file(file, ios::in );
    if(!in_file){
        cerr<<"File can not be opened"<<endl;
        exit(1);
    }

    string line;
    int ptr=0;
    while(getline(in_file,line)) {
        int brk_point=0;
        //去掉注释和空行
        if(line[0]=='#' || line.size()==0) {
            continue;
        }
        else {
            for(int i=0; i<line.length();i++) {
                //找到第一个'.'并存储'.'之前的值到start_value
                if(line[i]=='.' && brk_point==0){
                    brk_point=i+2;
                    sscanf(line.substr(0,i).c_str(),"%x", &data[ptr].start_value);
                }
                //找到end_value
                if(line[i]==';') {
                    //存end_value
                    sscanf(line.substr(brk_point,i-brk_point).c_str(), "%x", &data[ptr].end_value);

                    //存name
                    strcpy(data[ptr].name, line.substr(i+2,line.length()-i-2).c_str());
                    break;
                }
            }
        }
//        printf("%c\n",data[ptr].name[0]);
//        printf("%d",ptr);
//        cout<<data[ptr].start_value<<endl;
//        cout<<data[ptr].end_value<<endl;
        ptr++;
    }



}
void findUncdName(Unicode data[], long given_value){
    for(int i=0; i< SIZE; i++) {
        //防止空指针报错
        if (strcmp(data[i].name, "")) {
            if (data[i].start_value <= given_value && given_value <= data[i].end_value) {
                cout<<data[i].name<<endl;
            }
        }
            //若指针为空，break
        else {
            break;
        }
    }
}
