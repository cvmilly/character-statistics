# character-statistics
c++ program that collects the statistics of word, number, and character usage in a file 

In the main function, the program reads the input until it reaches the end, counting the number of times each word, number, and character is used.
-A word is defined as a sequence of letters
-Words are case insensitive
-A number is defined as a sequence of digits 
-Both numbers and words are separated by numbers or other non-letter and non-digit characters

The program outputs the ten most used characters (case sensitive), the ten most used numbers, and the ten most used words (case insensitive) as well as the number of times these characters/numbers/words are used. The characters, numbers and words are outputted in descending order based on the number of times they are used.

**When two words (numbers) happen in the same number of times, the word (number) that occurs earlier in the input is considered as being used more frequently. When two characters happen in the same number of times, the character with a smaller ASCII value is considered as being used more frequently.  
