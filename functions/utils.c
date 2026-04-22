void invert(unsigned char* e1, unsigned char* e2){
	unsigned char aux = *e1;
	*e1 = *e2;
	*e2 = aux;
}
int invert_array(unsigned char *array,int size){
	if(!array || size<0) return 0;

	for(int i=0,j=size-1; i<j; i++,j--){
		invert(&array[i],&array[j]);
	}
	return 1;
}

