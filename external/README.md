# External Directory Usage
This directory is intended for the following purposes:
1. To store source code of third party dependencies which should be built during compilation of the application source code. This could include source code of third party dependency which you must modify to fit your use case, or source code that you require more control over (for example glad as I'll be using different versions at different times to match different opengl specs)
   - /external/somelib/src
   - /external/somelib/include
   - /external/somelib/CMakeLists.txt
      - build library either static or shared
	  - copy public include files to /build/external/export/include/{libName}
	  - copy binary|binaries to /build/external/export/static|shared/{libName}

2. To store public header files and a precompiled binary of a dependency that is too complex to have an automated build process for.
   - /external/somelib2/include
   - /external/somelib2/bin
      - somelib2.lib
   - /external/somelib2/CMakeLists.txt
      - copy public include files to /build/external/export/include/{libName}
	  - copy binary|binaries to /build/external/export/static|shared/{libName}

3. To store cmake module files that are responsible for obtaining other third party dependencies