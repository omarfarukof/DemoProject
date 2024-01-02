#include "CppProject/CppProject.h"

#include <filesystem>
#include <iostream>
#include <fstream>


namespace fs = std::filesystem;


std::string Get_Static_Lib_name()
{
    std::string Project_Name;
    // std::string Project_Path;
    std::cout << "Enter the name of the static library: ";
    std::cin >> Project_Name;
    
    return Project_Name;
}

std::string Get_Static_Lib_path()
{
    std::string Project_Path;
    std::cout << "Enter the path of the static library: ";
    std::cin >> Project_Path;
    
    return Project_Path;
}

// Complete Tree Structure
void Create_file_Tree(std::string path , std::string module_name , std::string file_name )
{
    // Static_Lib_Name
    // |___include
    //    |___Lib_name
    //        |___Lib_name.h
    // |___src
    //     |___Lib_name.cpp
    fs::path file_directory = fs::path(path);
    fs::path include_directory = file_directory / "include" / module_name;
    fs::path src_directory = file_directory / "src";

    // fs::create_directories(project_directory);
    // if include_directory not exists
    if ( !fs::exists(include_directory) )
    {
        fs::create_directories(include_directory);
    }
    if ( !fs::exists(src_directory) )
    {
        fs::create_directories(src_directory);
    }


    fs::path include_file = include_directory / (file_name + ".h");
    fs::path src_file = src_directory / (file_name + ".cpp");

    std::string ow_include = "new";

    if (fs::exists(include_file))
    {
        std::cout << "Include File Already exists. Want to Overwrite! [y/N] : ";
        std::cin >> ow_include;
    }

    if (ow_include == "Y" || ow_include == "y" || ow_include=="new")
    {
        std::ofstream include_file_stream(include_file);
        if (include_file_stream.is_open())
        {
            include_file_stream << "#pragma once" << std::endl;
            include_file_stream.close();
        }
        std::cout << "Writing into Include File" << std::endl;
    }
    else{
        std::cout << "Not Writing into Include File" << std::endl;
    }

    std::string ow_src = "new";

    if (fs::exists(src_file))
    {
        std::cout << "Source File Already exists. Want to Overwrite! [y/N] : ";
        std::cin >> ow_src;
    }
    
    if (ow_src == "Y" || ow_src == "y" || ow_src=="new")
    {
        std::ofstream src_file_stream(src_file);
        if (src_file_stream.is_open())
        {
            src_file_stream << "#include \"" << module_name + "/" + file_name << ".h\"" << std::endl;
            src_file_stream.close();
        }
        std::cout << "Writing into Source File" << std::endl;

    }
    else{
        std::cout << "Not Writing into Source File" << std::endl;
    }

     
}

void Create_lib_file_Tree(std::string path , std::string lib_name , std::string module_name , std::string file_name )
{
    fs::path lib_directory = fs::path(path) / "libs" / lib_name;

    Create_file_Tree( lib_directory , module_name , file_name );

}

void Create_project_file(std::string path , std::string project_name )
{
    fs::path file_directory = fs::path(path);
    fs::path project_directory = file_directory / "app" / "src";


    if ( !fs::exists(project_directory) )
    {
        fs::create_directories(project_directory);
    }

    fs::path project_file = project_directory / (project_name + ".cpp");

    std::string ow_project = "new";

    if (fs::exists(project_file))
    {
        std::cout << "Project File Already exists. Want to Overwrite! [y/N] : ";
        std::cin >> ow_project;
    }

    if (ow_project == "Y" || ow_project == "y" || ow_project=="new")
    {
        std::ofstream project_file_stream(project_file);
        if (project_file_stream.is_open())
        {
            std::string project_file_content = "#include \"app/app.h\"\n\nint main( int argc , char* argv[] )\n{\n\tmain_app( argc , argv );\n\n\treturn 0;\n}" ;

            project_file_stream << project_file_content << std::endl;

            project_file_stream.close();
        }
        std::cout << "Writing into Project File" << std::endl;
    }
    else{
        std::cout << "Not Writing into Project File" << std::endl;
    }
}

