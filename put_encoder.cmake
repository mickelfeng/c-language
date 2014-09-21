#
# This is a CMake makefile.  You can find the cmake utility and
# information about it at http://www.cmake.org
#

cmake_minimum_required(VERSION 2.6)

# create a variable called target_name and set it to the string "htmlify"
set (target_name put_encoder)

PROJECT(${target_name})

# add all the cpp files we want to compile to this list.  This tells
# cmake that they are part of our target (which is the executable named htmlify)
ADD_EXECUTABLE(${target_name} 
   zencode.c
   php_screw.c
   )

# Tell cmake to link our target executable to dlib.

INCLUDE_DIRECTORIES("J:/phpdev/phpsdk/php53dev/vc9/x86/php-5.4.4")
INCLUDE_DIRECTORIES("J:/phpdev/phpsdk/php53dev/vc9/x86/php-5.4.4/main")
INCLUDE_DIRECTORIES("J:/phpdev/phpsdk/php53dev/vc9/x86/php-5.4.4/Zend")
INCLUDE_DIRECTORIES("J:/phpdev/phpsdk/php53dev/vc9/x86/php-5.4.4/TSRM")
INCLUDE_DIRECTORIES("J:/phpdev/phpsdk/php53dev/vc9/x86/php-5.4.4/win32")
INCLUDE_DIRECTORIES("J:/libs/zlib127/include/")

LINK_DIRECTORIES("J:/phpdev/phpsdk/php53dev/vc9/x86/php-5.4.4/Release_TS/php-5.4.4-devel-VC9-x86/lib")
LINK_DIRECTORIES("J:/libs/zlib127/lib/")


TARGET_LINK_LIBRARIES(${target_name} php5ts )


INSTALL(TARGETS ${target_name}
	RUNTIME DESTINATION bin
)
