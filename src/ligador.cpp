#include <iostream>
#include <string>
#include <map>

using namespace std;

int main(int argc, char **argv){
    map<string, pair<int,int>> a;
    a["a1"] = pair<int,int>(2,2);
    printf("%d\n", a["m2"].second);

    /*
    vector<string> m = assembler::split("STOP", " ,");
    for (int i = 0; i < m.size(); ++i) {
        printf("%s\n", m[i].c_str());
    }*/
    return 0;
}
