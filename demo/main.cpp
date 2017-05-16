#include <iostream>
#include <fstream>
#include "lib/subtitle-parser/SubtitleParserFactory.h"
#include "lib/subtitle-parser/SubtitleParser.h"
using namespace std;

int main(int argc, char *argv[]) {

    // If filename not provided
    if(argc < 2) {
        cout << "Please pass the filename as an argument: ./a.out filename.srt\n";
        return 0;
    }

    SubtitleParserFactory *subParserFactory = new SubtitleParserFactory(argv[1]);
    SubtitleParser *parser = subParserFactory->getParser();

    std::vector<SubtitleItem*> sub = parser->getSubtitles();

    ofstream myfile;
    myfile.open ("out.srt");

    for(SubtitleItem * element : sub)
    {
        myfile<<"start : "<<element->getStartTime()<<endl;
        myfile<<"end : "<<element->getEndTime()<<endl;
        myfile<<"text : "<<element->getText()<<endl;
        myfile<<"justDialogue : "<<element->getDialogue()<<endl;
        myfile<<"speakerCount : "<<element->getSpeakerCount()<<endl;

        if(element->getSpeakerCount())
        {
            std::vector<std::string> name = element->getSpeakerNames();
            for(std::string display : name)
                myfile<<"speakers : "<<display<<", ";
            myfile<<endl;
        }
        myfile<<"ignore : "<<element->getIgnoreStatus()<<endl;
        myfile<<"____________________________________________"<<endl<<endl;
    }

    return 0;
}