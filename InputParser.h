#include "io_utils.h"
#include "InvalidGameModeException.h"

class InputParser {
public:
    int mode = NULL;
    vector <string> tokens;
    InputParser(int& argc, char** argv) {
        for (int i = 1; i < argc; ++i)
            this->tokens.push_back(string(argv[i]));
    }

    void checkMode();
   
 
    bool cmdOptionExists(const string& option) const {
        return find(this->tokens.begin(), this->tokens.end(), option)
            != this->tokens.end();
    }

    void printFirstToken() {
        string tmp = tokens[0];
        cout << tmp << endl;
    }

    const string& getCmdOption(const string& option) const {
        vector<string>::const_iterator itr;
        itr = find(this->tokens.begin(), this->tokens.end(), option);
        if (itr != this->tokens.end() && ++itr != this->tokens.end()) {
            return *itr;
        }
        static const string empty_string("");
        return empty_string;
    }

};