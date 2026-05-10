cmake_minimum_required(VERSION 3.16)
project(MediCoreHospitalSystem)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(NOT SFML_DIR)
    set(SFML_DIR "C:/Users/m-uxa/Desktop/oop_project/SFML-2.6.1/build")
endif()

find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

include_directories(include)

add_executable(MediCore
    src/main.cpp
    src/TextUtil.cpp
    src/Person.cpp
    src/Patient.cpp
    src/Doctor.cpp
    src/Admin.cpp
    src/Appointment.cpp
    src/Bill.cpp
    src/Prescription.cpp
    src/HospitalException.cpp
    src/FileNotFoundException.cpp
    src/InsufficientFundsException.cpp
    src/InvalidInputException.cpp
    src/SlotUnavailableException.cpp
    src/Storage.cpp
    src/Validator.cpp
    src/FileHandler.cpp
    src/HospitalSystem.cpp
    src/Gui.cpp
)

target_link_libraries(MediCore sfml-graphics sfml-window sfml-system)

file(COPY data DESTINATION ${CMAKE_BINARY_DIR})

file(GLOB SFML_RUNTIME_DLLS "C:/Users/m-uxa/Desktop/oop_project/SFML-2.6.1/build/lib/*.dll")
if(SFML_RUNTIME_DLLS)
    add_custom_command(TARGET MediCore POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${SFML_RUNTIME_DLLS}
        $<TARGET_FILE_DIR:MediCore>
    )
endif()
