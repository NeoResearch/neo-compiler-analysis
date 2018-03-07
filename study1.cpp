#include<iostream>
#include "Scanner++/Scanner.h"
#include<vector>
#include<sstream>

using namespace std;
using namespace scannerpp;

// type 1 (PUSH): PUSH00, PUSH01, ...
// type 2 arithmetic
// type 3 jumps (JMP...)
// type 4....
int opcodeCategory(string op) {


}


vector<string> opcodes(Scanner& scanner) {
   vector<string> vs;
   while(scanner.hasNext()) {
     string op = scanner.next();
     scanner.nextLine();
     vs.push_back(op);
   }
   return vs;
}


void study1(string filebase) {
    stringstream spython;
    spython << "Samples/"+ filebase << ".py.opcodes";
    stringstream scs;
    scs << "Samples/" + filebase << ".cs.opcodes";

    cout << "open: " << spython.str() << endl; 
    Scanner scanFilePy(new File(spython.str()));
    vector<string> vop_py = opcodes(scanFilePy);
    for(unsigned i=0; i<vop_py.size(); i++)
       cout << vop_py[i] << " ";
    cout << endl;

    cout << "open: " << scs.str() << endl; 
    Scanner scanFileCs(new File(scs.str()));
    vector<string> vop_cs = opcodes(scanFileCs);

    cout << "RESULT1\tpy\t" << vop_py.size() << "\tcs\t" << vop_cs.size() << endl;

}


int main() {

   string filelist="filelist.txt";

   Scanner scanner(new File(filelist));

   while(scanner.hasNext()) {
      string path = scanner.nextLine();
      cout << path << endl;
      study1(path);
   }

   return 0;
}


