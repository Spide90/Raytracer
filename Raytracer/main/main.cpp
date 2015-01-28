#include<iostream>
#include <time.h>

void a_cameras();

void a_solids();

void a_indexing();

void a_lighting();

void a_materials();

void a_textures();

void a_mappers();

void a_instancing();

void a_csg();

void a_distributed();

void a_smooth();

void a_bumpmappers();

void a_volume();

void a_test();

void a_rendComp();

void a_horse();

#define TEST_CAMERA false
#define TEST_SOLID false
#define TEST_INDEX false
#define TEST_LIGHTING false
#define TEST_MATERIAL false
#define TEST_TEXTURES false
#define TEST_MAPPERS false
#define TEST_INSTANCING false
#define TEST_CSG false
#define TEST_DISTRIBUTED false
#define TEST_SMOOTH false
#define TEST_BUMP false
#define TEST_VOLUME false

#define TEST_DEBUG true

#define REND_COMP false
#define TEST_HORSE false

int main(int argc, char* argv[]) {
	if (TEST_CAMERA) {
		unsigned int start = clock() / 1000;
		std::cout << "starting camera tests\n";
		a_cameras();
		unsigned int stop = clock() / 1000;
		std::cout << "camera tests finished in " << ((stop - start) / 1000)
				<< "seconds\n";
	}
	if (TEST_SOLID) {
		unsigned int start = clock() / 1000;
		std::cout << "starting solid tests\n";
		a_solids();
		unsigned int stop = clock() / 1000;
		std::cout << "solid tests finished in " << ((stop - start) / 1000)
				<< "seconds\n";
	}
	if (TEST_INDEX) {
		unsigned int start = clock() / 1000;
		std::cout << "starting index tests\n";
		a_indexing();
		unsigned int stop = clock() / 1000;
		std::cout << "index tests finished in " << ((stop - start) / 1000)
				<< "seconds\n";
	}
	if (TEST_LIGHTING) {
		unsigned int start = clock() / 1000;
		std::cout << "starting lighting tests\n";
		a_lighting();
		unsigned int stop = clock() / 1000;
		std::cout << "lighting tests finished in " << ((stop - start) / 1000)
				<< "seconds\n";
	}
	if (TEST_MATERIAL) {
		unsigned int start = clock() / 1000;
		std::cout << "starting material tests\n";
		a_materials();
		unsigned int stop = clock() / 1000;
		std::cout << "material tests finished in " << ((stop - start) / 1000)
				<< "seconds\n";
	}
	if (TEST_TEXTURES) {
		unsigned int start = clock() / 1000;
		std::cout << "starting textures tests\n";
		a_textures();
		unsigned int stop = clock() / 1000;
		std::cout << "textures tests finished in " << ((stop - start) / 1000)
				<< "seconds\n";
	}
	if (TEST_MAPPERS) {
		unsigned int start = clock() / 1000;
		std::cout << "starting mapper tests\n";
		a_mappers();
		unsigned int stop = clock() / 1000;
		std::cout << "mapper tests finished in " << ((stop - start) / 1000)
				<< "seconds\n";
	}
	if (TEST_INSTANCING) {
		unsigned int start = clock() / 1000;
		std::cout << "starting instancing tests\n";
		a_instancing();
		unsigned int stop = clock() / 1000;
		std::cout << "instancing tests finished in " << ((stop - start) / 1000)
				<< "seconds\n";
	}
	if (TEST_CSG) {
		unsigned int start = clock() / 1000;
		std::cout << "starting csg tests\n";
		a_csg();
		unsigned int stop = clock() / 1000;
		std::cout << "csg tests finished in " << ((stop - start) / 1000)
				<< "seconds\n";
	}
	if (TEST_DISTRIBUTED) {
		unsigned int start = clock() / 1000;
		std::cout << "starting distributed tests\n";
		a_distributed();
		unsigned int stop = clock() / 1000;
		std::cout << "distributed tests finished in " << ((stop - start) / 1000)
				<< "seconds\n";
	}
	if (TEST_SMOOTH) {
		unsigned int start = clock() / 1000;
		std::cout << "starting smoothing tests\n";
		a_smooth();
		unsigned int stop = clock() / 1000;
		std::cout << "smoothing tests finished in " << ((stop - start) / 1000)
				<< "seconds\n";
	}
	if (TEST_BUMP) {
		unsigned int start = clock() / 1000;
		std::cout << "starting bumping tests\n";
		a_bumpmappers();
		unsigned int stop = clock() / 1000;
		std::cout << "bumping tests finished in " << ((stop - start) / 1000)
				<< "seconds\n";
	}
	if (TEST_VOLUME) {
		unsigned int start = clock() / 1000;
		std::cout << "starting volume tests\n";
		a_volume();
		unsigned int stop = clock() / 1000;
		std::cout << "volume tests finished in " << ((stop - start) / 1000)
				<< "seconds\n";
	}
	if (TEST_DEBUG) {
		unsigned int start = clock() / 1000;
		std::cout << "starting rendering competition\n";
		a_test();
		unsigned int stop = clock() / 1000;
		std::cout << "rendering competition finished in "
				<< ((stop - start) / 1000) << "seconds\n";
	}
	if (REND_COMP) {
		unsigned int start = clock() / 1000;
		std::cout << "starting rendering competition\n";
		a_rendComp();
		unsigned int stop = clock() / 1000;
		std::cout << "rendering competition finished in "
				<< ((stop - start) / 1000) << "seconds\n";
	}
	if (TEST_HORSE) {
		unsigned int start = clock() / 1000;
		std::cout << "starting rendering competition\n";
		a_horse();
		unsigned int stop = clock() / 1000;
		std::cout << "rendering competition finished in "
				<< ((stop - start) / 1000) << "seconds\n";
	}
	return 0;
}
