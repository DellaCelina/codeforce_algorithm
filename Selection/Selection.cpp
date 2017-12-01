#include "Selection.h"

/*
*locationÀº 1ºÎÅÍ
*/
uint selection(uint loc, uint arr[], uint len) {
	uint* tmpArr = NULL;
	if (loc > len) return 0;
	if (len == 1) return arr[0];
	if (len == 2) {
		if (arr[0] <= arr[1])
			return (loc == 1) ? arr[0] : arr[1];
		else
			return (loc == 1) ? arr[1] : arr[0];
	}
	tmpArr = (uint*)malloc(len * sizeof(uint));
	if (len < 5) {
		uint mid = mediam(arr, tmpArr, len);
		ret_recursive(loc, mid, len, tmpArr);
	}
	else {
		uint* midArr = (uint*)malloc(len / 5 * sizeof(uint));
		uint midStar;
		uint mid;
		arr_reloc(arr, len);
		for (uint i = 0; i < len / 5; i++) {
			midArr[i] = arr[i * 5];
		}
		midStar = selection(len / 10 + 1, midArr, len / 5);
		free(midArr);
		mid = init_tmpArr(arr, tmpArr, len, midStar);
		ret_recursive(loc, mid, len, tmpArr);
	}
}

uint mediam(uint arr[], uint tmpArr[], uint len)
{
	for (uint i = 0; i < len; i++) {
		tmpArr[i] = arr[i];
	}
	if (len == 3) {
		if (tmpArr[0] > tmpArr[1]) swap(tmpArr[0], tmpArr[1]);
		if (tmpArr[1] > tmpArr[2]){
			if (tmpArr[0] <= tmpArr[2]) swap(tmpArr[1], tmpArr[2]);
			else {
				swap(tmpArr[1], tmpArr[2]);
				swap(tmpArr[0], tmpArr[1]);
			}
			return 2;
		}
		return 2;
	}
	else if (len == 4) {
		if (tmpArr[0] > tmpArr[1]) swap(tmpArr[0], tmpArr[1]);
		if (tmpArr[2] > tmpArr[3]) swap(tmpArr[2], tmpArr[3]);
		if (tmpArr[1] <= tmpArr[3]) {
			if (tmpArr[1] > tmpArr[2]) {
				swap(tmpArr[1], tmpArr[2]);
				if (tmpArr[0] > tmpArr[1]) swap(tmpArr[0], tmpArr[1]);
			}
		}
		else {
			swap(tmpArr[1], tmpArr[3]);
			if (tmpArr[0] > tmpArr[1]) swap(tmpArr[0], tmpArr[2]);
			else {
				swap(tmpArr[1], tmpArr[2]);
				if (tmpArr[0] > tmpArr[1]) swap(tmpArr[0], tmpArr[1]);
			}
		}
		return 2;
	}
}

void arr_reloc(uint arr[], uint len)
{
	uint len_last = len / 5 * 5;
	for (uint i = 0; i < len_last; i += 5) {
		_arr_reloc(arr + i);
	}
}

void _arr_reloc(uint arr[])
{
	if (arr[1] > arr[3]) swap(arr[1], arr[3]);
	if (arr[2] > arr[4]) swap(arr[2], arr[4]);
	if (arr[3] > arr[4]) {
		swap(arr[3], arr[4]);
		swap(arr[1], arr[2]);
	}
	if (arr[0] > arr[2]) swap(arr[0], arr[2]);
	if (arr[2] > arr[3]) {
		swap(arr[2], arr[3]);
		swap(arr[0], arr[1]);
	}
	if (arr[1] > arr[2]) swap(arr[0], arr[1]);
	else swap(arr[0], arr[2]);
}

uint init_tmpArr(uint arr[], uint tmpArr[], uint len, uint midStar)
{
	uint len_last = len / 5 * 5;
	uint last_set_len = len % 5;
	uint lp = 0, rp = len - 1;
	uint current, mid_cnt = 0;
	for (current = 0; current < len_last; current += 5) {
		if (arr[current] < midStar) {
			tmpArr[lp++] = arr[current];
			tmpArr[lp++] = arr[current + 1];
			tmpArr[lp++] = arr[current + 2];
			if (arr[current + 3] < midStar) tmpArr[lp++] = arr[current + 3];
			else tmpArr[rp--] = arr[current + 3];
			if (arr[current + 4] < midStar) tmpArr[lp++] = arr[current + 4];
			else tmpArr[rp--] = arr[current + 4];
		}
		else if (arr[current] > midStar) {
			tmpArr[rp--] = arr[current];
			tmpArr[rp--] = arr[current + 3];
			tmpArr[rp--] = arr[current + 4];
			if (arr[current + 1] < midStar) tmpArr[lp++] = arr[current + 1];
			else tmpArr[rp--] = arr[current + 3];
			if (arr[current + 2] < midStar) tmpArr[lp++] = arr[current + 2];
			else tmpArr[rp--] = arr[current + 2];
		}
		else {
			tmpArr[lp++] = arr[current + 1];
			tmpArr[lp++] = arr[current + 2];
			tmpArr[rp--] = arr[current + 3];
			tmpArr[rp--] = arr[current + 4];
			mid_cnt++;
		}
	}
	if (last_set_len) {
		for (uint i = 0; i < last_set_len; i++) {
			if (arr[current] < midStar) tmpArr[lp++] = arr[current];
			else tmpArr[rp--] = arr[current];
			current++;
		}
	}
	for (int i = 0; i < mid_cnt; i++) {
		tmpArr[lp++] = midStar;
	}
	if (lp != rp + 1)
		return 0;
	else return lp;
}

uint ret_recursive(uint loc, uint mid, uint len, uint tmpArr[])
{
	if (loc == mid) {
		uint tmp = tmpArr[mid - 1];
		free(tmpArr);
		return tmp;
	}
	else if (loc < mid) {
		uint tmp = selection(loc, tmpArr, mid - 1);
		free(tmpArr);
		return tmp;
	}
	else {
		uint tmp = selection(loc - mid, &tmpArr[mid], len - mid);
		free(tmpArr);
		return tmp;
	}
}
