#include <zconf.h>
#include <zlib.h>
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>

int main(int argc, char** argv)
{
	if (argc < 2)
		return 0;

	std::ifstream i;
	const char* file_name = argv[1]; 
	i.open(argv[1], std::ios_base::binary);
	i.seekg(0, std::ios_base::end);
	int file_size = i.tellg();
	i.seekg(0, std::ios_base::beg);

	std::vector<char> data_to_compress(file_size);
	i.read(data_to_compress.data(), data_to_compress.size());
	i.close();

	std::vector<Bytef> data_compressed(compressBound(data_to_compress.size()));
	uLongf data_compressed_size = data_compressed.size();
	compress(data_compressed.data(), &data_compressed_size, (const Bytef*)data_to_compress.data(), data_to_compress.size());

	std::ofstream o;
	std::stringstream ss;
	ss << std::string(file_name) << std::string(".compressed");

	o.open(ss.str(), std::ios_base::binary);
	
	o.write((char *)&file_size, sizeof(int));
	o.write((char *)data_compressed.data(), data_compressed_size);
	o.close();

	/*i.open("aj.mesh.compressed", std::ios_base::binary);
	i.seekg(0, std::ios_base::end);
	file_size = i.tellg();
	i.seekg(0, std::ios_base::beg);

	int original_size;
	i.read((char *)&original_size, sizeof(int)); 
	i.close();

	std::vector<Bytef> data_uncompressed(original_size);

	uncompress(data_uncompressed.data(), (uLongf *)&original_size, data_compressed.data(), data_compressed_size);*/

	return 0;
}