/*
 * mikrofon.c
 *
 *  Created on: Nov 6, 2026
 *      Author: Zofia Kozłowska
 */


#include "mikrofon.h"

#define AUDIO_BUFFER_SIZE 256

//to z maina pobieramy
extern DFSDM_Filter_HandleTypeDef hdfsdm1_filter0;

int32_t audioBuffer[AUDIO_BUFFER_SIZE];

volatile uint32_t audioLevel = 0;




volatile uint32_t firstHalfReady = 0;
volatile uint32_t secondHalfReady = 0;


HAL_StatusTypeDef Mikrofon_Start(void)
{
    firstHalfReady = 0;
    secondHalfReady = 0;

    return HAL_DFSDM_FilterRegularStart_DMA(
        &hdfsdm1_filter0, audioBuffer, AUDIO_BUFFER_SIZE);
}


void Mikrofon_Process(void)
{
    uint64_t sum = 0;
    uint32_t start;



    if (firstHalfReady)
    {
        firstHalfReady = 0;
        start = 0;
    }
    else if (secondHalfReady)
    {
        secondHalfReady = 0;
        start = AUDIO_BUFFER_SIZE / 2;
    }
    else
    {
        return;
    }





    for (uint32_t i = start; i < start + AUDIO_BUFFER_SIZE / 2; i++)
    {
        int32_t sample = audioBuffer[i] >> 8;
        //przesuneliśmy o 8 bitów, bo w nim są zapisywane informacje a nie wynik

        if (sample < 0)
        {
            sample = -sample;
        }

        sum += (uint32_t)sample;
    }

    audioLevel = sum / (AUDIO_BUFFER_SIZE / 2);


}


void HAL_DFSDM_FilterRegConvHalfCpltCallback(
    DFSDM_Filter_HandleTypeDef *hdfsdm_filter)
{
    if (hdfsdm_filter == &hdfsdm1_filter0)
    {
        firstHalfReady = 1;
    }
}


void HAL_DFSDM_FilterRegConvCpltCallback(
    DFSDM_Filter_HandleTypeDef *hdfsdm_filter)
{
    if (hdfsdm_filter == &hdfsdm1_filter0)
    {
        secondHalfReady = 1;
    }
}
