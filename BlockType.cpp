//
// Created by coldus on 5/8/20.
//

#include <fstream>
#include "BlockType.h"
#include "StringManager.h"

DoomCopy::Blocks::Blocks(const char* path, Texture& text) {
    load(path, text);
}

void DoomCopy::Blocks::load(const char* path, Texture& text) {
    std::string line = "";
    std::ifstream file;
    file.open(path);
    std::getline(file, line);
    int i = 0;

    int nr = DoomCopy::StringManager::string_to_double(StringManager::get_substring_btwn_first_occurences(line,"number="," "));
    bool firstSolid = StringManager::get_substring_btwn_first_occurences(line, "type=\"", "\"").find("solid") != std::string::npos;

    std::string pathToText = "";
    std::string textName = "";

    if (line.find("texture") != std::string::npos) {
        pathToText = StringManager::get_substring_after_first_occurence_of_and_last_occurence_of(line,"texture=\"","\"");
        textName = StringManager::get_substring_btwn_first_occurences(pathToText,"/",".");

        text.addImg(pathToText.c_str(),textName.c_str());
    }

    //std::cout << "szam " << nr << " bool " << firstSolid << "\n";

    blockType.setHead(BlockType(nr,firstSolid,textName.c_str()));
    while(!file.eof()) {
        //i++;

        std::getline(file,line);
        nr = StringManager::string_to_double(StringManager::get_substring_btwn_first_occurences(line,"number="," "));
        firstSolid = (StringManager::get_substring_btwn_first_occurences(line,"type=\"","\"").find("solid") != std::string::npos);

        if (line.find("texture") != std::string::npos) {
            pathToText = StringManager::get_substring_after_first_occurence_of_and_last_occurence_of(line,"texture=\"","\"");
            textName = StringManager::get_substring_btwn_first_occurences(pathToText,"/",".");

            text.addImg(pathToText.c_str(),textName.c_str());
        }

        //std::cout << textName << std::endl;
        blockType.addItem(BlockType(nr,firstSolid,textName.c_str()));
    }
}

bool DoomCopy::Blocks::isTypeSolid(int type) const {
    ListItem<BlockType>* iter = blockType.getHead();
    while(iter->next != NULL) {
        if (iter->item.x == type)
            return iter->item.isSolid;
        iter = iter->next;
    }
    if (iter->item.x == type)
        return iter->item.isSolid;
    throw "This blocktype is not present in the database therefore it is not known whether it is solid or not.";
}

std::string DoomCopy::Blocks::getTextureName(int type) {
    ListItem<BlockType>* iter = blockType.getHead();
    while(iter->next != NULL) {
        if (iter->item.x == type)
            return iter->item.textureName;
        iter = iter->next;
    }
    if (iter->item.x == type)
        return iter->item.textureName;
    throw "This blocktype is not present in the database.";
}

void DoomCopy::Blocks::printTypes() {
    ListItem<BlockType>* iter = blockType.getHead();
    while(iter->next != NULL) {
        std::cout << iter->item.x << std::endl;
        iter = iter->next;
    }
    std::cout << iter->item.x << std::endl;
}