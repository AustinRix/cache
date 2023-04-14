#include<iostream>
#include<fstream>
#include<cstdlib>
using namespace std;

const int MAX_SIZE = 1000;

class Entry {
public:
  Entry();
  ~Entry();
  void display(ofstream& outfile);

  void set_tag(int _tag) { tag = _tag; }
  int get_tag() { return tag; }

  void set_valid(bool _valid) { valid = _valid; }
  bool get_valid() { return valid; }

  void set_ref(int _ref) { ref = _ref; }
  int get_ref() { return ref; }

private:
  bool valid;
  unsigned tag;
  int ref;
};

class Cache {
public:
  Cache(int, int);
  ~Cache();

  void display(ofstream& outfile);


  int get_index(unsigned long addr);
  int get_tag(unsigned long addr);

  unsigned long retrieve_addr(int way, int index);

  bool hit(ofstream& outfile, unsigned long addr);

  void update(ofstream& outfile, unsigned long addt);


private:
  int assoc;
  unsigned num_entries;
  int num_sets;
  Entry **entries;
};


int main(int argc, char*argv[]) {

    /* check if the correct number of arguments have been passed; bail otherwise */
    if (argc < 4) {
        cout << "Usage: " << endl;
        cout << "   ./cache num_entries associativity filename" << endl;
        return 0;
    }

    if (argc < 2) {
        cout << "Usage: " << endl;
        cout << "   ./file_process filename" << endl;
        return 0;
    }
    /* get args; all args come in as strings; need to convert to int with atoi() */
    unsigned entries = atoi(argv[1]);
    unsigned assoc = atoi(argv[2]);
    string filename = argv[3];
    string input_filename = filename + "_input";
    string output_filename = filename + "_output";
    ofstream output;
    ifstream input;

    // input start
    input.open(input_filename);
    if (!input.is_open()) {
        cerr << "Could not open input file " << input_filename << ". Exiting ..." << endl;
        exit(0);
    }

    unsigned long *nums = new unsigned long[MAX_SIZE];
    int count = 0;
    while (!input.eof() && count < MAX_SIZE) {
        input >> nums[count];
        count++;
    }

    input.close();

    // output start
    output.open(output_filename);
    for (int i = 0; i < count; i++)
        output << "ADDR : " << nums[i] << endl;
    output.close();

    /* print the args */
    cout << "Number of entries: " << entries << endl;
    cout << "Associativity: " << assoc << endl;
    cout << "Input File Name: " << filename << endl;

    return 0;
}

