#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <iomanip>
#include <functional>
#include <string>

using namespace std;

// struct determines word type, how often it appears, and the order of which it appears
struct word_type
{
  string word;                  
  int frequency;
  int order;
};

typedef word_type word_type;

// based on ASCII values to determine which category they belong to
bool isDigit(int c);
bool isLetter(int c);
bool isOther(int c);
bool isUpper(int c);
bool isNonPrintable(int c);

size_t GetLongestChar(std::map<int, int> &tmpChars);
size_t GetLongestKey(std::vector<word_type> &tmpWords); 
void ParseInput(std::vector<word_type> &tmpWords, std::vector<word_type> &tmpNumbers, std::map<int, int> &tmpChars);

// prints based off of word type
void PrintWords(std::vector<word_type> &tmpWords);
void PrintNumbers(std::vector<word_type> &tmpNumbers);
void PrintCharacters(std::map<int,int> &tmpChars);

int CountCharacters(std::map<int,int> &tmpChars);


// if amount of times word appears is the same, then it is sorted by the order
bool sortdesc(const word_type &a, const word_type &b)
{

  if(a.frequency==b.frequency)
    return (a.order<b.order);
  return (a.frequency>b.frequency);
}



std::vector<word_type>::iterator find(vector<word_type> &vect, string str)
{
  std::vector<word_type>::iterator it;

  for (it = vect.begin(); it != vect.end(); ++it)
    {
      if (str == it->word)
	{
	  break;
	}
    }
  return it;
}



void insert_to_vector(std::vector<word_type>& vect, const word_type& item, int& order)
{
  std::vector<word_type>::iterator it;
  word_type elem = item;

  it = find(vect, elem.word);
  if (it != vect.end())
    {
      it->frequency++;
    }
  else
    {
      order++;
      elem.frequency++;
      elem.order = order;
      vect.push_back(elem);
    }
}


bool isDigit(int c)
{
  return (c>=48 && c<=57)?true:false;
}




bool isLetter(int c)
{
  return ((c>=65 && c<=90) || (c>=97 && c<=122))?true:false;
}



bool isOther(int c)
{
  return !(isDigit(c) ||isLetter(c));
}



bool isUpper(int c)
{
  return (c >= 65 && c <= 90) ? true : false;
}



bool isNonPrintable(int c)
{
  return ((c >= 0 && c <= 31) || (c == 127)) ? true : false;
}



size_t GetLongestChar(std::map<int, int> &tmpChars)
{
  size_t max_len = 1;

  for (auto const& pair : tmpChars)
    {
      if (pair.first == 9 || pair.first == 10)
	{
	  max_len = 2;
	  break;
	}
    }

  return max_len;
}


size_t GetLongestKey(std::vector<word_type> &tmpWords)
{
  size_t max_len = 0;

  for (auto const& item : tmpWords)
    {
      if (max_len < item.word.size())
	{
	  max_len = item.word.size();
	}
    }

  return max_len;
}


int CountCharacters(std::map<int, int> &tmpChars)
{
  int cnt = 0;

  for (auto const &pair : tmpChars)
    {
      if (pair.second > 0)
	{
	  cnt++;
	}
    }

  return cnt;
}



// convert a std::map<K,V> to std::multimap<V,K>
template<typename K, typename V>
std::multimap<V,K,greater<V>>InvertMap(std::map<K,V>const &tmpMap)
{
  std::multimap<V,K,greater<V>> tmpMultimap;

  for(auto const &pair:tmpMap)
    {
      tmpMultimap.insert(std::make_pair(pair.second,pair.first));
    }

  return tmpMultimap;
}



