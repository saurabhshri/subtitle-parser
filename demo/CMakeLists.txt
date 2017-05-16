cmake_minimum_required(VERSION 3.6)
project(srtExtract)

set(CMAKE_CXX_STANDARD 11)

include_directories(/lib/ /lib/subtitle-parser/)
include_directories(/lib/subtitle-parser/)

set(SOURCE_FILES main.cpp lol.cpp /subtitle-parser/ lib/subtitle-parser/subparser.cpp lib/subtitle-parser/SubRipParser.cpp lib/subtitle-parser/SubtitleItem.cpp lib/subtitle-parser/SubtitleParserFactory.cpp lib/subtitle-parser/SubtitleParser.cpp lib/subtitle-parser/SubtitleWord.cpp)
add_executable(srtExtract ${SOURCE_FILES} ${PARSER} lol.cpp)