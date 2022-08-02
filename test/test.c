/*
clang -emit-llvm -S test.c -o test.ll -O0
*/
int a[2][2] = {{1,2},{3,4}};
const int x = 0;

int main(){
	const int inner_x = 1;
	return 0;
}