///////////////////////// TO-DO (1) //////////////////////////////
  /// Include necessary header files
  /// Hint:  Include what you use, use what you include
  ///
  /// Do not put anything else in this section, i.e. comments, classes, functions, etc.  Only #include directives
#include "WordFrequency.hpp"
/////////////////////// END-TO-DO (1) ////////////////////////////







// unnamed, anonymous namespace providing non-member private working area
namespace
{
  std::string sanitize( const std::string & word )
  {
    constexpr char bad_char[] = " \t\n\b\v_-\"'(){}+/*,=.!?:;";            // leading and trailing characters to be removed
    static std::locale locality;

    auto startIndex = word.find_first_not_of( bad_char );                  // start with the first non-bad character
    if( startIndex == std::string::npos ) startIndex = word.size();        // if the word contains only bad characters ...

    std::size_t count    = 0;                                              // assume the word contains only bad characters ...
    auto        endIndex = word.find_last_not_of( bad_char );              // end with the first non-bad character

    if( endIndex != std::string::npos ) count = endIndex - startIndex + 1; // number of characters to use in results

    auto result = word.substr( startIndex, count );                        // strip the leading and trailing bad characters
    for( auto & c : result ) c = std::tolower( c, locality );              // convert to lower case

    return result;
  }
}  // unnamed, anonymous namespace







// Implement WordFrequency::WordFrequency( std::istream ) - See requirements
///////////////////////// TO-DO (2) //////////////////////////////
WordFrequency::WordFrequency( std::istream & iStream )
{
  std::string words;
  while(iStream >> words)
  {
    ++frequency[sanitize(words)];
  } 
}
/////////////////////// END-TO-DO (2) ////////////////////////////







// Implement WordFrequency::numberOfWords() const - See requirements
///////////////////////// TO-DO (3) //////////////////////////////
std::size_t WordFrequency::numberOfWords() const
{
  return frequency.size();
}
/////////////////////// END-TO-DO (3) ////////////////////////////







// Implement WordFrequency::wordCount( const std::string & ) const - See requirements
///////////////////////// TO-DO (4) //////////////////////////////
std::size_t WordFrequency::wordCount( const std::string & word) const
{
  std::unordered_map<std::string, int>::const_iterator getWord = frequency.find(sanitize(word));
  if (getWord == frequency.end())
  {
    return 0;
  }
  else
  {
    return getWord->second;
  }
}

/////////////////////// END-TO-DO (4) ////////////////////////////







// Implement WordFrequency::mostFrequentWord() const - See requirements
///////////////////////// TO-DO (5) //////////////////////////////
std::string WordFrequency::mostFrequentWord() const
{
  int value = 0;                   //Stores the amount of times the most frequent word occurs.
  std::string mostFrequent = "";   //Stores the most frequent word.
  
  if (frequency.empty() == true)
  {
    return "";
  }
  else
  {
    for (auto word : frequency)
    {
      if (word.second > value)
      {
        mostFrequent = sanitize(word.first);
        value = word.second;
      }
    }
  }
  return mostFrequent;
}
/////////////////////// END-TO-DO (5) ////////////////////////////







// Implement WordFrequency::maxBucketSize() const - See requirements
///////////////////////// TO-DO (6) //////////////////////////////
  /// Hint: see the unordered_map's bucket interface at https://en.cppreference.com/w/cpp/container/unordered_map
std::size_t WordFrequency::maxBucketSize() const
{
  unsigned long bucket = frequency.bucket_count();
  std::size_t currentMax = 0;
  for (std::size_t i = 0; i < bucket; ++i)
  {
    if(frequency.bucket_size(i) >= currentMax)
    {
      currentMax = frequency.bucket_size(i);
    }
  }
  return currentMax;
}
/////////////////////// END-TO-DO (6) ////////////////////////////
