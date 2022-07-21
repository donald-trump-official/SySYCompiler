/*
clang -emit-llvm -S test.c -o test.ll -O0
*/
const float f=0.1;
void func(int a){
	return;
}
int main(){
	int a[2][2] = {2,{3,4}};
	int x=-(+1);
	if(1) func(0);
	else{
		func(1);
	}
	while(1){
		func(2);
		break;
		continue;
	}
	int x=a[1];
	return 0;
}