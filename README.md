# mwl-parser

This is my ongoing attempt at writing an intermediate C++ representation for Lunar Magic's MWL file format. If/after this parser is implemented,
I would like to write an MWL <-> YAML/JSON/other text format converter in order to allow level data to be more easily tracked and merged with git
as well as making it generally easier to programmatically generate level data or interface with it in a higher level way than operating on plain bytes.
Since parts of MWL data are relatively similar or identical to the actual ROM level data, this could also potentially aid in the development of alternative
SMW editors.

Parsing the format is challenging as the documentation of both the MWL format and level data is outdated and incomplete, which is why progress has been
very slow. I'm explicitly making this repo public in case anyone else feels like contributing or carrying on with this undertaking.

So far, this library provides functionality for parsing the header, data pointers, palette data, ExAnimation data and bypass information of an MWL into 
C++ classes and converting from those C++ classes back to the original bytes.

Sadly, the other sections of the format are either a lot of work to parse (i.e. object data) or require further research because the documentation is outdated.

I'm getting most of my information about the format from these sources:

- [MWL File Format](https://github.com/kaizoman666/SMW-Data/blob/master/Misc/MWL%20File%20Format.md)
- [Level Data Format](https://smwspeedruns.com/index.php/Level_Data_Format)

The solution uses Visual Studio 2022 and consists of a library and a test project.
