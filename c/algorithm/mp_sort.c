#include<stdio.h>

void mp_sort(int array[], int length){
  int swap_buffer, i, max_tail, flag = length - 1;
	while(flag > 0){
		max_tail = flag;
		flag = 0;
	  for(i=0;i<max_tail;i++){
		  if(array[i] > array[i+1]){
			  swap_buffer = array[i];
				array[i] = array[i+1];
				array[i+1] = swap_buffer;
				flag = i;
			}
		}
	}
}

void print_array(int array[],int length){
  int i;
	for(i=0;i<length;i++)
		printf("%d ", array[i]);
  printf("\n");
}

int main(){
  int i;
  int a[10] = {2,5,4,7,9,8,7,1,3,10};
  int b[10] = {1,2,3,4,5,6,7,8,9,10};
  int c[10] = {10,9,8,7,6,5,4,3,2,1};
	mp_sort(a,10);
	print_array(a, 10);

	mp_sort(b,10);
	print_array(b, 10);

	mp_sort(c,10);
	print_array(c, 10);
	return 0;
}
