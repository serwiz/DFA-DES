#ifndef H_KEY_H
#define H_KEY_H



/**
 * Récupére la clé K16 grâce au chiffré juste et aux chiffrés faux
 * @param encrypted_message   message chiffré juste
 * @param encrypted_wrong     messages chiffrés avec fautes
 * @return  la clé K16
 **/
uint64_t generateK16(uint64_t encrypted_message, long * encrypted_wrong);

#endif