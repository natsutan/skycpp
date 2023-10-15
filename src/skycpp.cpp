#include <stdio.h>
#include <iostream>
#include <string>
#include "skycpp.h"

using namespace std;

void usage(void);

void usage() {
    cout << "Usage: skycpp <infile> <outfile>" << endl;
    cout << "  infile:  the input file to be compiled" << endl;
    cout << "  outfile: the output file to be created" << endl;
    exit(1);
}


int main(int argc, char *argv[]) {
    if (argc != 3) {
        usage();
    }

    string infile = argv[1];
    string outfile = argv[2];

    cout << "Compiling " << infile << " to " << outfile << endl;

    tokenizer::Tokenizer tokenizer(infile);

    return 0;
}
