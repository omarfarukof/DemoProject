# Autometically Creates Project Stracture 

## Create app structure
```shell
./Scripts/ProjectCreator --app
```

## Create static lib structure
```shell
./Scripts/ProjectCreator --static_lib
```

## Create *.lua files for Static Library
```shell
sh ./Scripts/run.sh --luastaticlib ./libs/<Lib_Name>
```

## Create *.lua file for MainApp
```shell
sh ./Scripts/run.sh --luamainbuild ./
```

## Create make file with premake5
```shell
sh ./Scripts/Setup-Linux.sh ./
```   

## Build the project
```shell
make
```

or
```shell
make config=release
```

Project is compiled in `./bin/linux-x86_64/<build_config>/MainApp`

> lua file creation option will be added to ProjectCreator Later.