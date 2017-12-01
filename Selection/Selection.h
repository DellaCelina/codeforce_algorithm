#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <memory>
#define swap(a, b) do{ int tmp; tmp = a; a = b; b = tmp;}while(0)

typedef unsigned int uint;

uint selection(uint loc, uint arr[], uint len);

uint mediam(uint arr[], uint tmpArr[], uint len);

void arr_reloc(uint arr[], uint len);
void _arr_reloc(uint arr[]);

uint init_tmpArr(uint arr[], uint tmpArr[], uint len, uint midStar);

uint ret_recursive(uint loc, uint mid, uint len, uint tmpArr[]);