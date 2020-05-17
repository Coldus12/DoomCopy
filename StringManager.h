//
// Created by coldus on 5/8/20.
//

#ifndef DOOMCOPY_STRINGMANAGER_H
#define DOOMCOPY_STRINGMANAGER_H

#include <string>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////                                           StringManager                                                        ////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


namespace DoomCopy {
    class StringManager {
    public:

        ///Egy adott stringbol visszaad egy substringet, ami az after_what es az until_what kozott talalhato.
        ///Ha tobbszor szerepel a forras stringben az after_what vagy az until_what, akkor a tobbszor szereplo
        ///stringek kozul az(oka)t hasznalja, ami elsokent talalhato a forras stringben.
        ///@param source - forras string - ebbol szeretnenk egy substringet
        ///@param after_what - milyen string utan kezdodik a substring
        ///@param until_what - milyen string elott fejezodik be a keresett substring
        ///@return - a keresett substring/ures string ha nem talalhhato a keresett substring
        static std::string get_substring_btwn_first_occurences(const std::string& source, const std::string& after_what, const std::string& until_what) {
            try {
                int posStart = (source.find(after_what) + after_what.size());

                //Ha az until_what ures, akkor a after_what-tol a string vegieg tart a substring amit visszaad a fuggveny.
                if (!until_what.empty()) {
                    int posEnd = source.find(until_what);
                    posEnd -= posStart;

                    return source.substr(posStart, posEnd);
                } else {
                    return source.substr(posStart);
                }
            } catch (std::exception& ex) {
                std::cerr << "An error occured in \"get_substring_btwn_first_occurences\". source: " << source << " after_what: "
                          << after_what << " until_what: " << until_what << " error message: " << ex.what() << std::endl;
            }

            return "";
        }

        ///Egy adott stringbol visszaad egy substringet, ami az after_what es az until_what kozott talalhato.
        ///Ha tobbszor szerepel a forras stringben az after_what vagy az until_what, akkor a tobbszor szereplo
        ///stringek kozul az(oka)t hasznalja, ami utolsonak talalhato a forras stringben.
        ///@param source - forras string - ebbol szeretnenk egy substringet
        ///@param after_what - milyen string utan kezdodik a substring
        ///@param until_what - milyen string elott fejezodik be a keresett substring
        ///@return - a keresett substring/ures string ha nem talalhhato a keresett substring
        static std::string get_substring_btwn_last_occurences(const std::string& source, const std::string& after_what, const std::string& until_what) {
            try {
                int posStart =  (source.find_last_of(after_what) + after_what.size());

                //Ha az until_what ures, akkor a after_what-tol a string vegieg tart a substring amit visszaad a fuggveny.
                if (!until_what.empty()) {
                    int posEnd = source.find_last_of(until_what);
                    posEnd -= posStart;

                    return source.substr(posStart, posEnd);
                } else {
                    return source.substr(posStart);
                }
            } catch (std::exception& ex) {
                std::cerr << "An error occured in \"get_substring_btwn_last_occurences\". source: " << source << " after_what: "
                          << after_what << " until_what: " << until_what << " error message: " << ex.what() << std::endl;
            }

            return "";
        }

