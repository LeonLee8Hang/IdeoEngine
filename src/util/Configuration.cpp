

#include "ideoengine/util/Configuration.h"
#include "ideoengine/util/StringUtil.h"

#include <fstream>
#include <string>
#include <vector>
#include <iostream>

const char ITEM_SPLITTER = '=';

namespace ideoengine {
    namespace util {
        void Configuration::Parse(const std::string& fileName) {
            std::ifstream inputFile(fileName.c_str());

            while ( !inputFile.eof() ) {
                std::string line;
                std::getline(inputFile, line);

                if ( inputFile.eof() ) {
                    break;
                }

                if ( line.empty() ) {
                    continue;
                }

                std::vector<std::string> words = SplitString(line, ITEM_SPLITTER);
                std::string propertyName = TrimString(words[0]);
                std::string propertyValue = TrimString(words[1]);

                SetProperty(propertyName, propertyValue);
            }
        }
    }
}
