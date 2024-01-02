#pragma once

// #include <Class_Cpp_Static_Lib.h>
#include <string>

std::string Get_Static_Lib_name();
std::string Get_Static_Lib_path();

void Create_file_Tree(std::string path , std::string module_name , std::string file_name);
void Create_lib_file_Tree(std::string path , std::string lib_name , std::string module_name , std::string file_name );

void lib_creator_cli();
void app_creator_cli();

void Create_Static_Lib_Tree(std::string path);
void Create_Static_Lib_Lua(std::string path);


// private:
// std::string Project_Name ;
// std::string Project_Path ;