#include "CppProject/CppProject.h"
#include <iostream>
#include <cstring>

int main_app( int argc , char* argv[] )
{
    // CppProject();
    // Create_file_Tree( "./TestLib" , "Lib01" , "Lib01" );

    // std::cout << argc << std::endl;
    
    // for (int i = 0; i < argc; i++)
    // {
    //     std::cout << argv[i] << std::endl;
    // }
    
    // std::cout << std::strcmp( argv[1] , "--lib" ) << std::endl;
    // std::cout << !std::strcmp( argv[1] , "--lib" ) << std::endl;



    // if (argv[1] == "--lib")
    if ( !std::strcmp( argv[1] , "--static_lib" ) )
    {
        // std::string Lib_Path ;
        // std::string Lib_Name ;
        // std::string Module_Name;
        // std::string File_Name;

        // std::cout << "Library Path: ";
        // std::cin >> Lib_Path;

        // std::cout << "Library Name: ";
        // std::cin >> Lib_Name;

        // std::cout << "Module_Name: ";
        // std::cin >> Module_Name;

        // std::cout << "File_Name: ";
        // std::cin >> File_Name;

        // Create_lib_file_Tree( Lib_Path , Lib_Name , Module_Name , File_Name );

        lib_creator_cli();

    }

    if ( !std::strcmp( argv[1] , "--app" ) )
    {
        app_creator_cli();
    }
    

    return 0;
}