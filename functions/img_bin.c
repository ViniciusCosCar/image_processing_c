char img_bin(unsigned char *data, int datasize, unsigned char limiar){
	if(datasize<0) return 0;

	for(int i=0; i<datasize; i++)
		if(data[i]<limiar) data[i]=0;

	return 1;
}