void lib_creator_cli()
{
    std::string Lib_Path ;
    std::string Lib_Name ;
    std::string Module_Name;
    std::string File_Name;

    std::cout << "Library Path: ";
    std::cin >> Lib_Path;

    std::cout << "Library Name: ";
    std::cin >> Lib_Name;

    std::cout << "Module_Name: ";
    std::cin >> Module_Name;

    std::cout << "File_Name: ";
    std::cin >> File_Name;

    Create_lib_file_Tree( Lib_Path , Lib_Name , Module_Name , File_Name );
}

void Create_app_file_Tree(std::string path , std::string app_name , std::string module_name , std::string file_name )
{
    fs::path app_directory = fs::path(path) / app_name;

    Create_file_Tree( app_directory , module_name , file_name );

}

void app_creator_cli()
{
    std::string App_Path ;
    std::string App_Name = "app";
    std::string Module_Name = "app";
    std::string File_Name = "app";
    std::string Project_Name;

    std::cout << "App Path: ";
    std::cin >> App_Path;

    std::cout << "Project_Name: ";
    std::cin >> Project_Name;

    Create_project_file(App_Path , Project_Name);

    // std::cout << "Library Name: ";
    // std::cin >> Lib_Name;

    // std::cout << "Module_Name: ";
    // std::cin >> Module_Name;

    // std::cout << "File_Name: ";
    // std::cin >> File_Name;

    Create_app_file_Tree( App_Path , App_Name , Module_Name , File_Name );
    
    // Open the file in append mode
    fs::path app_file_Path = fs::path(App_Path) / "app" / "include" / "app" / "app.h";
    std::ofstream outFile(app_file_Path, std::ios::app);
    if (!outFile.is_open()) {
        std::cout << "Error opening the file for appending." << std::endl;
    }
    // Append content to the file
    outFile << "\nint main_app( int argc , char* argv[] );\n";
    outFile.close();

    // Open the file in append mode
    app_file_Path = fs::path(App_Path) / "app" / "src" / "app.cpp" ;
    std::ofstream outFile2(app_file_Path, std::ios::app);
    if (!outFile2.is_open()) {
        std::cout << "Error opening the file for appending." << std::endl;
    }
    std::string app_file_content = "\n\nint main_app( int argc , char* argv[] )\n{\n\n\n\treturn 0;\n}" ;
    // Append content to the file
    outFile2 << app_file_content;
    outFile2.close();

}

void Create_Static_Lib_Lua(std::string path)
{
    
// Static Lua Build File 
std::string Static_lib_lua="project \"${directory_name}\"\n\n\
    kind \"StaticLib\"\n\
    language \"C++\"\n\
    cppdialect \"C++20\"\n\
    staticruntime \"off\"\n\n\
    targetdir ( LibRelativeDir .. \"bin/\" .. OutputDir .. \"/\%{prj.name}\")\n\
    objdir ( LibRelativeDir .. \"bin/Intermediates/\" .. OutputDir .. \"/\%{prj.name}\")\n\n\
    files { \"include/**.h\", \"src/**.cpp\" }\n\
    includedirs { \"include\" }\n\
    filter \"system:windows\"\n\
        systemversion \"latest\"\n\
        defines { \"WINDOWS\" }\n\n\
    filter \"configurations:Debugn\"\n\
        defines { \"DEBUG\" }\n\
        runtime \"Debug\"\n\
        symbols \"On\"\n\n\
    filter \"configurations:Release\"\n\
        defines { \"RELEASE\" }\n\
        runtime \"Release\"\n\
        optimize \"On\"\n\
        symbols \"On\"\n\n\
    filter \"configurations:Dist\"\n\
        defines { \"DIST\" }\n\
        runtime \"Release\"\n\
        optimize \"On\"\n\
        symbols \"Off\"";



}