void ParseInput(std::vector<word_type> &tmpWords, std::vector<word_type > &tmpNumbers, std::map<int, int> &tmpChars)
{
  int ch, numOfWords = 0, numOfNumbers = 0;
  std::string str = "";
  std::string tmp;

  word_type tmp_w;

  ch = cin.get();
  int state = 0;

  while (1)
    {
      if (ch != EOF)
	{
	  tmpChars[ch] = tmpChars[ch] + 1;
	}

      // convert to lowercase
      if (isUpper(ch))
	{
	  ch = ch + 32;
	}

      tmp = (char)ch;

      switch (state)
	{
	case 0:
	  str = tmp;
	  if (isDigit(ch))
	    {
	      state = 1;
	    }
	  else if (isLetter(ch))
	    {
	      state = 2;
	    }
	  else if (isOther(ch))
	    {
	      state = 3;
	    }
	  else if (ch == EOF)
	    {
	      state = 4;
	    }
	  break;
	case 1:
	  if (isDigit(ch))
	    {
	      str.append(tmp);
	      state = 1;
	    }
	  else if (isLetter(ch))
	    {
	      tmp_w = { str, 0, 0 };
	      insert_to_vector(tmpNumbers, tmp_w, numOfNumbers);
	      str = tmp;
	      state = 2;
	    }
	  else if (isOther(ch))
	    {
	      tmp_w = { str, 0, 0 };
	      insert_to_vector(tmpNumbers, tmp_w, numOfNumbers);
	      str = tmp;
	      state = 3;
	    }
	  else if (ch == EOF)
	    {
	      state = 4;
	    }
	  break;
	case 2:
	  if (isDigit(ch))
	    {
	      tmp_w = { str, 0, 0 };
	      insert_to_vector(tmpWords, tmp_w, numOfWords);
	      str = tmp;
	      state = 1;
	    }
	  else if (isLetter(ch))
	    {
	      str.append(tmp);
	    }
	  else if (isOther(ch))
	    {
	      tmp_w = { str, 0, 0 };
	      insert_to_vector(tmpWords, tmp_w, numOfWords);
	      str = tmp;
	      state = 3;
	    }
	  else if (ch == EOF)
	    {
	      state = 4;
	    }
	  break;
	case 3:
	  if (isDigit(ch))
	    {
	      str = tmp;
	      state = 1;
	    }
	  if (isLetter(ch))
	    {
	      str = tmp;
	      state = 2;
	    }
	  if (isOther(ch))
	    {
	      state = 3;
	    }
	  if (ch == EOF)
	    {
	      state = 4;
	    }
	  break;
	}

      if (state == 4)
	{
	  break;
	}

      ch = cin.get();
    }

  return;
}


void PrintWords(std::vector<word_type> &tmpWords)
{
  int cnt1 = 0, cnt2 = 10;
  int total = (int)tmpWords.size();

  if (total < cnt2)
    {
      cnt2 = total;
    }

  cout << "\nTotal " << total << " different words, " << cnt2 << " most used words:" << endl;

  size_t len = GetLongestKey(tmpWords) + 5;

  sort(tmpWords.begin(), tmpWords.end(), sortdesc);

  for (auto const& item : tmpWords)
    {
      cout << "No. " << cnt1 << ": ";
      cout << left << setw(len) << item.word;
      cout << item.frequency << endl;

      if (cnt1 < cnt2 - 1)
	{
	  cnt1++;
	}
      else
	{
	  break;
	}
    }
}


void PrintNumbers(std::vector<word_type> &tmpNumbers)
{
  int cnt1 = 0, cnt2 = 10;
  int total = (int)tmpNumbers.size();

  if (total < cnt2)
    {
      cnt2 = total;
    }

  cout << "\nTotal " << total << " different numbers, " << cnt2 << " most used numbers:" << endl;

  size_t len = GetLongestKey(tmpNumbers) + 5;

  sort(tmpNumbers.begin(), tmpNumbers.end(), sortdesc);

  for (auto const& item : tmpNumbers)
    {
      cout << "No. " << cnt1 << ": ";
      cout << left << setw(len) << item.word;
      cout << item.frequency << endl;

      if (cnt1 < cnt2 - 1)
	{
	  cnt1++;
	}
      else
	{
	  break;
	}
    }
}


void PrintCharacters(std::map<int, int> &tmpChars)
{
  int cnt1 = 0, cnt2 = 10;
  int total = CountCharacters(tmpChars);

  if (total < cnt2)
    {
      cnt2 = total;
    }

  cout << "\nTotal " << total << " different characters, " << cnt2 << " most used characters:" << endl;

  size_t len = GetLongestChar(tmpChars) + 5;

  // invert map
  std::multimap<int, int, greater<int>> mymp = InvertMap(tmpChars);

  for (auto const &pair : mymp)
    {
      if (isNonPrintable(pair.second))
	{
	  if (pair.second == 10)
	    {
	      cout << "No. " << cnt1 << ": ";
	      cout << left << setw(len) << "\\n";
	      cout << pair.first << endl;
	    }
	  else if (pair.second == 9)
	    {
	      cout << "No. " << cnt1 << ": ";
	      cout << left << setw(len) << "\\t";
	      cout << pair.first << endl;
	    }
	  else
	    {
	      // ignore non-printable characters
	    }
	}
      else
	{
	  cout << "No. " << cnt1 << ": ";
	  cout << left << setw(len) << (char)pair.second;
	  cout << pair.first << endl;
	}

      if (cnt1 < cnt2 - 1)
	{
	  cnt1++;
	}
      else
	{
	  break;
	}
    }
}



int main()
{
  std::map<int, int> characters;
  std::vector<word_type> words;
  std::vector<word_type> numbers;

  for (int k = 0; k < 128; ++k)
    {
      characters.insert({ k, 0 });
    }

  ParseInput(words, numbers, characters);

  PrintCharacters(characters);
  PrintWords(words);
  PrintNumbers(numbers);

  return 0;
} 
