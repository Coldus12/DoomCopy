//
// Created by coldus on 5/8/20.
//

#ifndef DOOMCOPY_STRINGMANAGER_H
#define DOOMCOPY_STRINGMANAGER_H

#include <string>
//#include "DoomCopy.h"

namespace DoomCopy {
    class StringManager {
    public:

        static std::string get_substring_btwn_first_occurences(std::string source, std::string after_what, std::string until_what) {
            int posStart = (source.find(after_what) + after_what.size());
            int posEnd = source.find(until_what);
            posEnd -= posStart;

            return source.substr(posStart,posEnd);
        }

        static std::string get_substring_btwn_last_occurences(std::string source, std::string after_what, std::string until_what) {
            int posStart =  (source.find_last_of(after_what) + after_what.size());
            int posEnd = source.find_last_of(until_what);
            posEnd -= posStart;

            return source.substr(posStart,posEnd);
        }

        static std::string get_substring_after_first_occurence_of_and_last_occurence_of(std::string source, std::string after_what, std::string until_what) {
            int posStart = (source.find(after_what) + after_what.size());
            int posEnd = source.find_last_of(until_what);
            posEnd -= posStart;

            return source.substr(posStart,posEnd);
        }

        static std::string get_substring_after_last_occurence_of_and_first_occurence_of(std::string source, std::string after_what, std::string until_what){
            int posStart = (source.find_last_of(after_what) + after_what.size());
            int posEnd = source.find(until_what);
            posEnd -= posStart;

            return source.substr(posStart,posEnd);
        }

        static std::string get_substring_btwn_first_and_next(std::string source, std::string after_what, std::string until_what) {
            std::string substring = get_substring_btwn_first_occurences(source,after_what,until_what);
            substring = get_substring_btwn_first_occurences(substring,"",until_what);

            return substring;
        }

        static double string_to_double(std::string str) {
            std::string::size_type mi;
            return std::stod(str, &mi);
        }
    };
}

#endif //DOOMCOPY_STRINGMANAGER_H
