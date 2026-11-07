/*
 * pamiec.c
 *
 *  Created on: 7 lis 2026
 *      Author: Zofia Kozłowska
 */
#include "pamiec.h"
Nagranie nagrania[MAX_NAGRAN];
uint32_t liczbaNagran = 0;

uint32_t Pamiec_RozmiarNagrania(Nagranie nagranie)
{
    return nagranie.liczbaProbek * AUDIO_SAMPLE_SIZE;
}

uint32_t Pamiec_NastepnyAdres(Nagranie nagranie)
{
    return nagranie.adres + Pamiec_RozmiarNagrania(nagranie);
}

uint32_t Pamiec_DodajNagranie(uint32_t liczbaProbek)
{
    if (liczbaNagran >= MAX_NAGRAN || liczbaProbek == 0)
    {
        return 0;
    }

    uint32_t adres = FLASH_AUDIO_START;

    if (liczbaNagran > 0)
    {
        adres = Pamiec_NastepnyAdres(nagrania[liczbaNagran - 1]);
    }

    if (adres >= FLASH_SIZE_CALC ||
        liczbaProbek > (FLASH_SIZE_CALC - adres) / AUDIO_SAMPLE_SIZE)
    {
        return 0;
    }

    nagrania[liczbaNagran].adres = adres;
    nagrania[liczbaNagran].liczbaProbek = liczbaProbek;

    liczbaNagran++;

    return 1;
}
