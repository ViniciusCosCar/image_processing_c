int img_ascii(unsigned char *data, int datasize){
	if(datasize<0) return 0;

	// https://paulbourke.net/dataformats/asciiart/
	// char illumination[] = "$@B%8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/()1{}[]?-_+~<>i!lI;:,`'. ";
	char illumination[] = "@%#*+=-:. ";
	int scale_div = sizeof(illumination)/sizeof(char);

	for(int i=0; i<datasize; i++)
		data[i]=illumination[(int) (data[i]*(scale_div-1))/255];

	return 1;
}
