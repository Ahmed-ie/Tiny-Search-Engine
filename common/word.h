#ifndef __WORD_H
#define __WORD_H

/**************** normalizeWord() ****************/
/* Convert all characters in a word to lowercase.
 *
 * Caller provides:
 *   valid pointer to a string.
 * We guarantee:
 *   The string's characters will be converted to lowercase.
 * Note:
 *   If the provided pointer is NULL, no action will be taken.
 */
void normalizeWord(char *word);

#endif // __WORD_H