        ///Egy adott stringbol visszaad egy olyan substringet, ami az after_what es az until_what stringek kozott talalhato a forras stringben.
        ///Ha tobbszor szerepel a forras stringben az after_what vagy az until_what, akkor az after_what-hoz hasonlo stringek kozul azt hasznalja,
        ///ami elsokent szerepel, mig az until_what-hoz hasonlo stringek kozul azt ami utoljara szerepel a forras stringben, es az ezek kozotti
        ///substringet adja vissza.
        ///@param source - forras string - ebbol szeretnenk egy substringet
        ///@param after_what - milyen string utan kezdodik a substring
        ///@param until_what - milyen string elott fejezodik be a keresett substring
        ///@return - a keresett substring
        static std::string get_substring_after_first_occurence_of_and_last_occurence_of(const std::string& source, const std::string& after_what, const std::string& until_what) {
            try {
                int posStart = (source.find(after_what) + after_what.size());

                //Ha az until_what ures, akkor a after_what-tol a string vegieg tart a substring amit visszaad a fuggveny.
                if (!until_what.empty()) {
                    int posEnd = source.find_last_of(until_what);
                    posEnd -= posStart;

                    return source.substr(posStart,posEnd);
                } else {
                    return source.substr(posStart);
                }
            } catch (std::exception& ex) {
                std::cerr << "An error occured in \"get_substring_after_first_occurence_of_and_last_occurence_of\". source: " << source << " after_what: "
                          << after_what << " until_what: " << until_what << " error message: " << ex.what() << std::endl;
            }

            return "";
        }

        ///Egy adott stringbol visszaad egy olyan substringet, ami az after_what es az until_what stringek kozott talalhato a forras stringben.
        ///Ha tobbszor szerepel a forras stringben az after_what vagy az until_what, akkor az after_what-hoz hasonlo stringek kozul azt hasznalja,
        ///ami utolsokent szerepel, mig az until_what-hoz hasonlo stringek kozul azt ami elsokent szerepel a forras stringben, es az ezek kozotti
        ///substringet adja vissza.
        ///@param source - forras string - ebbol szeretnenk egy substringet
        ///@param after_what - milyen string utan kezdodik a substring
        ///@param until_what - milyen string elott fejezodik be a keresett substring
        ///@return - a keresett substring
        static std::string get_substring_after_last_occurence_of_and_first_occurence_of(const std::string& source, const std::string& after_what, const std::string& until_what){
            try {
                int posStart = (source.find_last_of(after_what) + after_what.size());

                //Ha az until_what ures, akkor a after_what-tol a string vegieg tart a substring amit visszaad a fuggveny.
                if (!until_what.empty()) {
                    int posEnd = source.find(until_what);
                    posEnd -= posStart;

                    return source.substr(posStart, posEnd);
                } else {
                    return source.substr(posStart);
                }
            } catch (std::exception& ex) {
                std::cerr << "An error occured in \"get_substring_after_last_occurence_of_and_first_occurence_of\". source: " << source << " after_what: "
                          << after_what << " until_what: " << until_what << " error message: " << ex.what() << std::endl;
            }
        }

        ///Egy adott stringbol visszaad egy substringet, ami az after_what es az until_what kozott talalhato.
        ///A visszaadott substring a forras stringben talalhato elso after_what utan kezdodik, es az elso
        ///after_what utani until_what utan er veget.
        ///Pelda: forras string: "test string" , after_what: "test ", until_what: "t"
        ///Visszaadott ertek: "s", mert habar a forrasban addig mar ketszer szerepelt a "t", minket az erdekel
        ///ami az after_what utan eloszor szerepel.
        ///@param source - forras string - ebbol szeretnenk egy substringet
        ///@param after_what - milyen string utan kezdodik a substring
        ///@param until_what - milyen string elott fejezodik be a keresett substring
        ///@return - a keresett substring
        static std::string get_substring_btwn_first_and_next(const std::string& source, const std::string& after_what, const std::string& until_what) {
            std::string substring = get_substring_btwn_first_occurences(source,after_what,until_what);
            substring = get_substring_btwn_first_occurences(substring,"",until_what);

            return substring;
        }

        ///Stringet valos szamma konvertal
        ///@param str - string amibol szam lesz
        ///@return - a valos szam
        static double string_to_double(std::string str) {
            if (str.empty())
                throw std::invalid_argument("Empty \"str\"");

            try {
                std::string::size_type mi;
                return std::stod(str, &mi);
            } catch (std::exception& ex) {
                std::cerr << ex.what() << std::endl;
            }

            return 0;
        }
    };
}

#endif //DOOMCOPY_STRINGMANAGER_H
