/**
 *
 * Motorola S-Record Format to Binary
 *
 * @author Ru^3
 * @date 2012/10/26
 *
 * @todo AS68以外の出力ファイルは検証してない
 *
 */

#include <stdio.h>

int main(int argc, char *argv[])
{
	unsigned char c, num;
	unsigned int data, count, address, loop = 0;
	FILE *rfp, *wfp;

	printf("Motorola s19 file to binary v0.01 (c)Ru^3\n\n");

	if (argc <= 2) {
		printf("usage: s19tobin [in.s19] [out.bin]\n");
		return -1;
	}

	rfp = fopen(argv[1], "rb");
	wfp = fopen(argv[2], "w+b");

	if (!rfp || !wfp) {
		printf("file open error.\n");
		return -2;
	}

	c = fgetc(rfp);
	while (!feof(rfp))
	{
		if (c == 'S')
		{
			if (fgetc(rfp) == '1')
			{
				fscanf(rfp, "%2x%4x", &num, &address);
				printf("Address : %4x\n", address);
				for(count = 0; count < (num - 3); count++)
				{
					fscanf(rfp, "%2x", &data);
					fwrite(&data, 1, 1, wfp);
				}
			}
		}
		c = fgetc(rfp);
	}

	if (rfp) {
		fclose(rfp);
	}
	if (wfp) {
		fclose(wfp);
	}
	return 0;
}
