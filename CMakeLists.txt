# CMakeList.txt : CMake project for InventoryManagementSystem, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("InventoryManagementSystem")

# Add source to this project's executable.
add_executable (InventoryManagementSystem src/main.cpp
src/DataManager.cpp src/GUI.cpp src/InventoryManager.cpp src/Product.cpp src/PurchaseTransaction.cpp src/SalesTransaction.cpp src/Transaction.cpp)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET InventoryManagementSystem PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
include_directories(include)

target_include_directories(InventoryManagementSystem PUBLIC "C:\\nana\\nana-master\\include")

add_definitions(-D_SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING)

target_link_libraries(InventoryManagementSystem "nana_v143_Debug_x64")