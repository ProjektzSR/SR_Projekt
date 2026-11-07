/*
 * pamiec.h
 *
 *  Created on: 7 lis 2026
 *      Author: Zofia Kozłowska
 */

#ifndef INC_PAMIEC_H_
#define INC_PAMIEC_H_



#include <stdint.h>

#define AUDIO_SAMPLE_RATE 22050 //Hz
#define AUDIO_SAMPLE_SIZE 2 //16 bitów
#define FLASH_AUDIO_START 0x001000 // 4kb na informacje
#define FLASH_SIZE_CALC (128 * 1048576 / 8)
#define MAX_NAGRAN 20

typedef struct
{
    uint32_t adres;
    uint32_t liczbaProbek;
} Nagranie;


uint32_t Pamiec_RozmiarNagrania(Nagranie nagranie);

uint32_t Pamiec_NastepnyAdres(Nagranie nagranie);

uint32_t Pamiec_DodajNagranie(uint32_t liczbaProbek);



extern Nagranie nagrania[MAX_NAGRAN];
extern uint32_t liczbaNagran;

#endif /* INC_PAMIEC_H_ */
