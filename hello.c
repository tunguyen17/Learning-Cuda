#include <iostream> 

__global__ void add( int a, int b, int *c){
	# global qualifier to standard C
	# Alerts the compiler that a function should be compiled to run on a device instead of the host
	*c = a + b;
}

int main( void ) {
	int c;
	int *dev_c;
	
	# cudaMalloc allocate memory on the device
		# first argument: pointer to pointer of the address of the value you want to make
		# second argument: size of the allocation 	

	HANDLE_ERROR( cudaMalloc( (void**)&dev_c, sizeof(int) ) );
	
	add<<1,1>>(2, 7, dev_c);
	
	HANDLE_ERROR( cudaMemcpy( &c,
				  dev_c,
				  sizeof(int),
				  cudaMemcpyDeviceToHost ) );

	printf( "2 + 7 = %d\n", c );
	cudaFree(dev_c);

	return 0;
}	
