cmake_minimum_required(VERSION 3.6)
project(DocxFactory)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
if (CYGWIN)
  add_definitions(-D_GLIBCXX_USE_C99)
endif (CYGWIN)
if (NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Debug")
  message(STATUS "DEBUG BUILD")
elseif (CMAKE_BUILD_TYPE STREQUAL "Debug")
  message(STATUS "DEBUG BUILD")
  add_definitions(-DDEBUG)
  add_definitions(-D_DEBUG)
elseif (CMAKE_BUILD_TYPE STREQUAL "Release")
  message(STATUS "RELEASE BUILD")
  if (CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -s")
  endif (CMAKE_COMPILER_IS_GNUCXX)
endif ()


if (NOT WIN32)
  include_directories(SYSTEM /usr/include)
  include_directories(SYSTEM /usr/local/include)
endif (NOT WIN32)

if (CMAKE_COMPILER_IS_GNUCXX)
  set(START_GROUP_LINK -Wl,--start-group)
  set(END_GROUP_LINK -Wl,--end-group)
endif (CMAKE_COMPILER_IS_GNUCXX)

if (WIN32)
  add_definitions(/D_WIN32)
  add_definitions(/D_SCL_SECURE_NO_WARNINGS)
  add_definitions(/D_CRT_SECURE_NO_WARNINGS)
  add_definitions(/D_CRT_NONSTDC_NO_DEPRECATE)
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /ignore:4275")
  add_definitions(/DNOMINMAX)
  add_definitions(/DAPR_DECLARE_STATIC)
  add_definitions(/DCMS_DLL)
  add_definitions(/DCMS_EXPORTS)
else (WIN32)
  if (CYGWIN)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")
  else (CYGWIN)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fPIC")
  endif (CYGWIN)
  add_compile_options("-Wno-deprecated-declarations")
endif (WIN32)

########### TODO : replace with find
set(SWF "/home/ivk/coding/swf")
set(ZINT_INCLUDE_DIRS "${SWF}/base_alt64/x32/zint/include")
set(ZINT_LIB_DIRS "${SWF}/base_alt64/x32/zint/lib")
set(ZINT_LIBRARIES "-lzint")
message(STATUS "ZINT => ${ZINT_LIB_DIRS} ${ZINT_LIBRARIES}")
###########

include_directories(${ZINT_INCLUDE_DIRS})
link_directories(${ZINT_LIB_DIRS})

########### TODO : replace with find
set(RAPIDJSON_INCLUDE_DIRS "${SWF}/base_alt64/x32/rapidjson/include")
message(STATUS "RAPIDJSON => ${RAPIDJSON_INCLUDE_DIRS}")
###########

include_directories(${RAPIDJSON_INCLUDE_DIRS})

########### TODO : replace with find
set(MINIZIP_INCLUDE_DIRS "/usr/include")
set(MINIZIP_LIB_DIRS "/usr/lib")
set(MINIZIP_LIBRARIES "-lminizip")
message(STATUS "MINIZIP => ${MINIZIP_LIB_DIRS} ${MINIZIP_LIBRARIES}")
###########

include_directories(${MINIZIP_INCLUDE_DIRS})
link_directories(${MINIZIP_LIB_DIRS})

########### TODO : replace with find
set(LIBREOFFICE_SDK_INCLUDE_DIRS "/opt/libreoffice5.3/sdk/include" "/opt/libreoffice5.3/sdk/include_generated")
set(LIBREOFFICE_SDK_LIB_DIRS "/opt/libreoffice5.3/sdk/lib")
set(LIBREOFFICE_SDK_LIBRARIES "-luno_cppu -luno_cppuhelpergcc3 -luno_sal -luno_salhelpergcc3")
message(STATUS "LIBREOFFICE => ${LIBREOFFICE_SDK_LIB_DIRS} ${LIBREOFFICE_SDK_LIBRARIES}")
###########

include_directories(${LIBREOFFICE_SDK_INCLUDE_DIRS})
link_directories(${LIBREOFFICE_SDK_LIB_DIRS})

if (WIN32)
  find_package(ICU COMPONENTS dt in io le lx tu uc REQUIRED)
else (WIN32)
  find_package(ICU COMPONENTS data i18n io le lx tu uc REQUIRED)
endif (WIN32)
include_directories(${ICU_INCLUDE_DIRS})

find_package(ImageMagick COMPONENTS Magick++ REQUIRED)
include_directories(${ImageMagick_Magick++_INCLUDE_DIRS})
find_package(ImageMagick COMPONENTS MagickWand REQUIRED)
include_directories(${ImageMagick_MagickWand_INCLUDE_DIRS})
find_package(ImageMagick COMPONENTS MagickCore REQUIRED)
include_directories(${ImageMagick_MagickCore_INCLUDE_DIRS})


if (NOT WIN32)
  string(REPLACE "lib64" "lib" ImageMagick_Magick++_LIBRARY ${ImageMagick_Magick++_LIBRARY})
  string(REPLACE "lib64" "lib" ImageMagick_MagickWand_LIBRARY ${ImageMagick_MagickWand_LIBRARY})
  string(REPLACE "lib64" "lib" ImageMagick_MagickCore_LIBRARY ${ImageMagick_MagickCore_LIBRARY})
endif (NOT WIN32)

add_definitions( -DMAGICKCORE_QUANTUM_DEPTH=16 )
add_definitions( -DMAGICKCORE_HDRI_ENABLE=0 )


find_package(XercesC REQUIRED)
include_directories(${XercesC_INCLUDE_DIR})

find_package(ZLIB REQUIRED)
include_directories(${ZLIB_INCLUDE_DIRS})

include_directories(include)
link_directories(${CMAKE_LIBRARY_OUTPUT_DIRECTORY})

# libDocxFactoryLib
set(DOCXFACTORYLIB_SRC 
    # barcode
    src/barcode/BarcodeFunc.cpp
    # console
    src/console/ConsoleException.cpp
    src/console/ConsoleUsageException.cpp
    src/console/getopt.c
    src/console/GetOptException.cpp
    src/console/InvalidArgException.cpp
    src/console/InvalidOptException.cpp
    src/console/MissingArgException.cpp
    src/console/MissingOptException.cpp
    src/console/UnexpectedArgException.cpp
    src/console/UnexpectedOptException.cpp
    # json
    src/json/JsonFunc.cpp
    src/json/JsonException.cpp
    src/json/ParseJsonException.cpp
    src/json/ParseJsonFileException.cpp
    # locale
    src/locale/IcuException.cpp
    src/locale/InvalidCodePageException.cpp
    src/locale/InvalidDateFormatException.cpp
    src/locale/InvalidDateTimeStrException.cpp
    src/locale/InvalidFirstWeekDayException.cpp
    src/locale/InvalidYearOffsetException.cpp
    src/locale/LocaleException.cpp
    src/locale/LocaleFunc.cpp 
    # math
    src/math/MathFunc.cpp
    # os
    src/os/DirNotFoundException.cpp
    src/os/FileExistsException.cpp
    src/os/FileNotFoundException.cpp
    src/os/FileNotOpenException.cpp
    src/os/FileNotRemovedException.cpp
    src/os/InvalidFileUrlException.cpp
    src/os/OsException.cpp
    src/os/OsFunc.cpp
    src/os/PathMissingExtException.cpp
    src/os/PathMissingFileException.cpp
    src/os/UnsupportedFileTypeException.cpp
    # parser
    src/parser/ParserException.cpp
    src/parser/ParserFunc.cpp
    src/parser/UnclosedBracketException.cpp
    src/parser/UnexpectedBracketException.cpp
    src/parser/UnmatchedQuoteException.cpp
    # str
    src/str/StrEntries.cpp
    src/str/StrFunc.cpp
    # time
    src/time/TimeFunc.cpp  
    # util
    src/util/ArgTypeMismatchException.cpp
    src/util/DocxFactoryException.cpp
    src/util/DocxFactoryTimer.cpp
    src/util/GeneralException.cpp
    #src/util/OsNotCompatibleException.cpp
    src/util/UnknownException.cpp 
    # xml
    src/xml/AsciiToXMLCh.cpp
    src/xml/DomException.cpp
    src/xml/InvalidXmlPathException.cpp
    src/xml/NodeNotFoundException.cpp
    src/xml/ParseXmlException.cpp
    src/xml/ParseXmlFileException.cpp
    src/xml/StrToXMLCh.cpp
    src/xml/Utf8ToXMLCh.cpp
    src/xml/XmlException.cpp
    src/xml/XmlFunc.cpp
    src/xml/XmlInitializer.cpp
    src/xml/XmlTreeDriller.cpp
    # zip
    src/zip/FileInfo.cpp
    src/zip/MinizipException.cpp
    src/zip/UnzipFile.cpp
    src/zip/ZipException.cpp
    src/zip/ZipFile.cpp
    src/zip/ZipFileNotOpenException.cpp
    src/zip/ZipFunc.cpp
    src/zip/ZipStreamNotOpenException.cpp
    src/zip/ZipStreamOpenException.cpp
)

if (NOT WIN32)
  set(DOCXFACTORYLIB_SRC ${DOCXFACTORYLIB_SRC} 
      # unix
      src/unix/UnixFunc.cpp
  )
else(NOT WIN32)
  set(DOCXFACTORYLIB_SRC ${DOCXFACTORYLIB_SRC} 
      # win
      src/win/WinFunc.cpp
  )
endif (NOT WIN32)


add_library(DocxFactoryLib SHARED ${DOCXFACTORYLIB_SRC})
target_link_libraries(DocxFactoryLib 
${ZINT_LIBRARIES} 
${ICU_LIBRARIES} 
${ImageMagick_Magick++_LIBRARY} ${ImageMagick_MagickWand_LIBRARY} ${ImageMagick_MagickCore_LIBRARY} 
${XercesC_LIBRARY} 
${ZLIB_LIBRARIES}
${MINIZIP_LIBRARIES}
)

link_directories(${CMAKE_CURRENT_BINARY_DIR})

# libUnoUtil
set(UNOUTIL_SRC
    src/UnoUtil/PropertyMap.cpp
    src/UnoUtil/UnoException.cpp
    src/UnoUtil/UnoUtilImpl.cpp
)
set_source_files_properties(src/UnoUtil/UnoUtilImpl.cpp PROPERTIES COMPILE_FLAGS "-DUNX -DGCC -DLINUX -DCPPU_ENV=gcc3")

add_library(UnoUtil SHARED ${UNOUTIL_SRC})
target_link_libraries(UnoUtil
${LIBREOFFICE_SDK_LIBRARIES}
DocxFactoryLib
)
add_dependencies(UnoUtil DocxFactoryLib)
# libDocxFactory
set(DOCXFACTORY_SRC
    # ConverterPrinter
    src/ConverterPrinter/ConversionNotSupportedException.cpp 
    src/ConverterPrinter/ConverterPrinter.cpp 
    src/ConverterPrinter/ConverterPrinterException.cpp 
    src/ConverterPrinter/ExportFormatNotSupportedException.cpp 
    src/ConverterPrinter/ExportFormatNotSupportedException.cpp 
    src/ConverterPrinter/GradeGroup.cpp
    src/ConverterPrinter/OdfConverterUtil.cpp
    src/ConverterPrinter/OleException.cpp 
    src/ConverterPrinter/OpenOfficeUtil.cpp 
    src/ConverterPrinter/PrintingNotSupportedException.cpp 
    src/ConverterPrinter/UtilFailedException.cpp 
    src/ConverterPrinter/UtilNotFoundException.cpp
    # opc
    src/opc/ContentTypeNotFound.cpp
    src/opc/OpcContentTypes.cpp
    src/opc/OpcException.cpp
    src/opc/OpcFunc.cpp
    src/opc/OpcImageCache.cpp
    src/opc/OpcImageFile.cpp
    src/opc/OpcPackage.cpp
    src/opc/OpcPart.cpp
    src/opc/OpcRelationship.cpp
    src/opc/OpcRelationships.cpp
    src/opc/PartNotFoundException.cpp
    src/opc/PartTypeNotFoundException.cpp
    # WordProcessing
    src/WordProcessingCompiler/dfwc.cpp
    src/WordProcessingMerger/dfw.cpp
    src/WordProcessingMerger/WordProcessingException.cpp
    src/WordProcessingMerger/InvalidMergeDataException.cpp
    src/WordProcessingMerger/InvalidItemNameException.cpp
    src/WordProcessingMerger/TemplateNotLoadedException.cpp
    src/WordProcessingMerger/CompileVersionMismatchException.cpp
    # DocxCompiler
    src/DocxCompiler/DocxCompilerAltChunkField.cpp
    src/DocxCompiler/DocxCompilerBarcodeField.cpp
    src/DocxCompiler/DocxCompilerBooleanField.cpp
    src/DocxCompiler/DocxCompilerBookmark.cpp
    src/DocxCompiler/DocxCompilerDateTimeField.cpp
    src/DocxCompiler/DocxCompilerField.cpp
    src/DocxCompiler/DocxCompilerFile.cpp
    src/DocxCompiler/DocxCompilerItem.cpp
    src/DocxCompiler/DocxCompilerItemFile.cpp
    src/DocxCompiler/DocxCompilerItemGroup.cpp
    src/DocxCompiler/DocxCompilerItemLayout.cpp
    src/DocxCompiler/DocxCompilerNumberField.cpp
    src/DocxCompiler/DocxCompilerPicField.cpp
    src/DocxCompiler/DocxCompilerStyle.cpp
    src/DocxCompiler/DocxCompilerStyleFile.cpp
    src/DocxCompiler/DocxCompilerSettingsFile.cpp
    src/DocxCompiler/DocxCompilerTableStyle.cpp
    src/DocxCompiler/DocxCompilerTextField.cpp
    src/DocxCompiler/DocxCompilerXmlString.cpp
    src/DocxCompiler/DocxCompilerId.cpp
    src/DocxCompiler/DocxCompilerChartField.cpp
    src/DocxCompiler/DocxCompilerChartFieldSeries.cpp
    src/DocxCompiler/DocxCompilerChartFieldSingleSeries.cpp
    src/DocxCompiler/DocxCompilerChartFieldFixedSeries.cpp
    src/DocxCompiler/DocxCompilerChartFieldXY.cpp
    src/DocxCompiler/DocxCompilerChartFieldXYSize.cpp
    # DocxMerger
    src/DocxMerger/DocxMergerAltChunkField.cpp
    src/DocxMerger/DocxMergerBarcodeField.cpp
    src/DocxMerger/DocxMergerBooleanField.cpp
    src/DocxMerger/DocxMergerDateTimeField.cpp
    src/DocxMerger/DocxMergerException.cpp
    src/DocxMerger/DocxMergerField.cpp
    src/DocxMerger/DocxMergerFile.cpp
    src/DocxMerger/DocxMergerSettingsFile.cpp
    src/DocxMerger/DocxMergerItem.cpp
    src/DocxMerger/DocxMergerItemFile.cpp
    src/DocxMerger/DocxMergerItemGroup.cpp
    src/DocxMerger/DocxMergerItemLayout.cpp
    src/DocxMerger/DocxMergerNumberField.cpp
    src/DocxMerger/DocxMergerPasteAltChunkField.cpp
    src/DocxMerger/DocxMergerPasteBarcodeField.cpp
    src/DocxMerger/DocxMergerPasteBooleanField.cpp
    src/DocxMerger/DocxMergerPasteDateTimeField.cpp
    src/DocxMerger/DocxMergerPasteField.cpp
    src/DocxMerger/DocxMergerPasteFieldGroup.cpp
    src/DocxMerger/DocxMergerPasteItem.cpp
    src/DocxMerger/DocxMergerPasteItemGroup.cpp
    src/DocxMerger/DocxMergerPasteNumberField.cpp
    src/DocxMerger/DocxMergerPastePicField.cpp
    src/DocxMerger/DocxMergerPasteTextField.cpp
    src/DocxMerger/DocxMergerPicField.cpp
    src/DocxMerger/DocxMergerTextField.cpp
    src/DocxMerger/DocxMergerXmlString.cpp
    src/DocxMerger/DocxMergerId.cpp
    src/DocxMerger/DocxMergerChartField.cpp
    src/DocxMerger/DocxMergerChartFieldSeries.cpp
    src/DocxMerger/DocxMergerChartFieldSingleSeries.cpp
    src/DocxMerger/DocxMergerChartFieldFixedSeries.cpp
    src/DocxMerger/DocxMergerChartFieldXY.cpp
    src/DocxMerger/DocxMergerChartFieldXYSize.cpp
    src/DocxMerger/DocxMergerChartAxis.cpp
    src/DocxMerger/DocxMergerChartAxisText.cpp
    src/DocxMerger/DocxMergerChartAxisNumber.cpp
    src/DocxMerger/DocxMergerChartAxisDateTime.cpp
    src/DocxMerger/DocxMergerChartValues.cpp
    src/DocxMerger/DocxMergerPasteChartField.cpp
    src/DocxMerger/DocxMergerPasteChartFieldSeries.cpp
    src/DocxMerger/DocxMergerPasteChartFieldSingleSeries.cpp
    src/DocxMerger/DocxMergerPasteChartFieldFixedSeries.cpp
    src/DocxMerger/DocxMergerPasteChartFieldXY.cpp
    src/DocxMerger/DocxMergerPasteChartFieldXYSize.cpp
    src/DocxMerger/DocxMergerPasteChartAxis.cpp
    src/DocxMerger/DocxMergerPasteChartAxisText.cpp
    src/DocxMerger/DocxMergerPasteChartAxisNumber.cpp
    src/DocxMerger/DocxMergerPasteChartAxisDateTime.cpp
    src/DocxMerger/DocxMergerPasteChartValues.cpp
)
if (WIN32)
set(DOCXFACTORY_SRC ${DOCXFACTORY_SRC}
    src/ConverterPrinter/MsExcelUtil.cpp
    src/ConverterPrinter/MsOfficeUtil.cpp
    src/ConverterPrinter/MsWordUtil.cpp
)
endif (WIN32)
add_library(DocxFactory SHARED ${DOCXFACTORY_SRC})
target_link_libraries(DocxFactory 
UnoUtil
${CMAKE_DL_LIBS}
)
add_dependencies(DocxFactory UnoUtil)

# word-processing-merger
set(WORD_PROCESSING_MERGER_SRC
    src/WordProcessingCompiler/word-processing-compiler.cpp
)
add_executable(word-processing-merger ${WORD_PROCESSING_MERGER_SRC})
target_link_libraries(word-processing-merger
DocxFactory
)
add_dependencies(word-processing-merger DocxFactory)

# word-processing-compiler
set(WORD_PROCESSING_COMPILER_SRC
    src/WordProcessingCompiler/word-processing-compiler.cpp
)
add_executable(word-processing-compiler ${WORD_PROCESSING_COMPILER_SRC})
target_link_libraries(word-processing-compiler
DocxFactory
)
add_dependencies(word-processing-merger DocxFactory)