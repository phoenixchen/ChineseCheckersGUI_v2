#include <sstream>
#include <fstream>
#include "json.hpp"
using namespace std;
using json = nlohmann::json;

#include "../info/information.h"

json read_json(char filename[]);

void write_json(char filename[],Info *information);