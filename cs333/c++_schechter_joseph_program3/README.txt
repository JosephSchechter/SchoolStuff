minimal proof of O(N):

N being the number of characters, I read in each character once, and as I read each letter in, I keep track of the size of the words in a linked list. The overhead is constant*N: O(N)

I then copy all of that information from the linked linked list into an array. To copy all of the characters and their corresponding info: O(N)


I then call my recursive string sorting method
I go through and count each letter in a specific place once (I eventually will count all of the N characters once in some inner recursive call): O(N)

The counting-sort part of sorting per character place (trackingArray) is done in constant time due to the fact there can only be 53 different character possibilities: O(1)

Backing up the array is done in a fraction of N: O(N)

Putting the words in the correct order per round is a fraction of the words that gets smaller with each recursive call. Each move corresponds to a particular letter, so it i is O(N) and shrinking since I split the array of words into different pieces depending on what letter/letter-position we looked at. I dont even count all letters. If it is a word that starts with a letter, and is the only word starting with that letter, I don't sort that string anymore.

The actual recursive call is at most a fraction of N since it just goes through the counting array and then calls the function on a section of the whole array: O(N)

printing out the list in the end is a fraction of N, at most all N: O(N)

The biggest asymtotic value is O(N), therefore it is an O(N) program, with N being the total number of characters.
