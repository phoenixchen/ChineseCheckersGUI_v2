
#include "replay.h"

json read_json(char filename[]){
    ifstream inFile;
    inFile.open(filename);
    stringstream strStream;
    strStream << inFile.rdbuf();// Read the file
    string string = strStream.str();// string holds the content of the file
    json inputJson = json::parse(string);
    return inputJson;
}


void write_json(char filename[],Info *information){
    struct list_member *lm;
    json output_json;
    for ((*information).list_iter=(*information).info_list.begin(); (*information).list_iter!=(*information).info_list.end(); ++((*information).list_iter)){
        lm = &(*((*information).list_iter));
        char temp1[255];
        strcpy(temp1,(*lm).str_info);
        //int temp2 = happyJson["Moves"][i]["Item2"];
        //output_json["Moves"][i]["Item1"] = temp1;
        //output_json["Moves"][i]["Item2"] = temp2;
    }
    //int winner = input_Json["Winner"];
    //output_json["Winner"] = winner;

    ofstream outfile;
    outfile.open(filename);
    std::string s = output_json.dump();
    outfile << s;
    outfile.close();
}