# C++ Subtitle Parser Library
LibSub-Parser - A simple C++ Subtitle Parser library.
___
#### Formats
* SubRip

#### Sample Usage

Please go to the demo directory for a functioning demo.

```cpp

	SubtitleParserFactory *subParserFactory = new SubtitleParserFactory(argv[1]);
	SubtitleParser *parser = subParserFactory->getParser();
    std::vector<SubtitleItem*> sub = parser->getSubtitles();

    ofstream myfile;
    myfile.open ("out.srt");

    for(SubtitleItem * element : sub)
    	myfile<<element->getStartTime()<<" +++ "<<element->getEndTime()<<"\n"<<element->getText()<<"\n";

    string data = parser->getFileData();
    cout<<data;
```
