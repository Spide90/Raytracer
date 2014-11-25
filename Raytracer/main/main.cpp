#include<iostream>

void a_cameras();

void a_solids();

void a_indexing();

void a_lighting();

void a_materials();

#define TEST_CAMERA false
#define TEST_SOLID false
#define TEST_INDEX false
#define TEST_LIGHTING false
#define TEST_MATERIAL true

int main(int argc, char* argv[]) {
	if (TEST_CAMERA) {
		std::cout << "starting camera tests\n";
		a_cameras();
		std::cout << "camera tests finished\n";
	}
	if (TEST_SOLID) {
		std::cout << "starting solid tests\n";
		a_solids();
		std::cout << "solid tests finished\n";
	}
	if (TEST_INDEX) {
		std::cout << "starting index tests\n";
		a_indexing();
		std::cout << "index tests finished\n";
	}
	if (TEST_LIGHTING) {
		std::cout << "starting lighting tests\n";
		a_lighting();
		std::cout << "lighting tests finished\n";
	}
	if (TEST_MATERIAL) {
		std::cout << "starting material tests\n";
		a_materials();
		std::cout << "material tests finished\n";
	}
	return 0;
}
